#include "Mesh.h"

namespace Mantis {

Mesh::Mesh(const std::vector<float>& vertice_data) : vertice_data_(vertice_data)
{ }

Mesh::Mesh(std::vector<float>&& vertice_data) : vertice_data_(std::move(vertice_data))
{ }

Mesh::Mesh(std::initializer_list<float> vertice_data) : vertice_data_(vertice_data)
{ }

}
