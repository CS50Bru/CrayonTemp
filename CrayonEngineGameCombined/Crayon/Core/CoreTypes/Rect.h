//holds the position of a rectangle, along with its width and height

#pragma once
#include"Libraries/glm/vec2.hpp"
namespace Crayon
{
	struct Rect
	{
	public:

		Rect() :
			origin(0.0,0.0)
			, extent(1.0,1.0) {}


		Rect( glm::vec2 inOrigin, glm::vec2 inExtent = {} ) :
			origin(inOrigin), extent (inExtent){ }

		//to do: I'm pretty sure we can take the alignment stuff out of this
		alignas(8)glm::vec2 origin;
		alignas(8)glm::vec2 extent;

		glm::vec2 getTopLeftRaw() const;
		glm::vec2 getTopRightRaw() const;
		glm::vec2 getBottomRightRaw() const;
		glm::vec2 getBottomLeftRaw() const;

		float getMinXRaw() const;
		float getMaxXRaw() const;
		float getMinYRaw() const;
		float getMaxYRaw() const;
	};
}