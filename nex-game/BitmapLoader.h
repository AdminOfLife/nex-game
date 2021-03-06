#pragma once
#include "stdafx.h"


// tight alignment for bitmap structure
#pragma pack(push, 1)
struct BM_FILEHEADER
{
	WORD bfType;			// specifies the file type
	DWORD bfSize;			// specifies the size in bytes of the bitmap file
	WORD bfReserved1;		// reserved; must be 0
	WORD bfReserved2;		// reserved; must be 0
	DWORD bfOffBits;		// species the offset in bytes from the bitmapfileheader to the bitmap bits
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BM_INFOHEADER
{
	DWORD biSize;			// specifies the number of bytes required by the struct
	LONG biWidth;			// specifies width in pixels
	LONG biHeight;			// species height in pixels
	WORD biPlanes;			// specifies the number of color planes, must be 1
	WORD biBitCount;		// specifies the number of bit per pixel
	DWORD biCompression;	// spcifies the type of compression
	DWORD biSizeImage;		// size of image in bytes
	LONG biXPelsPerMeter;	// number of pixels per meter in x axis
	LONG biYPelsPerMeter;	// number of pixels per meter in y axis
	DWORD biClrUsed;		// number of colors used by th ebitmap
	DWORD biClrImportant;	// number of colors that are important
};
#pragma pack(pop)

int LoadBitmapFile(char *filename, BM_INFOHEADER *bitmapInfoHeader, COLORREF output[], int width, int height);
