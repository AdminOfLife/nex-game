#pragma once
#include "stdafx.h"


const int CONSOLE_SIZE_X = 80;
const int CONSOLE_SIZE_Y = 30;
const int SCREEN_SIZE_X = 320;
const int SCREEN_SIZE_Y = 240;
const int FBUFFER_SIZE = (SCREEN_SIZE_X * SCREEN_SIZE_Y);

typedef struct
{
	double x, y, z;
} VECTOR;

typedef struct
{
	VECTOR cx, cy, cz;
} MATRIX;

typedef struct
{
	VECTOR shift;
	MATRIX rotate;
} TRANSFORM;

typedef struct
{
	int nv;					// Number of vertices
	VECTOR vert[20];		// Array of vertices - position vectors
	COLORREF colour;		// Colour, struct of 3 BYTE's R, G, B

	VECTOR normal;			//Surface Normal Vector

	int vertVecNo[20];		// holds vertex vector number
//	TEXMAP *texMap;			// pointer to texture map
//	TEXCOORD texPos[20];	//Position of corresponding numbered vertex in texture map
} POLYGON;

class Render
{
public:
	Render();
	~Render();
	void setFrameBufferPixel(int x, int y, COLORREF colour);
	void drawBitmap(COLORREF* arr, int x, int y, int width, int height, COLORREF trans); // arr length should be width * height
	void drawLine();
	void drawPolygon(POLYGON* p);
	void clear();
	void update();

	void clientToFrame(POINT* point);

	HWND windowHandle_; // todo: safe interface

private:
	COLORREF * frameBuffer_;
	void drawTrapezium(COLORREF c, int& st_x, int& st_y, int& en_x, int& en_y, float sl_l, float sl_r);
};
