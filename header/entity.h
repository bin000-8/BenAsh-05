#ifndef ENTITY_H
#define ENTITY_H
#include "../header/mesh.h"
#include "../header/model.h"
#include "../header/texture.h"
#include "../header/material.h"

struct Entity {
	Mesh mesh;
	Model model;
	Texture texture;
	Material material;
	bool is_simple;
	bool is_emitter;

	Entity();
	Entity(const std::vector<Vertex>& cube_vertices, const std::vector<GLuint>& cube_indices,
		   bool is_simple, bool is_emitter);
};
#endif