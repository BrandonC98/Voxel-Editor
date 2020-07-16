#include "ShaderManager.h"


std::string ShaderManager::GetShader(shaderType typeOfShader, std::string fileName)
{

	std::string shader;
	std::string filepath;
	switch (typeOfShader)
	{

	case 0:
		filepath = "Resources/Shaders/Vertex/";
		break;

	case 1:
		filepath = "Resources/Shaders/Fragment/";
		break;
	
	}

	std::ifstream stream(filepath + fileName);

	std::string line;

	//gets each line of the shader file and stores it in the line variable that is then 
	//added to the shader string
	while (getline(stream, line))
	{

		shader += line + '\n';

	}

	return shader;

}


ShaderManager::ShaderManager(const std::string& vertexShader, const std::string& fragmentShader)
{

	id = CreateShader(vertexShader, fragmentShader);

}


ShaderManager::~ShaderManager()
{

	glDeleteProgram(id);

}

void ShaderManager::Bind() const
{

	glUseProgram(id);
}

void ShaderManager::Unbind() const
{

	
	glUseProgram(0);

}

void ShaderManager::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{

	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);

}



void ShaderManager::SetTranform(glm::mat4 transform)
{
	 
	unsigned int transLoc = glGetUniformLocation(id, "model");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

}

void ShaderManager::UnifromMat4(const std::string& name, glm::mat4 mat4)
{
	
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat4));

}

 int ShaderManager::GetUniformLocation(const std::string& name)
{

	 int location = glGetUniformLocation(id, name.c_str());
	if (location == -1) std::cout << " Error: uniform " << name << " doesn't exist" << std::endl;
	return location;

}

 unsigned int ShaderManager::CompileShader(GLuint type, const std::string& source)
{

	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);


	//error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}


	return id;

}

 unsigned int ShaderManager::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	
	GLuint program = glCreateProgram();

	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

