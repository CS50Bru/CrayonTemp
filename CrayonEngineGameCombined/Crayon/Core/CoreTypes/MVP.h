#pragma once
#include"Libraries/glm/mat4x4.hpp"
#include"Libraries/glm/vec2.hpp"

//3 matrices:
//model matrix: converts into world space
//view matrix: converts to camera space
//projection matrix: transforms into normalized device coordinates
namespace Crayon
{
	//adheres to std140 (check you got that name right): mat4s need to align to 16
	struct MVP
	{
		alignas(alignof (glm::vec4)) glm::mat4 model;
		alignas(alignof (glm::vec4)) glm::mat4 view;
		alignas(alignof (glm::vec4)) glm::mat4 proj;
	};
}