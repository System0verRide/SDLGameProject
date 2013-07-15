#pragma once
#include <functional>
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

private:
	void Initialize();
	void Frame();
	void Destruction();

	//Event System
	void OnQuit(SDL_Event e);
	void OnKeyDown(SDL_Event e);
	void OnKeyUp(SDL_Event e);

};

