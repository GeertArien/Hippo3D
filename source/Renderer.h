#pragma once

//forward declarations
#include "ShaderProgram.h"

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


		ShaderProgram shader_program_;
		ToolKit* tool_kit_;
		Window* window_;
		Scene* scene_;

	};

}