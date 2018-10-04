#include "RenderFactory.h"
#include "gfx/shaders/shaders.h"
#include "GL_impl.h"


namespace Mantis {
namespace GFX {

unsigned int RenderFactory::InitShader(const std::string& name) {
	std::string vertex_shader, fragment_shader;
	try {
		vertex_shader = VERTEX_SHADERS.at(name);
	}
	catch (const std::out_of_range&) {
		throw std::runtime_error("Invalid vertex shader name: " + name);
	}

	try {
		fragment_shader = FRAGMENT_SHADERS.at(name);
	}
	catch (const std::out_of_range&) {
		throw std::runtime_error("Invalid fragment shader name: " + name);
	}

	return CreateShaderProgram(vertex_shader.c_str(), fragment_shader.c_str());
}

unsigned int RenderFactory::CreateShaderProgram(const char* vertex_shader_source,
												const char* fragment_shader_source)
{
	unsigned int vertex_shader = CompileShader(vertex_shader_source, GL_VERTEX_SHADER);
	unsigned int fragment_shader = CompileShader(fragment_shader_source, GL_FRAGMENT_SHADER);
	unsigned int shader_program;
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	int success;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if(!success) {
		char info_log[512];
		glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
		throw std::runtime_error("Shader linking failed:\n" + std::string(info_log));
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

unsigned int RenderFactory::CompileShader(const char* shader_source, unsigned int shader_type) {
	unsigned int shader;
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success) {
		char info_log[512];
		glGetShaderInfoLog(shader, 512, nullptr, info_log);
		throw std::runtime_error("Shader compilation failed:\n" + std::string(info_log));
	}

	return shader;
}

}
}
