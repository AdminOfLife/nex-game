#pragma once
#include "stdafx.h"

#include "Render.h"
#include "Sprite.h"


class Game
{
public:
	Game();
	~Game();
	void AddSprite(Sprite sprite);
	void Splash(Render * render);
	int Update(Render * render);
	Sprite GetSprite(int index);

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
	vector<Sprite> SpriteList;
};