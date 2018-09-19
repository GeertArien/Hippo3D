#include "Object.h"

namespace Mantis {

void Object::SetMesh(std::initializer_list<Mesh::unit> vertice_data) {
	mesh_ = Mesh(vertice_data);
}

void Object::SetPosition(const glm::vec3& position) {
	position_ = position;
}

}