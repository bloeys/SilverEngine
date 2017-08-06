#pragma once

#include <GL/glew.h>
#include "Vertex.h"
#include "IndexBuffer.h"
#include "Renderer2DBase.h"

class VertexArray;

namespace Silver {
	class Renderer2D : public Renderer2DBase
	{
	private:
		GLuint vaoID, bufferID;
		Vertex* buffer;
		IndexBuffer* ibo;
		GLsizei indexCount = 0;

	private:
		void Init();

	public:
		Renderer2D();
		void BeginAdd() override;
		void Add(const Renderable2D *r) override;
		//void EndAdd();
		void Flush() override;
		~Renderer2D();
	};
}