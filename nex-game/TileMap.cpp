/*
TileMap
A [TileMap] is a 20x15 set of [Sprite]s which must be 16x16 pixels.

*/
#include "stdafx.h"

#include "Game.h"
#include "Render.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "EntityManager.h"
#include "Tile.h"
#include "TileMap.h"


TileMap::TileMap()
{
	//
}

TileMap::TileMap(EntityManager* em, SpriteManager* sm)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < 20 * 15; ++i)
	{
		if (i%15 == 0)
			tileList[i] = new Tile(em, sm->GetSprite(3), x, y);

		else
			tileList[i] = new Tile(em, sm->GetSprite(rand() % 2), x, y);

		x += 16;
		if (x >= 320)
		{
			x = 0;
			y += 16;
		}
	}
}

TileMap::TileMap(Tile* tiles[20 * 15])
{
	for (int i = 0; i < 20 * 15; ++i)
		tileList[i] = tiles[i];
}

void TileMap::getTiles(Tile* tile[])
{
	for (int i = 0; i < 20 * 15; ++i)
		tile[i] = tileList[i];
}

Tile* TileMap::getTile(int index)
{
	return tileList[index];
}

void TileMap::setTile(int index, Tile* tile)
{
	tileList[index] = tile;
}
