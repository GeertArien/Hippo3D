#ifndef HIPPO3D_WINDOW_H
#define HIPPO3D_WINDOW_H

#include <GLFW/glfw3.h>


namespace Hippo3D {
	class Camera;
}


namespace Hippo3D {

	class Window {

	public:
		Window(int width, int height, const char* title);

		void AttachCamera(Camera& camera); // replace with observable pattern?
		void ProcessInput();

		bool ShouldClose() const
		{ return glfwWindowShouldClose(glfw_window_) > 0; };

		void SwapBuffers() const
		{ glfwSwapBuffers(glfw_window_); }

		GLFWwindow* operator*() const
		{ return glfw_window_; }

	private:
		GLFWwindow* glfw_window_;
		Camera* camera_;

		float last_frame_ = 0.f;
		float last_x_ = 0.f;
		float last_y_ = 0.f;
		bool first_mouse_ = true;

		static void FrameBufferSizeCallback(GLFWwindow*, int width, int height);
		static void MouseCallback(GLFWwindow* glfw_window, double pos_x, double pos_y);
		static void ScrollCallback(GLFWwindow* glfw_window, double, double offset_y);

	};

}


#endif //HIPPO3D_WINDOW_H
