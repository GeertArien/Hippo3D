#pragma once

// forward declarations
namespace Mantis {
	class InputManager;
	class Camera;
}

namespace Mantis {

	class FirstPersonControls final {

	public:
		void ProcessInput(const Mantis::InputManager& inputManager, Mantis::Camera& camera);

	private:
		float last_frame_ = 0.f;
		float last_x_ = 0.f;
		float last_y_ = 0.f;
		bool first_mouse_ = true;
		bool first_scroll_ = true;
		float last_scroll_y_ = 0.f;

		void ProcessFPSMovement(const Mantis::InputManager& inputManager, Mantis::Camera& camera);
		void ProcessMouseMove(const Mantis::InputManager& inputManager, Mantis::Camera& camera);
		void ProcessScroll(const Mantis::InputManager& inputManager, Mantis::Camera& camera);

	};

}
