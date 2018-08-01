#include "Renderer.h"
#include "ToolKit.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "glad/glad.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


namespace Hippo3D {

Renderer::Renderer(Hippo3D::ToolKit& tool_kit, Hippo3D::Window& window) :
	tool_kit_(&tool_kit), window_(&window)
{ }

void Renderer::Render() const {
	Hippo3D::ShaderProgram shader_program("flat", "flat");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
			// positions          // colors           // texture coords
			0.5f,  0.5f, 0.0f,    1.0f, 1.0f,   // top right
			0.5f, -0.5f, 0.0f,    1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left
	};

	unsigned int indices[] = {
			0, 1, 2,   				// first triangle
			0, 2, 3	   				// second triangle
	};

	const Hippo3D::Texture texture0("container.jpg");

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	glUseProgram(shader_program.GetID());
	shader_program.SetUniform("texture0", 0);

	// render loop
	// -----------
	while(!window_->ShouldClose()) {
		// input
		// -----
		window_->ProcessInput();

		// clear buffer
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render
		// ------
		glUseProgram(shader_program.GetID());
		glm::mat4 trans(1.f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		shader_program.SetUniform("transform", trans);

		glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, texture0.GetID());
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window_->SwapBuffers();
		tool_kit_->PollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

}

}