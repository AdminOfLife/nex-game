#pragma once
#include "stdafx.h"

class TileMap;
class SpriteManager;

class Level
{
public:
	Level(SpriteManager* sm, char * seed);
	TileMap* GetTileMap(int index);
	int GetActiveMap();

private:
	vector<TileMap*> TileMapList;
	int ActiveMap;
};
