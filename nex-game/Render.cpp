#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <cmath>

#include "Render.h"
#include "Sprite.h"
#include "Game.h"

Render::Render()
{
	windowHandle_ = GetConsoleWindow();
	// set console stuff
	COORD size = { CONSOLE_SIZE_X, CONSOLE_SIZE_Y };
	SetConsoleScreenBufferSize(windowHandle_, size);

	frameBuffer_ = new COLORREF[FBUFFER_SIZE];
}

Render::~Render()
{
}

void Render::setFrameBufferPixel(int x, int y, COLORREF colour)
{
	frameBuffer_[(y * SCREEN_SIZE_X) + x] = colour;
}

void Render::drawBitmap(COLORREF* arrptr, int posx, int posy, int width, int height, COLORREF trans)
{
	if (posx < 0 || posx > SCREEN_SIZE_X)
	{
		printf("ERROR: drawBitmap attempted to write in a negative X value (%d).", posx);
		return;
	}

	if (posy < 0 || posy > SCREEN_SIZE_Y)
	{
		printf("ERROR: drawBitmap attempted to write in a negative Y value (%d).", posy);
		return;
	}

	int iter = 0;

	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			if (x < 0 || x > SCREEN_SIZE_X)
				continue;

			if (y < 0 || y > SCREEN_SIZE_Y)
				continue;

			if (arrptr[iter] == trans)
			{
				iter++;
				continue;
			}

			frameBuffer_[((posy + y) * SCREEN_SIZE_X) + (posx + x)] = arrptr[iter++];
		}
	}
}

void Render::drawLine()
{
}

void Render::drawPolygon(POLYGON* p)
{
	int
		topVert = 0,
		botVert = 0;

	for (int i = 0; i < p->nv; ++i)
	{
		if (p->vert[i].y < p->vert[topVert].y)
			topVert = i;

		if (p->vert[i].y > p->vert[botVert].y)
			botVert = i;
	}

	int
		currentLeft = topVert,
		currentRight = topVert,
		nextLeft = (currentLeft == 0) ? p->nv - 1 : currentLeft - 1,
		nextRight = (currentRight == p->nv - 1) ? 0 : currentRight + 1;

	// Check for straight lines along X for the left side by stepping from current to next and comparing their Y's
	while ((abs(p->vert[currentLeft].y - p->vert[nextLeft].y) < 0.01))
	{
		currentLeft = nextLeft;
		nextLeft = (currentLeft == 0) ? p->nv - 1 : currentLeft - 1;
	}
	// Then again for right side
	while ((abs(p->vert[currentRight].y - p->vert[nextRight].y) < 0.01))
	{
		currentRight = nextRight;
		nextRight = (currentRight == p->nv - 1) ? 0 : currentRight + 1;
	}

	// Now calculate the slopes of each side
	float
		slopeLeft = (p->vert[currentLeft].x - p->vert[nextLeft].x) / (p->vert[currentLeft].y - p->vert[nextLeft].y),
		slopeRight = (p->vert[currentRight].x - p->vert[nextRight].x) / (p->vert[currentRight].y - p->vert[nextRight].y);

	int
		st_x = p->vert[currentLeft].x,
		en_x = p->vert[currentRight].x,
		st_y = p->vert[currentLeft].y,
		en_y = p->vert[nextRight].y < p->vert[nextLeft].y ? p->vert[nextRight].y : p->vert[nextLeft].y; // or nextLeft

	drawTrapezium(p->colour, st_x, st_y, en_x, en_y, slopeLeft, slopeRight);

	do
	{
		if (int(p->vert[nextLeft].y) > en_y)
		{
			// A right side vert completed a trapezium
			// increment right marker
			currentRight = (currentRight == p->nv - 1) ? 0 : currentRight + 1;
			nextRight = (currentRight == p->nv - 1) ? 0 : currentRight + 1;

			// the slopeRight needs to be re-calculated since the algorithm reached a vert on the right side slopeLeft remains the same.
			slopeRight = (p->vert[currentRight].x - p->vert[nextRight].x) / (p->vert[currentRight].y - p->vert[nextRight].y);

			// the start and end Y values are updated with the current and next vert positions.
			st_y = p->vert[currentRight].y;
			en_y = p->vert[nextRight].y <= p->vert[nextLeft].y ? p->vert[nextRight].y : p->vert[nextLeft].y;

			drawTrapezium(p->colour, st_x, st_y, en_x, en_y, slopeLeft, slopeRight);
		}
		else
		{
			// A left side vert completed a trapezium
			// increment left marker
			currentLeft = (currentLeft == 0) ? p->nv - 1 : currentLeft - 1;
			nextLeft = (currentLeft == 0) ? p->nv - 1 : currentLeft - 1;

			slopeLeft = (p->vert[currentLeft].x - p->vert[nextLeft].x) / (p->vert[currentLeft].y - p->vert[nextLeft].y),
				st_y = p->vert[currentLeft].y;
			en_y = p->vert[nextRight].y <= p->vert[nextLeft].y ? p->vert[nextRight].y : p->vert[nextLeft].y;

			drawTrapezium(p->colour, st_x, st_y, en_x, en_y, slopeLeft, slopeRight);
		}
	}
	while (currentLeft != botVert && currentRight != botVert);
}

void Render::drawTrapezium(COLORREF c, int& st_x, int& st_y, int& en_x, int& en_y, float sl_l, float sl_r)
{
	if (en_x < st_x)
		return;

	if (st_x < 0)
		return;

	if (en_x < 0)
		return;

	float f_st_x = float(st_x);
	float f_en_x = float(en_x);

	for (int i = st_y; i < en_y; i++)
	{
		for (int j = f_st_x; j < f_en_x; j++)
		{
			frameBuffer_[(i * SCREEN_SIZE_X) + j] = c;
		}
		f_st_x += sl_l;
		f_en_x += sl_r;
	}

	st_x = int(f_st_x);
	en_x = int(f_en_x);
}

void Render::clear()
{
	for(int i = 0; i < FBUFFER_SIZE; ++i)
		frameBuffer_[i] = 0;
}

void Render::update()
{
	// the device context
	HDC hdc;

	// the in-memory virtual device
	HDC hdcMem;

	// the bitmap frame buffer
	HBITMAP bitmap;

	// the rectangle of the inner console window
	RECT c;

	int width, height;

	GetClientRect(windowHandle_, &c);

	width = c.right - c.left;
	height = c.bottom - c.top;

	// calculate the position to render based on window size and frame size
	int x, y;
	x = (width / 2) - (SCREEN_SIZE_X / 2);
	y = (height / 2) - (SCREEN_SIZE_Y / 2);

	// get/create stuff
	hdc = GetDC(windowHandle_);
	hdcMem = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, SCREEN_SIZE_X, SCREEN_SIZE_Y);

	SelectObject(hdcMem, bitmap);

	// Copy each sprite to draw onto the virtual hdc
	int bufferpointer = 0;
		
	for (int y = 0; y < SCREEN_SIZE_Y; y++)
	{
		for (int x = 0; x < SCREEN_SIZE_X; x++)
		{
			SetPixel(hdcMem, x, y, frameBuffer_[bufferpointer++]);
		}
	}

	// blt the virtual DC into the screen DC
	BitBlt(hdc, x, y, c.right - c.left, SCREEN_SIZE_Y, hdcMem, 0, 0, SRCCOPY);

	// clean up
	DeleteDC(hdcMem);
	DeleteObject(bitmap);
	ReleaseDC(windowHandle_, hdc);
}

void Render::clientToFrame(POINT* point)
{
	RECT c;

	GetClientRect(windowHandle_, &c);

	point->x -= ((c.right - c.left) / 2) - (SCREEN_SIZE_X / 2);
	point->y -= ((c.bottom - c.top) / 2) - (SCREEN_SIZE_Y / 2);
}
