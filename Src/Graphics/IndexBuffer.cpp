#include "Graphics/IndexBuffer.h"

namespace Silver {
	IndexBuffer::IndexBuffer(GLuint* indices, GLsizei indicesCount)
	{
		count = indicesCount;
		glGenBuffers(1, &bufferID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &bufferID);
	}
}