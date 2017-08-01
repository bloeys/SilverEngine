#pragma once

namespace Silver {
	class Shader
	{
	private:
		unsigned int shaderID = 0;

	private:
		void CreateShader(const char* vertFilePath, const char* fragFilePath);
	public:
		Shader(const char* vertFilePath, const char* fragFilePath);
		void Enable() const;
		void Disable() const;
		~Shader();
	};
}