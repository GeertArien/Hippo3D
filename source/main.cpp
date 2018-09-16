#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include <stb_image.h>

#include "ToolKit.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {

	//todo: use unique pointer for window and camera etc

	Mantis::ToolKit tool_kit(3, 3, GLFW_OPENGL_CORE_PROFILE);
	Mantis::Window window = tool_kit.CreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mantis");
	tool_kit.SetContext(window);
	tool_kit.LoadFunctionPointers();

	Mantis::Camera camera(45.f, static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.f);
	camera.SetPosition(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));
	camera.SetTarget(window);
	Mantis::Scene scene(camera);

	Mantis::Renderer renderer(tool_kit, window, scene);
	renderer.Render();

	return 0;
}