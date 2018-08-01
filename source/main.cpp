#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include <stb_image.h>

#include "ToolKit.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Renderer.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	Hippo3D::ToolKit tool_kit(3, 3, GLFW_OPENGL_CORE_PROFILE);
	Hippo3D::Window window = tool_kit.CreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hippo3D");
	tool_kit.SetContext(window);
	tool_kit.LoadFunctionPointers();

	Hippo3D::Renderer renderer(tool_kit, window);
	renderer.Render();

	return 0;
}