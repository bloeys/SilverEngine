#version 330 core

layout (location = 0) in vec4 pos;

uniform mat4 projectionMat;
uniform mat4 viewMat = mat4(1.0);
uniform mat4 modelMat = mat4(1.0);

void main()
{
	gl_Position = projectionMat * viewMat * modelMat * pos;
}