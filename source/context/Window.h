#pragma once

#include <string>
#include <GLFW/glfw3.h>

namespace Mantis {

	class Window final {

	public:
		Window(int width, int height, const std::string& title);

		void ProcessInput();

		bool ShouldClose() const
		{ return glfwWindowShouldClose(glfw_window_) > 0; };

		void SwapBuffers() const
		{ glfwSwapBuffers(glfw_window_); }

		GLFWwindow* operator*() const
		{ return glfw_window_; }

	private:
		GLFWwindow* glfw_window_;

		static void FrameBufferSizeCallback(GLFWwindow*, int width, int height);


	};

}