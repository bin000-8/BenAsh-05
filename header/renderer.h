#ifndef RENDERER_H	
#define RENDERER_H
#include <glad/glad.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include "../header/types.h"
#include "../header/context.h"
#include "../header/camera.h"
#include "../header/entity.h"
#include "../header/texture.h"

struct plRenderer {
	plContext* context = nullptr;

	plRenderer(plContext* context);
	void generate_buffers(Entity& entity);
	void generate_textures(Entity& entity);
	void generate_objects(Entity& entity);
	void generate_shader(GLuint& shader_handle, const std::string& path_to_vertex_shader, const std::string& path_to_fragment_shader);
	std::string load_shader_as_string(const std::string& filename);
	GLuint create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader);
	GLuint compile_shader(GLuint, const std::string& source);
	void start_frame();
	void predraw(Entity& entity, GLuint& shader);
	void upload_uniform_4fv(const GLfloat* value, GLint& uniform_location, GLuint& shader, const std::string& uniform_name_in_shader);
	GLint get_uniform_location(const GLint& pipeline, const GLchar* uniform_name);
	void draw(const Entity& entity, const GLuint& shader);
	void render(Entity& entity, GLuint& shader);
	void scene_render(std::vector<std::pair<Entity, shader>>& scene);
};
#endif