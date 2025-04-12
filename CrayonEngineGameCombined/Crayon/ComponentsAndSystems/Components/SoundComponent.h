#pragma once

//currently doesn't store a WAVEFORMATEX structure, because with our current setup we don't submit
//other buffers to an existing source voice (so we don't need to check that the formats match)

#include<xaudio2.h>
#include<stdlib.h>

#include"ReflectionHelpers.h"

namespace Crayon
{

	//currently basically just a wrapper around a source voice pointer, with some extra volume-related info.
	struct SoundComponent
	{
		bool wantPlay =false;
		bool volumeChanged = true;
		float volume =1.f;
		IXAudio2SourceVoice* pSourceVoice = nullptr;

		
		
		SoundComponent() = default;
		SoundComponent( IXAudio2SourceVoice* pNewSource, float inVolume );
		SoundComponent& operator=( SoundComponent&& other ) noexcept;
		SoundComponent( SoundComponent&& other ) noexcept;
		
		SoundComponent( const SoundComponent& other ) = delete;
		SoundComponent& operator=( SoundComponent& other ) = delete;
		
		virtual ~SoundComponent();

	};
}