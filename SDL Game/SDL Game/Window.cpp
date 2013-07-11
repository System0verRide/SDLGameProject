#include "Window.h"

int Game::EventCallback::refcount = 0;

Game::Window::Window()
{

}

Game::Window::Window(const Window& other)
{

}

Game::Window::~Window(void)
{
}

void Game::Window::Initialize(std::function<void()> OnInit, std::function<void()> OnFrame, std::function<void()> OnDestruction)
{
	running = true;

	window = nullptr;
	window = SDL_CreateWindow("Game", 200, 200, 640, 480, SDL_WINDOW_SHOWN);
	
	if(window == nullptr)
	{
		running = false;
		error.push_back("Window creation has failed...");
	}

	/*
	OpenGL 4.0 Context Creation
	*/

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	context = SDL_GL_CreateContext(window);

	gl::sys::LoadFunctions();

	/*
	renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == nullptr)
	{
		running = false;
		error.push_back("Could not create a valid render context");
	}
	*/

	init = OnInit;
	frame = OnFrame;
	destruction = OnDestruction;
}

void Game::Window::Run()
{
	init();

	while(running)
	{
		pollEventSystem();
		frame();
	}

	destruction();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::Window::SetFullscreen(Uint32 flag)
{
	SDL_SetWindowFullscreen(window, flag);
}

SDL_Renderer* Game::Window::GetRenderer()
{
	return renderer;
}

void Game::Window::Quit()
{
	running = false;
}

void Game::Window::AddEventCallback(EventCallback event)
{
	registeredEvents.push_back(event);
}

void Game::Window::RemoveEventCallback(EventCallback event)
{
	std::vector<EventCallback>::iterator it = registeredEvents.begin();
	for(unsigned int i = 0; i < registeredEvents.size(); i++)
	{
		if(event.GetUUID() == registeredEvents.at(i).GetUUID())
		{
			it += i;
			registeredEvents.erase(it);
			break;
		}
	}
}

std::string Game::Window::GetLastError()
{
	return error.back();
}


void Game::Window::pollEventSystem()
{
	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		dispatchEvent(e);
		
	}
}

void Game::Window::dispatchEvent(SDL_Event e)
{
	if(!registeredEvents.empty())
	{
		for(unsigned int i = 0; i < registeredEvents.size(); i++)
		{
			if(registeredEvents.at(i).e == e.type)
			{
				registeredEvents.at(i).Dispatch(e);
			}
		}
	}
}
