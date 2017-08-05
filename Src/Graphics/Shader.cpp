#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Graphics/Shader.h"
#include "FileUtils.h"

namespace Silver {
	Shader::Shader(const char* vertFilePath, const char* fragFilePath)
	{
		CreateShader(vertFilePath, fragFilePath);
	}

	void Shader::CreateShader(const char* vertFilePath, const char* fragFilePath)
	{
		//Get ids
		shaderID = glCreateProgram();
		GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//Read src
		std::string vertFile = ReadFile(vertFilePath);
		std::string fragFile = ReadFile(fragFilePath);

		const char* vertSrc = vertFile.c_str();
		const char* fragSrc = fragFile.c_str();

		//Vertex shader
		glShaderSource(vertShaderID, 1, &vertSrc, NULL);
		glCompileShader(vertShaderID);

		GLint state;
		glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &state);
		if (state == GL_FALSE)
		{
			GLint logLength;
			glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<char>errMsg(logLength);
			glGetShaderInfoLog(vertShaderID, logLength, &logLength, &errMsg[0]);
			std::cout << "Vertex Shader Failed To Compile:\n";
			for (size_t i = 0; i < errMsg.size(); i++) std::cout << errMsg[i];
			glDeleteShader(vertShaderID);
			return;
		}

		//Frag shader
		glShaderSource(fragShaderID, 1, &fragSrc, NULL);
		glCompileShader(fragShaderID);

		glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &state);
		if (state == GL_FALSE)
		{
			int logLength;
			glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<char>errMsg(logLength);
			glGetShaderInfoLog(fragShaderID, logLength, &logLength, &errMsg[0]);
			std::cout << "Fragment Shader Failed To Compile:\n";
			for (size_t i = 0; i < errMsg.size(); i++) std::cout << errMsg[i];
			glDeleteShader(fragShaderID);
			return;
		}

		//Link
		glAttachShader(shaderID, vertShaderID);
		glAttachShader(shaderID, fragShaderID);
		glLinkProgram(shaderID);

		glDeleteShader(vertShaderID);
		glDeleteShader(fragShaderID);
	}

	void Shader::AddUniform(const char* uniform)
	{
		GLint uniformLocation = glGetUniformLocation(shaderID, uniform);
		
		if (uniformLocation == GL_INVALID_INDEX)
		{
			std::cout << "Couldn't Find Uniform: " << uniform;
			return;
		}

		uniforms[uniform] = uniformLocation;
	}

	void Shader::SetUniform(const char* uniform, const GLint i)
	{
		glUniform1i(uniforms[uniform], i);
	}

	void Shader::SetUniform(const char* uniform, const GLfloat f)
	{
		glUniform1f(uniforms[uniform], f);
	}

	void Shader::SetUniform(const char* uniform, const GLdouble d)
	{
		glUniform1d(uniforms[uniform], d);
	}

	void Shader::SetUniform(const char* uniform, const glm::vec2 &v2)
	{
		glUniform2f(uniforms[uniform], v2.x, v2.y);
	}

	void Shader::SetUniform(const char* uniform, const glm::vec3 &v3)
	{
		glUniform3f(uniforms[uniform], v3.x, v3.y, v3.z);
	}

	void Shader::SetUniform(const char* uniform, const glm::vec4 &v4)
	{
		glUniform4f(uniforms[uniform], v4.x, v4.y, v4.z, v4.w);
	}

	void Shader::SetUniform(const char* uniform, const glm::mat4 &m4)
	{
		glUniformMatrix4fv(uniforms[uniform], 1, GL_FALSE, &m4[0][0]);
	}

	void Shader::Enable() const
	{
		glUseProgram(shaderID);
	}

	void Shader::Disable() const
	{
		glUseProgram(0);
	}

	Shader::~Shader()
	{
		if (shaderID != 0)
			glDeleteProgram(shaderID);
	}
}