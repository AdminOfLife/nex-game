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

Sprite::Sprite(char * filename, int w, int h, SPRITE_TYPE stype, COLLISION_TYPE coltype)
{
	BM_INFOHEADER  bitmapInfoHeader;
	bitmap_ = new COLORREF[w * h];

	int ret = LoadBitmapFile(filename, &bitmapInfoHeader, bitmap_, w, h);

	if (ret != 0)
		printf("ERROR: Could not load bitmap file in Sprite constructor (return %d)", ret);

	width_ = w;
	height_ = h;
	drawType_ = stype;
	collType_ = coltype;
}

Sprite::~Sprite()
{
	printf("DELETE SPRITE\n");
	delete[] bitmap_;
}

void Sprite::DrawAt(Render* render, int x, int y)
{
	render->drawBitmap(bitmap_, x, y, width_, height_, 0xFFFFFF);
}

void Sprite::DrawAt(Render* render, int x, int y, double angle)
{
	COLORREF* tmp = new COLORREF[width_ * height_];
	int u, v;

	angle -= 3.141592359;

	for (int i = 0; i<height_; i++)
	{
		for (int j = 0; j<width_; j++)
		{
			u = (int)round(cos(angle) * (j - (height_ / 2)) + sin(angle) * (i - (width_ / 2)) + (width_ / 2));
			v = (int)round(-sin(angle) * (j - (height_ / 2)) + cos(angle) * (i - (width_ / 2)) + (height_ / 2));

			if (u >= 0 && u < width_ && v >= 0 && v < height_)
				tmp[(i * width_) + j] = bitmap_[(v * width_) + u];

			else
				tmp[(i * width_) + j] = 0xFFFFFF;
		}
	}

	render->drawBitmap(tmp, x - (width_ / 2), y - (height_ / 2), width_, height_, 0xFFFFFF);

	delete[] tmp;
}

void Sprite::getSize(int& width, int& height)
{
	width = width_;
	height = height_;
}

SPRITE_TYPE Sprite::getType()
{
	return drawType_;
}

COLLISION_TYPE Sprite::getColType()
{
	return collType_;
}
