#pragma once
#include"ECS.h"

#include"TransformComponent.h"
#include"RigidBodyComponent.h"
#include"LocomotionComponent.h"
#include"InvaderMovementComponent.h"

namespace Crayon
{
	class InvaderSystem: public System
	{
	public:
		InvaderSystem()
		{
			requireComponent<TransformComponent>();
			requireComponent<RigidBodyComponent>();
			requireComponent<LocomotionComponent>();
			requireComponent<InvaderMovementComponent>();
		}

		void updateInvaderMovement( double deltaTime, float invaderLeftBoundary, float invaderRightboundary ) 
		{
			for ( Entity entity : m_entityIds )
			{
				RigidBodyComponent& rigidBody = entity.getComponent<RigidBodyComponent>();
				TransformComponent& transform = entity.getComponent<TransformComponent>();
				LocomotionComponent& locomotion = entity.getComponent<LocomotionComponent>();

				if ( transform.location.x <= invaderLeftBoundary || transform.location.x >= invaderRightboundary )
				{
					rigidBody.velocity.x *= -1;
					transform.location.y += 20.f;
				}

			}
		}

	};



}