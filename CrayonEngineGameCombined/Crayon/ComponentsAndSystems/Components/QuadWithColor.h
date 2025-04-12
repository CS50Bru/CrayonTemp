#pragma once
#include"Core/CoreTypes/Rect.h"
#include"ECS.h"

namespace Crayon
{
	class QuadWithColor
	{
	public:
		QuadWithColor() = default;

		QuadWithColor(glm::vec2 origin, glm::vec2 extent):
			rect(origin, extent){}

		Rect rect =Rect(glm::vec2(0.f,0.f), glm::vec2(100.f, 100.f));
	};




}