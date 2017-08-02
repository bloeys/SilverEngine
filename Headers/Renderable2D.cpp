#include "Renderable2D.h"

namespace Silver {
	Renderable2D::Renderable2D(glm::vec3 position, glm::vec2 size, Shader &shader)
		: pos(position), size(size), color(1, 1, 1, 1), shader(shader)
	{
		Init();
	}

	Renderable2D::Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader &shader)
		: pos(position), size(size), color(color), shader(shader)
	{
		Init();
	}

	void Renderable2D::Init()
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

		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
		ibo = new IndexBuffer(indices, 6);
	}

	Renderable2D::~Renderable2D()
	{
		delete vao;
		delete ibo;
	}
}