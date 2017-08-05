#pragma once

#include <vector>
#include <GL/glew.h>
#include "FloatBuffer.h"

namespace Silver {
	class VertexArray
	{
	private:
		GLuint arrayID;
		std::vector<FloatBuffer*> buffers;

	public:
		VertexArray();
		void AddFloatBuffer(FloatBuffer* buffer, GLuint layoutLocation);
		void Bind() const;
		void UnBind() const;
		~VertexArray();
	};
}