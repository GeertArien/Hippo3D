#include "InputManager.h"

namespace Mantis {

InputManager::InputManager(GLFWwindow* glfw_window) : glfw_window_(glfw_window) {
	//todo: this should be window!
	glfwSetWindowUserPointer(glfw_window, this);
	glfwSetScrollCallback(glfw_window, ScrollCallback);
}

void InputManager::SetCallbackTarget(void* callback_target) {
	callback_target_ = callback_target;
}

void InputManager::SetKeyPressCallback(const std::function<void(void*, int)>& on_key_press) {
	on_key_press_ = on_key_press;
	glfwSetKeyCallback(glfw_window_, KeyCallBack);
}

void InputManager::SetMouseMoveCallback(const std::function<void(void*, double, double)>& on_mouse_move) {
	on_mouse_move_ = on_mouse_move;
	glfwSetCursorPosCallback(glfw_window_, MouseCallback);
}

void InputManager::SetScrollCallback(const std::function<void(void*, double, double)>& on_scroll) {
	on_scroll_ = on_scroll;
}

void InputManager::KeyCallBack(GLFWwindow* glfw_window, int key, int /*scancode*/, int action, int /*mods*/) {
	if (action == GLFW_PRESS) {
		auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));
		input_manager->on_key_press_(input_manager->callback_target_, key);
	}
}

void InputManager::MouseCallback(GLFWwindow* glfw_window, double pos_x, double pos_y) {
	auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));
	input_manager->on_mouse_move_(input_manager->callback_target_, pos_x, pos_y);
}

void InputManager::ScrollCallback(GLFWwindow* glfw_window, double pos_x, double pos_y) {
	auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));
	input_manager->scroll_position_.x = pos_x;
	input_manager->scroll_position_.y = pos_y;

	if (input_manager->on_scroll_ != nullptr) {
		input_manager->on_scroll_(input_manager->callback_target_, pos_x, pos_y);
	}
}

}