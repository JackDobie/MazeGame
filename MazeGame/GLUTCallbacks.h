#pragma once
class Game;

namespace GLUTCallbacks
{
	void Init(Game* gl);
	void Display();
	void Timer(int preferredRefresh);
	void Restart(int);
}