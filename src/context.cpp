#include "../header/context.h"
#include <glad/glad.h>
#include <stdexcept>
#include <iostream>

plContext::plContext() {
	if(!SDL_Init(SDL_INIT_VIDEO)) throw std::runtime_error("SDL video could not be initialized");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	window = SDL_CreateWindow(
		"GL Window",
		screen_width,
		screen_height,
		SDL_WINDOW_OPENGL
	);
	if(window == nullptr) throw std::runtime_error("SDL window could not be initialized");
	context = SDL_GL_CreateContext(window);
	if(context == nullptr) throw std::runtime_error("SDL OpenGL context not avaliable");
	SDL_WarpMouseInWindow(window, screen_width / 2, screen_height / 2);
	SDL_SetWindowRelativeMouseMode(window, true);
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) throw std::runtime_error("GLAD could not be initialized");
}

void plContext::set_camera(plCamera* plCamera) {
	this->camera = plCamera;
}

void plContext::swap_window() {
	SDL_GL_SwapWindow(window);
}

void plContext::get_GL_version() {
	std::cout<<"Vendor: "<<glGetString(GL_VENDOR)<<std::endl<<
			   "Renderer: "<<glGetString(GL_RENDERER)<<std::endl<<
			   "Language: "<<glGetString(GL_VERSION)<<std::endl<<
			   "Shading Language: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
}

void plContext::dispose() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}