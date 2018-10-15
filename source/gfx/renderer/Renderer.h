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

		struct uniform_block {
			unsigned int id;
			unsigned int base;
		};

		class Renderer final {

		public:
			void Setup(Scene& scene);
			void TearDown();
			void Render(Scene& scene, Camera& camera) const;

		private:
			std::map<unsigned int, unsigned int> vao_map_;
			std::map<std::string, unsigned int> shader_map_;
			std::map<std::string, uniform_block> uniform_block_map_;
			unsigned int matrices;

		};

	}

}