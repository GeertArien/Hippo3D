#ifndef HIPPO3D_SHADER_H
#define HIPPO3D_SHADER_H

#include <string>
#include <detail/type_mat.hpp>

namespace Hippo3D {

	class ShaderProgram final {

	public:
		ShaderProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

		void SetUniform(const std::string& name, const unsigned int value) const ;
		void SetUniform(const std::string& name, const glm::mat4& matrix) const;

		unsigned int GetID() const noexcept
		{ return ID_; }

	private:
		unsigned int ID_;

		unsigned int CreateShaderProgram(const char* vertex_shader_source, const char* fragment_shader_source) const;
		unsigned int CompileShader(const char* shader_source, unsigned int shader_type) const;

	};

}


#endif //HIPPO3D_SHADER_H
