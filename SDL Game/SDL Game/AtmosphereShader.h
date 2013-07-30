#pragma once
#include "Shader.h"
#include <glm.hpp>
#include <math.h>

class AtmosphereShader : public Shader
{
public:
	AtmosphereShader(void);
	~AtmosphereShader(void);

	void UpdateWorldViewProjMatrix(glm::mat4 matrix);
	void UpdateCameraPos(glm::vec3 camPos);
	void UpdateLightPos(glm::vec3 lightPos);

private:
	glm::vec3 cameraPos;
	glm::vec3 lightPos;
	glm::vec3 invWavelength;
	float cameraHeight;
	float cameraHeight2;
	float outerRadius;
	float outerRadius2;
	float innerRadius;
	float innerRadius2;
	float raylieghConstant;
	float mieConstant;
	float raylieghConstant4Pi;
	float mieConstant4Pi;
	float scale;
	float scaleDepth;
	float scaleOverScaleDepth;

	float waveLength[3];
	float wavelength4[3];

	int uniformLocations[17];
};

