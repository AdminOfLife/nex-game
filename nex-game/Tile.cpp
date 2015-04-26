/*
Tile
A [Tile] consists of a sprite and a tile position.
A tile position is an x,y between [(0,0),(20,15)].
*/

#include "stdafx.h"

#include "Sprite.h"
#include "Tile.h"


Tile::Tile()
{
	//
}

Tile::Tile(int x, int y, Sprite* spr)
{
	sprite = spr;
	tilePosX = x;
	tilePosY = y;
	posX = x * 16;
	posY = y * 16;
}

Tile::~Tile()
{
	// nothing to delete
}

void Tile::Draw(Render* render)
{
	sprite->DrawAt(render, posX, posY);
}

void Tile::SetSprite(Sprite* spr)
{
	sprite = spr;
}

Sprite* Tile::GetSprite()
{
	return sprite;
}

void Tile::GetTilePos(int &x, int &y)
{
	x = tilePosX;
	y = tilePosY;
}
void Tile::getPos(int &x, int &y)
{
	x = posX;
	y = posY;
}
