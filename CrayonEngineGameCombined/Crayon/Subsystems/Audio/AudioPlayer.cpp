
#include<fstream>
#include<iostream>
#include<stdint.h>
#include<vector>
#include<unordered_set>

#include"AudioPlayer.h"
#include"Core.h"
#include"SoundComponent.h"

namespace Crayon
{

	AudioPlayer::AudioPlayer() :
		m_pAudioEngine( nullptr )
		, m_pMasteringVoice( nullptr )
	{
		//initialize COM
		CoInitializeEx( nullptr, COINIT_MULTITHREADED );
		//create an audio engine
		XAudio2Create( &m_pAudioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR );

#ifdef DEBUG
		XAUDIO2_DEBUG_CONFIGURATION debugConfig = {};
		debugConfig.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
		debugConfig.BreakMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
		debugConfig.LogFileline = true;
		m_pAudioEngine->SetDebugConfiguration( &debugConfig, NULL );
#endif // DEBUG
		m_pAudioEngine->CreateMasteringVoice( &m_pMasteringVoice );

	  m_oneshotCleanupThread=std::thread(&AudioPlayer::oneshotCleanupLoop, this);
	}


	bool AudioPlayer::checkAndReuseBuffer( const char* fileName, IXAudio2SourceVoice*& pSourceVoice )
	{
		if ( const auto& it = m_audioHandleMap.find( fileName ); it != m_audioHandleMap.end() )
		{
			// Buffer exists, so create a source voice and submit the buffer
			m_pAudioEngine->CreateSourceVoice( &pSourceVoice, &it->second.waveFormat );
			pSourceVoice->SubmitSourceBuffer( &it->second.buffer );
			return true;
		}
		return false;
	}



	IXAudio2SourceVoice* AudioPlayer::createSourceVoice( const char* fileName,  uint32_t loopCount, IXAudio2VoiceCallback* pCallback )
	{
		IXAudio2SourceVoice* pSourceVoice = nullptr;

		//if we've already got a buffer for that audio data, use that to create the source voice
		checkAndReuseBuffer( fileName, pSourceVoice );

		if ( pSourceVoice )
		{
			return pSourceVoice;
		}
		
		//otherwise, we need to check that the audio file is a .wav file
		AudioHandle newHandle{};

		std::ifstream file( fileName, std::ios_base::binary );
		assertIsRIFF( file );

		uint32_t fileSize = getFileSize(file);

		assertIsWave( file );

		auto waveFormat = getWaveFormat( file, fileSize );
		CRAYON_ASSERT( waveFormat.has_value() );
		newHandle.waveFormat = waveFormat.value();
		
		//now that we know the format (not the file format, but the actual WAVEFORMATEX) we can create our source voice
		//(source voices are locked into playing sounds of a certain sample rate etc.)
		if ( pCallback )
		{
			if ( FAILED( m_pAudioEngine->CreateSourceVoice( &pSourceVoice, &newHandle.waveFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, pCallback ) ))
			{
				CRAYON_ASSERT( false );
			}
		}
		else
		{
			m_pAudioEngine->CreateSourceVoice( &pSourceVoice, &newHandle.waveFormat);
		}


		//Now we can load in the actual audio data and use that to create a buffer
		//go back up to the start of the first sub-chunk, and start jumping through the subchunks again,
		//this time looking for the sound data
		file.seekg( 3 * sizeof( DWORD ) );

		bool soundDataFound = false;
		while ( !soundDataFound && file.tellg() < fileSize )
		{
			DWORD subchunkLabel;
			file.read( reinterpret_cast<char*>(&subchunkLabel), sizeof( DWORD ) );
			DWORD subchunkSize;
			file.read( reinterpret_cast<char*>(&subchunkSize), sizeof( DWORD ) );
			if ( subchunkLabel == 'atad' )
			{
				soundDataFound = true;
				void* pData = malloc( subchunkSize );
				file.read( (char*)pData, subchunkSize );
				newHandle.buffer.AudioBytes = subchunkSize;
				newHandle.buffer.pAudioData = (BYTE*)pData;
				newHandle.buffer.Flags = XAUDIO2_END_OF_STREAM;
				newHandle.buffer.LoopCount = loopCount;
			}
			else
			{
				uint32_t currentPos = file.tellg();
				file.seekg( currentPos + subchunkSize );
			}
		}

		m_audioHandleMap[fileName] = newHandle;

		CRAYON_ASSERT( soundDataFound );

		pSourceVoice->SubmitSourceBuffer( &newHandle.buffer );
		return pSourceVoice;
	}

	void AudioPlayer::setMasterVolume( float volume )
	{
		m_pMasteringVoice->SetVolume( volume );
	}

	void AudioPlayer::playOneshot( const std::string& fileName )
	{
		IXAudio2SourceVoice*  pSourceVoice = createSourceVoice( fileName.c_str(), 0);
		if ( pSourceVoice )
		{
			m_sourceVoiceBuffer.addSourceVoice( pSourceVoice );
			pSourceVoice->Start( 0 );
		}
	}

	void AudioPlayer::oneshotCleanupLoop()
	{
		std::vector<IXAudio2SourceVoice*> oneshotVoices;

		while ( m_keepCheckingOneshots )
		{
			m_sourceVoiceBuffer.copyNewVoicesToOld(oneshotVoices);

			auto it = oneshotVoices.begin();
			while ( it != oneshotVoices.end() )
			{
				IXAudio2SourceVoice* pVoice = *it;
				XAUDIO2_VOICE_STATE voiceState;
				// this is where we'll clean up any oneshots that are done
				pVoice->GetState( &voiceState );

				if ( voiceState.BuffersQueued == 0 )
				{
					pVoice->Stop();
					pVoice->DestroyVoice();
					//.erase() returns an iterator that points to the element after the one erased
					it= oneshotVoices.erase( it );
				}
				else
				{
					++it;
				}
			}
			std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
		}

	}


	bool AudioPlayer::areWaveFormatsEqual( const WAVEFORMATEX& format1, const WAVEFORMATEX& format2 )
	{
		return format1.wFormatTag == format2.wFormatTag &&
			format1.nChannels == format2.nChannels &&
			format1.nSamplesPerSec == format2.nSamplesPerSec &&
			format1.nAvgBytesPerSec == format2.nAvgBytesPerSec &&
			format1.nBlockAlign == format2.nBlockAlign &&
			format1.wBitsPerSample == format2.wBitsPerSample;
	}

	void AudioPlayer::assertIsRIFF( std::ifstream& file ) const
	{
		constexpr DWORD riffLabel = 'FFIR';
		DWORD label;
		file.read( reinterpret_cast<char*>(&label), sizeof( DWORD ) );
		CRAYON_ASSERT( label == riffLabel );
	}

	void AudioPlayer::assertIsWave( std::ifstream& file ) const
	{
		DWORD fileFormatLabel;
		file.read( reinterpret_cast<char*>(&fileFormatLabel), sizeof( DWORD ) );
		CRAYON_ASSERT( fileFormatLabel == 'EVAW' );
	}

	std::optional<WAVEFORMATEX> AudioPlayer::getWaveFormat( std::ifstream& file, uint32_t fileSize ) const
	{
		bool formatSubchunkFound = false;
		WAVEFORMATEX waveFormat;

		while ( !formatSubchunkFound && file.tellg() < fileSize )
		{
			//read in the subchunk's label and size
			DWORD subchunkLabel;
			file.read( reinterpret_cast<char*>(&subchunkLabel), sizeof( DWORD ) );
			DWORD subchunkSize;
			file.read( reinterpret_cast<char*>(&subchunkSize), sizeof( DWORD ) );
			//if the label is 'fmt', then read in the subchunk and use it to creat a source voice
			if ( subchunkLabel == ' tmf' )
			{
				formatSubchunkFound = true;
				file.read( (char*)&waveFormat, sizeof( waveFormat ) );
				return waveFormat;
			}
			//otherwise, skip ahead by the size of the chunk
			else
			{
				uint32_t currentPos = file.tellg();
				file.seekg( currentPos + subchunkSize );
				return std::nullopt;
			}
		}
		return std::nullopt;
		CRAYON_ASSERT( formatSubchunkFound );
	}

	uint32_t AudioPlayer::getFileSize( std::ifstream& file ) const
	{
		uint32_t fileSize = 0;
		file.read( (char*)(&fileSize), sizeof( DWORD ) );
		return fileSize;
	}




	//make sure to stop all of your Sound objects before destroying the AudioPlayer
	AudioPlayer::~AudioPlayer()
	{
		m_keepCheckingOneshots = false;
		m_oneshotCleanupThread.join();
		m_sourceVoiceBuffer.cleanupVoices();

		for ( auto& audioHandle : m_audioHandleMap )
		{
			free( (void*)audioHandle.second.buffer.pAudioData );
		}
		m_audioHandleMap.clear();

		m_pAudioEngine->StopEngine();


		m_pMasteringVoice->DestroyVoice();
		m_pMasteringVoice = nullptr;

		m_pAudioEngine->Release();
		m_pAudioEngine = nullptr;
	}
	inline void SourceVoiceBuffer::copyNewVoicesToOld( std::vector<IXAudio2SourceVoice*>& oldVoices )
	{
		std::lock_guard<std::mutex>lock( m_newVoiceAccessMutex );
		for ( auto& newSourceVoice : m_newSourceVoices )
		{
			oldVoices.push_back( newSourceVoice );
		}
		m_newSourceVoices.clear();
	}
	inline void SourceVoiceBuffer::addSourceVoice( IXAudio2SourceVoice* pSourceVoice )
	{
		std::lock_guard<std::mutex>lock( m_newVoiceAccessMutex );
		m_newSourceVoices.push_back( pSourceVoice );
	}
	void SourceVoiceBuffer::cleanupVoices()
	{
		std::lock_guard<std::mutex>lock( m_newVoiceAccessMutex );

		for ( auto& voice : m_newSourceVoices )
		{
			voice->Stop();
			voice->DestroyVoice();
		}
	}
}

