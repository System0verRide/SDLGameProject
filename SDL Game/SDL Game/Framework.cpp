#include "Framework.h"


Framework::Framework(void)
{
	Window = new Game::Window();
}

Framework::Framework(const Framework& other)
{

}

Framework::~Framework(void)
{
	delete Window;
}

void Framework::Initialize()
{
	//Register Event Callbacks here
	Game::EventCallback OnQuitCallback = Game::EventCallback(SDL_QUIT, std::bind(&Framework::OnQuit, this, std::placeholders::_1));
	Game::EventCallback OnKeyDownCallback = Game::EventCallback(SDL_KEYDOWN, std::bind(&Framework::OnKeyDown, this, std::placeholders::_1));
	Game::EventCallback OnKeyUpCallback = Game::EventCallback(SDL_KEYUP, std::bind(&Framework::OnKeyUp, this, std::placeholders::_1));

	Window->AddEventCallback(OnQuitCallback);
	Window->AddEventCallback(OnKeyDownCallback);
	Window->AddEventCallback(OnKeyUpCallback);
}

void Framework::Start()
{
	Window->Initialize(std::bind(&Framework::Initialize, this), std::bind(&Framework::Frame, this), std::bind(&Framework::Destruction, this));
	Window->Run();
}

void Framework::Frame()
{
	SDL_RenderClear(Window->GetRenderer());
	SDL_RenderPresent(Window->GetRenderer());
}

void Framework::Destruction()
{

}

void Framework::OnQuit(SDL_Event e)
{
	Window->Quit();
}

void Framework::OnKeyDown(SDL_Event e)
{

}

void Framework::OnKeyUp(SDL_Event e)
{

}