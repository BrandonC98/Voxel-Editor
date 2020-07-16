#pragma once

#include <GL\glew.h>

class VBuffer
{

private:
	unsigned int id;	

public:
	VBuffer(const void* data, unsigned int size);
	~VBuffer();
	void Bind() const;
	void Unbind() const;

};

