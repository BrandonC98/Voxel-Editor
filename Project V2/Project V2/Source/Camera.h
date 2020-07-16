#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DeltaTime.h"
#include <iostream>
 class Camera
{
	 	 
public:
	~Camera();
	static Camera* GetInstance(float x, float y, float z, float speed);
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void SetFront(glm::vec3 _front);
	void Zoom(float scrollY);
	float GetSpeed();
	void SetSpeed(float _speed);
	void SetPerspective(float width, float height);
	glm::mat4 GetPerspective();
	glm::mat4 GetLookAt();
	float speed;
	float sensitivity = 0.05f;
	bool firstMove = true;
	void Rotate(float xoffset, float yoffset);
	float fov = 45.0f;

private:
	Camera(float x, float y, float z, float _speed);
	static Camera* instance;
	
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 direction;

	glm::mat4 view = glm::mat4(1.0f);
	float yaw;
	float pitch;
	glm::mat4 projection = glm::mat4(1);
	glm::vec3 position;



};

