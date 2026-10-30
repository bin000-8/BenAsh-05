#ifndef CONTEXT_H
#define CONTEXT_H
#include <SDL3/SDL.h>
struct plCamera;

struct plContext {
	const size_t screen_width = 640 * 2;
	const size_t screen_height = 480 * 2;
	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;
	bool end = false;
	plCamera* camera = nullptr;

	plContext();
	void swap_window();
	void dispose();
	void get_GL_version();
	void set_camera(plCamera* camera);
};
#endif