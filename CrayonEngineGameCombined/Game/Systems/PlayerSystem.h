#pragma once
#include"Core.h"
#include"ECS.h"
#include"LocomotionComponent.h"
#include"InputComponent.h"
#include"WindowAndInput/InputManager.h"
#include"RigidBodyComponent.h"
#include"BoxCollider.h"
#include"DespawnProjectileComponent.h"
#include"TransformComponent.h"
#include"SpriteComponent.h"
#include"ProjectileSpawningComponent.h"

namespace Crayon
{

	class PlayerSystem : public System
	{
	private:
		bool m_fireKeyReleased = true;
	public:
		PlayerSystem()
		{
			requireComponent<LocomotionComponent>();
			requireComponent<RigidBodyComponent>();
			requireComponent<InputComponent>();
			requireComponent<ProjectileSpawningComponent>();
		}

		void updatePlayerMovement( double deltaTime, const InputManager& inputManager, Registry& registry,  Renderer& renderer, AudioPlayer& audioPlayer )
		{
			
			if ( inputManager.getKeyIsDown( InputName::Space ) && m_fireKeyReleased )
			{
				m_fireKeyReleased = false;
				for ( Entity entity : m_entityIds )
				{
					const TransformComponent& transform = entity.getComponent<TransformComponent>();
					Entity laserEntity = registry.queueEntityForCreation();
					laserEntity.addComponent<TransformComponent>(transform.location + glm::vec2(0.f, -30.f));
					laserEntity.addComponent<SpriteComponent>( renderer.addTextureIfNew("Textures/laser.png"));
					glm::vec2 laserTextureDimensions = renderer.getTextureHandle( renderer.addTextureIfNew( "Textures/laser.png" ) ).imageDimensions;
					laserEntity.addComponent<RigidBodyComponent>( glm::vec2( 0.f, -300.f ) );
					laserEntity.addComponent<BoxCollider>( glm::vec2{}, laserTextureDimensions );
					double projectileLifespan = 2.0;
					laserEntity.addComponent<DespawnProjectileComponent>(projectileLifespan);

					const ProjectileSpawningComponent& spawnComponent = entity.getComponent<ProjectileSpawningComponent>();

					audioPlayer.playOneshot( spawnComponent.soundAsset.assetPath );

				}
			}
			else if (! inputManager.getKeyIsDown(InputName::Space) )
			{
				m_fireKeyReleased = true;
			}

			glm::vec2 movementDirection {0.f, 0.f};
			bool inputReceived = false;

			if ( inputManager.getKeyIsDown( InputName::A ) )
			{
				movementDirection.x += -1.f;
				inputReceived = true;
			}
			if ( inputManager.getKeyIsDown( InputName::D ) )
			{
				movementDirection.x += 1.f;
				inputReceived = true;

			}
			if ( inputManager.getKeyIsDown( InputName::W ) )
			{
				movementDirection.y += -1.f;
				inputReceived = true;

			}
			if ( inputManager.getKeyIsDown( InputName::S ) )
			{
				movementDirection.y += 1.f;
				inputReceived = true;

			}

			if ( inputReceived )
			{
				for ( Entity entity : m_entityIds )
				{
					const LocomotionComponent& locomotion = entity.getComponent<LocomotionComponent>();
					RigidBodyComponent& rigidBody = entity.getComponent<RigidBodyComponent>();

					rigidBody.velocity = rigidBody.velocity + (static_cast<float>(deltaTime) * movementDirection * locomotion.movementSpeed);
				}
			}

			else
			{
				for ( Entity entity : m_entityIds )
				{
					//for decceleration, I basically shove everything into the positive part of the x/y (the top-right), subtract the decelaration from the velocity and clamp to zero, then re-add the original polarity

					const LocomotionComponent& locomotion = entity.getComponent<LocomotionComponent>();
					RigidBodyComponent& rigidBody = entity.getComponent<RigidBodyComponent>();

					const glm::vec2 absoluteDeceleration = glm::abs( locomotion.deceleration ) * static_cast<float>(deltaTime);
					const glm::vec2 absoluteVelocity = glm::abs( rigidBody.velocity );
					const glm::vec2 absoluteEndpoint = absoluteVelocity - absoluteDeceleration;
					const glm::vec2 clampedAbsoluteEndpoint = glm::max( absoluteEndpoint, glm::vec2( 0.f ) );

					rigidBody.velocity = glm::sign( rigidBody.velocity ) * clampedAbsoluteEndpoint;

				}
			}

		}

	};



}