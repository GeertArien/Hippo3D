#pragma once

#include <map>

//forward declarations
namespace Mantis {
	class Scene;
	class Camera;
	class Window;
}


namespace Mantis {

	class Renderer final {

	public:
		void Setup(Scene& scene);
		void TearDown();
		void Render(Scene& scene, Camera& camera, Window& window);
		void BeforeRenderPass(Scene& scene, Window& window);
		void RenderPass(Scene& scene, Camera& camera, Window& window) const;

	private:
		std::map<unsigned int, unsigned int> vbo_map_;

	};

}