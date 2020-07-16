#include "Renderer.h"


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderManager& shader) const
{

	shader.Bind();
	va.Bind();
	ib.Bind();

	//draws the object to the screem
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::Clear() const
{

	//clears the buffers 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
