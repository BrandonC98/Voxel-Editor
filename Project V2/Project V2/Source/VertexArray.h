#pragma once
#include <GL\glew.h>
#include "VBuffer.h"

class VertexArray
{

private:
	unsigned int id;
	float stride;

	int index;
	int componentsPerVert;	
	bool normalised;

public:
	VertexArray();
	~VertexArray();

	
	void AddBuffer(const VBuffer& vb);
	void Bind() const;
	void Unbind() const;
	void SetStride(float size);
	void VertexBufferLayout(int index, int compPerV, bool normalised);
};

