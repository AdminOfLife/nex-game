#pragma once
#include "stdafx.h"

#include "Render.h"
#include "Sprite.h"

enum GState
{
	GAME_STATE_INIT,
	GAME_STATE_ACTIVE,
	GAME_STATE_END
};

class Game
{
public:
	Game();
	~Game();
	void AddSprite(Sprite* sprite);
	void Splash(Render* render);
	int Update(Render* render);
	Sprite* GetSprite(int index);

	GState GameState;

private:
	int GameTick;
	vector<Sprite*> SpriteList;
};
