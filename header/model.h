#ifndef MODEL_H
#define MODEL_H
#include "../header/mesh.h"
#include "../header/model.h"

struct Model {
	glm::vec3 offset;
	glm::vec3 rotation;
	float scale;

	Model();
};
#endif