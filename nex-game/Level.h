#pragma once
#include "stdafx.h"

class TileMap;
class EntityManager;
class SpriteManager;

class Level
{
public:
	Level(EntityManager* em, SpriteManager* sm, char * seed);
	TileMap* GetTileMap(int index);
	int GetActiveMap();

private:
	vector<TileMap*> TileMapList;
	int ActiveMap;
};
