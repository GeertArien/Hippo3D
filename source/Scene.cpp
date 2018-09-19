#include "Scene.h"


namespace Mantis {

Scene::Scene(Camera& camera) : camera_(&camera)
{ }

void Scene::AddObject(const Object& object) {
	objects_.push_back(object);
}

void Scene::AddObject(Object&& object) {
	objects_.push_back(std::move(object));
}

}