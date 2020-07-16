#include "Window.h"

Window::Window(int _width, int _hight)
{

	width = _width;
	hight = _hight;

	//make the window 
	window = glfwCreateWindow(width, hight, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error: window not created correctly" << std::endl;
		glfwTerminate();

	}
	
}

Window::~Window()
{

	glfwDestroyWindow(window);

}

void Window::Bind()
{

	glfwMakeContextCurrent(window);

	//sets screen fresh to that of the monitors
	glfwSwapInterval(1);

}

int Window::GetHight()
{

	return hight;

}

int Window::GetWidth()
{

	return width;

}

void Window::Unbind()
{

	glfwMakeContextCurrent(NULL);

}

void Window::SetViewPort()
{

	glViewport(0, 0, width, hight);

}

GLFWwindow* Window::GetWindow()
{

	return window;

}