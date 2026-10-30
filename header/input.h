#ifndef INPUT_H
#define INPUT_H
#include "../header/context.h"

struct plInput {
	plContext* context;

	plInput(plContext* context);
	void handle_input();
};
#endif