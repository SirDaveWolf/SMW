#pragma once
#include "BaseGame.h"
#include "Dummy.h"
#include <vector>

namespace SMW
{
	class Game : public BaseGame
	{
	public:
		Game();
		~Game();

	protected:
		virtual bool InitializeGame(int argc, char** argv);

		virtual void Render();
		virtual void Think();

	private:
		std::vector<BaseEntity*> _dummies;
	};
}
