#include "InputManager.h"

namespace Mantis {

InputManager::InputManager(GLFWwindow* glfw_window) {
	//todo: this should be window!
	glfwSetWindowUserPointer(glfw_window, this);
	glfwSetKeyCallback(glfw_window, KeyCallBack);
	glfwSetCursorPosCallback(glfw_window, MouseCallback);
	glfwSetScrollCallback(glfw_window, ScrollCallback);
}

void InputManager::KeyCallBack(GLFWwindow* glfw_window, int key, int scancode, int action, int mods) {
	auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));
	auto current_frame = static_cast<float>(glfwGetTime());
	float delta_time = current_frame - input_manager->last_frame_;
	input_manager->last_frame_ = current_frame;

	const auto& it = input_manager->key_callbacks_.find(key);

	if (it != input_manager->key_callbacks_.end()) {
		it->second(delta_time);
	}
}

void InputManager::MouseCallback(GLFWwindow* glfw_window, double pos_x, double pos_y) {
	auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));

	auto pos_x_f = static_cast<float>(pos_x);
	auto pos_y_f = static_cast<float>(pos_y);

	if(input_manager->first_mouse_) {
		input_manager->last_x_ = pos_x_f;
		input_manager->last_y_ = pos_y_f;
		input_manager->first_mouse_ = false;
	}

	float offset_x = pos_x_f - input_manager->last_x_;
	float offset_y = input_manager->last_y_ - pos_y_f; // reversed since y-coordinates range from bottom to top
	input_manager->last_x_ = pos_x_f;
	input_manager->last_y_ = pos_y_f;

	input_manager->on_mouse_move_(offset_x, offset_y);
}

void InputManager::ScrollCallback(GLFWwindow* glfw_window, double, double offset_y) {
	auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));
	input_manager->on_mouse_scroll_(static_cast<float>(offset_y));
}

}