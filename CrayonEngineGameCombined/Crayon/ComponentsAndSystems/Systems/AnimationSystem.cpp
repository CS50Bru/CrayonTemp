#include"AnimationSystem.h"
#include"AnimationComponent.h"
#include"SpriteComponent.h"
#include"Logger.h"
namespace Crayon
{

	AnimationSystem::AnimationSystem()
	{
		requireComponent<SpriteComponent>();
		requireComponent<AnimationComponent>();
	}

	void AnimationSystem::update( double deltaTime )
	{
		for ( Entity entity : m_entityIds )
		{
			//work out what frame you're on
			AnimationComponent& animComp = entity.getComponent<AnimationComponent>();

			//if you let this become 0.0, which is easy to do in the Editor, then you can get undefined behaviour, and if the animation component's time point becomes NEGATIVE as a result, then even changing the frameDuration won't fix it and that animation component is effectively 'dead'
			animComp.frameDuration = animComp.frameDuration == 0.0 ? 1.0 : animComp.frameDuration;
			
			const double endOfAnimationTime = animComp.rows*animComp.columns * animComp.frameDuration;
			
			//if you've reached the end of the animation and you're not supposed to loop, move onto the next entity
			const double rawTimeElapsed = animComp.timepointInAnimation + deltaTime;
			if ( rawTimeElapsed >= endOfAnimationTime && !animComp.shouldLoop )
			{
				continue;
			}

			//otherwise, finish working out the frame number.
			animComp.timepointInAnimation = fmod( rawTimeElapsed, endOfAnimationTime );

			uint32_t frameNumber = static_cast<uint32_t>( animComp.timepointInAnimation / animComp.frameDuration);


			//get the UV rectangle for that frame in our SpriteSheet
			const uint32_t column = frameNumber % animComp.columns;
			const uint32_t row = frameNumber / animComp.columns;

			float xUVStart = static_cast<float> (column) / animComp.columns;
			float xUVOffset = 1.f / animComp.columns;


			float yUVStart = static_cast<float>(row) / animComp.rows;
			float yUVOffset = 1.f / animComp.rows;


			//set the appropriate UV rectagnle on the sprite component
			SpriteComponent& spriteComponent = entity.getComponent<SpriteComponent>();
			spriteComponent.uvRect.origin = glm::vec2( xUVStart, yUVStart );
			spriteComponent.uvRect.extent = glm::vec2( xUVOffset, yUVOffset );
		}
	}

}