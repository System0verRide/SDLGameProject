#include <SDL.h>
#include "Framework.h"
#include "ConfigLoader.h"


int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return 1;
	}
	ConfigLoader::OpenConfig("configuration.config");
	std::cout << "Using Seed: " << ConfigLoader::ReadString("seed") << std::endl;
	std::cout << "Number Of Icosphere Iterations: " << ConfigLoader::ReadString("iterations") << std::endl;
	Framework framework;
	framework.Start();

	return 0;
}