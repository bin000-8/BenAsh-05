#include "../header/renderer.h"
#include "../header/context.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../external/stb/stb_image.h"

plRenderer::plRenderer(plContext* context) {
	this->context = context;
	stbi_set_flip_vertically_on_load(true);
}

void plRenderer::generate_buffers(Entity& entity) {
	// Generate the VBO for [x,y,z|nx,ny,nz|u,v]
	glGenBuffers(1, &entity.mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, entity.mesh.vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		entity.mesh.vertices.size() * sizeof(Vertex),
		entity.mesh.vertices.data(),
		GL_STATIC_DRAW
	);

	// Generate an additional VBO for [rgb] if simple
	if (entity.is_simple) {
		glGenBuffers(1, &entity.mesh.rgb_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, entity.mesh.rgb_vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			entity.mesh.rgb_vertices.size() * sizeof(glm::vec3),
			entity.mesh.rgb_vertices.data(),
			GL_STATIC_DRAW
		);
	} // If it's not simple, generate it's textures
	else {
		generate_textures(entity);
	}

	// Generate the index buffer object
	glGenBuffers(1, &entity.mesh.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity.mesh.ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		entity.mesh.indices.size() * sizeof(GLuint),
		entity.mesh.indices.data(),
		GL_STATIC_DRAW
	);
}

void plRenderer::generate_textures(Entity& entity) {
	entity.texture.texture_handle = 0;
	glGenTextures(1, &entity.texture.texture_handle); 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity.texture.texture_handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		entity.texture.image_width,
		entity.texture.image_height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		entity.texture.data
	);
	glGenerateMipmap(GL_TEXTURE_2D);
	entity.texture.stbi_release_texture();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void plRenderer::generate_objects(Entity& entity) {
	// Generate the VAO
	glGenVertexArrays(1, &entity.mesh.vao);
	glBindVertexArray(entity.mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, entity.mesh.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity.mesh.ibo);

	// Inform the GPU of [x, y, z]
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		false,
		sizeof(Vertex),
		(void*)offsetof(Vertex, position_coordinates)
	);

	// Inform the GPU of [nx, ny, nz]
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		false,
		sizeof(Vertex),
		(void*)offsetof(Vertex, normal_coordinates)
	);

	// (if using rgb)
	// Inform the GPU of [r, b, b]
	if (entity.is_simple) {
		glBindBuffer(GL_ARRAY_BUFFER, entity.mesh.rgb_vbo);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			3,
			GL_FLOAT,
			false,
			sizeof(glm::vec3),
			(void*)0
		);
	}
	else {
	// (if not using rgb)
	// Inform the GPU of [u, v]
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			false,
			sizeof(Vertex),
			(void*)offsetof(Vertex, texture_coordinates)
		);
	}
	glBindVertexArray(0);
}

void plRenderer::generate_shader(GLuint& shader_handle,
							   const std::string& path_to_vertex_shader,
						       const std::string& path_to_fragment_shader) {
	std::string vertex_shader_source = load_shader_as_string(path_to_vertex_shader);
	std::string fragment_shader_source = load_shader_as_string(path_to_fragment_shader);
	shader_handle = create_shader_program(vertex_shader_source, fragment_shader_source);
}

std::string plRenderer::load_shader_as_string(const std::string& filename) {
	std::string result = "";
	std::string line = "";
	std::ifstream file(filename.c_str());
	if(file.is_open()) {
		while(std::getline(file, line)) {
			result += line + "\n";
		}
		file.close();
	}
	return result;
}

GLuint plRenderer::create_shader_program(const std::string& vertex_shader_source,
									     const std::string& fragment_shader_source) {
	GLuint program_object = glCreateProgram();
	GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
	GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
	glAttachShader(program_object, vertex_shader);
	glAttachShader(program_object, fragment_shader);
	glLinkProgram(program_object);
	glValidateProgram(program_object);
	return program_object;
}

GLuint plRenderer::compile_shader(GLuint type_of_shader, const std::string& source) {
	GLuint shader_object = glCreateShader(type_of_shader);
	const char* c_source = source.c_str();
	glShaderSource(shader_object, 1, &c_source, nullptr);
	glCompileShader(shader_object);
	return shader_object;
}

void plRenderer::start_frame() {
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void plRenderer::predraw(Entity& entity, GLuint& shader) {
	glUseProgram(shader);
	glm::mat4 model(1.0f);
	model = glm::translate(model, entity.model.offset);
	model = glm::rotate(model, glm::radians(entity.model.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(entity.model.rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(entity.model.rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(entity.model.scale));

	GLint uModel_matrix_location;
	upload_uniform_4fv(glm::value_ptr(model), uModel_matrix_location, shader, "uModel_matrix");

	context->camera->view = context->camera->get_view_matrix();
	GLint uView_matrix_location;
	upload_uniform_4fv(glm::value_ptr(context->camera->view), uView_matrix_location, shader, "uView_matrix"); 
	
	GLint uProjection_location;
	upload_uniform_4fv(glm::value_ptr(context->camera->projection), uProjection_location, shader, "uProjection_matrix");

	// Upload the color of the light
	GLint uLight_color_location = glGetUniformLocation(shader, "uLight_color");
	glUniform3f(uLight_color_location, 1.0, 1.0, 1.0);
	// USE LATER: glUniform3fv(uLight_color_location, 1, glm::value_ptr(light.mesh.rgb_vertices[0]));


	// Upload the position of the light
	GLint uLight_position_location = glGetUniformLocation(shader, "uLight_position");
	glUniform3f(uLight_position_location, 0.0, 0.5, -2.5);

	// Upload the position of the viewer
	GLint uView_position_location = glGetUniformLocation(shader, "uView_position");
	glUniform3fv(uView_position_location, 1, glm::value_ptr(context->camera->eye));

	// Upload the Material type of the object
	GLint uMaterial_ambient_location = glGetUniformLocation(shader, "uMaterial.ambient");
	glUniform3fv(uMaterial_ambient_location, 1, glm::value_ptr(entity.material.ambient));
	GLint uMaterial_diffuse_location = glGetUniformLocation(shader, "uMaterial.diffuse");
	glUniform3fv(uMaterial_diffuse_location, 1, glm::value_ptr(entity.material.diffuse));
	GLint uMaterial_specular_location = glGetUniformLocation(shader, "uMaterial.specular");
	glUniform3fv(uMaterial_specular_location, 1, glm::value_ptr(entity.material.specular));
	GLint uMaterial_shininess_location = glGetUniformLocation(shader, "uMaterial.shininess");
	glUniform1f(uMaterial_shininess_location, entity.material.shininess);

	if (!entity.is_simple) {
		// If the entity is not simple, upload its tex
		GLint uTex0_location = get_uniform_location(shader, "uTex0");
		glUniform1i(uTex0_location, 0);
	}
	else {
		// Upload the color of the entity
		GLint uColor_location = glGetUniformLocation(shader, "uColor");
		glUniform3f(
			uColor_location,
			entity.mesh.rgb_vertices[0].x,
			entity.mesh.rgb_vertices[0].y,
			entity.mesh.rgb_vertices[0].z
		);
	}
}

void plRenderer::upload_uniform_4fv(const GLfloat* value, GLint& uniform_location,
								GLuint& shader, const std::string& uniform_name_in_shader) {
	uniform_location = get_uniform_location(shader, uniform_name_in_shader.c_str());
	glUniformMatrix4fv(uniform_location, 1, false, value);
}

GLint plRenderer::get_uniform_location(const GLint& pipeline, const GLchar* uniform_name) {
	GLint uUniform_location = glGetUniformLocation(pipeline, uniform_name);
	if(uUniform_location == -1) {
		std::cerr<<"Could not find "<<uniform_name<<" uniform variable"<<std::endl;
		exit(EXIT_FAILURE);
	}
	return uUniform_location;
}

void plRenderer::draw(const Entity& entity, const GLuint& shader) {
	if (!entity.is_simple) {
		glBindTexture(GL_TEXTURE_2D, entity.texture.texture_handle);
	}
	glUseProgram(shader);
	glBindVertexArray(entity.mesh.vao);
	glDrawElements(GL_TRIANGLES, entity.mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glUseProgram(0);
}

void plRenderer::render(Entity& entity, GLuint& shader) {
	predraw(entity, shader);
	draw(entity, shader);
}

void plRenderer::scene_render(std::vector<std::pair<Entity, shader>>& scene) {
	for (std::pair<Entity, shader>& p : scene) {
		render(p.first, p.second);
	}
}