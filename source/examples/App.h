#pragma once

#include "interface/display/Window.h"
#include "gfx/scene/Camera.h"
#include "interface/input/InputManager.h"
#include "gfx/scene/Scene.h"

class App {

public:
	App();

private:
	Mantis::Display::Window window_;
	Mantis::GFX::Scene scene_;
	Mantis::GFX::Camera camera_;

};


