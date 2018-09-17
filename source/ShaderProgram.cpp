#include "ShaderProgram.h"

#include "GL_impl.h"
#include <stdexcept>
#include <gtc/type_ptr.hpp>

#include "shaders/shaders.h"

namespace Mantis {

ShaderProgram::ShaderProgram(const std::string& vertex_shader_name, const std::string& fragment_shader_name) {
	std::string vertex_shader, fragment_shader;
	try {
		vertex_shader = Shader::VERTEX_SHADERS.at(vertex_shader_name);
	}
	catch (const std::out_of_range& e) {
		throw std::runtime_error("Invalid vertex shader name: " + vertex_shader_name);
	}

	try {
		fragment_shader = Shader::FRAGMENT_SHADERS.at(fragment_shader_name);
	}
	catch (const std::out_of_range& e) {
		throw std::runtime_error("Invalid fragment shader name: " + fragment_shader_name);
	}

	ID_ = CreateShaderProgram(vertex_shader.c_str(), fragment_shader.c_str());
}

void ShaderProgram::SetUniform(const std::string& name, const unsigned int value) const {
	glUniform1i(glGetUniformLocation(ID_, name.c_str()), value);
}

void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(ID_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int ShaderProgram::CreateShaderProgram(const char* vertex_shader_source,
												const char* fragment_shader_source) const
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
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		throw std::runtime_error("Shader linking failed:\n" + std::string(info_log));
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

unsigned int ShaderProgram::CompileShader(const char* shader_source, unsigned int shader_type) const {
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