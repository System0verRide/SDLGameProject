#pragma once
#include <SDL.h>
#include <functional>
#include <vector>
#include <iostream>
#include <GL\glew.h>

namespace Game
{

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
		void Initialize(std::function<void()> OnInit, std::function<void()> OnFrame, std::function<void()> OnDestruction);
		void Quit();

		void Run();

		void AddEventCallback(EventCallback event);
		void RemoveEventCallback(EventCallback event);

		void SetFullscreen(Uint32 flag);

		SDL_Window* GetWindow();

		std::string GetLastError();

	private:
		void pollEventSystem();
		void dispatchEvent(SDL_Event e);

	private:
		std::vector<EventCallback> registeredEvents;
		std::vector<std::string> error;
		SDL_Window* window;
		SDL_GLContext context;
		bool running;

		/*
		std::fuctions (callbacks) for initialization, frame, and, destruction.
		Initialization called once on window creation.
		Frame called every frame.
		Destruction is called once before the destruction of the window.
		*/
		std::function<void()> init;
		std::function<void()> frame;
		std::function<void()> destruction;
	};

};