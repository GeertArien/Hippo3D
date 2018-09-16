#ifndef Mantis_TEXTURE_H
#define Mantis_TEXTURE_H

#include <string>

namespace Mantis {

	class Texture final {

	public:
		Texture(const std::string& uri);

		unsigned int GetID() const noexcept
		{ return ID_; }

	private:
		unsigned int ID_;

		unsigned int CreateTextureUnit(const std::string& uri) const;

	};

}


#endif //Mantis_TEXTURE_H
