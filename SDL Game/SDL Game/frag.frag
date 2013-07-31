#version 330 core

out vec4 out_Color;
in float light;
in vec3 height;

void main (void)
{
	float colorClamp = 1.0 - height.length();
	colorClamp = colorClamp*5;
	float brightness = mix(0.0, 1.0, colorClamp);
	out_Color = vec4(light, light, light, 1.0);
}