#include"AudioSystem.h"
#include"Audio/AudioPlayer.h"

void Crayon::AudioSystem::update( double deltaTime )
{
	for ( Entity entity : m_entityIds )
	{
		SoundComponent& soundComponent = entity.getComponent<SoundComponent>();
		if ( soundComponent.wantPlay )
		{
			soundComponent.wantPlay = false;
			soundComponent.pSourceVoice->SetVolume( soundComponent.volume );
			soundComponent.volumeChanged = false;
			soundComponent.pSourceVoice->Start();
		}

		if ( soundComponent.volumeChanged )
		{
			soundComponent.pSourceVoice->SetVolume( soundComponent.volume );
		}
	}
}

