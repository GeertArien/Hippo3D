#pragma once

#include <map>

//forward declarations
namespace Mantis {
	namespace GFX {
		class Scene;
		class Camera;
	}
}


namespace Mantis {

	namespace GFX {

		class Renderer final {

		public:
			void Setup(Scene& scene);
			void TearDown();
			void Render(Scene& scene, Camera& camera) const;

		private:
			std::map<unsigned int, unsigned int> vbo_map_;
			std::map<std::string, unsigned int> shader_map_;

		};

	}

}