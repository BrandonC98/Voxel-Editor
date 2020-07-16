#include "DeltaTime.h"

DeltaTime* DeltaTime::instance = 0;

DeltaTime* DeltaTime::GetInstance()
{

	if (instance == 0)
	{

		instance = new DeltaTime();

		return instance;

	}
	else
	{

		return instance;

	}

}

DeltaTime::DeltaTime() {};

DeltaTime::~DeltaTime()
{

	delete instance;

}

void DeltaTime::UpdateTime(float time)
{

	float currentFrame = time;
	deltaTime = currentFrame - lastFrame;
	 lastFrame = currentFrame;

}

float DeltaTime::GetDeltaTime()
{

	return deltaTime;

}