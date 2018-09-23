#pragma once

#include <memory>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include "Mesh.h"
#include "Material.h"

namespace Mantis {

class Object final {

public:
	void SetMesh(std::initializer_list<Mesh::unit> vertice_data);
	void SetPosition(const glm::vec3& position);
	void SetRotation(float angle, const glm::vec3& axis);

	const Material& GetMaterial() const
	{ return material_; }
	const Mesh& GetMesh() const
	{ return *mesh_; }
	glm::vec3 GetPosition() const
	{ return position_; };
	float GetRotationAngle() const
	{ return rotation_angle_; };
	glm::vec3 GetRotationAxis() const
	{ return rotation_axis_; };
	glm::mat4 GetModelMatrix() const
	{ return model_matrix_; };

private:
	Material material_;
	std::shared_ptr<Mesh> mesh_;
	glm::vec3 position_ = glm::vec3(0.f);
	float rotation_angle_ = 0.f;
	glm::vec3 rotation_axis_ = glm::vec3(0.f);
	glm::mat4 model_matrix_ = glm::mat4(1.f);

	void UpdateModelMatrix();

};

}


