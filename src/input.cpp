#include "../header/input.h"
#include "../header/camera.h"
#include <glad/glad.h>
#include <iostream>

plInput::plInput(plContext* context) {
	this->context = context;
}

void plInput::handle_input() {
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0){
		if(e.type == SDL_EVENT_QUIT){
			context->get_GL_version();
			std::cout<<std::endl<<"Closing..."<<std::endl;
			context->end = true;
		} else if (e.type == SDL_EVENT_MOUSE_MOTION) {
			context->camera->mouse_look(e.motion.xrel, e.motion.yrel);
		}
	}
	const bool* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		SDL_Event quit_event;
		quit_event.type = SDL_EVENT_QUIT;
		SDL_PushEvent(&quit_event);
	}

	if (state[SDL_SCANCODE_W]) {
		context->camera->move_foward(context->camera->MOVE_SPEED);
	}

	if (state[SDL_SCANCODE_A]) {
		context->camera->move_left(context->camera->MOVE_SPEED);
	}

	if (state[SDL_SCANCODE_S]) {
		context->camera->move_backward(context->camera->MOVE_SPEED);
	}

	if (state[SDL_SCANCODE_D]) {
		context->camera->move_right(context->camera->MOVE_SPEED);
	}

	if (state[SDL_SCANCODE_SPACE]) {
		context->camera->move_up(context->camera->MOVE_SPEED);
	}

	if (state[SDL_SCANCODE_LALT]) {
		context->camera->move_down(context->camera->MOVE_SPEED);
	}
	SDL_PumpEvents();

}