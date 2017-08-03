#include <glm/gtc/matrix_transform.hpp>
#include "Renderer2D.h"
#include <cstddef>

#define MAX_SPRITES 50000
#define SPRITE_SIZE sizeof(Vertex) * 4

namespace Silver {
	Renderer2D::Renderer2D()
	{
		Init();
	}

	void Renderer2D::Init()
	{
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		//Create buffer to hold batch data
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, SPRITE_SIZE * MAX_SPRITES, NULL, GL_DYNAMIC_DRAW);	//Setup an empty buffer big enough to hold max size of sprites we are handling per batch

		//Position attribute settings
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);

		//Color attribute settings
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Vertex::color));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Generate indices array capable of handling the vertices for all the sprites(current max is 10K sprites)
		//MAX_SPRITES * 6 since each sprites needs 6 indices to be drawn
		GLuint* indices = new GLuint[MAX_SPRITES * 6];
		GLuint offset = 0;
		for (size_t i = 0; i < MAX_SPRITES * 6; i += 6)
		{
			indices[i] = indices[i + 3] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = indices[i + 4] = offset + 2;
			indices[i + 5] = offset + 3;

			offset += 4;
		}

		ibo = new IndexBuffer(indices, MAX_SPRITES * 6);
		glBindVertexArray(0);
	}

	void Renderer2D::BeginAdd()
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::Add(const Renderable2D *rend)
	{
		//Override the buffer with the data of the renderables sent to us
		const glm::vec3 &p		=	rend->pos;
		const glm::vec2 &s		=	rend->size;
		const glm::vec4 &color	=	rend->color;

		//Setting color takes too much time, so instead we send color as an uint packed with 4 bytes. int=32bits, byte=8bits, 
		//so we can pack the 4 bytes of the color into a single uint reducing copying time significantly.(~100FPS boost!)
		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;

		unsigned int c = a << 24 | b << 16 | g << 8 | r;

		//First vertex
		buffer->pos = p;
		buffer->color = c;
		buffer++;

		//Second vertex
		buffer->pos.x = p.x;
		buffer->pos.y = p.y + s.y;
		buffer->pos.z = p.z;
		buffer->color = c;
		buffer++;

		buffer->pos.x = p.x + s.x;
		buffer->pos.y = p.y + s.y;
		buffer->pos.z = p.z;
		buffer->color = c;
		buffer++;

		buffer->pos.x = p.x + s.x;
		buffer->pos.y = p.y;
		buffer->pos.z = p.z;
		buffer->color = c;
		buffer++;

		indexCount += 6;
	}

	void Renderer2D::EndAdd()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer2D::Draw()
	{
		glBindVertexArray(vaoID);
		ibo->Bind();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
		ibo->UnBind();
		glBindVertexArray(0);

		indexCount = 0;
	}

	Renderer2D::~Renderer2D()
	{
		glDeleteBuffers(1, &bufferID);
		delete ibo;
	}
}