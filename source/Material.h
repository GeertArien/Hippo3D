#pragma once

#include "ShaderProgram.h"
#include "Texture.h"

namespace Mantis {

	class Material final {

	public:
		Material();
		Material(const std::string& type);

	private:
		ShaderProgram shader_;
		//Texture texture_;

	};

}