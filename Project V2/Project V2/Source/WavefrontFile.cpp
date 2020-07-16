#include "WavefrontFile.h"

WavefrontFile::WavefrontFile(std::string fileName)
{

	file.open(fileName);

		
}

void WavefrontFile::EndObject()
{

	faceCounter += 8;

}

void WavefrontFile::Insert(std::string line)
{
	
	//adds the line to the file
	file << line;

}

void WavefrontFile::InsertFace(int v1, int v2, int v3, int v4)
{

	std::ostringstream ssV1, ssV2, ssV3, ssV4;

	ssV1 << v1 + faceCounter;
	ssV2 << v2 + faceCounter;
	ssV3 << v3 + faceCounter;
	ssV4 << v4 + faceCounter;

	//the f character represents the vertices index of a face. the vertices are gathered from InsertVertex()
	std::string line = "f " + ssV1.str() + " " + ssV2.str() + " " + ssV3.str() + " " + ssV4.str() + "\n";

	Insert(line);

}

void WavefrontFile::InsertVertex(float x, float y, float z)
{

	std::ostringstream ssX, ssY, ssZ;

	ssX << x;
	ssY << y;
	ssZ << z;

	//the v Character represents vertices
	std::string line = "v " + ssX.str() + " " + ssY.str() + " " + ssZ.str() + "\n";

	Insert(line);

}

void WavefrontFile::InsertEmptyLine()
{

	Insert("\n");

}

void WavefrontFile::Close()
{

	file.close();

}

void WavefrontFile::InsertComment(std::string comment)
{

	//the # symbol defines a comment in obj files
	std::string line = "# " + comment + "\n";

	Insert(line);

}


