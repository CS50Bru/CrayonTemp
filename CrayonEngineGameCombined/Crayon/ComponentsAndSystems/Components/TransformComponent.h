#pragma once
#include"Libraries/glm/glm.hpp"
#include"ReflectionHelpers.h"

using namespace Crayon;
struct TransformComponent
{
	REGISTER_CLASS(TransformComponent)
public:
	TransformComponent( glm::vec2 inLocation=glm::vec2{0.f, 0.f}, glm::vec2 inScale={1.f, 1.f}, double inRotation =0.0) :
	 location(inLocation), 
		scale(inScale),
		rotation(inRotation){}

	EXPOSE_PROPERTY(location)
	glm::vec2 location;

	EXPOSE_PROPERTY(scale)
	glm::vec2 scale;

	EXPOSE_PROPERTY(rotation)
	double rotation;
	
	FINISH_REGISTRATION(TransformComponent)
};

