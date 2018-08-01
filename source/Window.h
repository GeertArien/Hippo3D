#ifndef HIPPO3D_WINDOW_H
#define HIPPO3D_WINDOW_H

#include <GLFW/glfw3.h>


namespace Hippo3D {

	class Window {

	public:
		Window(const int width, const int height, const char* title);

		void ProcessInput() const;

		bool ShouldClose() const
		{ return glfwWindowShouldClose(glfw_window_) > 0; };

		void SwapBuffers() const
		{ glfwSwapBuffers(glfw_window_); }

		GLFWwindow* operator*() const
		{ return glfw_window_; }

	private:
		GLFWwindow* glfw_window_;

		static void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);

	};

}


#endif //HIPPO3D_WINDOW_H
