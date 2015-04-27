/*
Level
Groups together a set of [TileMap]s which are composed of [Tile]s
*/

#include "stdafx.h"

#include "Level.h"
#include "TileMap.h"
#include "EntityManager.h"
#include "SpriteManager.h"

Level::Level(EntityManager* em, SpriteManager* sm, char * seed)
{
	// generate a set of TileMaps based on seed

	int mapcount = 1;
	TileMap* a;

	for (int i = 0; i < mapcount; ++i)
	{
		TileMapList.push_back(a = new TileMap(em, sm));
	}
}

TileMap* Level::GetTileMap(int index)
{
	return TileMapList.at(index);
}

int Level::GetActiveMap()
{
	return ActiveMap;
}
