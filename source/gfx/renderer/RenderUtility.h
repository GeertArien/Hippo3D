#pragma once

#include <string>
#include <detail/type_mat.hpp>
#include <ext.hpp>
#include <gfx/renderer/GL_impl.h>


namespace Mantis {

	namespace GFX {

		void SetUniform(const unsigned int program, const std::string& name, const unsigned int value) {
			glUniform1i(glGetUniformLocation(program, name.c_str()), value);
		}

		void SetUniform(const unsigned int program, const std::string& name, const glm::mat4& matrix) {
			glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
		}

	}
}
