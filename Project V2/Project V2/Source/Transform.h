#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{

public:
	Transform();
	void Translate(float x, float y, float z);
	void Rotate(float angle, float xAxis, float yAxis, float zAxis);
	void Scale(float xScale, float yScale, float zScale);
	glm::mat4 Result();

private:
	glm::mat4 trans;
	glm::mat4 results;

};

