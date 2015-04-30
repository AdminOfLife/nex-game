#pragma once
#include "stdafx.h"

class Render;
class Sprite;
class SpriteManager;
class EntityManager;
class Level;
class Character;

enum GState
{
	GAME_STATE_INIT,
	GAME_STATE_ACTIVE,
	GAME_STATE_END
};

class Game
{
public:
	Game(Render* render, SpriteManager* sf);
	~Game();
	void init();
	void wait(int ms);
	int update(Render* render);
	void drawText(char* string, COLORREF colour);

	GState GameState;

	Level* GameLevel;

private:
	int gameTick_;
	DWORD waitTick_;

	Render* renderHandle_;
	EntityManager* entityManager_;
	SpriteManager* spriteManager_;
	Character* playerCharacter_;

	COLORREF splashBmp_[320 * 240];
	COLORREF charMapBmp_[16 * 1520];
};
