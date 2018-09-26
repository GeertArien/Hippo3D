#include "InputManager.h"

namespace Mantis {

InputManager::InputManager(GLFWwindow* glfw_window) {
	//todo: this should be window!
	glfwSetWindowUserPointer(glfw_window, this);
	glfwSetKeyCallback(glfw_window, KeyCallBack);
	glfwSetCursorPosCallback(glfw_window, MouseCallback);
	glfwSetScrollCallback(glfw_window, MouseScrollCallback);
}

void InputManager::SetCallbackTarget(void* callback_target) {
	callback_target_ = callback_target;
}

void InputManager::KeyCallBack(GLFWwindow* glfw_window, int key, int /*scancode*/, int action, int /*mods*/) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));
		input_manager->on_key_press_(input_manager->callback_target_, key);
	}
}

void InputManager::MouseCallback(GLFWwindow* glfw_window, double pos_x, double pos_y) {
	auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));
	input_manager->on_mouse_move_(input_manager->callback_target_, pos_x, pos_y);
}

void InputManager::MouseScrollCallback(GLFWwindow* glfw_window, double pos_x, double pos_y) {
	auto input_manager = static_cast<InputManager*>(glfwGetWindowUserPointer(glfw_window));
	input_manager->on_mouse_scroll_(input_manager->callback_target_, pos_x, pos_y);
}

}