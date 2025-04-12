#pragma once
#include"Audio/SoundAsset.h"
#include"ReflectionHelpers.h"
namespace Crayon
{
	struct ProjectileSpawningComponent
	{
	REGISTER_CLASS( ProjectileSpawningComponent )

	EXPOSE_PROPERTY(soundAsset)
	SoundAsset soundAsset;


	FINISH_REGISTRATION(ProjectileSpawningComponent)
	};



}