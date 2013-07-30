#pragma once
#include <functional>
#include <glm.hpp>
#include <gtc/constants.hpp>
#include <gtc/matrix_transform.hpp>
#include "Atmosphere.h"
#include "Shader.h"
#include "Window.h"

class Framework
{
public:
	Framework(void);
	Framework(const Framework& other);
	~Framework(void);

public:
	void Start();

private:
	Game::Window* Window;
	Atmosphere* theAtmosphere;
	Shader* atmosphereShader;

	glm::vec3 cameraView;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 worldMatrix;
	glm::mat4 worldViewProjectionMatrix;

	int worldViewProjectionMatrixLoc;

private:
	void Initialize();
	void Frame();
	void Destruction();

	//Event System
	void OnQuit(SDL_Event e);
	void OnKeyDown(SDL_Event e);
	void OnKeyUp(SDL_Event e);

};

