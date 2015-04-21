#pragma once
#include "stdafx.h"

#include "Game.h"
#include "Tile.h"

class TileMap
{
public:
	TileMap(); // empty constructor does nothing
	TileMap(Game * game);
	TileMap(Game * game, Tile tiles[20 * 15]);
	void GetTiles(Tile tiles[]);

private:
	Tile * tileList;
};