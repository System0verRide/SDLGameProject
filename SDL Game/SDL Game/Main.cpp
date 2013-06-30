#include <SDL.h>
#include "Framework.h"


int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 1;
	}

	Framework framework;
	framework.Start();

	return 0;
}