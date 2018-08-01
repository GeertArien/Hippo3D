#include "ToolKit.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdexcept>


namespace Hippo3D {

ToolKit::ToolKit(const int version_major, const int version_minor, const int opengl_profile) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, opengl_profile);
}

ToolKit::~ToolKit() {
	glfwTerminate();
}

Window ToolKit::CreateWindow(const int width, const int height, const char* title) const {
	return Window(width, height, title);
}

void ToolKit::LoadFunctionPointers() const {
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}
}

}