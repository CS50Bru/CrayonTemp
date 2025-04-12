#pragma once
#include"ECS.h"
#include"Core.h"
#include"Libraries/glm/glm.hpp"


//to do: currently has very little to do with physics and is just used to make things orbit the player's cursor as an experiment
class PhysicsSystem: public System
{
private:

public:
	PhysicsSystem();

	void updateAndFollowCursor( double deltaTime, glm::vec2 worldPos );

};