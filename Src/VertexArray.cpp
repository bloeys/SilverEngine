#include "VertexArray.h"

namespace Silver {
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &arrayID);
	}
	
	void VertexArray::AddFloatBuffer(FloatBuffer* buffer, GLuint layoutLocation)
	{
		Bind();
		buffer->Bind();

		glEnableVertexAttribArray(layoutLocation);
		glVertexAttribPointer(layoutLocation, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
		buffers.emplace_back(buffer);
		buffer->UnBind();
		UnBind();
	}
	
	void VertexArray::Bind() const
	{
		glBindVertexArray(arrayID);
	}
	void VertexArray::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &arrayID);

		for (size_t i = 0; i < buffers.size(); i++)
			delete buffers[i];
	}
}