#include "GL_impl.h"
#include <iostream>
#include <cmath>
#include <stb_image.h>

#include "core/ShaderProgram.h"
#include "core/Texture.h"
#include "core/Renderer.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "context/Window.h"
#include "context/InputManager.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {

	Mantis::Window window(SCR_WIDTH, SCR_HEIGHT, "Mantis");

	Mantis::Camera camera(45.f, static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.f);
	camera.SetPosition(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));
	//todo: this should probably be moved to renderer (settarget)
	window.AttachCamera(camera);
	Mantis::Scene scene(camera);

	Mantis::InputManager input_manager(*window);
	input_manager.on_mouse_move_ = std::bind( &Mantis::Camera::ProcessMouseMovement, &camera,
			std::placeholders::_1,
			std::placeholders::_2 );
	input_manager.on_mouse_scroll_ = std::bind( &Mantis::Camera::ProcessZoom, &camera, std::placeholders::_1);
	input_manager.key_callbacks_[GLFW_KEY_W] = std::bind( &Mantis::Camera::ProcessMovement, &camera,
														  Mantis::Camera::Movement::FORWARD,
														  std::placeholders::_1);
	input_manager.key_callbacks_[GLFW_KEY_S] = std::bind( &Mantis::Camera::ProcessMovement, &camera,
														  Mantis::Camera::Movement::BACKWARD,
														  std::placeholders::_1);
	input_manager.key_callbacks_[GLFW_KEY_A] = std::bind( &Mantis::Camera::ProcessMovement, &camera,
														  Mantis::Camera::Movement::LEFT,
														  std::placeholders::_1);
	input_manager.key_callbacks_[GLFW_KEY_D] = std::bind( &Mantis::Camera::ProcessMovement, &camera,
														  Mantis::Camera::Movement::RIGHT,
														  std::placeholders::_1);

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

	Mantis::Renderer renderer(window, scene);
	renderer.Render();

	return 0;
}