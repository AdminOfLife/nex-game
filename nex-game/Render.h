#pragma once

#include <windows.h>

const int CONSOLE_SIZE_X = 120;
const int CONSOLE_SIZE_Y = 30;
const int SCREEN_SIZE_X = 320;
const int SCREEN_SIZE_Y = 240;
const int FBUFFER_SIZE = (SCREEN_SIZE_X * SCREEN_SIZE_Y);

class Render
{
public:
	Render();
	~Render();
	void Update();
	void SetFrameBufferPixel(int x, int y, COLORREF colour);
	//void DrawSprite(Sprite sprite, int x, int y);

private:
	HWND windowhandle;
	COLORREF framebuffer[FBUFFER_SIZE];
};
