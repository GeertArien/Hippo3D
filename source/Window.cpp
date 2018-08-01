#include "Window.h"
#include <glad/glad.h>
#include <stdexcept>


namespace Hippo3D {

Window::Window(const int width, const int height, const char* title) {
	glfw_window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (glfw_window_ == nullptr)	{
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwSetFramebufferSizeCallback(glfw_window_, FrameBufferSizeCallback);
}

void Window::ProcessInput() const {
	if(glfwGetKey(glfw_window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(glfw_window_, true);
}

void Window::FrameBufferSizeCallback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


}