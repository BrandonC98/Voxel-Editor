#include "Vox.h"



void Vox::SetPosition(float x, float y, float z)
{

	position[0] = x;
	position[1] = y;
	position[2] = z;


}

void Vox::SetColour(float r, float g, float b)
{

	colour[0] = r;
	colour[1] = g;
	colour[2] = b;

}

bool Vox::IsColourTheSame(float r, float g, float b)
{

	if (colour[0] == r && colour[1] == g && colour[2] == b)
		return true;
	else return false;
	
}

float Vox::GetColour(int col)
{

	return colour[col];

}
