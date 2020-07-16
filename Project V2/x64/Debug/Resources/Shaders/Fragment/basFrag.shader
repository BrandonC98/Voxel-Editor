#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Colour;

void main()
{
	color = u_Colour;
};