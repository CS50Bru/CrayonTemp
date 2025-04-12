//NB the SpriteComponent doesn't contain all the info you need to make up a sprite: for that, you need a SpriteComponent
//and a TransformComponent.

//The SpriteComponent's job is just to tell you what texture to draw, and what part of it to draw.

#pragma once
#include"Libraries/glm/glm.hpp"
#include"Rect.h"
#include"ReflectionHelpers.h"
#include"TextureIdentifier.h"
namespace Crayon
{
	//contains id of texture, the draw index, and a uvRect specifying what section of the texture to draw.
	struct SpriteComponent
	{
		REGISTER_CLASS(SpriteComponent)

		//basically just a wrapper around a size_t texture index
		EXPOSE_PROPERTY( textureIndex )
		TextureIdentifier textureIndex;
		
		
		EXPOSE_PROPERTY(drawIndex, CUSTOM_DISPLAY( []( void* ) { ImGui::Text( "ROFL" ); } ) )
		size_t drawIndex=0;

		
		EXPOSE_PROPERTY(uvRect)
		Rect uvRect;

		SpriteComponent() :
			 uvRect(), drawIndex(0) {}

		SpriteComponent( TextureIdentifier inTextureIndex, Rect inUvRect={}, uint32_t inDrawIndex=0) :
			textureIndex( inTextureIndex ), uvRect( inUvRect ), drawIndex(inDrawIndex) {}


	FINISH_REGISTRATION(SpriteComponent)
	};
}

