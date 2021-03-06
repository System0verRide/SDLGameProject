#version 330 core

uniform mat4 worldViewProjectionMatrix;
uniform vec3 cameraPos;

in vec3 in_Normal;
in vec3 in_Position;
out float light;


void main()
{
	vec3 lightPos = vec3(1, 0.3, 0.3);
	vec4 surfaceNormal = worldViewProjectionMatrix * vec4(in_Normal, 0.0);
	light = max(dot(surfaceNormal.xyz, lightPos), 0.0);
	gl_Position = worldViewProjectionMatrix * vec4(in_Position, 1.0);
}