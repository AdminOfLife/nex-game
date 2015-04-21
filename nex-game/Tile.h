#pragma once
#include "stdafx.h"

#include "Sprite.h"


class Tile
{
public:
	Tile();
	Tile(int x, int y, Sprite spr);
	~Tile();
	void Draw(Render * render);
private:
	Sprite sprite;
	int posX;
	int posY;
};