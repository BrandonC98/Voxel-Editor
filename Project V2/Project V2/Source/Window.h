#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

/*

	this class handles the window creation. 
	Bind() will make the window the current
	context. this class needs GLFW to operate.

*/

class Window
{

public:
	void Bind();
	void Unbind();
	void SetViewPort();
	GLFWwindow* GetWindow();
	Window(int _width, int _hight);
	~Window();
	int GetHight();
	int GetWidth();



private:
	GLFWwindow* window;
	const char* title = "Voxel Editor";
	int width;
	int hight;

};