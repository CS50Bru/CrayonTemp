#include "SoundComponent.h"
#include "Audio/AudioPlayer.h"

Crayon::SoundComponent::SoundComponent( IXAudio2SourceVoice* pNewSource, float inVolume ):
	pSourceVoice(pNewSource), volume(inVolume) 
{
	if ( pSourceVoice )
	{
		pSourceVoice->SetVolume( volume );
	}
}

Crayon::SoundComponent& Crayon::SoundComponent::operator=( SoundComponent&& other ) noexcept
{
		volume = other.volume;

		if ( pSourceVoice )
		{
			pSourceVoice->DestroyVoice();
		}
		pSourceVoice = other.pSourceVoice;
		other.pSourceVoice = nullptr;
		return *this;
}


Crayon::SoundComponent::SoundComponent( SoundComponent&& other ) noexcept
	:
	volume( other.volume )
{
	pSourceVoice = other.pSourceVoice;
	other.pSourceVoice = nullptr;
}


Crayon::SoundComponent::~SoundComponent()
{
	if ( pSourceVoice )
	{
		pSourceVoice->Stop();
		pSourceVoice->DestroyVoice();
		pSourceVoice = nullptr;
	}
}

