#pragma once

#include"ReflectionHelpers.h"
namespace Crayon
{

	struct LocomotionComponent
	{
	REGISTER_CLASS(LocomotionComponent)

	public:
		LocomotionComponent(): movementSpeed(100.f, 100.f), deceleration(4.f*movementSpeed)
		{
		}

		EXPOSE_PROPERTY( movementSpeed )
			glm::vec2 movementSpeed;

		EXPOSE_PROPERTY( deceleration )
			glm::vec2 deceleration;
		
			
		FINISH_REGISTRATION(LocomotionComponent)
	};

}