#pragma once

#include <iostream>
#include <fstream>

#include <sstream>
#include <string>

/*

this class creates and writes to a file. 

*/

class WavefrontFile
{

public:
	WavefrontFile(std::string fileName);
	void InsertComment(std::string comment);
	void InsertVertex(float x, float y, float z);
	void InsertFace(int v1, int v2, int v3, int v4);
	void EndObject();
	void Close();
	void InsertEmptyLine();

private:
	void Insert(std::string line);
	std::string	fileName;
	int faceCounter = 0;
	
	std::ofstream file;
};

