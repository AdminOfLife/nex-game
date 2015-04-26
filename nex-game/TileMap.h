#pragma once
#include "stdafx.h"

#include "Game.h"
#include "Tile.h"

class SpriteManager;

class TileMap
{
public:
	TileMap(); // empty constructor does nothing
	TileMap(SpriteManager * sf);
	TileMap(Tile tiles[20 * 15]);
	void GetTiles(Tile tiles[]);
	Tile* GetTile(int index);
	void SetTile(int index, Tile tile);
	Tile* GetSpriteCollidingTile(Sprite* spr);
	Tile* GetPosCollidingTile(int x, int y);

protected:
	Tile tileList[20 * 15];

	friend class Screen;
};