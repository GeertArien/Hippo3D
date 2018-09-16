#ifndef Mantis_SCENE_H
#define Mantis_SCENE_H

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


#endif //Mantis_SCENE_H
