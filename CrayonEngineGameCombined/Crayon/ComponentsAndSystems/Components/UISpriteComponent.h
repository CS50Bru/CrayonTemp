#pragma once
#include"SpriteComponent.h"

namespace Crayon
{
	class UISpriteComponent : public SpriteComponent
	{
	public: UISpriteComponent():SpriteComponent(){}

		  UISpriteComponent( uint32_t inTextureIndex, Rect inUvRect = {}, uint32_t inDrawIndex = 0 ) :
			  SpriteComponent( inTextureIndex, inUvRect, inDrawIndex ){}
	};
}
