#pragma once

#include <GL/glew.h>

namespace Silver {
	class IndexBuffer
	{
	private:
		GLuint bufferID, count;

	public:
		IndexBuffer(GLuint* indices, GLsizei indicesCount);
		inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID); }
		inline void UnBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
		inline GLuint GetCount() const { return count; }
		~IndexBuffer();
	};
}