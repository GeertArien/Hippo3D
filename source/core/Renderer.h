#pragma once

#include <map>

//forward declarations
namespace Mantis {
	class Scene;
	class Camera;
}


namespace Mantis {

	class Renderer final {

	public:
		void Setup(Scene& scene);
		void TearDown();
		void Render(Scene& scene, Camera& camera) const;

	private:
		std::map<unsigned int, unsigned int> vbo_map_;

	};

}