#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include "../header/context.h"

struct plCamera {
	plContext* context;
	glm::mat4 projection;
	glm::vec3 eye;
	glm::vec3 view_direction;
	glm::vec3 up_vector;
	glm::mat4 view;
	const float SENSITIVITY = 0.5f;
	const float MOVE_SPEED = 0.3f;

	plCamera(plContext* context);
	glm::mat4 get_view_matrix();
	void mouse_look(float dx, float dy);
	void move_foward(float speed);
	void move_backward(float speed);
	void move_left(float speed);
	void move_right(float speed);
	void move_up(float speed);
	void move_down(float speed);
};
#endif