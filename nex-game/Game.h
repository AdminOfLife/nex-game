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
	Game(Render* render);
	~Game();
	void Wait(int ms);
	void AddSprite(Sprite* sprite);
	void DrawSplash();
	int Update(Render* render);
	Sprite* GetSprite(int index);
	void DrawString(char* string, COLORREF colour);

	GState GameState;
	Render* GameRenderer;

private:
	int GameTick;
	DWORD WaitTick;
	vector<Sprite*> SpriteList;

	COLORREF Splash[320 * 240];
	COLORREF CharMap[16 * 1520];
};
