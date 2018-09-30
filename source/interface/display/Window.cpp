#include "Window.h"
#include "core/Camera.h"
#include "GL_impl.h"
#include <stdexcept>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


namespace Mantis {

Window::Window(int width, int height, const std::string& title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ES_API);

	glfw_window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (glfw_window_ == nullptr)	{
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(glfw_window_);

#ifndef EMSCRIPTEN
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
#endif

	glfwSetWindowUserPointer(glfw_window_, this);
	glfwSetFramebufferSizeCallback(glfw_window_, FrameBufferSizeCallback);
}

void Window::FrameBufferSizeCallback(GLFWwindow*, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


}