#pragma once
#include"SerializableEnum.h"

namespace Crayon
{
	class CollisionType : public SerializableEnum
	{
	public:
		INIT_SERIALIZABLE_ENUM(CollisionType)
		ADD_ENUM_MEMBER(Default)
		ADD_ENUM_MEMBER(Projectile)
	};

}
