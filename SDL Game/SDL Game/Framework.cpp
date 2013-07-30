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

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		
	glEnable(GL_BLEND);				
	glAlphaFunc(GL_GREATER,0.1);
	glEnable(GL_ALPHA_TEST);					
	glEnable(GL_TEXTURE_2D);					
	glEnable(GL_CULL_FACE);
	glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
	theAtmosphere = new Atmosphere();
	theAtmosphere->Init();
	atmosphereShader = new Shader();
	atmosphereShader->Init("vert.vert", "frag.frag");
	projectionMatrix = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraView = glm::vec3(2.0f, 2.0f, 2.0f);
	//Uniform locations

	atmosphereShader->Bind();

	atmosphereShader->Unbind();
}

void Framework::Start()
{
	Window->Initialize(std::bind(&Framework::Initialize, this), std::bind(&Framework::Frame, this), std::bind(&Framework::Destruction, this));
	Window->Run();
}

void Framework::Frame()
{
	worldMatrix = glm::rotate(worldMatrix, 0.1f, glm::vec3(0, 1, 0));
	worldViewProjectionMatrix = projectionMatrix * viewMatrix * worldMatrix;
	glViewport(0, 0, 800, 600);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	atmosphereShader->Bind();
	worldViewProjectionMatrixLoc = glGetUniformLocation(atmosphereShader->Id(), "worldViewProjectionMatrix");
	int cameraViewLoc = glGetUniformLocation(atmosphereShader->Id(), "cameraPos");
	glUniformMatrix4fv(worldViewProjectionMatrixLoc, 1, GL_FALSE, &worldViewProjectionMatrix[0][0]);
	glUniform3f(cameraViewLoc, cameraView.x, cameraView.y, cameraView.z); 
	theAtmosphere->Draw();
	atmosphereShader->Unbind();
	SDL_GL_SwapWindow(Window->GetWindow());
}

void Framework::Destruction()
{
	theAtmosphere->Destroy();
	delete theAtmosphere;
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