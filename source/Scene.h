#pragma once

#include "Camera.h"
#include "Object.h"


namespace Mantis {

class Scene {

public:
	Scene(Camera& camera);

	const Camera& GetCamera() const noexcept
	{ return *camera_; }

	void AddObject(const Object& object);
	void AddObject(Object&& object);

private:
	Camera* camera_;
	std::vector<Object> objects_;

};

}