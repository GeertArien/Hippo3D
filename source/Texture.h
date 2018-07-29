#ifndef HIPPO3D_TEXTURE_H
#define HIPPO3D_TEXTURE_H

#include <string>

namespace Hippo3D {

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


#endif //HIPPO3D_TEXTURE_H
