#include "Renderer.h"
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "GL_impl.h"
#include "gfx/scene/Scene.h"
#include "gfx/scene/Texture.h"
#include "gfx/scene/Camera.h"
#include "gfx/scene/Mesh.h"
#include "RenderFactory.h"
#include "RenderUtility.h"


namespace Mantis {
namespace GFX {

void Renderer::Setup(Scene& scene) {
	glEnable(GL_DEPTH_TEST);

	for (const auto& object : scene.GetObjects()) {
		const Mesh& mesh = object.GetMesh();
		const unsigned int id = mesh.GetID();

		if (vbo_map_.find(id) == vbo_map_.end()) {
			unsigned int VBO;
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, mesh.GetDataSize(), mesh.GetDataPointer(), GL_STATIC_DRAW);
			vbo_map_[id] = VBO;
		}

		const std::string shader_name = object.GetMaterial().GetShaderName();

		if (shader_map_.find(shader_name) == shader_map_.end()) {
			shader_map_[shader_name] = RenderFactory::InitShader(shader_name);
		}
	}

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Renderer::TearDown() {
	// optional: de-allocate all resources once they've outlived their purpose:
	for (const auto& vbo_pair : vbo_map_) {
		//todo: delete all in one call;
		glDeleteBuffers(1, &vbo_pair.second);
	}
	vbo_map_.clear();
}

void Renderer::Render(Scene& scene, Camera& camera) const {
	// clear buffer
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render
	// ------

	for (const auto& object : scene.GetObjects()) {
		const std::string shader_name = object.GetMaterial().GetShaderName();
		const unsigned int shader_id = shader_map_.at(shader_name);
		glUseProgram(shader_id);
		SetUniform(shader_id, "projection", camera.GetProjectionMatrix());
		SetUniform(shader_id, "view", camera.GetViewMatrix());
		SetUniform(shader_id, "model", object.GetModelMatrix());

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

}
}