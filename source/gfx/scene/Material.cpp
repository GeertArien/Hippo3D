#include "Material.h"

namespace Mantis {
namespace GFX {

Material::Material() : shader_name_("flat")
{ }

Material::Material(const std::string& type) : shader_name_(type)
{ }

}
}