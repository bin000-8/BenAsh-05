#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <string>

struct Texture {
	int image_width;
	int image_height;
	int nr_of_channels;
	std::uint8_t* data;
	GLuint texture_handle;

	void set(const std::string path_to_texture);
	void stbi_release_texture();
};
#endif