#pragma once
#include <SDL.h>
#include <functional>
#include <vector>



class EventCallback
{
	//Function pointers to member functions must use std::bind
public:
	EventCallback(SDL_EventType event, std::function<void(SDL_Event)> functor)
	{
		e = event;
		f = functor;
		refcount++;
		UUID = refcount;
	}

public:
	int GetUUID()
	{
		return UUID;
	}

	void Dispatch(SDL_Event e)
	{
		f(e);
	}

public:
	SDL_EventType e;

private:
	std::function<void(SDL_Event e)> f;
	int UUID;
	static int refcount;
};

class Window
{
public:
	Window();
	Window(const Window& other);
	~Window(void);

public:
	void Initialize(std::function<void(Window* window)> OnInit, std::function<void(Window* window)> OnFrame, std::function<void(Window* window)> OnDestruction);
	void Quit();

	void Run();

	void AddEventCallback(EventCallback event);
	void RemoveEventCallback(EventCallback event);

	std::string GetLastError();

private:
	void pollEventSystem();
	void dispatchEvent(SDL_Event e);

private:
	std::vector<EventCallback> registeredEvents;
	std::vector<std::string> error;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;

	std::function<void(Window* window)> init;
	std::function<void(Window* window)> frame;
	std::function<void(Window* window)> destruction;
};
