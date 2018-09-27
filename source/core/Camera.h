#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


// forward declarations
namespace Mantis {
	class Window;
}


namespace Mantis {

	class Camera {

	public:
		enum class Movement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

		Camera(float fov, float aspect_ratio, float near, float far);

		void SetPosition(const glm::vec3& camera_pos, const glm::vec3& camera_front, const glm::vec3& camera_up);
		void ProcessMovement(const Movement& movement, float delta_time);
		void ProcessMouseMovement(float offset_x, float offset_y);
		void ProcessZoom(float offset);

		glm::mat4 GetProjectionMatrix() const
		{ return glm::perspective(glm::radians(fov_), aspect_ratio_, near_, far_); }

		glm::mat4 GetViewMatrix() const
		{ return glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_); }

	private:

		constexpr static float MOVEMENT_SPEED_ = 2.5f;
		constexpr static float MOUSE_SENSITIVITY = 0.15f;

		glm::vec3 camera_pos_ = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 camera_front_ = glm::vec3(0.f, 0.f, -1.f);
		glm::vec3 camera_up_ = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 world_up = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 camera_right_ = glm::vec3(1.f, 0.f, 0.f);

		float fov_;
		float aspect_ratio_;
		float near_;
		float far_;

		float pitch_ = 0.f;
		float yaw_ = -90.f;

		void UpdateCameraVectors();

	};

}