#pragma once
#include "stdafx.h"

class TileMap;
class EntityManager;
class SpriteManager;

class Level
{
public:
	Level(EntityManager* em, SpriteManager* sm, char * seed);

	TileMap* getTileMap(int index);
	int getActiveMap();

private:
	vector<TileMap*> tileMapList_;
	int activeMap_;
};
