#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <cmath>

#include "Render.h"
#include "Sprite.h"
#include "Game.h"
#include "Screen.h"

HBITMAP image;
HWND hWnd;

Render::Render()
{
	hWnd = GetConsoleWindow();
	// set console stuff
	COORD size = { CONSOLE_SIZE_X, CONSOLE_SIZE_Y };
	SetConsoleScreenBufferSize(hWnd, size);

	FrameBuffer = new COLORREF[FBUFFER_SIZE];
}

Render::~Render()
{
}

void Render::SetFrameBufferPixel(int x, int y, COLORREF colour)
{
	FrameBuffer[(y * SCREEN_SIZE_X) + x] = colour;
}

void Render::BlockShiftBitmap(COLORREF * arrptr, int posx, int posy, int width, int height) // arr length should be width * height
{
	int iter = 0;

	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			//printf("%06x\n", arrptr[iter]);
			FrameBuffer[((posy + y) * SCREEN_SIZE_X) + (posx + x)] = arrptr[iter++];
		}
	}
}

void Render::Clear()
{
	for(int i = 0; i < FBUFFER_SIZE; ++i)
		FrameBuffer[i] = 0;
}

void Render::Update()
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
	y = (height / 2) - (SCREEN_SIZE_Y / 2);

	// get/create stuff
	hdc = GetDC(hWnd);
	hdcMem = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, SCREEN_SIZE_X, SCREEN_SIZE_Y);

	SelectObject(hdcMem, bitmap);

	// Copy each sprite to draw onto the virtual hdc
	int bufferpointer = 0;
		
	for (int y = 0; y < SCREEN_SIZE_Y; y++)
	{
		for (int x = 0; x < SCREEN_SIZE_X; x++)
		{
			SetPixel(hdcMem, x, y, FrameBuffer[bufferpointer++]);
		}
	}

	// blt the virtual DC into the screen DC
	BitBlt(hdc, x, y, c.right - c.left, SCREEN_SIZE_Y, hdcMem, 0, 0, SRCCOPY);

	// clean up
	DeleteDC(hdcMem);
	DeleteObject(bitmap);
	ReleaseDC(hWnd, hdc);
}



/*

#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <cmath>

#include "Render.h"

void Render::SetFrameBufferPixel(COLORREF fBuf[], int x, int y, COLORREF colour)
{
fBuf[(y * SCREEN_SIZE_Y) + x] = colour;
}

Render::Render()
{
// console handle
WindowHandle = GetConsoleWindow();

// set console stuff
COORD size = { CONSOLE_SIZE_X, CONSOLE_SIZE_Y };
SetConsoleScreenBufferSize(WindowHandle, size);

printf("w %d h %d buffer %d (%d bytes)", SCREEN_SIZE_X, SCREEN_SIZE_Y, FBUFFER_SIZE, FBUFFER_SIZE*4);
}

Render::~Render()
{
printf("Goodbye");
}

void Render::Update()
{
draw(FrameBuffer);
render(WindowHandle, FrameBuffer);
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

SetFrameBufferPixel(fBuf, x, y, RGB(255, 0, 0));
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