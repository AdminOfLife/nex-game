#include "stdafx.h"

#include "Tile.h"


Tile::Tile()
{
	//
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

void Tile::Draw(Render render)
{
	sprite.DrawAt(render, posX * 16, posY * 16);
}