#include "../header/texture.h"
#include "../external/stb/stb_image.h"
#include <iostream>

void Texture::set(const std::string path_to_texture) {
	this->texture_handle = 0;
    data = stbi_load(
        path_to_texture.c_str(),
        &image_width,
        &image_height,
        &nr_of_channels,
        0
    );
}

void Texture::stbi_release_texture() {
	stbi_image_free(this->data);
}