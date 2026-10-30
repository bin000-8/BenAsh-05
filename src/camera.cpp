#include "../header/camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/rotate_vector.hpp>

plCamera::plCamera(plContext* context) {
	this->context = context;
	context->set_camera(this);
	projection = glm::perspective(glm::radians(45.0f), (float)context->screen_width / (float)context->screen_height, 0.1f, 20.0f);
	eye = glm::vec3(0.0f, 0.0f, 0.0f);
	view_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	up_vector = glm::vec3(0.0f, 1.0f, 0.0f);
	view = get_view_matrix();
}

glm::mat4 plCamera::get_view_matrix() {
	return glm::lookAt(eye, eye + view_direction, up_vector);
}

void plCamera::mouse_look(float dx, float dy) {
    dx *= SENSITIVITY;
	view_direction = glm::rotate(view_direction, glm::radians(-dx), up_vector);
}

void plCamera::move_foward(const float speed = 1.0f) {
	eye += view_direction * speed;
}

void plCamera::move_backward(const float speed = 1.0f) {
	eye -= view_direction * speed;
}

void plCamera::move_left(const float speed = 1.0f) {
	glm::vec3 right_vector = glm::cross(view_direction, up_vector);
	eye -= right_vector * speed;
}

void plCamera::move_right(const float speed = 1.0f) {
	glm::vec3 right_vector = glm::cross(view_direction, up_vector);
	eye += right_vector * speed;
}

void plCamera::move_up(const float speed = 1.0f) {
	eye += up_vector * speed;
}

void plCamera::move_down(const float speed = 1.0f) {
	eye -= up_vector * speed;
}
