#pragma once

#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>
#include <GL/glew.h>

namespace Silver {
	class Shader
	{
	private:
		GLuint shaderID = 0;
		std::unordered_map<std::string, GLuint> uniforms;
		int attribCount;

	private:
		void CreateShader(const char* vertFilePath, const char* fragFilePath);

	public:
		Shader(const char* vertFilePath, const char* fragFilePath);
		void AddUniform(const char* uniform);

		//Remember to enable the shader first
		void SetUniform(const char* uniform, const GLint i);
		//Remember to enable the shader first
		void SetUniform(const char* uniform, const GLfloat f);
		//Remember to enable the shader first
		void SetUniform(const char* uniform, const GLdouble d);
		//Remember to enable the shader first
		void SetUniform(const char* uniform, const glm::vec2 &v2);
		//Remember to enable the shader first
		void SetUniform(const char* uniform, const glm::vec3 &v3);
		//Remember to enable the shader first
		void SetUniform(const char* uniform, const glm::vec4 &v4);
		//Remember to enable the shader first
		void SetUniform(const char* uniform, const glm::mat4 &m4);
		
		void Enable() const;
		void Disable() const;
		~Shader();
	};
}