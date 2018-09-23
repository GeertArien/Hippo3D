#include <gtc/matrix_transform.hpp>
#include "Object.h"

namespace Mantis {

void Object::SetMesh(std::initializer_list<Mesh::unit> vertice_data) {
	mesh_ = std::make_shared<Mesh>(vertice_data);
}

void Object::SetPosition(const glm::vec3& position) {
	position_ = position;
	UpdateModelMatrix();
}

void Object::SetRotation(float angle, const glm::vec3& axis) {
	rotation_angle_ = angle;
	rotation_axis_ = axis;
	UpdateModelMatrix();
}

void Object::UpdateModelMatrix() {
	model_matrix_ = glm::mat4(1.f);
	model_matrix_ = glm::translate(model_matrix_, position_);
	model_matrix_ = glm::rotate(model_matrix_, rotation_angle_, rotation_axis_);
}

}