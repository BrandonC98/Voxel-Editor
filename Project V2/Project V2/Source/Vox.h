#pragma once

class Vox
{
public: 

	bool IsVoxHere = false;
	void SetColour(float r, float g, float b);
	bool IsColourTheSame(float r, float g, float b);
	float GetColour(int col);
	void SetPosition(float x, float y, float z);
	inline bool SetActive()  { IsVoxHere = true; return IsVoxHere; };
	inline bool SetDeactive()  { IsVoxHere = false; return IsVoxHere; };

private:

	float position[3];
	float colour[3] = { 0.12f, 0.12f, 0.12f };

};

