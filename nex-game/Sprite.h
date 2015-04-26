#pragma once
#include "stdafx.h"

class Render;

enum SPRITE_TYPE
{
	MAP, // map tiles
	ENT, // entities
	CHR, // characters
	GUI  // ui
};

enum COLLISION_TYPE
{
	NOCOLL,
	CIRCLE,
	SQUARE
};

class Sprite
{
public:
	Sprite();
	Sprite(char* filename, int w, int h, SPRITE_TYPE stype, COLLISION_TYPE coltype);
	~Sprite();
	void DrawAt(Render* render, int x, int y);
	void DrawAt(Render* render, int x, int y, double angle);
	bool IsCollidingWith(Sprite* spr);
	bool IsCollidingWith(int x, int y, double range);

	void getSize(int& width, int& height);
	SPRITE_TYPE getType();
	COLLISION_TYPE GetColType();

private:
	COLORREF * bitmap_;
	int width_;
	int height_;
	SPRITE_TYPE drawType_;
	COLLISION_TYPE collType_;
};