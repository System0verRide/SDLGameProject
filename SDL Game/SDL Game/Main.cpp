#include <SDL.h>
#include <random>
#include "Window.h"

Window theWindow;
int r = 0;
int g = 255;
int b = 0;

void OnQuit(SDL_Event e)
{
	theWindow.Quit();
}

void Initialize(Window* window)
{
	EventCallback OnQuit(SDL_QUIT, OnQuit);
	window->AddEventCallback(OnQuit);
	window->SetFullscreen(SDL_WINDOW_FULLSCREEN);
}

void Frame(Window* window)
{
	SDL_SetRenderDrawColor(window->GetRenderer(), rand()%255, rand()%255, rand()%255, 255);
	SDL_RenderClear(window->GetRenderer());
	SDL_RenderPresent(window->GetRenderer());
	SDL_Delay(10);
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