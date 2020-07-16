#include "Transform.h"

Transform::Transform()
{

	trans = glm::mat4(1.0f);

}

void Transform::Translate(float x, float y, float z)
{
	glm::vec3 newPosition;
	newPosition.x = x;
	newPosition.y = y;
	newPosition.z = z;
	
	trans = glm::translate(trans, newPosition);
	

}

void Transform::Rotate(float angle, float xAxis, float yAxis, float zAxis)
{
	glm::vec3 axis;
	axis.x = xAxis;
	axis.y = yAxis;
	axis.z = zAxis;

	trans = glm::rotate(trans, glm::radians(angle), axis);

}

void Transform::Scale(float xScale, float yScale, float zScale)
{
	glm::vec3 scale;
	scale.x = xScale;
	scale.y = yScale;
	scale.z = zScale;

	trans = glm::scale(trans, scale);

}

glm::mat4 Transform::Result()
{

	results = trans;
	trans = glm::mat4(1.0f);
	
	return results;

}