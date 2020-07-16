#include "ToolBar.h"

void ToolBar::Render(bool& turnGridOn)
{
	cam = Camera::GetInstance(0, 0, 0, 0);

	//toolbar 
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Files"))
		{
			//export to OBJ. the S key is the shortcut for this
			if (ImGui::Button("Export	 S"))
			{

				save = true;

			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Options"))
		{
			ImGui::SliderFloat("Camera Sensitivty", &cam->speed, 1.0f, 10.0f);	//MAYBE DELETE

			//turns the floor grid off/on
			ImGui::Checkbox("Toggle Grid", &turnGridOn);

			//present style for the UI
			if (ImGui::Button("Style Classic"))	ImGui::StyleColorsClassic();
			if (ImGui::Button("Style Dark"))	ImGui::StyleColorsDark();
			if (ImGui::Button("Style Light"))	ImGui::StyleColorsLight();

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

}

void ToolBar::SetSaveButtonStateToTrue()
{

	save = true;

}

bool ToolBar::GetSaveButtonState()
{

	return save;

}

void ToolBar::ResetSaveButtonState()
{

	save = false;

}


