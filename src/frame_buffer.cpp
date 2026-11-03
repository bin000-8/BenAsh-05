#include "../header/frame_buffer.h"

plFrame_buffer::plFrame_buffer(plContext* context) {
	this->context = context;
}


void plFrame_buffer::initialize_framebuffer(const size_t width, const size_t height) {
    framebuffer_width = width;
    framebuffer_height = height;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenTextures(1, &framebuffer_color_texture);
    glBindTexture(GL_TEXTURE_2D, framebuffer_color_texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        framebuffer_color_texture,
        0
    );
    glGenRenderbuffers(1, &framebuffer_depth_stencil);
    glBindRenderbuffer(
        GL_RENDERBUFFER,
        framebuffer_depth_stencil
    );
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8,
        width,
        height
    );
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        framebuffer_depth_stencil
    );
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void plFrame_buffer::present_frame() {
    glBindFramebuffer(
        GL_READ_FRAMEBUFFER,
        framebuffer
    );
    glBindFramebuffer(
        GL_DRAW_FRAMEBUFFER,
        0
    );
    glBlitFramebuffer(
        0,
        0,
        framebuffer_width,
        framebuffer_height,
        0,
        0,
        framebuffer_width,
        framebuffer_height,

        GL_COLOR_BUFFER_BIT,
        GL_NEAREST
    );
    glBindFramebuffer(
        GL_FRAMEBUFFER,
        0
    );
}

void plFrame_buffer::destroy_framebuffer() {
    if (framebuffer_depth_stencil != 0) {
        glDeleteRenderbuffers(1, &framebuffer_depth_stencil);
        framebuffer_depth_stencil = 0;
    }
    if (framebuffer_color_texture != 0) {
        glDeleteTextures(1, &framebuffer_color_texture);
        framebuffer_color_texture = 0;
    }
    if (framebuffer != 0) {
        glDeleteFramebuffers(1, &framebuffer);
        framebuffer = 0;
    }
}

std::vector<unsigned char> plFrame_buffer::capture_frame() {
    std::vector<unsigned char> pixels(framebuffer_width * framebuffer_height * 4 /* since reading RGBA */);
    glBindFramebuffer(
        GL_READ_FRAMEBUFFER,
        framebuffer
    );
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glReadPixels(
        0,
        0,
        framebuffer_width,
        framebuffer_height,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixels.data()
    );
    return pixels;
}