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
#include "Map.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleTitle(L"Nex - Explore the internet!");

	Render render = Render();
	Map map = Map(render);
	Game game = Game();

	game.GameState = game.GAME_STATE_ACTIVE;
	char * filename = "fl1.bmp";
	COLORREF test[8 * 8];

	unsigned char * bitmap;
	BM_INFOHEADER  bitmapInfoHeader ;

	bitmap = LoadBitmapFile(filename, &bitmapInfoHeader);

	for (int i = 0; i < 8 * 8; ++i)
	{
		test[i] = RGB(255, 255, 0);
	}

	for (int i = 0; i <= 2068; i++)
		printf("#");

	printf("\n\n");

	while (game.GameState == game.GAME_STATE_ACTIVE)
	{
		game.Update(render);
		map.Update(render);
		render.BlockShiftBitmap(bitmap, 1, 1, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight);
		render.Update();
		Sleep(60000);
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