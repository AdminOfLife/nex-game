/*
Screen
Handles a single map of 20x15 tiles and draws it.
*/
#include "stdafx.h"

#include "Screen.h"
#include "Render.h"
#include "Game.h"
#include "Sprite.h"
#include "Tile.h"
#include "Level.h"


Screen::Screen(Render * render, Game * game, Level * level)
{
	tileMap = level->GetTileMap(level->GetActiveMap());
}

Screen::~Screen()
{

}

void Screen::Update(Render * render)
{
	Tile tilemap[20 * 15];
	tileMap.GetTiles(tilemap);

	for (int i = 0; i < 20 * 15; ++i)
	{
		tilemap[i].Draw(render);
	}

	// Test stuff
	int x = 0;
	int y = 0;
	for (int i = 0; i < 20 * 15; ++i)
	{
		// Delete the tile from here
		// create a new tile and assign it to here
		x++;
		if (x == 20)
		{
			x = 0;
			y++;
		}
	}
}
