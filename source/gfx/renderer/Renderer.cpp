#include "Renderer.h"
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
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

	unsigned int pv;
	unsigned int base = 0;
	glGenBuffers(1, &pv);
	glBindBuffer(GL_UNIFORM_BUFFER, pv);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, base, pv);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	uniform_block_map_["pv"].id = pv;
	uniform_block_map_["pv"].base = base;

	unsigned int m;
	++base;
	glGenBuffers(1, &m);
	glBindBuffer(GL_UNIFORM_BUFFER, m);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, base, m);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	uniform_block_map_["m"].id = m;
	uniform_block_map_["m"].base = base;

	for (const auto& object : scene.GetObjects()) {
		const Mesh& mesh = object.GetMesh();
		const unsigned int id = mesh.GetID();

		if (vao_map_.find(id) == vao_map_.end()) {
			unsigned int VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			vao_map_[id] = VAO;

			unsigned int VBO;
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, mesh.GetDataSize(), mesh.GetDataPointer(), GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		const std::string shader_name = object.GetMaterial().GetShaderName();

		if (shader_map_.find(shader_name) == shader_map_.end()) {
			shader_map_[shader_name] = RenderFactory::InitShader(shader_name);

			const unsigned int shader_id = shader_map_.at(shader_name);
			unsigned int uniformBlockIndex = glGetUniformBlockIndex(shader_id, "pv");
			glUniformBlockBinding(shader_id, uniformBlockIndex, uniform_block_map_["pv"].base);
		}
	}
}

void Renderer::TearDown() {
	// optional: de-allocate all resources once they've outlived their purpose:
	for (const auto& vao_pair : vao_map_) {
		//todo: delete all in one call;
		glDeleteBuffers(1, &vao_pair.second);
	}
	vao_map_.clear();
}

void Renderer::Render(Scene& scene, Camera& camera) const {
	// clear buffer
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = camera.GetProjectionMatrix();
	glm::mat4 view = camera.GetViewMatrix();

	glBindBuffer(GL_UNIFORM_BUFFER, uniform_block_map_.at("pv").id);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// render
	// ------
	for (const auto& object : scene.GetObjects()) {

		const std::string shader_name = object.GetMaterial().GetShaderName();
		const unsigned int shader_id = shader_map_.at(shader_name);

		glUseProgram(shader_id);
		glBindVertexArray(vao_map_.at(object.GetMesh().GetID()));

		glm::mat4 model = object.GetModelMatrix();

		glBindBuffer(GL_UNIFORM_BUFFER, uniform_block_map_.at("m").id);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(model));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

}
}