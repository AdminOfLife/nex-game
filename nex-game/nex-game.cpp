// nex-game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

#include "Render.h"
#include "Sprite.h"
#include "Game.h"
#include "Map.h"



int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTitle(L"Nex - Explore the internet!");

	Render render = Render();
	Map map = Map(render);
	Game game = Game();

	game.GameState = game.GAME_STATE_ACTIVE;

	for (int i = 0; i <= 2068; i++)
		printf("#");

	while (game.GameState == game.GAME_STATE_ACTIVE)
	{
		game.Update(render);
		map.Update(render);
		render.Update();
	}

	return 0;
}
