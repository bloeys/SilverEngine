#include "Graphics/Sprite.h"

namespace Silver {
	Sprite::Sprite(float x, float y, float width, float height, float r, float g, float b, float a)
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), glm::vec4(r, g, b, a))
	{
	}

	Sprite::Sprite(float x, float y, float width, float height, glm::vec4 col)
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), col)
	{
	}

	Sprite::Sprite(glm::vec3 position, glm::vec2 size)
		: Renderable2D(position, size, glm::vec4(1, 1, 1, 1))
	{
	}

	Sprite::Sprite(glm::vec3 position, glm::vec2 size, glm::vec4 color)
		: Renderable2D(position, size, color)
	{
	}

	Sprite::~Sprite()
	{
	}
}