/*
Tile
A [Tile] consists of a sprite and a tile position.
A tile position is an x,y between [(0,0),(20,15)].
*/

#include "stdafx.h"

#include "Tile.h"


Tile::Tile()
{
	// never used explicitly but just here for empty allocations
	posX = 0;
	posY = 0;
}

Tile::Tile(int x, int y, Sprite spr)
{
	sprite = spr;
	posX = x;
	posY = y;
}

Tile::~Tile()
{
	//
}

void Tile::Draw(Render * render)
{
	sprite.DrawAt(render, posX * 16, posY * 16);
}