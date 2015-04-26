#include "stdafx.h"
#include <iostream>

#include "BitmapLoader.h"
#include "Render.h"
#include "Game.h"
#include "Screen.h"
#include "Level.h"
#include "TileMap.h"
#include "Tile.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Character.h"


Game::Game(Render* render, SpriteManager* sm)
{
	BM_INFOHEADER  bitmapInfoHeader;

	GameRenderer = render;
	GameState = GAME_STATE_INIT;
	GameTick = 0;
	GameSpriteManager = sm;

	LoadBitmapFile("lespl.bmp", &bitmapInfoHeader, Splash, 320, 240);
	LoadBitmapFile("charmap.bmp", &bitmapInfoHeader, CharMap, 16, 1520);
}

Game::~Game()
{
	//
}

void Game::Init()
{
	GameRenderer->BlockShiftBitmap(Splash, 0, 0, 320, 240, -1);

	entityManager_ = new EntityManager();

	GamePlayer = new Character(entityManager_, GameSpriteManager, GameSpriteManager->GetSprite(2), { 8, 16 }, 0.0);
	GameLevel = new Level(GameSpriteManager, "NEXER");// "http://en.wikipedia.org/wiki/Main_Page");
}

void Game::Wait(int ms)
{
	WaitTick = GetTickCount() + ms;
}

double absoluteangle(double angle)
{
	while (angle < 0.0)angle += 360.0;
	while (angle > 360.0)angle -= 360.0;
	return angle;
}

int Game::Update(Render* render)
{
	if (GetTickCount() < WaitTick)
		return 1;

	if (GameState == GAME_STATE_INIT)
	{
		GameTick++;

		DrawString("Nice Memes :o)", RGB(255, 255, 128));

		if (GameTick < 100)
		{
			return 2;
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
		case ' ':
			GamePlayer->fireWeapon();
			break;
		}
	}

	if (GameState != GAME_STATE_ACTIVE)
		return 3;

	// Character movement
	POINT curspos;
	POINT charpos;

	GetCursorPos(&curspos);
	ScreenToClient(render->WindowHandle, &curspos);
	render->ClientToFrame(&curspos);

	// should hide the cursor only when it's hovered over the draw frame
	// doesn't seem to work
	/*
	if ((curspos.x < 0 || curspos.x > SCREEN_SIZE_X) && (curspos.y < 0 || curspos.y > SCREEN_SIZE_Y))
		ShowCursor(true);

	else
		ShowCursor(false);
	*/

	GamePlayer->getPos(charpos);

	double distance = sqrt(pow(curspos.x - charpos.x, 2) + pow(curspos.y - charpos.y, 2));
	double angle = absoluteangle(3.141592359 - atan2(curspos.x - charpos.x, curspos.y - charpos.y)) - 3.141592359;

	if (distance > 30.0 && distance < 300.0)
	{
		double speed = (distance > 4.0 ? 4.0 : distance) * 0.9;
		GamePlayer->setVelocity(speed * sin(-angle), speed * cos(-angle));
	}
	else
	{
		GamePlayer->setVelocity(0.0, 0.0);
	}

	GamePlayer->setAngle(angle);

	// Tile drawing
	Tile tilemap[20 * 15];
	GameLevel->GetTileMap(GameLevel->GetActiveMap())->GetTiles(tilemap);

	for (int i = 0; i < 20 * 15; ++i)
	{
		tilemap[i].Draw(render);
	}

	// Draw the character after tiles
	GamePlayer->update();
	GamePlayer->draw(render);

	GameTick++;

	return 0;
}


void Game::DrawString(char* string, COLORREF colour)
{
	int length = strlen(string);
	int charpos = 0;
	int idxpos = 0;

	// Width (x) = length * 16, Height = 16
	COLORREF* bitmap = new COLORREF[(length * 16) * 16];

	if (bitmap == nullptr)
	{
		printf("ERROR: Could not allocate memory for DrawString bitmap, size: %d", (length * 16) * 16);
		return;
	}

	for (int i = 0; i < (length * 16) * 16; i++)
		bitmap[i] = RGB(255, 128, 0);

	int r, g, b;
	int u = (colour >> 0) & 0xFF;
	int v = (colour >> 8) & 0xFF;
	int w = (colour >> 16) & 0xFF;

	int pixel = 0;

	for (int character = 0; character < length; ++character)
	{
		charpos = (string[character] - ' ') * 16 * 16;
		// memcpy(&bitmap[i * 16 * 16], &CharMap[charpos], 16 * 16 * 4);

		pixel = 0;

		for (int x = 0; x < 16; ++x)
		{
			for (int y = 0; y < 16; ++y)
			{
				r = (((CharMap[charpos + pixel] >> 0) & 0xFF) + 255 - u);
				g = (((CharMap[charpos + pixel] >> 8) & 0xFF) + 255 - v);
				b = (((CharMap[charpos + pixel] >> 16) & 0xFF) + 255 - w);

				idxpos = 16 * (x * length) + y + 16 * character;// ((pixel % 16) + (pixel / 16)) * 16 * length + 16 * character;// pixel + (character * 16 * 16);

				if (idxpos > (length * 16) * 16)
				{
					printf("ERROR:");
				}

				bitmap[idxpos] = RGB(r, g, b);;

				pixel++;
			}
		}
	}

	GameRenderer->BlockShiftBitmap(bitmap, 160 - ((length * 16) / 2), 112, length * 16, 16, 0xFFFFFF);

	delete[] bitmap;
}
