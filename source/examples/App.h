#pragma once

#include "interface/display/Window.h"
#include "core/Camera.h"
#include "interface/input/InputManager.h"
#include "core/Scene.h"

class App {

public:
	App();

private:
	Mantis::Window window_;
	Mantis::Scene scene_;
	Mantis::Camera camera_;

};


