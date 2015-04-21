#pragma once

#include <windows.h>

#include "Render.h"


enum SPRITE_TYPE
{
	GUI, // ui
	MAP, // map tiles
	CHR, // characters
	ENT  // entities
};

class Sprite
{
public:
	Sprite();
	Sprite(char * filename, int w, int h, int zpriority, SPRITE_TYPE type);
	~Sprite();
	void DrawAt(Render render, int x, int y);

private:
	COLORREF * bitmap;
	int width;
	int height;
	int zPriority;
	SPRITE_TYPE type;
};