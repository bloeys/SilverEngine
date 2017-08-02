#include <FloatBuffer.h>

namespace Silver {
	FloatBuffer::FloatBuffer(GLfloat* data, GLsizei dataCount, GLuint compCount)
	{
		componentCount = compCount;
		glGenBuffers(1, &bufferID);
		
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, dataCount * sizeof(GLfloat), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void FloatBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	}

	void FloatBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	FloatBuffer::~FloatBuffer()
	{
	}
}