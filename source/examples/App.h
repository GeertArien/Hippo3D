#pragma once

#include <context/Window.h>
#include <core/Camera.h>
#include <core/Scene.h>

class App {

public:
	App();

private:
	Mantis::Window window_;
	Mantis::Scene scene_;
	Mantis::Camera camera_;

	static void OnKeyPress(void* target, int key, float delta_time);
	static void OnMouseMove(void* target, float offset_x, float offset_y);
	static void OnMouseScroll(void* target, float offset);

};


