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
		Renderer(ToolKit& tool_kit, Window& window, Scene& scene);

		void Render();
		void RenderPass() const;

	private:
		ToolKit* tool_kit_;
		Window* window_;
		Scene* scene_;
		std::map<unsigned int, unsigned int> vbo_map_;

	};

}