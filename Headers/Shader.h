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
		std::unordered_map<std::string, GLuint> uniforms;	//Store uniforms for quick access
		int attribCount;

	private:
		void CreateShader(const char* vertFilePath, const char* fragFilePath);
	
	public:
		Shader(const char* vertFilePath, const char* fragFilePath);
		void AddUniform(const char* uniform);	//Adds uniforms(After linking
		void SetUniform(const char* uniform, const GLint i);
		void SetUniform(const char* uniform, const GLfloat f);
		void SetUniform(const char* uniform, const GLdouble d);
		void SetUniform(const char* uniform, const glm::vec2 &v2);
		void SetUniform(const char* uniform, const glm::vec3 &v3);
		void SetUniform(const char* uniform, const glm::vec4 &v4);
		void SetUniform(const char* uniform, const glm::mat4 &m4);
		void Enable() const;
		void Disable() const;
		~Shader();
	};
}