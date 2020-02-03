#pragma once
#include "GLFW/glfw3.h"
#include "RenderOptions.h"

namespace SMW
{
	class BaseGame
	{
	public:
		BaseGame();
		~BaseGame();

		bool Initialize(int argc, char** argv);
		void Run();

	protected:
		virtual bool InitializeGame(int argc, char** argv) = 0;

		virtual void Render() = 0;
		virtual void Think() = 0;

		void Terminate();

		RenderOptions _renderOptions;

	private:

		void DoRender();
		void DoThink();

		bool LoadSettings();

		GLFWwindow* _gameWindow;
		bool _terminated;
	};
}

