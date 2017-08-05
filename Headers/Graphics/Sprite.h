#pragma once

#include "Renderable2D.h"

namespace Silver {
	class Sprite : public Renderable2D
	{
	public:
		Sprite(float x, float y, float width, float height, float r, float g, float b, float a);
		Sprite(float x, float y, float width, float height, glm::vec4 col);
		Sprite(glm::vec3 position, glm::vec2 size);
		Sprite(glm::vec3 position, glm::vec2 size, glm::vec4 color);
		~Sprite();

	private:

	};
}