#pragma once

#include "../input/Key.h"


// forward declarations
namespace Mantis {
	class Camera;
	namespace Input {
		class InputManager;
	}
}


namespace Mantis {

	class FirstPersonControls final {

	public:
		enum class Movement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

		void SetKey(const Movement& movement, Input::Key key);
		void ProcessInput(const Input::InputManager& inputManager, Mantis::Camera& camera);

	private:
		float movement_speed_ = 2.5f;
		float mouse_sensitivity_ = 0.25f;
		Input::Key forward_key_ = Input::Key::INVALID;
		Input::Key backward_key_ = Input::Key::INVALID;
		Input::Key right_key_ = Input::Key::INVALID;
		Input::Key left_key_ = Input::Key::INVALID;

		float pitch_ = 0.f;
		float yaw_ = -90.f;

		float last_frame_ = 0.f;
		float last_x_ = 0.f;
		float last_y_ = 0.f;
		bool first_mouse_ = true;


		void ProcessFPSMovement(const Input::InputManager& inputManager, Mantis::Camera& camera);
		void ProcessMouseMove(const Input::InputManager& inputManager, Mantis::Camera& camera);
		void ProcessScroll(const Input::InputManager& inputManager, Mantis::Camera& camera);

	};

}
