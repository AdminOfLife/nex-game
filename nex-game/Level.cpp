/*
Level
Groups together a set of [TileMap]s which are composed of [Tile]s
*/

#include "stdafx.h"

#include "Game.h"
#include "Level.h"
#include "TileMap.h"

Level::Level(Game * game, char * seed)
{
	game->GameRenderer->Clear();
	game->DrawString(seed, RGB(255, 255, 128));
	game->Wait(3000);
	
	// generate a set of TileMaps based on seed

	int mapcount = 3;

	for (int i = 0; i < mapcount; ++i)
	{
		TileMapList.push_back(TileMap(game));
	}
}

TileMap Level::GetTileMap(int index)
{
	return TileMapList.at(index);
}

int Level::GetActiveMap()
{
	return ActiveMap;
}
