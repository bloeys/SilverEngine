#version 330 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 col;

uniform mat4 projectionMat;
uniform mat4 viewMat = mat4(1.0);
uniform mat4 modelMat = mat4(1.0);

out data
{
	vec4 pos;
	vec4 col;
} outData;


void main()
{
	gl_Position = projectionMat * viewMat * modelMat * pos;
	
	outData.pos = gl_Position;
	outData.col = col;
}