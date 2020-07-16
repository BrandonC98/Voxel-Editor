#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: count(count)
{
		
	//genrate buffer 
	glGenBuffers(1, &id);	  
	//bind the buffer for use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	//populates the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}


IndexBuffer::~IndexBuffer()
{

	glDeleteBuffers(1, &id);

}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
