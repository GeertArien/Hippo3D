#include "GL_impl.h"
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

#if EMSCRIPTEN
	Mantis::ToolKit tool_kit(2, 0, GLFW_OPENGL_ES_API);
#else
	Mantis::ToolKit tool_kit(2, 0, GLFW_OPENGL_ES_API);
#endif

	Mantis::Window window = tool_kit.CreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mantis");
	tool_kit.SetContext(window);
	tool_kit.LoadFunctionPointers();

	Mantis::Camera camera(45.f, static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.f);
	camera.SetPosition(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));
	//todo: this should probably be moved to renderer (settarget)
	camera.SetTarget(window);
	Mantis::Scene scene(camera);

	Mantis::Object default_object;
	default_object.SetMesh({
						   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
						   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
						   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
						   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

						   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
						   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
						   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
						   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

						   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

						   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						   0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

						   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
						   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

						   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
						   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
						   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
				   });

	std::array<glm::vec3, 10> cube_positions = {
			glm::vec3( 0.0f,  0.0f,  0.0f),
			glm::vec3( 2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3( 2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3( 1.3f, -2.0f, -2.5f),
			glm::vec3( 1.5f,  2.0f, -2.5f),
			glm::vec3( 1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (const auto& cube_position : cube_positions) {
		Mantis::Object object = default_object;
		object.SetPosition(cube_position);
		scene.AddObject(std::move(object));
	}

	Mantis::Renderer renderer(tool_kit, window, scene);
	renderer.Render();

	return 0;
}