#version 150 core

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;

in vec3 in_Position;

void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(in_Position, 1.0);
}