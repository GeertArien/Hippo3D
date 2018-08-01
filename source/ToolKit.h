#ifndef HIPPO3D_TOOLKIT_H
#define HIPPO3D_TOOLKIT_H

#ifdef CreateWindow
# undef CreateWindow
#endif

#include "Window.h"


namespace Hippo3D {

	class ToolKit {

	public:
		ToolKit(const int version_major, const int version_minor, const int opengl_profile);
		~ToolKit();

		Window CreateWindow(const int width, const int height, const char* title) const;

		void SetContext(const Window& window) const
		{ glfwMakeContextCurrent(*window); }

		void PollEvents() const
		{ glfwPollEvents(); }

		void LoadFunctionPointers() const;

	};

}

#endif //HIPPO3D_TOOLKIT_H
