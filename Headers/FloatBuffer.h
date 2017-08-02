#pragma once

#include <GL/glew.h>

namespace Silver {
	class FloatBuffer
	{
	private:
		GLuint bufferID;
		GLuint componentCount;	//How many floats make a component.e.g. 2 if buffering vec2, 3 for vec3 etc...
	
	public:
		FloatBuffer(GLfloat* data, GLsizei dataCount, GLuint compCount);
		void Bind() const;
		void UnBind() const;
		inline GLuint GetComponentCount() const { return componentCount; }
		~FloatBuffer();
	};
}