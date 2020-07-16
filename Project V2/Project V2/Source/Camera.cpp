#include "Camera.h"

Camera* Camera::instance = 0;

//the Camera is singleton
Camera* Camera::GetInstance(float x, float y, float z, float speed)
{

	if (instance == 0)
	{

		instance = new Camera(x, y, z, speed);
		return instance;

	}
	else return instance;

}

Camera::Camera(float x, float y, float z, float _speed)
{

	position.x = x;
	position.y = y;
	position.z = z;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	 up = glm::vec3(0.0f, 1.0f, 0.0f);
	 speed = _speed;
	 yaw = -90.0f;
	 pitch = 0;

	 direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	 direction.y = sin(glm::radians(pitch));
	 direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
}

//rotate the camera on the spot
void Camera::Rotate(float xoffset, float yoffset)
{

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	SetFront(glm::normalize(direction));

}

Camera::~Camera()
{}

void Camera::SetPerspective(float width, float height)
{


	projection = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);

}

glm::mat4 Camera::GetPerspective()
{

	return projection;

}

glm::mat4 Camera::GetLookAt()
{

	glm::mat4 view = glm::lookAt(position, position + front, up);
	return view;

	
}

float Camera::GetSpeed()
{

	DeltaTime* dtime = DeltaTime::GetInstance();

	float step = speed * dtime->GetDeltaTime();
	return step;

}

void Camera::SetFront(glm::vec3 _front)
{

	front = _front;

}

void Camera::SetSpeed(float _speed)
{

	speed = _speed;

}

void Camera::MoveUp()
{

	position += GetSpeed() * up;
	
}

void Camera::Zoom(float scrollY)
{

	if (fov >= 1.0f && fov <= 45.0f) fov -= scrollY;
	if (fov <= 1.0f) fov = 1.0f;
	if (fov >= 45.0f) fov = 45.0f;

}

void Camera::MoveDown()
{

	position -= GetSpeed() * up;

}

void Camera::MoveLeft()
{

	position -= glm::normalize(glm::cross(front, up)) * GetSpeed();

}

void Camera::MoveRight()
{

	position += glm::normalize(glm::cross(front, up)) * GetSpeed();
}

