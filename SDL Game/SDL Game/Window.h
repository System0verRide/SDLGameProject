#pragma once
#include <SDL.h>
#include <functional>
#include <vector>

class EventCallback
{
	//Function pointers to member functions must use std::bind
public:
	EventCallback(SDL_Event event, std::function<void(SDL_Event)> functor)
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
	SDL_Event e;

private:
	std::function<void(SDL_Event e)> f;
	int UUID;
	static int refcount;
};

class Window
{
public:
	Window(const char* title);
	Window(const Window& other);
	~Window(void);

public:
	void Initialize();
	void Quit();

	void AddEventCallback(EventCallback event);
	void RemoveEventCallback(EventCallback event);

private:
	void pollEventSystem();
	void dispatchEvent(SDL_Event e);
	void frame();

private:
	std::vector<EventCallback> registeredEvents;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;
};
