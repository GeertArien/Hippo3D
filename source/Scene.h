#ifndef HIPPO3D_SCENE_H
#define HIPPO3D_SCENE_H

#include "Camera.h"


namespace Hippo3D {

class Scene {

public:
	Scene(Camera& camera);

	const Camera& GetCamera() const noexcept
	{ return *camera_; }

private:
	Camera* camera_;

};

}


#endif //HIPPO3D_SCENE_H
