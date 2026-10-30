#include "../header/material.h"

void Material::set_material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	return;
}