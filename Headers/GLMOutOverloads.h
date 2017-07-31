#pragma once

#include <iosfwd>
#include <glm/fwd.hpp>

namespace Silver {
	std::ostream &operator<<(std::ostream &stream, const glm::vec2 &vec2);
	std::ostream &operator<<(std::ostream &stream, const glm::vec3 &vec3);
	std::ostream &operator<<(std::ostream &stream, const glm::vec4 &vec4);

	//Handle having endl on the left
	std::ostream& operator<<(const std::ostream& (*f)(std::ostream&), const glm::vec2 &vec2);
	std::ostream& operator<<(const std::ostream& (*f)(std::ostream&), const glm::vec3 &vec3);
	std::ostream& operator<<(const std::ostream& (*f)(std::ostream&), const glm::vec4 &vec4);
}