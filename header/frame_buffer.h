#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include "../header/context.h"
#include <glad/glad.h>
#include <vector>

struct plFrame_buffer {
    plContext* context = nullptr;
	GLuint framebuffer = 0;
    GLuint framebuffer_color_texture = 0;
    GLuint framebuffer_depth_stencil = 0;
    size_t framebuffer_width = 0;
    size_t framebuffer_height = 0;

    plFrame_buffer(plContext* context);
    void initialize_framebuffer(const size_t width, const size_t height);
    void present_frame();
    void destroy_framebuffer();
    std::vector<unsigned char> capture_frame();
};
#endif