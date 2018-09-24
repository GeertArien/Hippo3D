#pragma once

#include "Camera.h"
#include "Object.h"


namespace Mantis {

class Scene {

public:
	void AddObject(const Object& object);
	void AddObject(Object&& object);

	std::vector<Object>& GetObjects()
	{ return objects_; }

private:
	std::vector<Object> objects_;

};

}