/*
Sprite
A sprite consists of a bitmap, a position, a z-priority for rendering and a type.
*/

#pragma once
#include "stdafx.h"

#include "Sprite.h"
#include "Render.h"
#include "BitmapLoader.h"


Sprite::Sprite()
{
	//
}

Sprite::Sprite(char * filename, int w, int h, int zpriority, SPRITE_TYPE stype, bool issolid)
{
	BM_INFOHEADER  bitmapInfoHeader;
	bitmap = new COLORREF[w * h];

	int ret = LoadBitmapFile(filename, &bitmapInfoHeader, bitmap, w, h);

	if (ret != 0)
		printf("ERROR: Could not load bitmap file in Sprite constructor (return %d)", ret);

	width = w;
	height = h;
	zPriority = zpriority;
	type = stype;
	solid = issolid;
}

Sprite::~Sprite()
{
	//
}

void Sprite::DrawAt(Render * render, int x, int y)
{
	render->BlockShiftBitmap(bitmap, x, y, width, height, -1);
}