#include "interface/input/InputManager.h"
#include "core/Renderer.h"
#include "interface/controls/FirstPersonControls.h"
#include "App.h"


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
		camera_(FOV, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), NEAR_CLIP_PLANE, FAR_CLIP_PLANE)
{
	camera_.SetPosition(glm::vec3(0.0f, 0.0f,  3.0f));
	camera_.SetOrientation(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));

	Input::InputManager input_manager(*window_);
	input_manager.DisableCursor();
//	input_manager.SetScrollCallback(OnMouseScroll);

	auto key = Input::Key::W;

	FirstPersonControls fp_controls;
	fp_controls.SetKey(FirstPersonControls::Movement::FORWARD, Input::Key::W);
	fp_controls.SetKey(FirstPersonControls::Movement::BACKWARD, Input::Key::S);
	fp_controls.SetKey(FirstPersonControls::Movement::RIGHT, Input::Key::D);
	fp_controls.SetKey(FirstPersonControls::Movement::LEFT, Input::Key::A);


	Object default_object;
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
		Object object = default_object;
		object.SetPosition(cube_position);
		scene_.AddObject(std::move(object));
	}

	Renderer renderer;

	renderer.Setup(scene_);

#if EMSCRIPTEN
	emscripten_set_main_loop_arg(testing, this, 60, 1);
#else
	while(!window_.ShouldClose()) {

		input_manager.ProcessInput();

		fp_controls.ProcessInput(input_manager, camera_);

		if (input_manager.IsKeyPressed(Input::Key::ESCAPE)) {
			window_.SetShouldClose(true);
			continue;
		}

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


//void App::OnMouseScroll(void* target, double pos_x, double pos_y) {
//	auto app = reinterpret_cast<App*>(target);
//	app->camera_.ProcessZoom(static_cast<float>(pos_y));
//}