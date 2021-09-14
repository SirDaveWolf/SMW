#include "BaseGame.h"
#include <chrono>
#include <thread>
#include <iostream>

#include "json.hpp"
#include "File.h"

using json = nlohmann::json;
using namespace std;

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
	cout << "Initializing..." << endl;
	if (!LoadSettings())
		return false;

	cout << "Init GLFW..." << endl;
	if (!glfwInit()) 
		return false;

	_terminated = false;

	int width = _gameOptions.ScreenWidth;
	int height = _gameOptions.ScreenHeight;

	cout << "Creating window (" << width << "x" << height << ")..." << endl;
	_gameWindow = glfwCreateWindow(width, height, "Super Mario War", NULL, NULL);
	if (_gameWindow == nullptr)
	{
		Terminate();
		return false;
	}

	cout << "Setting up OpenGL renderer..." << endl;
	glfwMakeContextCurrent(_gameWindow);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glOrtho(0, width, height, 0, 0, 128);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cout << "Done." << endl << endl;
	return this->InitializeGame(argc, argv);
}

bool SMW::BaseGame::LoadSettings()
{
	cout << "Loading settings file 'settings.json'..." << endl;
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	bool result = true;
	try
	{
		string fileContents = File::ReadAllText("settings.json");
		json config = json::parse(fileContents);

		_gameOptions.MaxFPS = config["settings"]["MaxFPS"];
		_gameOptions.ScreenWidth = config["settings"]["ScreenWidth"];
		_gameOptions.ScreenHeight = config["settings"]["ScreenHeight"];
		_gameOptions.BaseEntityWidth = config["settings"]["BaseEntityWidth"];
		_gameOptions.BaseEntityHeight = config["settings"]["BaseEntityHeight"];
	}
	catch (exception ex)
	{
		cout << "Error at loading config: " << ex.what() << endl;
	}

	return result;
}

void SMW::BaseGame::Run()
{
	while (!glfwWindowShouldClose(_gameWindow))
	{
		auto start = chrono::high_resolution_clock::now().time_since_epoch().count();

		DoRender();
		DoThink();

		glfwPollEvents();

		auto diff = chrono::nanoseconds((chrono::high_resolution_clock::now().time_since_epoch().count()) - start);
		auto waitTime = (long long)(1000.0 / _gameOptions.MaxFPS * 1000000.0) - diff.count();
		if (waitTime < 0) waitTime = 0;
		this_thread::sleep_for(chrono::nanoseconds(waitTime));
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