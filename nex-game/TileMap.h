#pragma once
#include "stdafx.h"

#include "Game.h"
#include "Tile.h"

class SpriteManager;
class EntityManager;

class TileMap
{
public:
	TileMap(); // empty constructor does nothing
	TileMap(EntityManager* em, SpriteManager * sf);
	TileMap(Tile* tileList[20 * 15]);

	void getTiles(Tile* tileList[]);
	Tile* getTile(int index);
	void setTile(int index, Tile* tile);

protected:
	Tile* tileList_[20 * 15];
};
