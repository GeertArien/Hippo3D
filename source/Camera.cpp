#include "Camera.h"
#include "Window.h"

namespace Mantis {

Camera::Camera(float fov, float aspect_ratio, float near, float far)
	: fov_(fov), aspect_ratio_(aspect_ratio), near_(near), far_(far)
{ }

void Camera::SetTarget(Window& window) {
	target_ = &window;
	window.AttachCamera(*this);
}

void Camera::SetPosition(const glm::vec3& camera_pos, const glm::vec3& camera_front, const glm::vec3& camera_up) {
	camera_pos_ = camera_pos;
	camera_front_ = camera_front;
	camera_up_ = camera_up;
	world_up = camera_up;
	camera_right_ = glm::normalize(glm::cross(camera_front_, world_up));
}

void Camera::ProcessMovement(const Movement& movement, float delta_time) {
	float velocity = MOVEMENT_SPEED_ * delta_time;
	if (movement == Movement::FORWARD)
		camera_pos_ += camera_front_ * velocity;
	if (movement == Movement::BACKWARD)
		camera_pos_ -= camera_front_ * velocity;
	if (movement == Movement::LEFT)
		camera_pos_ -= camera_right_ * velocity;
	if (movement == Movement::RIGHT)
		camera_pos_ += camera_right_ * velocity;
}

void Camera::ProcessMouseMovement(float offset_x, float offset_y) {
	offset_x *= MOUSE_SENSITIVITY;
	offset_y *= MOUSE_SENSITIVITY;

	pitch_ += offset_y;
	yaw_   += offset_x;

	if (pitch_ > 89.0f)
		pitch_ =  89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;

	UpdateCameraVectors();
}

void Camera::ProcessZoom(float offset) {
	if(fov_ >= 1.0f && fov_ <= 45.0f)
		fov_ -= offset;
	if(fov_ <= 1.0f)
		fov_ = 1.0f;
	if(fov_ >= 45.0f)
		fov_ = 45.0f;
}

void Camera::UpdateCameraVectors() {
	glm::vec3 front;
	front.x = cosf(glm::radians(yaw_)) * cosf(glm::radians(pitch_));
	front.y = sinf(glm::radians(pitch_));
	front.z = sinf(glm::radians(yaw_)) * cosf(glm::radians(pitch_));
	camera_front_ = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	camera_right_ = glm::normalize(glm::cross(camera_front_, world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	camera_up_ = glm::normalize(glm::cross(camera_right_, camera_front_));
}

}