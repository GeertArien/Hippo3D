#include <interface/InputManager.h>
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

	renderer.Setup(scene_);

#if EMSCRIPTEN
	emscripten_set_main_loop_arg(testing, this, 60, 1);
#else
	while(!window_.ShouldClose()) {

		window_.ProcessInput();
		last_frame_ = static_cast<float>(glfwGetTime());

		// change rotations
		size_t i = 0;
		for (auto& object : scene_.GetObjects()) {
			const float angle = 20.0f * i++ + 10.f;
			object.SetRotation((float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		}

		renderer.Render(scene_, camera_);
		window_.SwapBuffers();
	}
#endif

	renderer.TearDown();
}

void App::OnKeyPress(void* target, int key) {
	auto app = reinterpret_cast<App*>(target);

	float current_frame = static_cast<float>(glfwGetTime());
	float delta_time = current_frame - app->last_frame_;
	app->last_frame_ = current_frame;

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
	else if (key == GLFW_KEY_ESCAPE) {
		app->window_.SetShouldClose(true);
	}
}

void App::OnMouseMove(void* target, double pos_x, double pos_y) {
	auto app = reinterpret_cast<App*>(target);

	auto pos_x_f = static_cast<float>(pos_x);
	auto pos_y_f = static_cast<float>(pos_y);

	if(app->first_mouse_) {
		app->last_x_ = pos_x_f;
		app->last_y_ = pos_y_f;
		app->first_mouse_ = false;
	}

	float offset_x = pos_x_f - app->last_x_;
	float offset_y = app->last_y_ - pos_y_f; // reversed since y-coordinates range from bottom to top
	app->last_x_ = pos_x_f;
	app->last_y_ = pos_y_f;

	app->camera_.ProcessMouseMovement(offset_x, offset_y);
}

void App::OnMouseScroll(void* target, double pos_x, double pos_y) {
	auto app = reinterpret_cast<App*>(target);
	app->camera_.ProcessZoom(static_cast<float>(pos_y));
}