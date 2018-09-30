#include "FirstPersonControls.h"
#include <GLFW/glfw3.h>
#include "interface/input/InputManager.h"
#include "gfx/scene/Camera.h"


namespace Mantis {
namespace Controls {

void FirstPersonControls::SetKey(const Movement& movement, Input::Key key) {
	switch (movement) {
		case Movement::FORWARD:
			forward_key_ = key;
			break;
		case Movement::BACKWARD:
			backward_key_ = key;
			break;
		case Movement::RIGHT:
			right_key_ = key;
			break;
		case Movement::LEFT:
			left_key_ = key;
			break;
	}
}

void FirstPersonControls::ProcessInput(const Input::InputManager& inputManager, GFX::Camera& camera) {
	ProcessFPSMovement(inputManager, camera);
	ProcessMouseMove(inputManager, camera);
	ProcessScroll(inputManager, camera);
}

void FirstPersonControls::ProcessFPSMovement(const Input::InputManager& inputManager, GFX::Camera& camera) {
	auto current_frame = static_cast<float>(glfwGetTime());
	const float delta_time = current_frame - last_frame_;
	last_frame_ = current_frame;
	const float velocity = delta_time * movement_speed_;

	glm::vec3 camera_position = camera.GetPosition();

	if (inputManager.IsKeyPressed(forward_key_)) {
		camera_position += camera.GetFrontDirection() * velocity;
	}
	if (inputManager.IsKeyPressed(backward_key_)) {
		camera_position += camera.GetFrontDirection() * -velocity;
	}
	if (inputManager.IsKeyPressed(right_key_)) {
		camera_position += camera.GetRightDirection() * velocity;
	}
	if (inputManager.IsKeyPressed(left_key_)) {
		camera_position += camera.GetRightDirection() * -velocity;
	}

	camera.SetPosition(camera_position);
}

void FirstPersonControls::ProcessMouseMove(const Input::InputManager& inputManager, GFX::Camera& camera) {
	Input::Position cursor_position = inputManager.GetCursorPosition();

	auto pos_x_f = static_cast<float>(cursor_position.x);
	auto pos_y_f = static_cast<float>(cursor_position.y);

	if (first_mouse_) {
		last_x_ = pos_x_f;
		last_y_ = pos_y_f;
		first_mouse_ = false;
	}

	float offset_x = (pos_x_f - last_x_) * mouse_sensitivity_;
	float offset_y = (last_y_ - pos_y_f) * mouse_sensitivity_; // reversed since y-coordinates range from bottom to top
	last_x_ = pos_x_f;
	last_y_ = pos_y_f;

	pitch_ += offset_y;
	yaw_   += offset_x;

	if (pitch_ > 89.0f)
		pitch_ =  89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;

	glm::vec3 front;
	front.x = cosf(glm::radians(yaw_)) * cosf(glm::radians(pitch_));
	front.y = sinf(glm::radians(pitch_));
	front.z = sinf(glm::radians(yaw_)) * cosf(glm::radians(pitch_));

	camera.SetFrontDirection(front);
}

void FirstPersonControls::ProcessScroll(const Input::InputManager& inputManager, GFX::Camera& camera) {
	Input::Position scroll_position = inputManager.GetScrollPosition();
	auto pos_y_f = static_cast<float>(scroll_position.y);
	const float new_fov = camera.GetFOV() - pos_y_f;

	if(new_fov >= 1.0f && new_fov <= 45.0f)
		camera.SetFOV(new_fov);
	else if(new_fov < 1.0f)
		camera.SetFOV(1.0f);
	else
		camera.SetFOV(45.0f);
}

}
}