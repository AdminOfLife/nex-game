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

Sprite::Sprite(char * filename, int w, int h, int zpriority, SPRITE_TYPE stype, COLLISION_TYPE coltype)
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
	colType = coltype;
}

Sprite::~Sprite()
{
	printf("DELETE SPRITE\n");
	delete[] bitmap;
}

void Sprite::DrawAt(Render* render, int x, int y)
{
	render->BlockShiftBitmap(bitmap, x, y, width, height, -1);
}

void Sprite::DrawAt(Render* render, int x, int y, double angle)
{
	COLORREF* tmp = new COLORREF[width * height];
	int u, v;

	angle -= 3.141592359;

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			u = round(cos(angle) * (j - (height / 2)) + sin(angle) * (i - (width / 2)) + (width / 2));
			v = round(-sin(angle) * (j - (height / 2)) + cos(angle) * (i - (width / 2)) + (height / 2));

			if (u >= 0 && u < width && v >= 0 && v < height)
				tmp[(i * width) + j] = bitmap[(v * width) + u];

			else
				tmp[(i * width) + j] = 0xFFFFFF;
		}
	}

	render->BlockShiftBitmap(tmp, x - (width / 2), y - (height / 2), width, height, 0xFFFFFF);

	delete[] tmp;
}

COLLISION_TYPE Sprite::GetColType()
{
	return colType;
}