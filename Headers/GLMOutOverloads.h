#pragma once

#include <iosfwd>
#include <glm/fwd.hpp>

namespace Silver {
	std::ostream &operator<<(std::ostream &stream, glm::vec2 &vec2);
	std::ostream &operator<<(std::ostream &stream, glm::vec3 &vec3);
	std::ostream &operator<<(std::ostream &stream, glm::vec4 &vec4);

	//Handle having endl on the left
	std::ostream& operator<<(std::ostream& (*f)(std::ostream&), glm::vec2 &vec2);
	std::ostream& operator<<(std::ostream& (*f)(std::ostream&), glm::vec3 &vec3);
	std::ostream& operator<<(std::ostream& (*f)(std::ostream&), glm::vec4 &vec4);
}