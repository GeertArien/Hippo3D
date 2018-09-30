#pragma once

#include <string>


namespace Mantis {

	namespace GFX {

		class Texture final {

		public:
			Texture(const std::string& uri);

			unsigned int GetID() const noexcept { return ID_; }

		private:
			unsigned int ID_;

			unsigned int CreateTextureUnit(const std::string& uri) const;

		};

	}
}