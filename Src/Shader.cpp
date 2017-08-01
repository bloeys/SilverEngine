#include <string>
#include <vector>
#include <GL/glew.h>
#include <iostream>
#include "Shader.h"
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
		unsigned int vertShaderID = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//Read src
		std::string vertFile = ReadFile(vertFilePath);
		std::string fragFile = ReadFile(fragFilePath);
		
		const char* vertSrc = vertFile.c_str();
		const char* fragSrc = fragFile.c_str();

		//Vertex shader
		glShaderSource(vertShaderID, 1, &vertSrc, NULL);
		glCompileShader(vertShaderID);

		int state;
		glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &state);
		if (state == GL_FALSE)
		{
			int logLength;
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
			std::cout << "Fragment Shader Failed To Compile:\n" ;
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
		glDeleteProgram(shaderID);
	}
}