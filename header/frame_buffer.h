#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include "../header/context.h"
#include <glad/glad.h>
#include <vector>

struct plFrame_buffer {
    plContext* context = nullptr;
	GLuint frame_buffer = 0;
    GLuint frame_buffer_color_texture = 0;
    GLuint frame_buffer_depth_stencil = 0;
    size_t frame_buffer_width = 0;
    size_t frame_buffer_height = 0;

    plFrame_buffer(plContext* context);
    void initialize_frame_buffer(const size_t width, const size_t height);
    void present_frame();
    void destroy_frame_buffer();
    std::vector<unsigned char> capture_frame();
};
#endif