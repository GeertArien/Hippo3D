#include "Window.h"
#include "Camera.h"
#include <glad/glad.h>
#include <stdexcept>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


namespace Hippo3D {

Window::Window(const int width, const int height, const char* title) {
	glfw_window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (glfw_window_ == nullptr)	{
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwSetWindowUserPointer(glfw_window_, this);

	glfwSetFramebufferSizeCallback(glfw_window_, FrameBufferSizeCallback);
	glfwSetInputMode(glfw_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfw_window_, MouseCallback);
}

void Window::AttachCamera(Hippo3D::Camera& camera) {
	camera_ = &camera;
}

void Window::ProcessInput() {
	if(glfwGetKey(glfw_window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(glfw_window_, true);

	auto current_frame = static_cast<float>(glfwGetTime());
	float delta_time = current_frame - last_frame_;
	last_frame_ = current_frame;

	if (glfwGetKey(glfw_window_, GLFW_KEY_W) == GLFW_PRESS)
		camera_->ProcessMovement(Camera::Movement::FORWARD, delta_time);
	if (glfwGetKey(glfw_window_, GLFW_KEY_S) == GLFW_PRESS)
		camera_->ProcessMovement(Camera::Movement::BACKWARD, delta_time);
	if (glfwGetKey(glfw_window_, GLFW_KEY_A) == GLFW_PRESS)
		camera_->ProcessMovement(Camera::Movement::LEFT, delta_time);
	if (glfwGetKey(glfw_window_, GLFW_KEY_D) == GLFW_PRESS)
		camera_->ProcessMovement(Camera::Movement::RIGHT, delta_time);
}

void Window::MouseCallback(GLFWwindow* glfw_window, double xpos, double ypos) {
	auto window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));

	auto pos_x_f = static_cast<float>(xpos);
	auto pos_y_f = static_cast<float>(ypos);

	if(window->first_mouse_) {
		window->last_x_ = pos_x_f;
		window->last_y_ = pos_y_f;
		window->first_mouse_ = false;
	}

	float offset_x = pos_x_f - window->last_x_;
	float offset_y = window->last_y_ - pos_y_f; // reversed since y-coordinates range from bottom to top
	window->last_x_ = pos_x_f;
	window->last_y_ = pos_y_f;

	window->camera_->ProcessMouseMovement(offset_x, offset_y);
}

void Window::FrameBufferSizeCallback(GLFWwindow*, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


}