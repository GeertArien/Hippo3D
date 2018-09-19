#pragma once

#include <string>
#include <detail/type_mat.hpp>

namespace Mantis {

	class ShaderProgram final {

	public:
		ShaderProgram(const std::string& name);

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