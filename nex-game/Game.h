#pragma once

class Game
{
public:
	Game();
	~Game();
	void Update(Render);

	enum GState
	{
		GAME_STATE_INIT,
		GAME_STATE_ACTIVE,
		GAME_STATE_END
	};

	GState GameState;

private:
};