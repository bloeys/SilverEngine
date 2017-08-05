#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Silver {
	class Renderable2D
	{
	public:
		glm::vec3 pos;	//Position is the center of the renderable
		glm::vec2 size;
		glm::vec4 color;

	public:
		Renderable2D(glm::vec3 pos, glm::vec2 size, glm::vec4 col);
	};
}