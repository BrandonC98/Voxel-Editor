#include "Input.h"

Input* Input::instance = 0;

Input::Input() {};

Input* Input::GetInstance()
{

	if (instance == 0)
	{

		instance = new Input();
		return instance;

	}
	else
	{

		return instance;

	}
	
}

glm::vec3 Input::ScreenToWorldSpace(glm::mat4 view, glm::mat4 projection, int screenWidth, int screenHeight)
{

	//converts screen position to world space
	// we get the mouse position in world space out of this
	glm::mat4 mat = (view * projection);
	mat = glm::inverse(mat);
	glm::vec4 results;
	results.x = (2.0f * ((float)(GetMouseX() - 0) / screenWidth - 0)) - 1.0f;
	results.y = 1.0f - (2.0f * ((float)(GetMouseY() - 0) / (screenHeight)-0));

	results.z = 2.0 * 1.0f - 1.0f;
	results.w = -1.0;

	glm::vec4 mouse = mat * results;

	mouse.w = 1.0f / mouse.w;

	mouse.x *= mouse.w;
	mouse.y *= mouse.w;
	mouse.z *= mouse.w;

	return mouse;

}




void Input::SetMousePosition(double xPosition, double yPosition)
{

	mouseX = xPosition;
	mouseY = yPosition;

}

double Input::GetMouseX() const
{

	return mouseX;

}

double Input::GetMouseY() const
{

	return mouseY;

}


