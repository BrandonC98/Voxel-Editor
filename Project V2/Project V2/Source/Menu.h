#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL\glew.h>


class Menu
{

public:
	void Render(float x, int y, float z, float colour[4], bool* turnWireFrameOn);
	//bool GetWireFrameState();

private:
	//bool wireFrameOn = false;



};
