#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position_coordinates;
	glm::vec3 normal_coordinates;
	glm::vec2 texture_coordinates;
	glm::vec3 rgb_values;
};
#endif