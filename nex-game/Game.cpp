#include "stdafx.h"
#include <iostream>

#include "BitmapLoader.h"
#include "Render.h"
#include "Game.h"
#include "Sprite.h"

Game::Game()
{
	GameState = GAME_STATE_INIT;
	GameTick = 0;
}

Game::~Game()
{
	//
}

void Game::AddSprite(Sprite* sprite)
{
	SpriteList.push_back(sprite);
}

Sprite* Game::GetSprite(int index)
{
	return SpriteList.at(index);
}

void Game::Splash(Render * render)
{
	COLORREF tmpsplash[320 * 240];
	BM_INFOHEADER  bitmapInfoHeader;

	int ret = LoadBitmapFile("spl.bmp", &bitmapInfoHeader, tmpsplash, 320, 240);

	render->BlockShiftBitmap(tmpsplash, 0, 0, 320, 240);
}

int Game::Update(Render * render)
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
			render->Clear();
			GameState = GAME_STATE_ACTIVE;
		}
	}

	if (_kbhit())
	{
		char c = _getch();

		switch (c)
		{
		case 'w':;
		case 's':;
		case 'a':;
		case 'd':;
		}

		system("cls");
	}

	POINT p;
	GetCursorPos(&p);

	ScreenToClient(render->WindowHandle, &p);


	// Game rule code

	GameTick++;

	return 0;
}