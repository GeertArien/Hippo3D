#include "FirstPersonControls.h"
#include <GLFW/glfw3.h>
#include "interface/InputManager.h"
#include "core/Camera.h"


namespace Mantis {

void FirstPersonControls::ProcessInput(const Mantis::InputManager& inputManager, Mantis::Camera& camera) {
	ProcessFPSMovement(inputManager, camera);
	ProcessMouseMove(inputManager, camera);
	ProcessScroll(inputManager, camera);
}

void FirstPersonControls::ProcessFPSMovement(const Mantis::InputManager& inputManager, Mantis::Camera& camera) {
	auto current_frame = static_cast<float>(glfwGetTime());
	float delta_time = current_frame - last_frame_;
	last_frame_ = current_frame;

	if (inputManager.IsKeyPressed(GLFW_KEY_W)) {
		camera.ProcessMovement(Mantis::Camera::Movement::FORWARD, delta_time);
	}
	if (inputManager.IsKeyPressed(GLFW_KEY_S)) {
		camera.ProcessMovement(Mantis::Camera::Movement::BACKWARD, delta_time);
	}
	if (inputManager.IsKeyPressed(GLFW_KEY_A)) {
		camera.ProcessMovement(Mantis::Camera::Movement::LEFT, delta_time);
	}
	if (inputManager.IsKeyPressed(GLFW_KEY_D)) {
		camera.ProcessMovement(Mantis::Camera::Movement::RIGHT, delta_time);
	}
}

void FirstPersonControls::ProcessMouseMove(const Mantis::InputManager& inputManager, Mantis::Camera& camera) {
	Mantis::Position cursor_position = inputManager.GetCursorPosition();

	auto pos_x_f = static_cast<float>(cursor_position.x);
	auto pos_y_f = static_cast<float>(cursor_position.y);

	if (first_mouse_) {
		last_x_ = pos_x_f;
		last_y_ = pos_y_f;
		first_mouse_ = false;
	}

	float offset_x = pos_x_f - last_x_;
	float offset_y = last_y_ - pos_y_f; // reversed since y-coordinates range from bottom to top
	last_x_ = pos_x_f;
	last_y_ = pos_y_f;

	camera.ProcessMouseMovement(offset_x, offset_y);
}

void FirstPersonControls::ProcessScroll(const Mantis::InputManager& inputManager, Mantis::Camera& camera) {
	Mantis::Position scroll_position = inputManager.GetScrollPosition();
	auto pos_y_f = static_cast<float>(scroll_position.y);

//	if (first_scroll_) {
//		last_scroll_y_ = pos_y_f;
//		first_scroll_ = false;
//	}
//
//	float offset_y = pos_y_f - last_scroll_y_;
//	last_scroll_y_ = pos_y_f;
	camera.ProcessZoom(pos_y_f);
}

}