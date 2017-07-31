#include <iostream>
#include <glm/glm.hpp>
#include "GLMOutOverloads.h"

namespace Silver {
	std::ostream &operator<<(std::ostream &stream, glm::vec2 &vec2)
	{
		stream << "Vec2(" << vec2.x << ", " << vec2.y << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, glm::vec3 &vec3)
	{
		stream << "Vec3(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")";
		return stream;
	}

	std::ostream &operator<<(std::ostream &stream, glm::vec4 &vec4)
	{
		stream << "Vec4(" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << ")";
		return stream;
	}

	//Handle having endl on the left
	std::ostream& operator<<(std::ostream& (*f)(std::ostream&), glm::vec2 &vec2)
	{
		return f(std::cout << "Vec2(" << vec2.x << ", " << vec2.y << ")");
	}

	std::ostream& operator<<(std::ostream& (*f)(std::ostream&), glm::vec3 &vec3)
	{
		return f(std::cout << "Vec3(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")");
	}

	std::ostream& operator<<(std::ostream& (*f)(std::ostream&), glm::vec4 &vec4)
	{
		return f(std::cout << "Vec4(" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << ")");
	}
}