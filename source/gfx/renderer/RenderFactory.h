#pragma once

#include <string>


namespace Mantis {

	namespace GFX {

		class RenderFactory {

		public:
			static unsigned int InitShader(const std::string& name);

		private:
			static unsigned int CreateShaderProgram(const char* vertex_shader_source, const char* fragment_shader_source);
			static unsigned int CompileShader(const char* shader_source, unsigned int shader_type);

		};

	}
}
