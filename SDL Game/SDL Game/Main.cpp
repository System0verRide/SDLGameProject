#include <SDL.h>
#include "Window.h"

Window theWindow;

void OnQuit(SDL_Event e)
{
	theWindow.Quit();
}

void Initialize(Window* window)
{
	EventCallback OnQuit(SDL_QUIT, OnQuit);
	window->AddEventCallback(OnQuit);
}

void Frame(Window* window)
{

}

void Destruction(Window* window)
{

}

int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 1;
	}

	theWindow.Initialize(Initialize, Frame, Destruction);

	theWindow.Run();

	return 0;
}