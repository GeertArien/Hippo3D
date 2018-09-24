#include <context/InputManager.h>
#include <core/Renderer.h>
#include "App.h"

// settings
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const std::string WINDOW_TITLE = "Mantis";

const float FOV = 45.f;
const float NEAR_CLIP_PLANE = 0.1f;
const float FAR_CLIP_PLANE = 100.f;

App::App() :
		window_(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE),
		scene_(),
		camera_(FOV, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), NEAR_CLIP_PLANE, FAR_CLIP_PLANE)
{
	camera_.SetPosition(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));

	Mantis::InputManager input_manager(*window_);
	input_manager.SetCallbackTarget(this);
	input_manager.on_key_press_ = OnKeyPress;
	input_manager.on_mouse_move_ = OnMouseMove;
	input_manager.on_mouse_scroll_ = OnMouseScroll;

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
		scene_.AddObject(std::move(object));
	}

	Mantis::Renderer renderer;
	renderer.Render(scene_, camera_, window_);
}

void App::OnKeyPress(void* target, int key, float delta_time) {
	auto app = reinterpret_cast<App*>(target);

	if (key == GLFW_KEY_W) {
		app->camera_.ProcessMovement(Mantis::Camera::Movement::FORWARD, delta_time);
	}
	else if (key == GLFW_KEY_S) {
		app->camera_.ProcessMovement(Mantis::Camera::Movement::BACKWARD, delta_time);
	}
	else if (key == GLFW_KEY_A) {
		app->camera_.ProcessMovement(Mantis::Camera::Movement::LEFT, delta_time);
	}
	else if (key == GLFW_KEY_D) {
		app->camera_.ProcessMovement(Mantis::Camera::Movement::RIGHT, delta_time);
	}
}

void App::OnMouseMove(void* target, float offset_x, float offset_y) {
	auto app = reinterpret_cast<App*>(target);
	app->camera_.ProcessMouseMovement(offset_x, offset_y);
}

void App::OnMouseScroll(void* target, float offset) {
	auto app = reinterpret_cast<App*>(target);
	app->camera_.ProcessZoom(offset);
}