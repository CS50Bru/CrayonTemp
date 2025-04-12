#pragma once
#include"ECS.h"

//animation components keep track of a time point, i.e. how far into their animation they are.
//The animation system moves that timepoint along, and sees what frame of the animation it's now on, working that out by how long each frame is held and how many rows and columns the texture is divided into. If you go off the end, it loops it back around or just stops updating if 'shouldLoop' is false.

//It's currently a very simple system that doesn't hold any info apart from its list of Entities.
namespace Crayon
{
	class AnimationSystem : public System
	{
	public:
		AnimationSystem();

		void update( double deltaTime ) override;
	};
}