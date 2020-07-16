#pragma once

#include <GL\glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderManager.h"

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer&, const ShaderManager& shader) const;
	void Clear() const;

};

