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
	// Unfinished, currently just randomises.

	int mapcount = 1;
	TileMap* a;

	for (int i = 0; i < mapcount; ++i)
	{
		tileMapList_.push_back(a = new TileMap(em, sm));
	}

	activeMap_ = 0;
}

TileMap* Level::getTileMap(int index)
{
	return tileMapList_.at(index);
}

int Level::getActiveMap()
{
	return activeMap_;
}
