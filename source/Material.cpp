#include "Material.h"

namespace Mantis {

Material::Material() : shader_("flat")
{ }

Material::Material(const std::string& type) : shader_(type)
{ }

}