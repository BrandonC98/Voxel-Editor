#include "Menu.h"

void Menu::Render(float x, int y, float z, float* colour, bool* turnWireFrameOn)
{


	if (ImGui::Begin("Menu"))
	{
		//displays the cursors current position
		ImGui::Text("X: %.0f, Y: %i, Z: %.0f", x, y, z);

		//displays a colour picker and assigns the values to the col array 
		ImGui::ColorPicker3("Colour", colour);

		//turns wireframe on/off
		ImGui::Checkbox("WireFrame Mode", turnWireFrameOn);
		if (turnWireFrameOn)
		{

			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);

		}
		else
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);

		}



		ImGui::End();
	}

}



