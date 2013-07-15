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

	glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
}

void Framework::Start()
{
	Window->Initialize(std::bind(&Framework::Initialize, this), std::bind(&Framework::Frame, this), std::bind(&Framework::Destruction, this));
	Window->Run();
}

void Framework::Frame()
{
	glViewport(0, 0, 640, 480);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(Window->GetWindow());
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