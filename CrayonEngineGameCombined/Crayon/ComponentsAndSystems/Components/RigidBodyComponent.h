#pragma once
#include"Libraries/glm/glm.hpp"
#include"ReflectionHelpers.h"

using namespace Crayon;
struct RigidBodyComponent
{
REGISTER_CLASS(RigidBodyComponent)
public:
	RigidBodyComponent( glm::vec2 inVelocity = glm::vec2{}, glm::vec2 inAcceleration = glm::vec2{} )
		:velocity(inVelocity), acceleration(inAcceleration){}

	EXPOSE_PROPERTY(velocity)
		glm::vec2 velocity{};

	EXPOSE_PROPERTY( acceleration )
	glm::vec2 acceleration{};

	EXPOSE_PROPERTY( netForce )
	glm::vec2 netForce{};

	EXPOSE_PROPERTY(mass)
	float mass = 1.f;

	FINISH_REGISTRATION(RigidBodyComponent)
};

