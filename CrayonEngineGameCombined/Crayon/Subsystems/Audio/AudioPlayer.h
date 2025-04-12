#pragma once
#include<xaudio2.h>
#include<mutex>
#include<stdint.h>
#include<unordered_map>
#include<string>
#include<optional>

#include"AudioHandle.h"
#include"Core.h"
namespace Crayon
{
	// XAudio2 architecture overview:
	// - Engine manages audio playback and creates mastering/source voices
	// - Buffers (XAUDIO2_BUFFER) store audio data and can be reused across voices
	// - Source voices are tied to specific audio formats and cannot be reused for different formats
	// - COM objects are managed via pointers for proper reference counting over in COM land: don't try to create local COM objects or pass them by value or anything like that!

	// AudioPlayer responsibilities:
	// - Initializes XAudio2 engine and mastering voice
	// - Manages audio buffer loading and caching
	// - Handles source voice creation
	// - Source voices are owned by SoundComponents for lifecycle management

	// Threading model:
	// Uses double-buffering approach for one-shot sounds:
	// - New source voices are collected in a temporary buffer
	// - Periodically copied to main buffer while preserving playing voices

	//SourceVoiceBuffer: just a wrapper around a vector of source voices. Lets you add to the vector, copy the vector over to another vector (which is v. fast because these are just pointers), and destroy the voices safely.
	class SourceVoiceBuffer
	{
	private:
		std::vector<IXAudio2SourceVoice*> m_newSourceVoices;
		std::mutex m_newVoiceAccessMutex;
		std::thread m_cleanupThread;

	public:
		void copyNewVoicesToOld( std::vector<IXAudio2SourceVoice*>& oldVoices );
		void addSourceVoice( IXAudio2SourceVoice* pSourceVoice );

		void cleanupVoices();
		~SourceVoiceBuffer() = default;;
	};



	class AudioPlayer
	{
	private:
		SourceVoiceBuffer m_sourceVoiceBuffer;
		IXAudio2* m_pAudioEngine;
		IXAudio2MasteringVoice* m_pMasteringVoice;

		std::unordered_map<std::string, AudioHandle> m_audioHandleMap;

		std::thread m_oneshotCleanupThread;

		static bool areWaveFormatsEqual( const WAVEFORMATEX& format1, const WAVEFORMATEX& format2 );

		std::optional<WAVEFORMATEX> getWaveFormat( std::ifstream& file, uint32_t fileSize ) const;
		uint32_t getFileSize( std::ifstream& file ) const;
		bool checkAndReuseBuffer( const char* fileName, IXAudio2SourceVoice*& pSourceVoice );
		void assertIsRIFF( std::ifstream& file ) const;
		void assertIsWave( std::ifstream& file ) const;

		std::atomic<bool> m_keepCheckingOneshots = true;

	public:

		AudioPlayer();
		~AudioPlayer();

		IXAudio2SourceVoice* createSourceVoice( const char* fileName, uint32_t loopCount = 0, IXAudio2VoiceCallback* pCallback = nullptr );
		void setMasterVolume( float volume );


		void playOneshot( const std::string& fileName );

		void oneshotCleanupLoop();

	};

}