#pragma once

//ties together all of the information that you need to hand over to the GPU for it to be able to draw
//a textured quad 
//(NB because this is going to be handed over to the GPU it all needs to be properly aligned)

#include"Libraries/glm/glm.hpp"
#include"Libraries/glm/gtc/matrix_transform.hpp"

#include "Rect.h"

namespace Crayon
{

	inline static Rect defaultUVRect{ glm::vec2( 0.0,0.0 ), glm::vec2( 1.0,1.0 ) };

	struct alignas(16) Sprite
	{
		friend class Renderer;

	public:
		Sprite() :
			position{}
			, uvRect()
			, scale{ 1.f,1.f }
			, textureIndex( 0 )
			, rotation( 0.f )
		{
			uvRect.origin = { 0.0, 0.0 };
			uvRect.extent = { 1.0, 1.0 };
		}

		Sprite( glm::vec2 inposition, glm::float32 inRot=0.f, glm::vec2 inScale={0.f,0.f}, uint32_t inTextureIndex=0, Rect inUVRect=defaultUVRect) :
			position( inposition ), uvRect(inUVRect), scale(inScale), textureIndex(inTextureIndex), rotation(inRot){}

		glm::vec2 position;

		//what part of the texture would you like to use? {0,0}= top left, {1,1}= bottom right
		alignas(8) Rect uvRect;
		//scale on the x and y axes (a Sprite's starting size is determined by the size, in pixels, of its texture)
		glm::vec2 scale;
	private:
	public:
		alignas(4)uint32_t textureIndex;
		//rotation is handled in radians
		alignas(4) glm::float32 rotation;

		void setRotation( float degrees )
		{
			rotation = glm::pi<float>() * degrees / 180.f;
		}

		void addRotation( float degrees )
		{
			rotation += glm::pi<float>() * degrees / 180.f;
		}

		void setPosition( float x, float y )
		{
			position.x = x;
			position.y = y;
		}

		void move( float x, float y )
		{
			position.x += x;
			position.y += y;
		}

		void setScale( float x, float y )
		{
			scale.x = x;
			scale.y = y;
		}


		void addToScale( float x, float y )
		{
			scale.x += x;
			scale.y += y;
		}

		uint32_t getTextureIndex()
		{
			return textureIndex;
		}
	};
}