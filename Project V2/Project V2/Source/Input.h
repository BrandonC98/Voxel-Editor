#pragma once

#include "glm/glm.hpp"

class Input
{

public:
	static Input* GetInstance();
	void SetMousePosition(double xPosition, double yPosition);
	double GetMouseX() const;
	double GetMouseY() const;
	glm::vec3 ScreenToWorldSpace(glm::mat4 view, glm::mat4 projection, int screenWidth, int screenHeight);
	float lastX = 1200;
	float lastY = 800;

private:
	Input();
	static Input* instance;
	double mouseX = 0;
	double mouseY = 0;
	float offsetX;
	float offsetY;


};
