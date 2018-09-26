#pragma once

#include <functional>
#include <map>
#include <GLFW/glfw3.h>

namespace Mantis {

	class InputManager final {

	public:
		explicit InputManager(GLFWwindow* glfw_window);

		void SetCallbackTarget(void* callback_target);

		std::function<void(void*, int)> on_key_press_ = nullptr;
		std::function<void(void*, double, double)> on_mouse_move_ = nullptr;
		std::function<void(void*, double, double)> on_mouse_scroll_ = nullptr;

	private:
		void* callback_target_ = nullptr;

		static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* glfw_window, double pos_x, double pos_y);
		static void MouseScrollCallback(GLFWwindow* glfw_window, double, double offset_y);

	};

}

