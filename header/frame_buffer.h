#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include <glad/glad.h>
#include "../header/context.h"

struct plFrame_buffer {
    plContext* context = nullptr;
	GLuint framebuffer = 0;
    GLuint framebuffer_color_texture = 0;
    GLuint framebuffer_depth_stencil = 0;
    size_t framebuffer_width = 0;
    size_t framebuffer_height = 0;

    plFrame_buffer(plContext* context);
    void initialize_framebuffer(size_t width, size_t height);
    void present_frame();
    void destroy_framebuffer();
};
#endif