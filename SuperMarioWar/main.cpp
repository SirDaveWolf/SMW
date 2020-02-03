#include "Game.h"

int main(int argc, char** argv)
{
	auto game = new SMW::Game();

	if (game->Initialize(argc, argv))
	{
		game->Run();
	}

	return 0;
}