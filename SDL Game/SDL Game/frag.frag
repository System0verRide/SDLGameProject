#version 330 core

varying vec3 v3Direction;
out vec4 out_Color;

void main (void)
{
	float fCos = dot(v3LightPos, v3Direction) / length(v3Direction);
	float fMiePhase = 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos*fCos) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
    gl_FragColor = gl_Color + fMiePhase * gl_SecondaryColor;
	gl_FragColor.a = gl_FragColor.b;
}