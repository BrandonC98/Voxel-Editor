#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Camera.h"

class ToolBar
{

public: 
	void Render(bool& turnGridOn);
	bool GetSaveButtonState();
	void ResetSaveButtonState();
	void SetSaveButtonStateToTrue();
		
private:
	bool save;
	Camera* cam;

};

