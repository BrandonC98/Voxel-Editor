#include "VoxGrid.h"

VoxGrid::VoxGrid()
{}

VoxGrid::VoxGrid(int _arraySize)
{

	arraySize = _arraySize;

	//creates 3 dimensional array
	vGrid = new Vox * *[arraySize];
	for (int x = 0; x < arraySize; x++)
	{

		vGrid[x] = new Vox * [arraySize];

		for (int y = 0; y < arraySize; y++)
		{

			vGrid[x][y] = new Vox[arraySize];



		}

	}

}

void VoxGrid::SetAllPositions()
{

	// sets the position for all voxel elements of the array
	for (int x = 0; x < arraySize; x++)
	{
		for (int y = 0; y < arraySize; y++)
		{

			for (int z = 0; z < arraySize; z++)
			{
				vGrid[x][y][z].SetPosition(x, y, z);
				

			}

		}

	}

}

void VoxGrid::DeactivateVox(int keyX, int keyY, int KeyZ)
{
	if (!OutOfBound(keyX, keyY, KeyZ))
	{
		vGrid[keyX][keyY][KeyZ].SetDeactive();
	}

}

float VoxGrid::GetVoxCol(int keyX, int keyY, int keyZ, int colourIndex)
{

	return vGrid[keyX][keyY][keyZ].GetColour(colourIndex);

}

void VoxGrid::SetVoxColour(int keyx, int keyY, int keyZ, float r, float g, float b)
{

	vGrid[keyx][keyY][keyZ].SetColour(r, g, b);

}

int VoxGrid::Count()
{
	
	return arraySize;

}

void VoxGrid::ActivateVox(int keyX, int keyY, int keyZ)
{


	if (!OutOfBound(keyX, keyY, keyZ))
	{
		vGrid[keyX][keyY][keyZ].SetActive();
	}
	else std::cout << "position out of bounds" << std::endl;

}

bool VoxGrid::IsVoxHere(int keyX, int keyY, int keyZ)
{
	if(!OutOfBound(keyX, keyY, keyZ))
	return vGrid[keyX][keyY][keyZ].IsVoxHere;
	else std::cout << "position out of bounds" << std::endl;
}

bool VoxGrid::IsVoxColourTheSame(int keyX, int keyY, int keyZ, float r, float g, float b)
{

	return vGrid[keyX][keyY][keyZ].IsColourTheSame(r, g, b);

}

bool VoxGrid::OutOfBound(int keyX, int keyY, int keyZ)
{
	//checks if x,y and z are within the grid limits
	if (keyX <= arraySize && keyX >= 0 && keyY <= arraySize && keyY >= 0 && keyZ <= arraySize && keyZ >= 0)
		return false;
	else return true;
}




VoxGrid::~VoxGrid()
{
}
