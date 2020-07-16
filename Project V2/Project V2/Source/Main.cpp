
//OpenGL Related
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//c++ Related
#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>

//Project Related
#include "ShaderManager.h"
#include "VBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "DeltaTime.h"
#include "Input.h"
#include "Transform.h"
#include "Camera.h"
#include "Window.h"
#include "VoxGrid.h"
#include "WavefrontFile.h"

//User interface related
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ToolBar.h"
#include "Menu.h"

#include <GLFW\glfw3.h>


 

//callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void Mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int const arraySize = 32;
int const offset = 2;

Input* input = 0;
glm::vec3 cursorPosition;

bool turnGridOn = true;
bool turnWireFrameOn = false;

bool placeVox = false;
bool removeVox = false;
bool leftClick = false;

float CurrentHight = 800;
float CurrentWidth = 1200;

bool editMode = true;
bool moveCam = false;
bool camControlMode = false;

int yCursor = 0;

ToolBar toolbar;

void GlfwSetUp()
{



	/* Initialize the library */
	if (glfwInit() == GL_TRUE)
	{

		std::cout << "GLFW Setup Successful" << std::endl;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		glDepthFunc(GL_LESS);

	}
	else
	{

		std::cout << "GLFW Setup Fail" << std::endl;

	}


}

int main(void)
{

	
	GlfwSetUp();

	Window window(CurrentWidth, CurrentHight);
	window.Bind();
	window.SetViewPort();

	if (glewInit() != GLEW_OK) std::cout << "glew not intialised" << std::endl;

	//set callbacks
	glfwSetFramebufferSizeCallback(window.GetWindow(), framebuffer_size_callback);
	glfwSetCursorPosCallback(window.GetWindow(), mouse_callback);
	glfwSetScrollCallback(window.GetWindow(), scroll_callback);
	glfwSetMouseButtonCallback(window.GetWindow(), Mouse_button_callback);
	glfwSetKeyCallback(window.GetWindow(), key_callback);

	//glEnable(GL_DEPTH_TEST);


	//define the voxels vertices
	float voxVerts[] =
	{

		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f




	};

	//define the indices 
	unsigned int voxIndices[]
	{


		5, 4, 0, 1,
		5, 0, 6, 5,
		1, 2, 6, 1,
		7, 6, 2, 3,
		7, 2, 4, 7,
		3, 0, 4, 3,
		6, 7, 4, 5,
		6, 4, 1, 0,
		3, 2, 1, 3

	};


	VertexArray vertexArray;
	VBuffer vertexBuffer(voxVerts, 24 * 3 * sizeof(float));

	vertexArray.VertexBufferLayout(0, 3, GL_FALSE);
	vertexArray.SetStride(3);
	vertexArray.AddBuffer(vertexBuffer);

	IndexBuffer indexBuffer(voxIndices, 36);

	//get the shader files and stores them in a string 

	std::string vertSrc = ShaderManager::GetShader(ShaderManager::VERTEX, "TransformVert.shader");
	std::string fragSrc = ShaderManager::GetShader(ShaderManager::FRAGMENT, "basFrag.shader");
	ShaderManager shader(vertSrc, fragSrc);
	shader.Unbind();

	Renderer renderer;


	glEnable(GL_DEPTH_TEST);

	const float objOffset = 0.5f;


	DeltaTime* dTime = DeltaTime::GetInstance();
	
	//sets the camera position to the middle of the grid 
	Camera* cam = Camera::GetInstance(arraySize / 2, 4.0f, arraySize + offset , 2.5f);
	
	input = Input::GetInstance();
	cam->SetPerspective(CurrentWidth, CurrentHight);
	bool firstMove = false;


	//set Cursor Voxel Colour
	float vCursorCol[3] = { 1, 1, 1 };
	VoxGrid voxGrid(arraySize);
	voxGrid.SetAllPositions();

	glm::vec3 gridTranslation = glm::vec3(0, 0, 0);

	//handles the voxels rgb values
	float col[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	float cursorSpeed = 1000;

	//turns the cursor off
	glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	Menu menu;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window.GetWindow()))
	{

		//BASIC FRAME SET UP
		// everything that needs to be done each frame
		// should be done here before anything is rendered
		// as rendering may rely on it 

		//sets the background colour
		glClearColor(0.12, 0.12, 0.12, 1);


		//clears all the opengl rendered objects in the scene
		renderer.Clear();

		cam->SetPerspective(CurrentWidth, CurrentHight);
		dTime->UpdateTime(glfwGetTime());

		//get the cursor position and converts that to world space
		glm::vec3 cursorPosition = input->ScreenToWorldSpace(cam->GetLookAt(), cam->GetPerspective(), CurrentWidth, CurrentHight);

		//only the x and y are used. the y will actually be used for the z axis as we use the scroll will for the y 
		//they are then rounded as the cursor needs to snap to and from positions
		cursorPosition.x = glm::round(cursorPosition.x * cursorSpeed);
		cursorPosition.y = glm::round(cursorPosition.y * cursorSpeed);


		//FLOOR GRID
		//draws a grid on the floor so the user 
		//can see where key can place voxels and if
		//they are in line

		//render Grid
		if (turnGridOn)
		{
			//this always needs to be solid so if 
			//wireframe is on this will disable it 
			//during the rendering of the grid
			if (turnWireFrameOn)
			{

				//turns wireframe off
				glPolygonMode(GL_FRONT, GL_FILL);
				glPolygonMode(GL_BACK, GL_FILL);


			}

				Transform gridTransform;

			//Z axis lines
			for (int i = 0; i <= arraySize; i++)
			{
				gridTransform.Translate(i, gridTranslation.y, gridTranslation.z);
				gridTransform.Scale(0.025, 0.025, arraySize);

				shader.Bind();
				shader.SetUniform4f("u_Colour", 1, 1, 1, 1.0);
				shader.SetTranform(gridTransform.Result());
				shader.UnifromMat4("view", cam->GetLookAt());
				shader.UnifromMat4("projection", cam->GetPerspective());
				renderer.Draw(vertexArray, indexBuffer, shader);
			}

			//X axis lines
			for (int i = 0; i >= -arraySize; i--)
			{
				gridTransform.Translate(gridTranslation.x, gridTranslation.y, -i);
				gridTransform.Scale(arraySize, 0.025, 0.025);

				shader.Bind();
				shader.SetUniform4f("u_Colour", 1, 1, 1, 1.0);
				shader.SetTranform(gridTransform.Result());
				shader.UnifromMat4("view", cam->GetLookAt());
				shader.UnifromMat4("projection", cam->GetPerspective());
				renderer.Draw(vertexArray, indexBuffer, shader);
			}

			if (turnWireFrameOn)
			{
				//turns wireframe on
				glPolygonMode(GL_FRONT, GL_LINE);
				glPolygonMode(GL_BACK, GL_LINE);

			}

		}

			   		 
		// RENDER VOXELS
		//loops through a 3 dimensional array. if the element
		//is true it runs the code to draw a voxel.
		//any thing that needs to be done to every voxel should be 
		//done in this loop 


		Transform vGridTransform;
		Transform voxelOutlineTransform;

		for (int x = 0; x < voxGrid.Count(); x++)
		{

			for (int y = 0; y < voxGrid.Count(); y++)
			{

				for (int z = 0; z < voxGrid.Count(); z++)
				{

					if (voxGrid.IsVoxHere(x, y, z) == true)
					{

						vGridTransform.Translate(x, y, z);
						voxelOutlineTransform.Translate(x, y, z);
						voxelOutlineTransform.Scale(1, 1, 1);

						if (!turnWireFrameOn)
						{
								//turns wireframe on
								glPolygonMode(GL_FRONT, GL_LINE);
								glPolygonMode(GL_BACK, GL_LINE);

						

							//the wireframe thickeness is determined by this value 
							//so its increased for this small part of rendering and then
							//changed back to 1 the normal thickness
							glLineWidth(5.0f);
							shader.Bind();

							//sets the colour to black
							shader.SetUniform4f("u_Colour", 0, 0, 0, 1);
							shader.SetTranform(voxelOutlineTransform.Result());
							shader.UnifromMat4("view", cam->GetLookAt());
							shader.UnifromMat4("projection", cam->GetPerspective());

							//only draws the wireframe of the voxel.
							//this is done to better define where  one voxel ends 
							//and another starts for the user
							renderer.Draw(vertexArray, indexBuffer, shader);

					
						
								//turns wireframe off
								glPolygonMode(GL_FRONT, GL_FILL);
								glPolygonMode(GL_BACK, GL_FILL);
						}

						glLineWidth(1.0f);

						//draws the actual voxel
						shader.Bind();
						shader.SetUniform4f("u_Colour", voxGrid.GetVoxCol(x, y, z, 0), voxGrid.GetVoxCol(x, y, z, 1), voxGrid.GetVoxCol(x, y, z, 2), 1.0);
						shader.SetTranform(vGridTransform.Result());
						shader.UnifromMat4("view", cam->GetLookAt());
						shader.UnifromMat4("projection", cam->GetPerspective());

						//draws the voxel
						renderer.Draw(vertexArray, indexBuffer, shader);



					}


				}

			}

		}

		//RENDER CURSOR VOXEL
		//this area is for the voxel cursor

		if (editMode)
		{

			Transform cursorTransform;

			//moves the cursors object position 
			cursorTransform.Translate(cursorPosition.x, yCursor, cursorPosition.y);

			//changes the cursor to red if out of bounds 
			if (!voxGrid.OutOfBound(cursorPosition.x, yCursor, cursorPosition.y))
			{

				vCursorCol[0] = 1;
				vCursorCol[1] = 1;
				vCursorCol[2] = 1;

			}
			else
			{

				vCursorCol[0] = 1;
				vCursorCol[1] = 0;
				vCursorCol[2] = 0;

			}
			 

			shader.Bind();

			//sets the cursor colour in via the shader
			shader.SetUniform4f("u_Colour", vCursorCol[0], vCursorCol[1], vCursorCol[2], 1);
			
			shader.SetTranform(cursorTransform.Result());
			shader.UnifromMat4("view", cam->GetLookAt());
			shader.UnifromMat4("projection", cam->GetPerspective());

			//draws a voxel at the position of the cursor
			//to show the users where they are and preview of what
			//a voxel would look like in that position. 
			renderer.Draw(vertexArray, indexBuffer, shader);

			if (leftClick)
			{
				//checks if a voxel is in the cursors current position
				if (!voxGrid.IsVoxHere(cursorPosition.x, yCursor, cursorPosition.y))
				{

					//adds a voxel to the voxel array 
					voxGrid.ActivateVox(cursorPosition.x, yCursor, cursorPosition.y);
					std::cout << "active vox " << "[" << cursorPosition.x << "][" << yCursor << "][" << cursorPosition.y << "]" << std::endl;

					voxGrid.SetVoxColour(cursorPosition.x, yCursor, cursorPosition.y, col[0], col[1], col[2]);
				
				}
				else
				{
				
					//removes a voxel from the voxel array
					voxGrid.DeactivateVox(cursorPosition.x, yCursor, cursorPosition.y);

				}

				leftClick = false;

			}

		}

		//SAVE AND EXPORT
		//handles the saving to obj.
		//the WavefrontFile class does all the work here
		//if any more file formats are add it should be
		//in this section

		if (toolbar.GetSaveButtonState())
		{

			//at the moment the file is created in the projects directory
			//under the name file
			WavefrontFile objFile("file.obj");

			objFile.InsertComment("Obj File Created with the Voxel Editor");

			//loops throw a 3 demensional arrray to check if a element needs to be rendered
			for (int x = 0; x < voxGrid.Count(); x++)
			{

				for (int y = 0; y < voxGrid.Count(); y++)
				{

					for (int z = 0; z < voxGrid.Count(); z++)
					{

						if (voxGrid.IsVoxHere(x, y, z) == true)
						{
							//adds a new line to make the source file more readable
							objFile.InsertEmptyLine();

							objFile.InsertVertex(x + objOffset, y + objOffset, z - objOffset);
							objFile.InsertVertex(x + objOffset, y - objOffset, z - objOffset);
							objFile.InsertVertex(x + objOffset, y + objOffset, z + objOffset);
							objFile.InsertVertex(x + objOffset, y - objOffset, z + objOffset);
							objFile.InsertVertex(x - objOffset, y + objOffset, z - objOffset);
							objFile.InsertVertex(x - objOffset, y - objOffset, z - objOffset);
							objFile.InsertVertex(x - objOffset, y + objOffset, z + objOffset);
							objFile.InsertVertex(x - objOffset, y - objOffset, z + objOffset);

							objFile.InsertEmptyLine();

							objFile.InsertFace(1, 5, 7, 3);
							objFile.InsertFace(4, 3, 7, 8);
							objFile.InsertFace(8, 7, 5, 6);
							objFile.InsertFace(6, 2, 4, 8);
							objFile.InsertFace(2, 1, 3, 4);
							objFile.InsertFace(6, 5, 1, 2);

							objFile.EndObject();

						}
					}
				}
			}

			objFile.Close();
			toolbar.ResetSaveButtonState();

		}


		//IMGUI USER INTERFACE
		//UI related tasks should be placed here
		//all the UI is done using ImGui

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		toolbar.Render(turnGridOn);

		if (ImGui::Begin("Menu"))
		{
			//displays the cursors current position
			ImGui::Text("X: %.0f, Y: %i, Z: %.0f", cursorPosition.x, yCursor, cursorPosition.y);	

			ImGui::TextColored(ImVec4(1, 1, 0, 1), "IMPORTANT NOTE: if VOXEL cursor is not visible\nmove the mouse until the coordinates\nabove are: X: 16, Y: 0, Z: 16\nAlso make sure editing mode is active\n(the cursor shouldn't be visible)");

			//displays a colour picker and assigns the values to the col array 
			ImGui::ColorPicker3("Colour", col);

			//turns wireframe on/off
			ImGui::Checkbox("WireFrame Mode", &turnWireFrameOn);
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

			//basic controls
			ImGui::Text("left mouse button: place/delete voxel");
			ImGui::Spacing();
			ImGui::Text("right mouse button: switch to cursor for UI or voxel cursor for editing");
			ImGui::Spacing();
			ImGui::Text("scroll wheel: move voxel cursor in the Y direction.\nuse while holding left Ctrl for zoom");
			ImGui::Spacing();
			ImGui::Text("hold left CTRL: move mouse to look around");
			ImGui::Spacing();
			ImGui::Text("Hold Left ALT: move mouse to move around the scene");
			ImGui::Spacing();
			//shortcut list
			ImGui::Text("shortcut list:\n S key: export\n G key: turn grid on/off\n W key: turn wireframe on/off");

			ImGui::End();
		}
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		/* Swap front and back buffers */
		glfwSwapBuffers(window.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();

	}

	indexBuffer.~IndexBuffer();
	shader.~ShaderManager();
	vertexBuffer.~VBuffer();
	vertexArray.~VertexArray();
	window.~Window();

	glfwTerminate();
	return 0;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	//KEYBOARD INPUT
	//this section is for standard keyboard input

	//close window on escape key
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//turn camera movement on/off
	if (mods == GLFW_MOD_ALT && action == GLFW_REPEAT)
	{

		moveCam = true;
		editMode = false;
	}
	else
	{
		moveCam = false;

	}

	//turn camera control off/on
	if (mods == GLFW_MOD_CONTROL && action == GLFW_REPEAT)
	{
		camControlMode = true;
		editMode = false;

	}
	else
	{
		camControlMode = false;
		editMode = true;
		
	}

	//SHORTCUT KEY INPUT
	//for shortcut mapping

	// wireframe mode shortcut
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{

		if (turnWireFrameOn) turnWireFrameOn = false;
		else turnWireFrameOn = true;

	}

	// grid toggle shortcut
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{

		if (turnGridOn) turnGridOn = false;
		else turnGridOn = true;

	}

	//export shortcut
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{

		toolbar.SetSaveButtonStateToTrue();

	}
		   
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	//ajusts the viewport to the correct size
	glViewport(0, 0, width, height);

	//stores the values to be updated throughtout the program
	//so nothing that needs the height and width is incorrect
	CurrentHight = height;
	CurrentWidth = width;

}

void Mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	input = Input::GetInstance();
	Camera* cam = Camera::GetInstance(0.0f, 0.0f, 9.0f, 2.5f);

	//place/delete voxel
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{

		leftClick = true;
	
	}

	//turn edit mode on/off
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{

		if (editMode)
		{
			editMode = false;
		}
		else editMode = true;

		if (!editMode)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		if (editMode)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	}

}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	input = Input::GetInstance();
	input->SetMousePosition(xpos, ypos);
	Camera* cam = Camera::GetInstance(0.0f, 0.0f, 0.0f, 0.0f);



		//moves the camera's position on the x and y axis
		if (moveCam)
		{
			if (ypos < input->lastY) cam->MoveUp();
			if (xpos < input->lastX) cam->MoveLeft();
			if (ypos > input->lastY) cam->MoveDown();
			if (xpos > input->lastX) cam->MoveRight();

			input->lastX = xpos;
			input->lastY = ypos;
		}

	if (camControlMode)
	{
		if (cam->firstMove)
		{
			//if its the camera's first move
			//then it won't have a last position
			//so it sets it to its current
			input->lastX = xpos;
			input->lastY = ypos;
			cam->firstMove = false;
		}
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



		//	yaw/ptich
		float xoffset = xpos - input->lastX;
		float yoffset = input->lastY - ypos;

		input->lastX = xpos;
		input->lastY = ypos;

		xoffset *= cam->sensitivity;
		yoffset *= cam->sensitivity;

		
		cam->Rotate(xoffset, yoffset);

	}
	   
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	//moves the cursor position up/down
	if (editMode)
	{
		if (yoffset > 0) yCursor++;
		else if (yoffset < 0) yCursor--;
	}

	//zooms the camera in/out
	if (camControlMode)
	{
		Camera* cam = Camera::GetInstance(0.0f, 0.0f, 9.0f, 2.5f);

		cam->Zoom(yoffset);
	}


}



