#include "BaseGame.h"
#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>

SMW::BaseGame::BaseGame()
	: _gameWindow(nullptr), _terminated(true)
{
	_gameOptions = GameOptions();
	_gameOptions.MaxFPS = 60;
	_gameOptions.ScreenWidth = 640;
	_gameOptions.ScreenHeight = 480;
	_gameOptions.BaseEntityWidth = _gameOptions.ScreenWidth / 20.0f;
	_gameOptions.BaseEntityHeight = _gameOptions.ScreenHeight / 15.0f;
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
		auto start = std::chrono::high_resolution_clock::now().time_since_epoch().count();

		DoRender();
		DoThink();

		glfwPollEvents();

		auto diff = std::chrono::milliseconds((std::chrono::high_resolution_clock::now().time_since_epoch().count()) - start);
		auto waitTime = (long long)(1000.0 / _gameOptions.MaxFPS * 1000000.0) - diff.count();
		if (waitTime < 0) waitTime = 0;
		std::this_thread::sleep_for(std::chrono::nanoseconds(waitTime));
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