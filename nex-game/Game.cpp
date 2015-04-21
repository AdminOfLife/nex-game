#include "stdafx.h"
#include <iostream>

#include "BitmapLoader.h"
#include "Render.h"
#include "Game.h"


Game::Game()
{
	GameState = GAME_STATE_INIT;
	GameTick = 0;

}

Game::~Game()
{
	//
}

void Game::Splash(Render render)
{
	COLORREF tmpsplash[320 * 240];
	BM_INFOHEADER  bitmapInfoHeader;

	int ret = LoadBitmapFile("spl.bmp", &bitmapInfoHeader, tmpsplash, 320, 240);

	render.BlockShiftBitmap(tmpsplash, 0, 0, 320, 240);
}

int Game::Update(Render render)
{
	if (GameState == GAME_STATE_INIT)
	{
		// render.BlockShiftBitmap(SplashScreen, 0, 0, 16, 16);
		// Pause the game and display the splash screen for a bit
		GameTick++;

		if (GameTick < 10)
		{
			return 1;
		}
		else
		{
			render.Clear();
			GameState = GAME_STATE_ACTIVE;
		}
	}

	// Game rule code

	GameTick++;

	return 0;
}