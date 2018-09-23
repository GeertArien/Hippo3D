#pragma once

#include <GLFW/glfw3.h>


namespace Mantis {
	class Camera;
}


namespace Mantis {

	class Window final {

	public:
		Window(int width, int height, const char* title);

		void AttachCamera(Camera& camera); // replace with observable pattern?
		void ProcessInput();

		bool ShouldClose() const
		{ return glfwWindowShouldClose(glfw_window_) > 0; };

		void SwapBuffers() const
		{ glfwSwapBuffers(glfw_window_); }

		GLFWwindow* operator*() const
		{ return glfw_window_; }

	private:
		GLFWwindow* glfw_window_;
		Camera* camera_;

		float last_frame_ = 0.f;

		static void FrameBufferSizeCallback(GLFWwindow*, int width, int height);


	};

}