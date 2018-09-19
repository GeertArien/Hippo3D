#include "Renderer.h"
#include "Scene.h"
#include "ToolKit.h"
#include "Window.h"
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

Renderer::Renderer(ToolKit& tool_kit, Window& window, Scene& scene) :
	tool_kit_(&tool_kit), window_(&window), scene_(&scene), shader_program_("flat")
{ }

void testing(void* renderer_p) {
	auto renderer = reinterpret_cast<Renderer*>(renderer_p);
	renderer->RenderPass();
}

void Renderer::Render() {

	glEnable(GL_DEPTH_TEST);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.GetDataSize(), mesh.GetDataPointer(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

#if EMSCRIPTEN
	emscripten_set_main_loop_arg(testing, this, 60, 1);
#else
	while(!window_->ShouldClose()) {
		RenderPass();
	}
#endif

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteBuffers(1, &VBO);

}

void Renderer::RenderPass() const {
	// input
	// -----
	window_->ProcessInput();

	// clear buffer
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render
	// ------
	glUseProgram(shader_program_.GetID());

	shader_program_.SetUniform("projection", scene_->GetCamera().GetProjectionMatrix());
	shader_program_.SetUniform("view", scene_->GetCamera().GetViewMatrix());

	glm::vec3 cubePositions[] = {
			glm::vec3( 0.0f,  0.0f,  0.0f),
			glm::vec3( 2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3( 2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3( 1.3f, -2.0f, -2.5f),
			glm::vec3( 1.5f,  2.0f, -2.5f),
			glm::vec3( 1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for(unsigned int i = 0; i < 10; i++) {
		glm::mat4 model(1.f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i + 10.f;
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader_program_.SetUniform("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	window_->SwapBuffers();
	tool_kit_->PollEvents();
}

}