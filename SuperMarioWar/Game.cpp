#include "Game.h"

#include <iostream>

using namespace std;

SMW::Game::Game()
{
}

SMW::Game::~Game()
{
	for (auto dummy : _dummies)
	{
		if (dummy != nullptr)
		{
			delete dummy;
		}

		_dummies.clear();
	}
}

bool SMW::Game::InitializeGame(int argc, char** argv)
{
	cout << "Initializing SMW game..." << endl;
	_dummies.push_back(new Dummy(_gameOptions, Point<float>(0.0f, 0.0f)));
	_dummies.push_back(new Dummy(_gameOptions, Point<float>(64.0f, 0.0f)));
	_dummies.push_back(new Dummy(_gameOptions, Point<float>(0.0f, 64.0f)));
	_dummies.push_back(new Dummy(_gameOptions, Point<float>(64.0f, 64.0f)));

	cout << "Done." << endl << endl;
	return true;
}

void SMW::Game::Render()
{
	for (auto dummy : _dummies)
	{
		dummy->Render();
	}
}

void SMW::Game::Think()
{
	for (auto dummy : _dummies)
	{
		dummy->Think(_dummies);
	}
}