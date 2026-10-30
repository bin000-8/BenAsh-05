#ifndef CLI_H
#define PLCLI_H
#include <iostream>
#include <string>
#include "../header/context.h"
#include "glm/glm.hpp"

struct plCli {
	plContext* context = nullptr;
	
	plCli(plContext* context);
};
#endif