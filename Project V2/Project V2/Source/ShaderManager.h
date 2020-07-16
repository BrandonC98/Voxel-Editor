#pragma once

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>
#include <fstream>

//using namespace std;

class ShaderManager
{
public: 

	ShaderManager(const std::string& vertexShader, const std::string& fragmentShader);
	~ShaderManager();

	
	//used to define the type of shader to retrive
	static enum shaderType 
	{
		NONE = -0, VERTEX = 0, FRAGMENT = 1
	};

	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetTranform(glm::mat4 transform);
	void UnifromMat4(const std::string& name, glm::mat4 mat4);

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	static std::string GetShader(shaderType typeOfShader, std::string fileName);

private: 
	unsigned int CompileShader(GLuint type, const std::string& source);
	unsigned int id;
	 int GetUniformLocation(const std::string& name);
};

