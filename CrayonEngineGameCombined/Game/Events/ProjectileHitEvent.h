#pragma once
#include"Event.h"

using namespace Crayon;
class ProjectileHitEvent: public Event
{
public:
	ProjectileHitEvent(size_t inProjectileId, size_t inStruckEntityId): m_projectileId(inProjectileId), m_struckEntityId(inStruckEntityId){}

	size_t m_projectileId;
	size_t m_struckEntityId;
};