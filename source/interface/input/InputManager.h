#pragma once

#include <functional>
#include <map>
#include <GLFW/glfw3.h>
#include "Key.h"


namespace Mantis {

	namespace Input {

		struct Position {
			double x = 0.;
			double y = 0.;
		};

		class InputManager final {

		public:
			explicit InputManager(GLFWwindow* glfw_window);

			void ProcessInput() {
				scroll_position_.x = 0.;
				scroll_position_.y = 0.;
				glfwPollEvents();
			}

			void DisableCursor() const { glfwSetInputMode(glfw_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }

			void SetCallbackTarget(void* callback_target);

			void SetKeyPressCallback(const std::function<void(void*, int)>& on_key_press);

			void SetMouseMoveCallback(const std::function<void(void*, double, double)>& on_mouse_move);

			void SetScrollCallback(const std::function<void(void*, double, double)>& on_mouse_scroll);

			bool IsKeyPressed(Key key) const { return (glfwGetKey(glfw_window_, static_cast<int>(key)) == GLFW_PRESS); }

			Position GetCursorPosition() const {
				Position position;
				glfwGetCursorPos(glfw_window_, &position.x, &position.y);
				return position;
			}

			Position GetScrollPosition() const { return scroll_position_; }

		private:
			GLFWwindow* glfw_window_ = nullptr;

			void* callback_target_ = nullptr;
			std::function<void(void*, int)> on_key_press_ = nullptr;
			std::function<void(void*, double, double)> on_mouse_move_ = nullptr;
			std::function<void(void*, double, double)> on_scroll_ = nullptr;

			Position scroll_position_;

			static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

			static void MouseCallback(GLFWwindow* glfw_window, double pos_x, double pos_y);

			static void ScrollCallback(GLFWwindow* glfw_window, double, double offset_y);

		};

	}

}

