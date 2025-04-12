#pragma once
#include"Libraries/glm/vec2.hpp"
namespace Crayon
{
	class RenderableLine
	{
		glm::vec2 start;
		glm::vec2 end;

	public:
		RenderableLine( glm::vec2 inStart, glm::vec2 inEnd):
			start(inStart), end(inEnd){}
		
		static RenderableLine RenderableLineStartAndOffset( glm::vec2 start, glm::vec2 offset )
		{
			return RenderableLine( start, start + offset );
		}
	};


}