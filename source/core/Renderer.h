#pragma once

#include <map>

//forward declarations
namespace Mantis {
	class Scene;
	class ToolKit;
	class Window;
}


namespace Mantis {

	class Renderer final {

	public:
		Renderer(Window& window, Scene& scene);

		void Setup();
		void TearDown();
		void Render();
		void BeforeRenderPass();
		void RenderPass() const;

	private:
		Window* window_;
		Scene* scene_;
		std::map<unsigned int, unsigned int> vbo_map_;

	};

}