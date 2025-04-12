#include "PhysicsSystem.h"
#include"TransformComponent.h"
#include"RigidBodyComponent.h"
#include"Logger.h"
PhysicsSystem::PhysicsSystem()
{
	requireComponent<TransformComponent>();
	requireComponent<RigidBodyComponent>();
}

void PhysicsSystem::updateAndFollowCursor( double deltaTime, glm::vec2 worldPos )
{
	/*Logger::get().log(worldPos.x);
	Logger::get().log( worldPos.y );*/

	for ( Entity entity : m_entityIds )
	{

		glm::vec2& location = entity.getComponent<TransformComponent>().location;
		glm::vec2& acceleration = entity.getComponent<RigidBodyComponent>().acceleration;
		glm::vec2& velocity = entity.getComponent<RigidBodyComponent>().velocity;
		float mass = std::fmax( entity.getComponent<RigidBodyComponent>().mass, 1.f );
		glm::vec2& netForce = entity.getComponent<RigidBodyComponent>().netForce;
		
		
		//apply cursor "gravity" to net force
		constexpr float gravityStrength = 13.f;
		glm::vec2 cursorPull= glm::normalize( worldPos - location ) * gravityStrength * mass;

		netForce += cursorPull;
		

		//turn net force into acceleration
		acceleration = netForce / mass;
		//reset net force, now that it's been converted to acceleration
		netForce = { 0.f,0.f };

		velocity += acceleration * static_cast<float>(deltaTime);
		location += velocity * static_cast<float>(deltaTime);

	}
}
