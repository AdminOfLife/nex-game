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

void Screen::Update(Render * render, Game * game)
{
	if (game->GameState != GAME_STATE_ACTIVE)
		return;
		
	Tile tilemap[20 * 15];
	tileMap.GetTiles(tilemap);

	for (int i = 0; i < 20 * 15; ++i)
	{
		tilemap[i].Draw(render);
	}

	return;
}
