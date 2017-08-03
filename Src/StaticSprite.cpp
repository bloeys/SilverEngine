#include "StaticSprite.h"

namespace Silver {
	StaticSprite::StaticSprite(float x, float y, float width, float height, float r, float g, float b, float a, Shader &shader)
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), glm::vec4(r, g, b, a)), shader(shader)
	{
		Init();
	}

	StaticSprite::StaticSprite(float x, float y, float width, float height, glm::vec4 col, Shader &shader)
		: Renderable2D(glm::vec3(x, y, 0), glm::vec2(width, height), col), shader(shader)
	{
		Init();
	}

	StaticSprite::StaticSprite(glm::vec3 position, glm::vec2 size, Shader &shader)
		: Renderable2D(position, size, glm::vec4(1, 1, 1, 1)), shader(shader)
	{
		Init();
	}

	StaticSprite::StaticSprite(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader &shader)
		: Renderable2D(position, size, color), shader(shader)
	{
		Init();
	}

	void StaticSprite::Init()
	{
		GLfloat vertices[] =
		{
			0,		0,		0,
			0,		size.y,	0,
			size.x,	size.y,	0,
			size.x,	0,		0
		};

		GLfloat vertColors[] =
		{
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w
		};

		vao = new VertexArray();
		vao->AddFloatBuffer(new FloatBuffer(vertices, 4 * 3, 3), 0);
		vao->AddFloatBuffer(new FloatBuffer(vertColors, 4 * 4, 4), 1);

		GLuint indices[] = { 0, 1, 2, 0, 2, 3 };
		ibo = new IndexBuffer(indices, 6);
	}

	StaticSprite::~StaticSprite()
	{
		delete vao;
		delete ibo;
	}
}