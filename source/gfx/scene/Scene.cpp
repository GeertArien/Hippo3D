#include "Scene.h"


namespace Mantis {
namespace GFX {

void Scene::AddObject(const Object& object) {
	objects_.push_back(object);
}

void Scene::AddObject(Object&& object) {
	objects_.push_back(std::move(object));
}

}
}