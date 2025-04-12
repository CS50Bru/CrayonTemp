#pragma once
#include"Rect.h"
#include"ReflectionHelpers.h"
#include"Game/Enums/CollisionType.h"
namespace Crayon
{
	class BoxCollider
	{
		REGISTER_CLASS(BoxCollider)
	public:
		BoxCollider( glm::vec2 offset = {}, glm::vec2 extent = {} ):
			offset(offset), extent(extent)  
		{
			std::string projectileName = "Projectile";
			collisionType={ projectileName };
		}


		EXPOSE_PROPERTY(offset)
		glm::vec2 offset{};

		EXPOSE_PROPERTY(extent)
		glm::vec2 extent{};

		CollisionType collisionType;

		

		
		FINISH_REGISTRATION(BoxCollider)
	};
}