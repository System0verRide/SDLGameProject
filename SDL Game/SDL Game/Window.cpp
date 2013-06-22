#include "Window.h"

int EventCallback::refcount = 0;

Window::Window()
{

}

Window::Window(const Window& other)
{

}

Window::~Window(void)
{
}

void Window::Initialize(std::function<void(Window* window)> OnInit, std::function<void(Window* window)> OnFrame, std::function<void(Window* window)> OnDestruction)
{
	running = true;

	window = nullptr;
	window = SDL_CreateWindow("Game", 200, 200, 1920, 1080, SDL_WINDOW_SHOWN);
	
	if(window == nullptr)
	{
		running = false;
		error.push_back("Window creation has failed...");
	}

	renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == nullptr)
	{
		running = false;
		error.push_back("Could not create a valid render context");
	}

	init = OnInit;
	frame = OnFrame;
	destruction = OnDestruction;
}

void Window::Run()
{
	init(this);

	while(running)
	{
		pollEventSystem();
		frame(this);
	}

	destruction(this);
}

void Window::SetFullscreen(Uint32 flag)
{
	SDL_SetWindowFullscreen(window, flag);
}

SDL_Renderer* Window::GetRenderer()
{
	return renderer;
}

void Window::Quit()
{
	running = false;
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

std::string Window::GetLastError()
{
	return error.back();
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
			if(registeredEvents.at(i).e == e.type)
			{
				registeredEvents.at(i).Dispatch(e);
			}
		}
	}
}
