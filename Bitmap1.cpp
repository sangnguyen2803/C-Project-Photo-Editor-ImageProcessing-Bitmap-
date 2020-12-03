
#include <string.h>
#include "Bitmap.h"
#include <iostream>
#pragma pack(1)

using namespace std;

struct BMFHeader
{
	char signature[2];
	unsigned int size;
	unsigned int reserved;
	unsigned int pixelAddress;
};

struct DIBHeader
{
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned short colorPlane;
	unsigned short colorDepth;
	unsigned char reserved[24];
};

int LoadBitmap(const char *fname, Bitmap &bmp)
{
	FILE *f = fopen(fname, "rb");
	if (f == NULL)
		return 0;
	
	// read BMFHeader
	BMFHeader bmfhd;
	if(fread(&bmfhd, sizeof(BMFHeader), 1, f) == 0)
		return 0;
	
	if(bmfhd.signature[0] != 'B' || bmfhd.signature[1] != 'M')
		return 0;
		
	printf("Size: %d bytes.\n", bmfhd.size);
	printf("Pixel offset: %d.\n", bmfhd.pixelAddress);
	
	// read DIBHeader
	DIBHeader dibhd;
	if(fread(&dibhd, sizeof(DIBHeader), 1, f) == 0)
		return 0;
		
	printf("Image Size: %d x %d pixels.\n", dibhd.width, dibhd.height);
	printf("Color Depth: %d bits/pixels.\n", dibhd.colorDepth);
	
	if(dibhd.colorDepth != 24 || dibhd.height < 0)
		return 0;
	
	// read pixels (24 bits = 3 bytes/pixel)
	bmp.width = dibhd.width;
	bmp.height = dibhd.height;
	bmp.rowSize = ((3 * bmp.width + 3)/4)*4;
	
	int pixArrSize = bmp.height * bmp.rowSize;
	bmp.pixels = new unsigned char[pixArrSize];
	if(bmp.pixels == NULL)
		return 0;
		
	fseek(f, bmfhd.pixelAddress, SEEK_SET);
	if(fread(bmp.pixels, 1, pixArrSize, f) < pixArrSize)
		return 0;
		
	fclose(f);
	
	return 1;
}

int SaveBitmap(const char *fname, const Bitmap &bmp)
{
	FILE *f = fopen(fname, "wb");
	if(f == NULL)
		return 0;
	
	// write BMFHeader	
	BMFHeader bmfhd;
	bmfhd.signature[0] = 'B';
	bmfhd.signature[1] = 'M';
	bmfhd.size = sizeof(BMFHeader) + sizeof(DIBHeader) + bmp.rowSize*bmp.height;
	bmfhd.reserved = 0;
	bmfhd.pixelAddress = sizeof(BMFHeader) + sizeof(DIBHeader);
	if(fwrite(&bmfhd, sizeof(BMFHeader), 1, f) == 0)
		return 0;
	
	// write DIBHeader
	DIBHeader dibhd;
	dibhd.size = sizeof(DIBHeader);
	dibhd.width = bmp.width;
	dibhd.height = bmp.height;
	dibhd.colorPlane = 1;
	dibhd.colorDepth = 24;
	memset(&dibhd.reserved, 0, sizeof(dibhd.reserved));
	if(fwrite(&dibhd, sizeof(DIBHeader), 1, f) == 0)
		return 0;
	
	// write pixels
	int pixArrSize = bmp.height * bmp.rowSize;
	if(fwrite(bmp.pixels, 1, pixArrSize, f) < pixArrSize)
		return 0;
		
	fclose(f);
	
	return 1;
}

void DisposeBitmap(Bitmap &bmp)
{
	if(bmp.pixels != NULL)
	{
		delete[] bmp.pixels;
		bmp.pixels = NULL;
	}
}
