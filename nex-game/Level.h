#pragma once
#include "stdafx.h"

#include "Game.h"
#include "TileMap.h"


class Level
{
public:
	Level(Game * game, char * seed);
	TileMap GetTileMap(int index);
	int GetActiveMap();

private:
	vector<TileMap> TileMapList;
	int ActiveMap;
};