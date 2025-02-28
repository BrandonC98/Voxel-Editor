#pragma once
#include <GL\glew.h>

class IndexBuffer
{

private:
	unsigned int id;	
	unsigned int count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind()const;

	inline unsigned int GetCount() const { return count; }

};
