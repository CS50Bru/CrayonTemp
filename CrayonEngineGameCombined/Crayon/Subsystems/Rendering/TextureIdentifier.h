#pragma once
#include"Core.h"
namespace Crayon
{
	struct TextureIdentifier
	{
		
		std::string assetPath = "Textures/default.png";
		size_t textureIndex = Core::InvalidSize;

		//The lack of a return type before operator emphasizes that this is an IMPLICIT conversion.
		operator size_t() const { return textureIndex; }

		TextureIdentifier( size_t inIndex ) :
			textureIndex( inIndex )
		{}

		TextureIdentifier() = default;

		TextureIdentifier& operator=( size_t newIndex )
		{
			textureIndex = newIndex;
			return *this;
		}

		TextureIdentifier& operator= ( uint32_t newIndex )
		{
			textureIndex = newIndex;
			return *this;
		}
		
	};
}