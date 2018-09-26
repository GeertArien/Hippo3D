#pragma once

#include <interface/Window.h>
#include <core/Camera.h>
#include <core/Scene.h>

class App {

public:
	App();

private:
	Mantis::Window window_;
	Mantis::Scene scene_;
	Mantis::Camera camera_;

	float current_frame_ = 0.f;
	float last_frame_ = 0.f;
	float last_x_ = 0.f;
	float last_y_ = 0.f;
	bool first_mouse_ = true;

	static void OnKeyPress(void* target, int key);
	static void OnMouseMove(void* target, double pos_x, double pos_y);
	static void OnMouseScroll(void* target, double pos_x, double pos_y);

};


