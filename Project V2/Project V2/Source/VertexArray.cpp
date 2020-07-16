#include "VertexArray.h"


VertexArray::VertexArray()
{

	glGenVertexArrays(1, &id);


}

VertexArray::~VertexArray()
{

	glDeleteVertexArrays(1, &id);

}

void VertexArray::Bind() const
{

	glBindVertexArray(id);

}

void VertexArray::Unbind() const
{


	glBindVertexArray(0);
}

void VertexArray::VertexBufferLayout(int _index, int _compPerV, bool _normalised)
{

	index = _index;
	componentsPerVert = _compPerV;
	normalised = _normalised;

}

void VertexArray::AddBuffer(const VBuffer& vb)
{

	Bind();
	vb.Bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, componentsPerVert, GL_FLOAT, normalised, stride, 0);

}

//used to distinguish where a set of data end and a new one starts
void VertexArray::SetStride(float size)
{
	
	stride = sizeof(float)* size;

}



