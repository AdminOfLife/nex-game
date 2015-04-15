#include "stdafx.h"

#include <windows.h>
#include <stdio.h>

#include "BitmapLoader.h"

/*
 *	LoadBitMapFile:
 *	Written by: StackOverflow user 'ollo' at 2013/01/11
 *	Accessed: 15/04/2015 from http://stackoverflow.com/a/14279511
 */
int LoadBitmapFile(char *filename, BM_INFOHEADER *bitmapInfoHeader, COLORREF output[])
{
	errno_t err;
	FILE *filePtr; //our file pointer
	BM_FILEHEADER bitmapFileHeader; //our bitmap file header
	unsigned char *bitmapImage;  //store image data
	DWORD imageIdx = 0;  //image index counter

	//open filename in read binary mode
	err = fopen_s(&filePtr, filename, "rb");

	if (err != 0)
	{
		printf("ERROR: File '%s' not found.\n", filename);
		return 1;
	}

	//read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BM_FILEHEADER), 1, filePtr);

	//verify that this is a bmp file by check bitmap id
	if (bitmapFileHeader.bfType != 0x4D42)
	{
		fclose(filePtr);
		return 2;
	}

	//read the bitmap info header
	fread(bitmapInfoHeader, sizeof(BM_FILEHEADER) * 4, 1, filePtr);

//	printf("\n\n%d = biSize\n", bitmapInfoHeader->biSize);
//	printf("%d = biWidth\n", bitmapInfoHeader->biWidth);
//	printf("%d = biHeight\n", bitmapInfoHeader->biHeight);
//	printf("%d = biPlanes\n", bitmapInfoHeader->biPlanes);
//	printf("%d = biBitCount\n", bitmapInfoHeader->biBitCount);
//	printf("%d = biCompression\n", bitmapInfoHeader->biCompression);
//	printf("%d = biSizeImage\n", bitmapInfoHeader->biSizeImage);
//	printf("%d = biXPelsPerMeter\n", bitmapInfoHeader->biXPelsPerMeter);
//	printf("%d = biYPelsPerMeter\n", bitmapInfoHeader->biYPelsPerMeter);
//	printf("%d = biClrUsed\n", bitmapInfoHeader->biClrUsed);
//	printf("%d = biClrImportant\n\n-\n\n", bitmapInfoHeader->biClrImportant);

	//move file point to the begging of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	//allocate enough memory for the bitmap image data
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];

	//verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return 3;
	}

	//read in the bitmap image data
	fread(bitmapImage, sizeof(unsigned char), bitmapInfoHeader->biSizeImage, filePtr);

	int i = 0, x = 0, y = bitmapInfoHeader->biHeight - 1;
	//swap the r and b values to get RGB (bitmap is BGR)

	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		output[(y * bitmapInfoHeader->biWidth) + x] = RGB(bitmapImage[imageIdx + 2], bitmapImage[imageIdx + 1], bitmapImage[imageIdx + 0]);

		//printf("%02d : %02x %02x %02x > %02d = %06x\n", imageIdx, bitmapImage[imageIdx + 2], bitmapImage[imageIdx + 1], bitmapImage[imageIdx + 0], (y * bitmapInfoHeader->biWidth) + x, output[(y * bitmapInfoHeader->biWidth) + x]);

		x++;

		if (x == bitmapInfoHeader->biWidth)
		{
			x = 0;
			y--;

			if (y < 0)
				break;
		}

	}

	//close file and return bitmap iamge data
	fclose(filePtr);

	return 0;
}
