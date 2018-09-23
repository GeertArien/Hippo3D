#pragma once

#include "Camera.h"
#include "Object.h"


namespace Mantis {

class Scene {

public:
	Scene(Camera& camera);

	Camera& GetCamera() noexcept
	{ return *camera_; }

	void AddObject(const Object& object);
	void AddObject(Object&& object);

	std::vector<Object>& GetObjects()
	{ return objects_; }

private:
	Camera* camera_;
	std::vector<Object> objects_;

};

}