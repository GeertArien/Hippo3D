#include "Renderer.h"
#include "Scene.h"
#include "context/Window.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "GL_impl.h"
#include "Camera.h"
#include "Mesh.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

#if EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif


namespace Mantis {

//void testing(void* renderer_p) {
//	auto renderer = reinterpret_cast<Renderer*>(renderer_p);
//	renderer->BeforeRenderPass();
//	renderer->RenderPass();
//}

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

void Renderer::BeforeRenderPass(Scene& scene, Window& window) {
	// input
	// -----
	window.ProcessInput();

	// change rotations
	size_t i = 0;
	for (auto& object : scene.GetObjects()) {
		const float angle = 20.0f * i++ + 10.f;
		object.SetRotation((float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	}
}

void Renderer::Render(Scene& scene, Camera& camera, Window& window) {

	Setup(scene);

#if EMSCRIPTEN
	emscripten_set_main_loop_arg(testing, this, 60, 1);
#else
	while(!window.ShouldClose()) {
		BeforeRenderPass(scene, window);
		RenderPass(scene, camera, window);
	}
#endif

	TearDown();

}

void Renderer::RenderPass(Scene& scene, Camera& camera, Window& window) const {
	// clear buffer
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render
	// ------

	for (const auto& object : scene.GetObjects()) {
		const ShaderProgram& shader_program = object.GetMaterial().GetShaderProgram();
		glUseProgram(shader_program.GetID());
		shader_program.SetUniform("projection", camera.GetProjectionMatrix());
		shader_program.SetUniform("view", camera.GetViewMatrix());
		shader_program.SetUniform("model", object.GetModelMatrix());

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	window.SwapBuffers();
}

}