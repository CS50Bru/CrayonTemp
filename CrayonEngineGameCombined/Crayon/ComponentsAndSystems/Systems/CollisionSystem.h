#pragma once
#include"ECS.h"
#include"BoxCollider.h"
#include"TransformComponent.h"
#include"CollisionEvent.h"
//ToDo: remove this
#include"Game/Events/ProjectileHitEvent.h"

namespace Crayon
{
	class CollisionSystem : public System
	{
	public:
		CollisionSystem()
		{
			requireComponent<BoxCollider>();
			requireComponent<TransformComponent>();
		}

		void update( double deltaTime ) override;

		std::vector<Rect> m_colliderRects;

		void generateCollisionRects();
		void processCollisionEvents();
		void clearCollisionEvents();


		const std::vector<Rect>& getRects() const;

		std::vector<CollisionEvent> m_collisionEvents;
		std::vector<ProjectileHitEvent> m_projectileHitEvents;

		std::vector<ProjectileHitEvent>& getProjectileHitEvents() { return m_projectileHitEvents; }
	};

}