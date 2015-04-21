#pragma once

class Game
{
public:
	Game();
	~Game();
	void Splash(Render render);
	int Update(Render render);

	enum GState
	{
		GAME_STATE_INIT,
		GAME_STATE_ACTIVE,
		GAME_STATE_END
	};

	GState GameState;

private:
	int GameTick;
	char KeyBuffer[6];
	char KeyBufferPtr = 0;
};