#pragma once
#include <cstdint>
#include"ReflectionHelpers.h"

namespace Crayon
{
	class AnimationComponent
	{
		REGISTER_CLASS(AnimationComponent)
	public:
		//how many rows and columns there are in your animation image: for example, if you have 2 frames going horizontally, put in 1 row and 2 columns
		EXPOSE_PROPERTY(columns)
		uint32_t columns = 1;
		EXPOSE_PROPERTY(rows)
		uint32_t rows = 1;

		EXPOSE_PROPERTY(frameDuration)
		double frameDuration = 1.f;
		double timepointInAnimation = 0.0;

		EXPOSE_PROPERTY(shouldLoop)
		bool shouldLoop = true;

		FINISH_REGISTRATION(AnimationComponent)
	};
}
