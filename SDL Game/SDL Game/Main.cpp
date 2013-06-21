#include <SDL.h>

int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 1;
	}

	SDL_Window *window = nullptr;
	window = SDL_CreateWindow("Game", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

	if(window == nullptr)
	{
		return 1;
	}


	SDL_Renderer *renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == nullptr)
	{
		return 1;
	}

	bool running = true;
	SDL_Event e;
	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				running = false;
			}

		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	return 0;
}