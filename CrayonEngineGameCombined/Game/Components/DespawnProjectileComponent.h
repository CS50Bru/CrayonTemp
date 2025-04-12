#pragma once
#include"ReflectionHelpers.h"
namespace Crayon
{
	class DespawnProjectileComponent
	{
	REGISTER_CLASS(DespawnProjectileComponent)
	public:
		DespawnProjectileComponent() = default;

		DespawnProjectileComponent( double lifespan ) : m_lifespan( lifespan ) {}

		double m_timeSinceSpawn = 0.f;

		EXPOSE_PROPERTY(m_lifespan)
		double m_lifespan = 5.f;

	FINISH_REGISTRATION(DespawnProjectileComponent)
	};



}