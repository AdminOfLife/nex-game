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
	void Game::Init();
	void Wait(int ms);
	int Update(Render* render);
	void MoveCharacter(double direction, double speed);
	void DrawString(char* string, COLORREF colour);

	GState GameState;
	Render* GameRenderer;
	SpriteManager* GameSpriteManager;

	Level* GameLevel;

private:
	int GameTick;
	DWORD WaitTick;
	Character* GamePlayer;
	EntityManager* entityManager_;

	COLORREF Splash[320 * 240];
	COLORREF CharMap[16 * 1520];
};
