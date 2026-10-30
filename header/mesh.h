#ifndef MESH_H
#define MESH_H
#include "../header/vertex.h"
#include <glad/glad.h>
#include <vector>

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLuint vbo; // Generics (xyz | nxnynz | uv)
	GLuint vao;
	GLuint ibo;
	GLuint rgb_vbo;
	std::vector<glm::vec3> rgb_vertices;

	Mesh();
};
#endif