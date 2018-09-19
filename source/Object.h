#pragma once

#include <vec3.hpp>
#include "Mesh.h"
#include "Material.h"

namespace Mantis {

class Object final {

public:
	void SetMesh(std::initializer_list<Mesh::unit> vertice_data);
	void SetPosition(const glm::vec3& position);

private:
	Mesh mesh_;
	Material material_;
	glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f);

};

}


