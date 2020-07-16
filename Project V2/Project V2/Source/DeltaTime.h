#pragma once

/*

	use this to get the deltaTime for smooth
	movement. it's a singleton. create a instance
	put UpdateDeltaTime() in the render loop and
	pass it the float that contains the time.
	use GetDeltaTime() to retive it.
	
*/

class DeltaTime
{

public:
	static DeltaTime *GetInstance();
	void UpdateTime(float time);
	float GetDeltaTime();
	~DeltaTime();

private:
	DeltaTime();
	static DeltaTime* instance;
	float deltaTime;
	float lastFrame;

};

