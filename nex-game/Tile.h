#pragma once
#include "stdafx.h"

class Sprite;
class Render;

class Tile
{
public:
	Tile();
	Tile(int x, int y, Sprite* spr);
	~Tile();
	void Draw(Render* render);
	void SetSprite(Sprite* spr);
	Sprite* GetSprite();
	void GetTilePos(int &x, int &y);
	void getPos(int &x, int &y);

private:
	Sprite* sprite;
	int tilePosX; // 0-19
	int tilePosY; // 0-14
	int posX; // screen pos
	int posY; // screen pos
};
