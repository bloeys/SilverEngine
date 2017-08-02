#version 330 core

in data
{
	vec4 pos;
	vec4 col;
} inData;

out vec4 color;

void main()
{
	color = inData.col;
}