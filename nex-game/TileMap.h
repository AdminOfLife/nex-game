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
	Tile* GetTile(int index);
	void SetTile(int index, Tile tile);

protected:
	Tile tileList[20 * 15];

	friend class Screen;
};