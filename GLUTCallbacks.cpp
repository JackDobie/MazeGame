#include "GLUTCallbacks.h"
#include "Game.h"

namespace GLUTCallbacks
{
	namespace
	{
		Game* game = nullptr;
	}

	void Init(Game* gl)
	{
		game = gl;
	}

	void Display()
	{
		if (game != nullptr)
		{
			game->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		if (game != nullptr)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			game->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			game->deltaTime = (float)updateTime;
			glutTimerFunc(preferredRefresh, GLUTCallbacks::Timer, preferredRefresh);
		}
	}

	void Restart(int)
	{

	}
}