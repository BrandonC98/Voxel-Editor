#pragma once
#include "Vox.h"
#include <iostream>

 class VoxGrid
{
public:
	VoxGrid();
	VoxGrid(int _arraySize);
	~VoxGrid();
	void ActivateVox(int keyX, int keyY, int KeyZ);
	void DeactivateVox(int keyX, int keyY, int KeyZ);
	bool IsVoxHere(int keyX, int keyY, int keyZ);
	bool IsVoxColourTheSame(int keyX, int keyY, int keyZ, float r, float g, float b);
	void SetVoxColour(int keyx, int keyY, int keyZ, float r, float g, float b);
	int Count();
	void SetAllPositions();
	float GetVoxCol(int keyX,int keyY,int keyZ, int colourIndex);
	bool OutOfBound(int keyX, int keyY, int KeyZ);

private:
	Vox ***vGrid;
	int arraySize;
	 
};

