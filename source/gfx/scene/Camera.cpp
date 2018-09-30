#include "Camera.h"

namespace Mantis {

namespace GFX {

Camera::Camera(float fov, float aspect_ratio, float near, float far)
	: fov_(fov), aspect_ratio_(aspect_ratio), near_(near), far_(far)
{ }

void Camera::SetPosition(const glm::vec3& position) {
	position_ = position;
}

void Camera::SetOrientation(const glm::vec3& front_dir, const glm::vec3& world_up_dir) {
	front_dir_ = front_dir;
	world_up_dir_ = world_up_dir;
	right_dir_ = glm::normalize(glm::cross(front_dir_, world_up_dir_));
	up_dir_ = glm::normalize(glm::cross(right_dir_, front_dir_));
}

void Camera::SetFrontDirection(const glm::vec3& front_dir) {
	front_dir_ = glm::normalize(front_dir);
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	right_dir_ = glm::normalize(glm::cross(front_dir_, world_up_dir_));
	up_dir_ = glm::normalize(glm::cross(right_dir_, front_dir_));
}

}
}