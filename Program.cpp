#include <stdio.h>
#include <iostream>
#include "Bitmap.h"
#include "RunProgram.h"
#include "Screen.h"

using namespace std;

int main()
{
	int code;
	char *inFileName = "img.bmp";
	char *outFileName = "RESULT.bmp";
	char *inFileName1 = "Image03.bmp";
	char *inTexture1 = "Snow_Texture.bmp";
//	char *inTexture1 = "Star_Texture.bmp";
//	char *inTexture1 = "Heart_Texture.bmp";
	char *GrainName = "Grain.bmp";
	Bitmap bmp, outbmp, outbmp2;
	Bitmap insert_bmp,insert_texture,grain;
	if(LoadBitmap(inFileName1,insert_bmp))
	{	
		cout<<"------------------------------------------"<<endl;
	}
	if(LoadBitmap(GrainName, grain))
	{	
		cout<<"------------------------------------------"<<endl;
	}
	if(LoadBitmap(inTexture1, insert_texture))
	{	
		cout<<"------------------------------------------"<<endl;
	}
	else
	{
		cout<<"Can not load the bitmap file text!!!";
	}
	if(LoadBitmap(inFileName, bmp))
	{
		clearscreen();
		run_program(50,100,code);
		textcolor(113);
		switch (code)
		{
			case 1: //Reduce Image
			{
				gotoxy(5,13);
				cout<<"The resolution of the image will be twice as SMALL as the original image."<<endl;
				ReduceImage( bmp, outbmp );
				break;
			}	
			case 2: //Enlarge Image
			{
				gotoxy(5,13);
				cout<<"The resolution of the image will be twice as LARGE as the original image."<<endl;
				EnlargeImage( bmp, outbmp );
				break;
			}
			case 3: //Crop Image
			{
				gotoxy(5,13);
				cout<<"Cropping photo";
				CropImage( bmp, outbmp );
				break;
			}
			case 4: //Mirror Mode 1
			{
				gotoxy(5,13);
				cout<<"Half of the image will reflect back to the other half."<<endl;
				Mirror_Mode1( bmp, outbmp );
				break;
			}
			case 5: //Mirror Mode 2
			{
				gotoxy(5,13);
				cout<<"Half of the image will reflect back to the other half."<<endl;
				Mirror_Mode2( bmp, outbmp );
				break;
			}
			case 6: //Flip Image Mode 1
			{
				gotoxy(5,13);
				cout<<"The image will be flipped horizontally."<<endl;
				Flip_ImageMode1( bmp, outbmp );
				break;
			}
			case 7: //Flip Image Mode 2
			{
				gotoxy(5,13);
				cout<<"The image will be flipped vertically."<<endl;
				Flip_ImageMode2( bmp, outbmp );
				break;
			}
			case 8: //Black-White Mode
			{
				gotoxy(5,13);
				cout<<"The image will be converted into black-white mode."<<endl;
				BlackWhite_Convert( bmp, outbmp );
				break;
			}
			case 9: //Color Filters
			{
				Filter_RGB( bmp, outbmp );
				break;
			}
			case 10:
			{
				gotoxy(5,13);
				cout<<"The image will be converted into the negative proof image";
				NegativeProof( bmp, outbmp);
				break;
			}
			case 11: //AdjustBrightness
			{

				AdjustBrightness( bmp, outbmp );
				break;
			}
			case 12: //AdjustingContrast
			{
				gotoxy(5,13);
				cout<<"The image will be edited automatically in contrast mode";				
				AdjustContrast( bmp, outbmp );
				break;
			}
			case 13: //Rotate
			{
				RotateImage( bmp, outbmp );
				break;
			}
			case 14: //CMYK Color channel
			{
				SetColor_CMYK( bmp, outbmp );
				break;
			}
			case 15: //Grain effect
			{
				gotoxy(5,13);
				cout<<"The grain effect is being set in your image";
				Grain(bmp,grain,outbmp);
				break;
			}
			case 16:
			{
				gotoxy(5,13);
				cout<<"The image that you inserted to the program will be added into the main image that you";
				gotoxy(5,14);
				cout<<"want to export to BMP file";
				InsertImage(bmp,insert_bmp,outbmp);
				break;
			}
			case 17:
			{
				gotoxy(5,13);
				cout<<"The texture that you inserted to the program will be added into the main image that you";
				gotoxy(5,14);
				cout<<"want to export to BMP file";				
				InsertTexture(bmp,insert_texture,outbmp);
				break;
			}
			case 18:
			{
				Bitmap pixelart;
				Pixel_Art_Mode(bmp,pixelart,outbmp);
				break;
			}
			case 19://Grey White Mode
			{
				GreyWhite_Convert(bmp,outbmp);
				break;
			}
		}
		if(SaveBitmap(outFileName, outbmp))
		{
			
		}
		else
			cout << "Can not save the bitmap file!!!" << endl;
		DisposeBitmap(bmp);
		DisposeBitmap(outbmp);
	}
	else
		cout << "Can not load the bitmap file!!!" << endl;
	return 0;
}
