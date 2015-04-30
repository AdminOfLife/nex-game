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


/*

#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <cmath>

#include "Render.h"

void Render::setFrameBufferPixel(COLORREF fBuf[], int x, int y, COLORREF colour)
{
fBuf[(y * SCREEN_SIZE_Y) + x] = colour;
}

Render::Render()
{
// console handle
windowHandle_ = GetConsoleWindow();

// set console stuff
COORD size = { CONSOLE_SIZE_X, CONSOLE_SIZE_Y };
SetConsoleScreenBufferSize(windowHandle_, size);

printf("w %d h %d buffer %d (%d bytes)", SCREEN_SIZE_X, SCREEN_SIZE_Y, FBUFFER_SIZE, FBUFFER_SIZE*4);
}

Render::~Render()
{
printf("Goodbye");
}

void Render::update()
{
draw(frameBuffer_);
render(windowHandle_, frameBuffer_);
}

void Render::draw(COLORREF fBuf[])
{
for (int i = 0; i < FBUFFER_SIZE; i++)
fBuf[i] = RGB(188, 188, 188);

int
x = (SCREEN_SIZE_X / 2),
y = (SCREEN_SIZE_Y / 2);

double
r = 0.0;

for (int i = 0; i < 100; i++)
{
x += (int)(2 * sin(0.1));
y += (int)(2 * cos(0.1));

setFrameBufferPixel(fBuf, x, y, RGB(255, 0, 0));
}
}

void Render::render(HWND hWnd, COLORREF fBuf[])
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

GetClientRect(hWnd, &c);

width = c.right - c.left;
height = c.bottom - c.top;

// calculate the position to render based on window size and frame size
int x, y;
x = (width / 2) - (SCREEN_SIZE_X / 2);
y = (height / 2) - (SCREEN_SIZE_Y / 2);;

// get/create stuff
hdc = GetDC(hWnd);
hdcMem = CreateCompatibleDC(hdc);
bitmap = CreateCompatibleBitmap(hdc, SCREEN_SIZE_X, SCREEN_SIZE_Y);

SelectObject(hdcMem, bitmap);

// print the buffer (fBuf) into the hdcMem virtual device

// blt the virtual DC into the screen DC
BitBlt(hdc, x, y, c.right - c.left, 200, hdcMem, 0, 0, SRCCOPY);

// clean up
DeleteDC(hdcMem);
DeleteObject(bitmap);
ReleaseDC(hWnd, hdc);
}

*/
