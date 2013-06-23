#pragma once
#include "Window.h"

class Framework
{
public:
	Framework(void);
	Framework(const Framework& other);
	~Framework(void);

public:
	

private:
	Game::Window* Window;
};

