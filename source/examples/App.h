#pragma once

#include "interface/display/Window.h"
#include "interface/input/InputManager.h"
#include "interface/controls/FirstPersonControls.h"
#include "gfx/scene/Camera.h"
#include "gfx/scene/Scene.h"
#include "gfx/renderer/Renderer.h"
#include "gfx/renderer/Renderer.h"


class App {

public:
	App();

private:
	Mantis::Display::Window window_;
	Mantis::GFX::Scene scene_;
	Mantis::GFX::Camera camera_;
	Mantis::GFX::Renderer renderer_;
	Mantis::Input::InputManager input_manager_;
	Mantis::Controls::FirstPersonControls first_person_controls_;

	void MainLoop();

#if EMSCRIPTEN
	static void ExecuteMainLoop(void* app_p);
#endif

};


