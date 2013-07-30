#include "AtmosphereShader.h"

AtmosphereShader::AtmosphereShader(void)
{
	raylieghConstant = 0.0025f;
	mieConstant = 0.0010f;
	innerRadius = 1.0f;
	innerRadius2 = innerRadius * innerRadius;
	outerRadius = 1.2f;
	outerRadius2 = outerRadius * outerRadius;
	cameraHeight = glm::length(cameraPos - glm::vec3(0.0f, 0.0f, 0.0f));
	cameraHeight2 = cameraHeight * cameraHeight;
	scale = 1 / (innerRadius * outerRadius);

	waveLength[0] = 0.650f;
	waveLength[1] = 0.570f;
	waveLength[2] = 0.475f;
	wavelength4[0] = std::powf(waveLength[0], 4.0f);
	wavelength4[1] = std::powf(waveLength[1], 4.0f);
	wavelength4[2] = std::powf(waveLength[2], 4.0f);
}


AtmosphereShader::~AtmosphereShader(void)
{
}
