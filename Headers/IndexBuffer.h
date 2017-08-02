#pragma once

#include <GL/glew.h>

namespace Silver {
	class IndexBuffer
	{
	private:
		GLuint bufferID, count;

	public:
		IndexBuffer(GLushort* indices, GLsizei indicesCount);
		void Bind() const;
		void UnBind() const;
		inline GLuint GetCount() const { return count; }
		~IndexBuffer();
	};
}