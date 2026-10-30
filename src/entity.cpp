#include "../header/entity.h"

Entity::Entity() {
	bool is_simple = false;
	bool is_light = false;
}

Entity::Entity(const std::vector<Vertex>& cube_vertices,
			   const std::vector<GLuint>& cube_indices,
			   bool is_simple,
			   bool is_emitter) {
	this->is_simple = is_simple;
	this->is_emitter = is_emitter;
	this->mesh.vertices = cube_vertices;
	this->mesh.indices = cube_indices;
}