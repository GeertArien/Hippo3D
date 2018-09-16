#pragma once

#include "Camera.h"


namespace Mantis {

class Scene {

public:
	Scene(Camera& camera);

	const Camera& GetCamera() const noexcept
	{ return *camera_; }

private:
	Camera* camera_;

};

}