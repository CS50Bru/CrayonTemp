#pragma once
#include"Event.h"

namespace Crayon
{
	class CollisionEvent : public Event
	{
	public:
		CollisionEvent( size_t inA, size_t inB, CollisionType inCollisionTypeA = {},
			CollisionType inCollisionTypeB = {} ) :
			a( inA ), b( inB ), collisionTypeA( inCollisionTypeA ), collisionTypeB( inCollisionTypeB )
		{
		}

		size_t a = 0;
		CollisionType collisionTypeA;
		size_t b = 0;
		CollisionType collisionTypeB;
	};
}
