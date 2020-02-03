#include "BaseGame.h"
#include <fstream>

SMW::BaseGame::BaseGame()
	: _gameWindow(nullptr), _terminated(true)
{
	_renderOptions = RenderOptions();
	_renderOptions.MaxFPS = 60;
	_renderOptions.ScreenWidth = 640;
	_renderOptions.ScreenHeight = 480;
	_renderOptions.BaseEntityWidth = _renderOptions.ScreenWidth / 20.0f;
	_renderOptions.BaseEntityHeight = _renderOptions.ScreenHeight / 15.0f;
}

SMW::BaseGame::~BaseGame()
{
	Terminate();
}

bool SMW::BaseGame::Initialize(int argc, char** argv)
{
	if (!LoadSettings())
		return false;

	if (!glfwInit()) 
		return false;

	_terminated = false;

	int width = 640;
	int height = 480;

	_gameWindow = glfwCreateWindow(width, height, "Super Mario War", NULL, NULL);
	if (_gameWindow == nullptr)
	{
		Terminate();
		return false;
	}

	glfwMakeContextCurrent(_gameWindow);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;
	glViewport(0, 0, width, height);
	glOrtho(0, width, height, 0, 0, 128);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return this->InitializeGame(argc, argv);
}

bool SMW::BaseGame::LoadSettings()
{
	bool result = true;
	try
	{
		auto configFile = std::ifstream();
		configFile.open("settings.cfg", std::ifstream::in);

		if (configFile.is_open())
		{

		}

		configFile.close();
	}
	catch (std::exception ex)
	{
		result = false;
	}

	return result;
}

void SMW::BaseGame::Run()
{
	while (!glfwWindowShouldClose(_gameWindow))
	{
		DoRender();
		DoThink();

		glfwPollEvents();
	}
}

void SMW::BaseGame::DoRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Render();

	glfwSwapBuffers(_gameWindow);
}

void SMW::BaseGame::DoThink()
{
	Think();
}

void SMW::BaseGame::Terminate()
{
	if (!_terminated)
	{
		glfwTerminate();
		_terminated = true;
	}
}