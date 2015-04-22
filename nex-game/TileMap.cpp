/*
TileMap
A [TileMap] is a 20x15 set of [Sprite]s which must be 16x16 pixels.

*/
#include "stdafx.h"

#include "Game.h"
#include "Render.h"
#include "Sprite.h"
#include "Tile.h"
#include "TileMap.h"


TileMap::TileMap()
{
	//
}

TileMap::TileMap(Game * game)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < 20 * 15; ++i)
	{
		tileList[i] = Tile(x, y, game->GetSprite(rand() % 2));
		x++;
		if (x == 20)
		{
			x = 0;
			y++;
		}
	}
}

TileMap::TileMap(Game * game, Tile tiles[20 * 15])
{
	for (int i = 0; i < 20 * 15; ++i)
		tileList[i] = tiles[i];
}

void TileMap::GetTiles(Tile tile[])
{
	for (int i = 0; i < 20 * 15; ++i)
		tile[i] = tileList[i];
}

Tile* TileMap::GetTile(int index)
{
	return &tileList[index];
}

void TileMap::SetTile(int index, Tile tile)
{
	tileList[index] = tile;
}