// nex-game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "BitmapLoader.h"
#include "Render.h"
#include "Sprite.h"
#include "Game.h"
#include "Tile.h"
#include "Map.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//SetConsoleTitle(L"NEXER - Explore the internet!");
	SetConsoleTitle(L"Southclaw's 2D Retro Rendering Rapter!");

	Render render = Render();
	Map map = Map(render);
	Game game = Game();

	for (int i = 0; i < 3840; i++)
		printf("#");

	game.Splash(render);

	while (game.GameState != game.GAME_STATE_END)
	{
		game.Update(render);
		map.Update(render);
		render.Update();
	}

	return 0;
}
/*
int randrange(int min, int max)
{
	return min + (rand() % (int)(max - min + 1));
}

void test(Render render)
{
	int x = 0, y = 0;
	COLORREF c;

	for (int i = 0; i < 100; i++)
	{
		x = randrange(0, SCREEN_SIZE_X);
		y = randrange(0, SCREEN_SIZE_Y);
		c = RGB(randrange(0, 255), randrange(0, 255), randrange(0, 255));
		render.SetFrameBufferPixel(x, y, c);
	}
}

*/