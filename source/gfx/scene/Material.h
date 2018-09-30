#pragma once

#include "Texture.h"

namespace Mantis {

	namespace GFX {

		class Material final {

		public:
			Material();

			explicit Material(const std::string& type);

			std::string GetShaderName() const { return shader_name_; }

		private:
			std::string shader_name_;
			//Texture texture_;

		};

	}
}