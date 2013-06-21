#include "Window.h"


Window::Window(const char* title)
{
	running = true;

	window = nullptr;
	SDL_CreateWindow(title, 0, 0, 640, 480, SDL_WINDOW_SHOWN);
	
	if(window == nullptr)
	{
		running = false;
	}

	renderer = nullptr;
	SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == nullptr)
	{
		running = false;
	}

	init();
	
	while(running)
	{
		pollEventSystem();
		frame();
	}
}

Window::Window(const Window& other)
{

}

Window::~Window(void)
{
}

void Window::AddEventCallback(EventCallback event)
{
	registeredEvents.push_back(event);
}

void Window::RemoveEventCallback(EventCallback event)
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


void Window::pollEventSystem()
{
	SDL_Event e;

	SDL_PollEvent(&e);
	dispatchEvent(e);
}

void Window::dispatchEvent(SDL_Event e)
{
	if(!registeredEvents.empty())
	{
		for(unsigned int i = 0; i < registeredEvents.size(); i++)
		{
			if(registeredEvents.at(i).e.type == e.type)
			{
				registeredEvents.at(i).Dispatch(e);
			}
		}
	}
}

void Window::frame()
{

}