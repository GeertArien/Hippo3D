#ifndef HIPPO3D_SHADER_H
#define HIPPO3D_SHADER_H

#include <string>

namespace Hippo3D {

	class ShaderProgram final {

	public:
		ShaderProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

		unsigned int GetID() const noexcept
		{ return ID_; }

	private:
		unsigned int ID_;

		unsigned int CreateShaderProgram(const char* vertex_shader_source, const char* fragment_shader_source) const;
		unsigned int CompileShader(const char* shader_source, unsigned int shader_type) const;

	};

}


#endif //HIPPO3D_SHADER_H
