#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Colour;
uniform vec4 lightColour;


void main()
{
	
	float ambientStrength = 0.5f;
	vec4 ambient = ambientStrength * lightColour;

	vec4 result = ambient * u_Colour;


	color = result;
};