#pragma once

#include <functional>
#include <map>
#include <GLFW/glfw3.h>

namespace Mantis {

	class InputManager final {

	public:
		explicit InputManager(GLFWwindow* glfw_window);
		std::map<int, std::function<void(float)>> key_callbacks_;
		std::function<void(float, float)> on_mouse_move_ = nullptr;
		std::function<void(float)> on_mouse_scroll_ = nullptr;

	private:
		float last_frame_ = 0.f;
		float last_x_ = 0.f;
		float last_y_ = 0.f;
		bool first_mouse_ = true;


		static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* glfw_window, double pos_x, double pos_y);
		static void ScrollCallback(GLFWwindow* glfw_window, double, double offset_y);

	};

}

