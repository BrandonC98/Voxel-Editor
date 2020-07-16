
#include "VBuffer.h"

VBuffer::VBuffer(const void* data, unsigned int size)
{

	//genrate buffer 
	glGenBuffers(1, &id);	 
	glBindBuffer(GL_ARRAY_BUFFER, id);
	//populates the bound buffer
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);	


}

VBuffer::~VBuffer()
{

	glDeleteBuffers(1, &id);

}

void VBuffer::Bind() const
{

	//this becomes the active buffer
	glBindBuffer(GL_ARRAY_BUFFER, id);	

}

void VBuffer::Unbind() const
{

	//this removes it from the active buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);	

}
