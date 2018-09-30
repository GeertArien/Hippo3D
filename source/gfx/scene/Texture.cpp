#include "Texture.h"
#include <stdexcept>
#include "gfx/renderer/GL_impl.h"
#include <stb_image.h>

namespace Mantis {
namespace GFX {

Texture::Texture(const std::string& uri) : ID_(CreateTextureUnit(uri))
{ }

unsigned int Texture::CreateTextureUnit(const std::string& uri) const {
	unsigned int texture_index;
	glGenTextures(1, &texture_index);
	glBindTexture(GL_TEXTURE_2D, texture_index);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	int width, height, nr_channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(uri.c_str(), &width, &height, &nr_channels, 0);

	if (data) {
		unsigned int data_type = 0;

		if (nr_channels == 3) {
			data_type = GL_RGB;
		}
		else if (nr_channels == 4) {
			data_type = GL_RGBA;
		}
		else {
			throw std::runtime_error("Invalid data type for texture.");
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, data_type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		throw std::runtime_error("Failed to load texture");
	}

	stbi_image_free(data);
	return texture_index;
}

}
}