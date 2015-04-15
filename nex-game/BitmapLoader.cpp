#include "stdafx.h"

#include <windows.h>
#include <stdio.h>

#include "BitmapLoader.h"

/*
 *	LoadBitMapFile:
 *	Written by: StackOverflow user 'ollo' at 2013/01/11
 *	Accessed: 15/04/2015 from http://stackoverflow.com/a/14279511
 */
unsigned char * LoadBitmapFile(char *filename, BM_INFOHEADER *bitmapInfoHeader, COLORREF output[])
{
	errno_t err;
	FILE *filePtr; //our file pointer
	BM_FILEHEADER bitmapFileHeader; //our bitmap file header
	unsigned char *bitmapImage;  //store image data
	COLORREF sprite;
	DWORD imageIdx = 0;  //image index counter
	unsigned char tempRGB;  //our swap variable

	//open filename in read binary mode
	err = fopen_s(&filePtr, filename, "rb");

	if (err != 0)
	{
		printf("ERROR: File '%s' not found.\n", filename);
		return NULL;
	}

	//read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BM_FILEHEADER), 1, filePtr);

	//verify that this is a bmp file by check bitmap id
	if (bitmapFileHeader.bfType != 0x4D42)
	{
		fclose(filePtr);
		return NULL;
	}

	//read the bitmap info header

	fread(bitmapInfoHeader, sizeof(BM_FILEHEADER), 1, filePtr);

	//move file point to the begging of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	//allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	//verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	//read in the bitmap image data
	fread(bitmapImage, sizeof(unsigned char), bitmapInfoHeader->biSizeImage, filePtr);

	//make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	int i = 0;
	//swap the r and b values to get RGB (bitmap is BGR)
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		output[i++] = RGB(bitmapImage[imageIdx + 0], bitmapImage[imageIdx + 1], bitmapImage[imageIdx + 2]);
	}

	//close file and return bitmap iamge data
	fclose(filePtr);
}
