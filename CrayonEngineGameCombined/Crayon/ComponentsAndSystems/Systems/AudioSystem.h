#pragma once
#include"ECS.h"
#include"SoundComponent.h"

namespace Crayon
{
	//currently very, very simple: just asks the SoundComponents with 'wantPlay' set to true to play themselves each frame. Doesn't manage any data or anything.
	class AudioSystem : public System
	{
		class AudioPlayer* m_pAudioPlayer;

	public:
		AudioSystem() :
			m_pAudioPlayer( nullptr )
		{
			requireComponent<SoundComponent>();
		}
		
		void update( double deltaTime ) override;


	};

}
