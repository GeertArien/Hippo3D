#include "App.h"
#include <array>

#if EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif


// settings
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const std::string WINDOW_TITLE = "Mantis";

const float FOV = 45.f;
const float NEAR_CLIP_PLANE = 0.1f;
const float FAR_CLIP_PLANE = 100.f;


using namespace Mantis;


App::App() :
		window_(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE),
		scene_(),
		camera_(FOV, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), NEAR_CLIP_PLANE, FAR_CLIP_PLANE),
		input_manager_(*window_)
{
	camera_.SetPosition(glm::vec3(0.0f, 0.0f,  3.0f));
	camera_.SetOrientation(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));

	input_manager_.DisableCursor();
//	input_manager.SetScrollCallback(OnMouseScroll);

	first_person_controls_.SetKey(Controls::FirstPersonControls::Movement::FORWARD, Input::Key::W);
	first_person_controls_.SetKey(Controls::FirstPersonControls::Movement::BACKWARD, Input::Key::S);
	first_person_controls_.SetKey(Controls::FirstPersonControls::Movement::RIGHT, Input::Key::D);
	first_person_controls_.SetKey(Controls::FirstPersonControls::Movement::LEFT, Input::Key::A);


	GFX::Object default_object;
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
		GFX::Object object = default_object;
		object.SetPosition(cube_position);
		scene_.AddObject(std::move(object));
	}

	renderer_.Setup(scene_);

#if EMSCRIPTEN
	emscripten_set_main_loop_arg(ExecuteMainLoop, this, 60, 1);
#else
	while(!window_.ShouldClose()) {
		MainLoop();
	}
#endif

	renderer_.TearDown();
}

void App::MainLoop(){
	input_manager_.ProcessInput();

	first_person_controls_.ProcessInput(input_manager_, camera_);

	if (input_manager_.IsKeyPressed(Input::Key::ESCAPE)) {
		window_.SetShouldClose(true);
		return;
	}

	// change rotations
	size_t i = 0;
	for (auto& object : scene_.GetObjects()) {
		const float angle = 20.0f * i++ + 10.f;
		object.SetRotation((float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	}

	renderer_.Render(scene_, camera_);
	window_.SwapBuffers();
}

#if EMSCRIPTEN
void App::ExecuteMainLoop(void* app_p) {
	auto app = reinterpret_cast<App*>(app_p);
	app->MainLoop();
}
#endif


//void App::OnMouseScroll(void* target, double pos_x, double pos_y) {
//	auto app = reinterpret_cast<App*>(target);
//	app->camera_.ProcessZoom(static_cast<float>(pos_y));
//}