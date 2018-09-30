#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


// forward declarations
namespace Mantis {
	class Window;
}


namespace Mantis {

	namespace GFX {

		class Camera final {

		public:
			Camera(float fov, float aspect_ratio, float near, float far);

			float SetFOV(const float fov) { fov_ = fov; }

			void SetPosition(const glm::vec3& position);

			void SetOrientation(const glm::vec3& front_dir, const glm::vec3& world_up_dir);

			void SetFrontDirection(const glm::vec3& front_dir);

			float GetFOV() const { return fov_; }

			glm::vec3 GetFrontDirection() const { return front_dir_; }

			glm::vec3 GetRightDirection() const { return right_dir_; }

			glm::vec3 GetPosition() const { return position_; }

			glm::mat4 GetProjectionMatrix() const {
				return glm::perspective(glm::radians(fov_), aspect_ratio_, near_, far_);
			}

			glm::mat4 GetViewMatrix() const { return glm::lookAt(position_, position_ + front_dir_, up_dir_); }

		private:
			glm::vec3 position_ = glm::vec3(0.f, 0.f, 0.f);
			glm::vec3 front_dir_ = glm::vec3(0.f, 0.f, -1.f);
			glm::vec3 up_dir_ = glm::vec3(0.f, 1.f, 0.f);
			glm::vec3 world_up_dir_ = glm::vec3(0.f, 1.f, 0.f);
			glm::vec3 right_dir_ = glm::vec3(1.f, 0.f, 0.f);

			float fov_ = 0.f;
			float aspect_ratio_ = 0.f;
			float near_ = 0.f;
			float far_ = 0.f;

		};

	}
}