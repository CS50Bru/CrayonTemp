#pragma once

#include"ECS.h"
#include"DespawnProjectileComponent.h"
#include"Game/Events/ProjectileHitEvent.h"
namespace Crayon
{
	class DespawnProjectileSystem : public System
	{
	public:

		DespawnProjectileSystem()
		{
			requireComponent<DespawnProjectileComponent>();
		}


		void update( double deltaTime ) override
		{
			for ( Entity entity : m_entityIds )
			{
				DespawnProjectileComponent& projectileComponent = entity.getComponent<DespawnProjectileComponent>();

				projectileComponent.m_timeSinceSpawn += deltaTime;

				if ( projectileComponent.m_timeSinceSpawn >= projectileComponent.m_lifespan )
				{
					entity.kill();
				}

			}
		}

		void processProjectileCollisionEvents( std::vector<ProjectileHitEvent>& projectileHitEvents )
		{
			Registry& registry = Registry::getRegistry();
			for ( auto& projectileHitEvent : projectileHitEvents )
			{
				if ( registry.entityHasComponent<DespawnProjectileComponent>( projectileHitEvent.m_projectileId ) )
				{
					registry.queueEntityForKill( projectileHitEvent.m_projectileId );
				}
				projectileHitEvent.m_handled = true;
			}
		}

	};



}