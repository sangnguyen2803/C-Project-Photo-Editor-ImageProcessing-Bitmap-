#include "Bitmap.h"
#include <stdio.h>
#include <iostream>
#include "Screen.h"
#include <Windows.h>


using namespace std;
// O(1)
int SetPixel(const Bitmap &bmp, int row, int col, Color color)
{
	if(row < 0 || row >= bmp.height
		 || col < 0 || col >= bmp.width)
		return 0;
	
	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col*3;
	bmp.pixels[offset] = color.B;
	bmp.pixels[offset + 1] = color.G;
	bmp.pixels[offset + 2] = color.R;
}

int GetPixel(const Bitmap &bmp, int row, int col, Color &color)
{
	if(row < 0 || row >= bmp.height
		 || col < 0 || col >= bmp.width)
		return 0;
	
	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col*3;
	color.B = bmp.pixels[offset];
	color.G = bmp.pixels[offset + 1];
	color.R = bmp.pixels[offset + 2];
}

void EnlargeImage(const Bitmap &inbmp, Bitmap &outbmp)
{
	int n;
	cout<<"How many times you want to enlarge your image?";
	cin>>n;
	outbmp.width = n * inbmp.width;
	outbmp.height = n * inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			for(int i = 1; i <= n; i++)
			{
					SetPixel(outbmp, n*row+i, n*col+i, color);
					for(int j = 1; j < n; j++)
						SetPixel(outbmp, n*row+j, n*col + i, color);
					for(int k = 1; k < n; k++)
						SetPixel(outbmp, n*row + i, n*col + k, color);		
			}
		}
}
void ReduceImage(const Bitmap &inbmp, Bitmap &outbmp)
{
	int n;
	cout<<"How many times you want to reduce your image?";
	cin>>n;
	outbmp.width = inbmp.width/n;
	outbmp.height = inbmp.height/n;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, row/n, col/n, color);
			SetPixel(outbmp, row/n, col/n + 1, color);
			SetPixel(outbmp, row/n + 1, col/n, color);
			SetPixel(outbmp, row/n + 1, col/n + 1, color);
		}
}
void Pixel_Art_Mode( const Bitmap &inbmp, Bitmap &outbmp, Bitmap &newoutbmp)
{
	gotoxy(5,13);
	cout<<"Your image will be edited as a pixel-art one";
	int n = 0;
	for(int i = 1; inbmp.height/i > 75 || inbmp.width/i > 75 ; i++)
	{
		n = i;
	}
	outbmp.width = inbmp.width/n;
	outbmp.height = inbmp.height/n;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, row/n, col/n, color);
			SetPixel(outbmp, row/n, col/n + 1, color);
			SetPixel(outbmp, row/n + 1, col/n, color);
			SetPixel(outbmp, row/n + 1, col/n + 1, color);
		}
		
	newoutbmp.width = n * outbmp.width;
	newoutbmp.height = n * outbmp.height;
	newoutbmp.rowSize = ((3 * newoutbmp.width + 3)/4)*4;
	newoutbmp.pixels = new unsigned char[newoutbmp.rowSize * newoutbmp.height];
	for(int row = 0; row < outbmp.height; row++)
		for(int col = 0; col < outbmp.width; col++)
		{
			Color color;
			GetPixel(outbmp, row, col, color);
			for(int i = 1; i <= n; i++)
			{
				SetPixel(newoutbmp, n*row+i, n*col+i, color);
				for(int j = 1; j < n; j++)
					SetPixel(newoutbmp, n*row+j, n*col + i, color);
				for(int k = 1; k < n; k++)
					SetPixel(newoutbmp, n*row + i, n*col + k, color);		
			}
		}
}
void CropImage(const Bitmap &inbmp, Bitmap &outbmp) //Crop image
{
	gotoxy(5,13);
	printf("Enter coordinates of the top left-hand corner - topleft-handcorner(X1;Y1)"); 
	gotoxy(5,14);
	printf("X1 = ");
	scanf("%d",&inbmp.cutting_point1);
	gotoxy(5,15);
	printf("Y1 = ");
	scanf("%d",&inbmp.cutting_point2);
	gotoxy(5,16);
	printf("Enter coordinates of the bottom right-hand corner - bottomright-handcorner(X2;Y2)");
	gotoxy(5,17);
	printf("X2 = ");
	scanf("%d",&inbmp.cutting_point3);
	gotoxy(5,18);
	printf("Y2 = ");
	scanf("%d",&inbmp.cutting_point4);
	outbmp.width = inbmp.cutting_point2 - inbmp.cutting_point1;
	outbmp.height = inbmp.cutting_point4 - inbmp.cutting_point3;
	gotoxy(5,19);
	printf("The width of photo - WIDTH = %d",outbmp.width);
	gotoxy(5,20);
	printf("The height of photo - HEIGHT = %d",outbmp.height);
	outbmp.rowSize =  ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize*outbmp.height];
	int x = 0, y = 0;
	for( int row = 0; row < outbmp.height; row++)
	{
		for(int col = 0; col < outbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp,inbmp.cutting_point3+x, inbmp.cutting_point1+y,color);
			SetPixel(outbmp,row,col,color);
			y++;
		}
		x++;
		y=0;
	}
}
void Mirror_Mode1(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	int x = 0, y = 0;
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, row, col, color);
		}
	for(int row = 0; row < inbmp.height; row++)
	{
		for(int col = 0; col < inbmp.width/2; col++)
		{
			Color color;
			GetPixel(inbmp,0 + y, inbmp.width - x, color);
			SetPixel(outbmp,row,col,color);
			x++;
		}
		y++;
		x = 0;
	}
}
void Mirror_Mode2(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	int x = 0, y = 0;
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, row, col, color);
		}
	for(int row = 0; row < inbmp.height/2; row++)
	{
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp,inbmp.height - y, 0 + x, color);
			SetPixel(outbmp,row,col,color);
			x++;
		}
		y++;
		x = 0;
	}
}
void Flip_ImageMode1(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	int x = 0, y = 0;
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, row, col, color);
		}
	for(int row = 0; row < inbmp.height; row++)
	{
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp,0+y, inbmp.width - x, color);
			SetPixel(outbmp,row,col,color);
			x++;
		}
		y++;
		x = 0;
	}
}
void Flip_ImageMode2(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	int x = 0, y = 0;
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, row, col, color);
		}
	for(int row = 0; row < inbmp.height; row++)
	{
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp,inbmp.height-y, 0 + x, color);
			SetPixel(outbmp,row,col,color);
			x++;
		}
		y++;
		x = 0;
	}
}
void BlackWhite_Convert(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp,row,col,color);
			if( color.B < 230 && color.B > 179 && color.G < 230 && color.G > 179 && color.R < 230 && color.R > 179)
			{
				color.B = 235;
				color.G = 235;
				color.R = 235;
			}
			else if( color.B < 180 && color.G < 180 && color.R < 180)
			{
				color.B = 0;
				color.G = 0;
				color.R = 0;
			}
			else
			{
				color.B = 250;
				color.G = 240;
				color.R = 245;
			}
			SetPixel(outbmp,row,col,color);
		}
}
void Filter_RGB( const Bitmap &inbmp, Bitmap &outbmp )
{
	double density;
	double colorDensity;
	int colormode;
	gotoxy(5,13);
	cout<<"Enter Density of the filter: ";
	cin>>density;
	gotoxy(5,14);
	cout<<"Color Density : Light Yellow = 0->127 - Light Blue = 128 - 255 - Color Density = ";
	cin>>colorDensity;
	density = (density/255);
	gotoxy(5,15);
	cout<<"Press 1 to use Red-filter";
	gotoxy(5,16);
	cout<<"Press 2 to use Green-filter";
	gotoxy(5,17);
	cout<<"Press 3 to use Blue-filter";
	gotoxy(5,18);
	cout<<"Press 4 to use Pink-filter";
	gotoxy(5,19);
	cout<<"Press 5 to use Orange-filter";
	gotoxy(5,20);
	cout<<"Press 6 to use Yellow-filter";
	gotoxy(5,21);
	cout<<"Press 7 to use Cyan-filter";
	gotoxy(5,22);
	cout<<"Press 8 to use Violet-filter";
	gotoxy(5,23);
	cout<<"Press 9 to use YB-Blended-Filter";
	gotoxy(5,24);
	cout<<"Press 10 to use Vintage-Filter";
	gotoxy(5,25);
	cout<<"Press 11 to use Reserved-Color-Filter";
	gotoxy(5,26);
	cout<<"Your selection: ";
	cin>>colormode;
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
	{
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp,row,col,color);
			switch (colormode)
			{
				case 1:
				{
					color.B = 0;
					color.G = 0;
					color.R = double(color.R)*density;
					break;
				}
				case 2:
				{
					color.B = 0;
					color.G = double(color.G)*density;
					color.R = 0;
					break;
				}
				case 3:
				{
					color.B =  double(color.B)*density;
					color.G = 0;
					color.R = 0;
					break;
				}
				case 4:
				{
					color.R = color.R + 50;
					color.G = 0 ;
					color.B = color.B + 50;
					if(color.R >= 255)
						color.R = 255;
					if(color.B >= 255)
						color.B = 255;
					color.R = double(color.R)*density;
					color.G = double(color.G)*density;
					color.B = double(color.B)*density;
					break;
				}
				case 5:
				{
					color.R = color.R + 50;
					color.G = color.G + 50;
					color.B = 0;
					if(color.R >= 255)
						color.R = 255;
					if(color.G >= 128)
						color.G = 128;
					color.R = double(color.R)*density;
					color.G = double(color.G)*density;
					color.B = double(color.B)*density;
					break;
				}
				case 6:
				{
					color.R = color.R + 50;
					color.B = 0 ;
					color.G = color.G + 50;
					if(color.R >= 255)
						color.R = 255;
					if(color.G >= 255)
						color.G = 255;
					color.R = double(color.R)*density;
					color.G = double(color.G)*density;
					color.B = double(color.B)*density;
					break;
				}
				case 7:
				{
					color.R = 0;
					color.B = color.B + 50;
					color.G = color.G + 50;
					if(color.B >= 255)
						color.B = 255;
					if(color.G >= 255)
						color.G = 255;
					color.R = double(color.R)*density;
					color.G = double(color.G)*density;
					color.B = double(color.B)*density;
					break;
				}
				case 8:
				{
					color.R = color.R + 50;
					color.G = 0;
					color.B = color.B + 50;
					if(color.B >= 255)
						color.B = 255;
					if(color.R >= 128)
						color.R = 128;
					color.R = double(color.R)*density;
					color.G = double(color.G)*density;
					color.B = double(color.B)*density;
					break;
				}
				case 9:
				{
					int offset = (inbmp.height - 1 - row)*inbmp.rowSize + col*3;
					inbmp.pixels[offset + 3] = color.A;
					color.A = colorDensity;
					break;
				}
				case 10://vintage mode
				{
					color.R = color.R + 50;
					color.G = color.G + 50;
					color.B = 0;
					if(color.R >= 128)
						color.R = 128;
					if(color.G >= 64)
						color.G = 64;
					color.R = double(color.R)*(density+0.1);
					color.G = double(color.G)*(density+0.1);
					color.B = double(color.B)*(density+0.1);
					break;
				}
				case 11://reversed color
				{
					int temp = color.B;
					color.B = color.G;
					color.G = color.R;
					color.R = temp;
					break;
				}
			}
			SetPixel(outbmp,row,col,color);
		}
	}	
}

void NegativeProof(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
	{
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			if( color.R < 127 && color.G < 127 && color.B )
			{
				color.R = 255 - color.R;
				color.G = 255 - color.G;
				color.B = 255 - color.B;
			}
			else
			{
				color.R = 0 + (255 - color.R);
				color.G = 0 + (255 - color.G);
				color.B = 0 + (255 - color.B);
			}
			SetPixel(outbmp, row, col, color);
		}
	}
}	

void AdjustBrightness(const Bitmap &bmp, Bitmap &outbmp)
{
	double factor;
	gotoxy(5,13);
	cout<<"Enter brightness level from 0 to 100 - BRIGHTNESS = ";
	cin>>factor;
	factor = (factor/100)*2;
	outbmp.width = bmp.width;
	outbmp.height = bmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < bmp.height; row++)
	{
		for(int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.R *= factor;
			if(color.R > 255)
				color.R = 255;	
			color.G *= factor;
			if(color.G > 255)
				color.G = 255;
			color.B *= factor;
			if(color.B > 255)
				color.B = 255;
			SetPixel(outbmp, row, col, color);
		}
	}
}
void AdjustContrast( const Bitmap &inbmp, Bitmap &outbmp)
{
	double factor;
	gotoxy(5,13);
	cout<<"Enter contrast level from 0 to 100 - CONTRAST = ";
	cin>>factor;
	factor = (factor/100)*4;
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color1,color2;
			GetPixel(inbmp, row, col, color1);
//			GetPixel(inbmp, row, col+1, color2);
			if( color1.R > 90 && color1.G > 90 && color1.R > 90)
			{
				color1.R = color1.R * ((factor-1)/8 + 1);
				if(color1.R > 255)
					color1.R = 240;
				color1.G = color1.G * ((factor-1)/8 + 1);
				if(color1.G > 255)
					color1.G = 240;
				color1.B = color1.B * ((factor-1)/8 + 1);
				if(color1.B > 255)
					color1.B = 240;
			}
			else
			{
				color1.R = color1.R/((factor-1)/12 + 1);
				color1.G = color1.G/((factor-1)/12 + 1);
				color1.B = color1.B/((factor-1)/12 + 1);
			}
			/*
			int a = 50, b = 70;
			if(color1.R < a && color2.R >= a && color1.G < a && color2.G >= a 
			&& color1.B < a && color2.B >= a  || color1.R > a && color2.R < a 
			&& color1.G > a && color2.G < a && color1.B > a && color2.B < a)
			{
				color1.R = color2.R = b;
				color1.G = color2.G = b;
				color1.B = color2.B = b;
			}
			*/
			SetPixel(outbmp, row, col, color1);
//			SetPixel(inbmp, row, col+1, color2);
		}
}


void RotateImage(const Bitmap &inbmp, Bitmap &outbmp)
{
	int code;
	gotoxy(5,13);
	cout<<"The photo will be rotated from right to left";
	gotoxy(5,14);
	cout<<"Press 1 to rotate photo 90 degrees";
	gotoxy(5,15);
	cout<<"Press 2 to rotate photo 180 degrees";
	gotoxy(5,16);
	cout<<"Press 3 to rotate photo 270 degrees";
	gotoxy(5,17);
	cout<<"Press 4 to rotate photo 360 degress";
	gotoxy(5,18);
	cout<<"Your selection : ";
	cin>>code;
	int x = 0, y = 0;
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	switch (code)
	{
		case 1:
		{
			outbmp.width = inbmp.height;
			outbmp.height = inbmp.width;
			outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
			outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
			for(int row = 0; row < outbmp.height; row++)
			{
				for(int col = 0; col < outbmp.width; col++)
				{
					Color color;
					GetPixel(inbmp, inbmp.height-y, 0+x, color);
					SetPixel(outbmp,row,col,color);
					y++;
				}
				x++;
				y = 0;
			}
			break;
		}
		case 2:
		{
			for(int row = 0; row < outbmp.height; row++)
			{
				for(int col = 0; col < outbmp.width; col++)
				{
					Color color;
					GetPixel(inbmp, inbmp.height-y, inbmp.width-x, color);
					SetPixel(outbmp,row,col,color);
					x++;
				}
				y++;
				x = 0;
			}
			break;
		}
		case 3:
		{
			outbmp.width = inbmp.height;
			outbmp.height = inbmp.width;
			outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
			outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
			for(int row = 0; row < outbmp.height; row++)
			{
				for(int col = 0; col < outbmp.width; col++)
				{
					Color color;
					GetPixel(inbmp, 0 + y, inbmp.width-x, color);
					SetPixel(outbmp,row,col,color);
					y++;
				}
				x++;
				y = 0;
			}
			break;
		}
		case 4:
		{
			for(int row = 0; row < inbmp.height; row++)
			{
				for(int col = 0; col < inbmp.width; col++)
				{
					Color color;
					GetPixel(inbmp,row,col,color);
					SetPixel(outbmp,row,col,color);
				}
			}
			break;
		}
	}
}
void Grain( const Bitmap &inbmp1, const Bitmap &texture, Bitmap &outbmp)
{
	outbmp.width = inbmp1.width;
	outbmp.height = inbmp1.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	int posX = 0;
	int posY = 0;
	int x = 0, y = 0;
	for(int row = 0; row < inbmp1.height; row++)
		for(int col = 0; col < inbmp1.width; col++)
		{
			Color color;
			GetPixel(inbmp1, row, col, color);
			SetPixel(outbmp, row, col, color);
		}
	for(int row = 0; row < texture.height; row++)
	{
		for(int col = 0; col < texture.width; col++)
		{
			Color color;
			GetPixel(texture, row, col, color);
//			color.A = 100;
			if(color.R > 80 && color.G > 80 && color.B > 80)
			{
				y++;
			}
			else
			{
				color.R = 10;
				color.G = 10;
				color.B = 10;
			SetPixel(outbmp, posX + x, posY + y, color);
			y++;
			}
		}
		x++;
		y = 0;
	}
}

void AdjustContrast( const Bitmap &inbmp, double factor)
{
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color1,color2;
			GetPixel(inbmp, row, col, color1);
//			GetPixel(inbmp, row, col+1, color2);
			if( color1.R > 90 && color1.G > 90 && color1.R > 90)
			{
				color1.R = color1.R * ((factor-1)/8 + 1);
				if(color1.R > 255)
					color1.R = 240;
				color1.G = color1.G * ((factor-1)/8 + 1);
				if(color1.G > 255)
					color1.G = 240;
				color1.B = color1.B * ((factor-1)/8 + 1);
				if(color1.B > 255)
					color1.B = 240;
			}
			else
			{
				color1.R = color1.R/((factor-1)/12 + 1);
				color1.G = color1.G/((factor-1)/12 + 1);
				color1.B = color1.B/((factor-1)/12 + 1);
			}
			/*
			int a = 50, b = 70;
			if(color1.R < a && color2.R >= a && color1.G < a && color2.G >= a 
			&& color1.B < a && color2.B >= a  || color1.R > a && color2.R < a 
			&& color1.G > a && color2.G < a && color1.B > a && color2.B < a)
			{
				color1.R = color2.R = b;
				color1.G = color2.G = b;
				color1.B = color2.B = b;
			}
			*/
			SetPixel(inbmp, row, col, color1);
//			SetPixel(inbmp, row, col+1, color2);
		}
}
void InsertImage(const Bitmap &inbmp1, const Bitmap &inbmp2, Bitmap &outbmp)
{
	gotoxy(5,16);
	cout<<"Enter the centre coordinate of image you want to insert upon your current image center(X;Y)";
	int posX = 0, posY = 0;
	gotoxy(5,17);
	cout<<"X = ";
	cin>>posX;
	gotoxy(5,18);
	cout<<"Y = ";
	cin>>posY;
	gotoxy(5,19);
	cout<<"The coordinate you entered is center("<<posX<<";"<<posY<<")";
	outbmp.width = inbmp1.width;
	outbmp.height = inbmp1.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	int x = 0, y = 0;
	for(int row = 0; row < inbmp1.height; row++)
		for(int col = 0; col < inbmp1.width; col++)
		{
			Color color;
			GetPixel(inbmp1, row, col, color);
			SetPixel(outbmp, row, col, color);
		}
	for(int row = 0; row < inbmp2.height; row++)
	{
		for(int col = 0; col < inbmp2.width; col++)
		{
			Color color;
			GetPixel(inbmp2, row, col, color);
			SetPixel(outbmp, posY + x, posX + y, color);
			y++;
		}
		x++;
		y = 0;
	}	
}
void InsertTexture(const Bitmap &inbmp1, const Bitmap &texture, Bitmap &outbmp)
{
	gotoxy(5,16);
	cout<<"Enter the centre coordinate of texture you want to insert upon your current image center(X;Y)";
	int posX = 0, posY = 0;
	gotoxy(5,17);
	cout<<"X = ";
	cin>>posX;
	gotoxy(5,18);
	cout<<"Y = ";
	cin>>posY;
	gotoxy(5,19);
	cout<<"The coordinate you entered is center("<<posX<<";"<<posY<<")";
	outbmp.width = inbmp1.width;
	outbmp.height = inbmp1.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	int x = 0, y = 0;
	for(int row = 0; row < inbmp1.height; row++)
		for(int col = 0; col < inbmp1.width; col++)
		{
			Color color;
			GetPixel(inbmp1, row, col, color);
			SetPixel(outbmp, row, col, color);
		}
	for(int row = 0; row < texture.height; row++)
	{
		for(int col = 0; col < texture.width; col++)
		{
			Color color;

			GetPixel(texture, row, col, color);
//			color.A = 100;
			if(color.R < 80 && color.G < 80 && color.B < 80)
			{
				y++;
			}
			else
			{
			//	color.R = 240;
			//	color.G = 240;
			//	color.B = 240;
				SetPixel(outbmp, posX + x, posY + y, color);
				y++;
			}
		}
		x++;
		y = 0;
	}
}
void SetColor_CMYK(const Bitmap &bmp, Bitmap &outbmp)
{
	int density;
	gotoxy(5,13);
	cout<<"Enter the density of photo - Density = ";
	cin>>density;
	density = density/255;
	outbmp.width = bmp.width;
	outbmp.height = bmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < bmp.height; row++)
	{
		for(int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.c = 255 - color.R;
			color.m = 255 - color.G;
			color.y = 255 - color.B;
			double min = color.c/2.55;
			if( color.m/255 < min )
				min = double(color.m)/2.55;
			else if ( color.y/2.55 < min )
				min = double(color.y)/2.55;
			color.K = min;
			if( color.K == 100)
				color.R = color.G = color.B = 0 ;
			if( color.K > 0 && color.K < 100)
			{
				color.R = (color.c /2.55 - color.K) * 100 /(100 - color.K);
				color.G = (color.m /2.55 - color.K) * 100 /(100 - color.K);
				color.B = (color.y /2.55 - color.K) * 100 /(100 - color.K);
			}
//			color.R = color.R*density;
//			color.G = color.R*density;
//			color.B = color.B*density;
			SetPixel(outbmp, row, col, color);
		}
	}
}
void GreyWhite_Convert(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = inbmp.width;
	outbmp.height = inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp,row,col,color);
			if( color.B < 230 && color.B > 179 && color.G < 230 && color.G > 179 && color.R < 230 && color.R > 179)
			{
				color.B = 235;
				color.G = 235;
				color.R = 235;
			}
			else if( color.B < 180 && color.G < 180 && color.R < 180)
			{
				color.B = 50;
				color.G = 50;
				color.R = 50;
			}
			else
			{
				color.B = 250;
				color.G = 240;
				color.R = 245;
			}
			SetPixel(outbmp,row,col,color);
		}
}
