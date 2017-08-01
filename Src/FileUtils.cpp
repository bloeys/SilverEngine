#include <iostream>
#include <fstream>
#include "FileUtils.h"

namespace Silver {
	std::string ReadFile(const char* filepath)
	{
		std::ifstream fileStream(filepath, std::ios::ate);	//Start and directly go to eof
		if (fileStream.fail())
		{
			std::cout << "File FAILED to open: " << filepath << std::endl;
			return "";
		}

		std::string file;
		file.resize(fileStream.tellg());	//Resize according to file size
		fileStream.seekg(0, std::ios::beg);

		fileStream.read(&file[0], file.size());
		fileStream.close();
		return file;
	}
}