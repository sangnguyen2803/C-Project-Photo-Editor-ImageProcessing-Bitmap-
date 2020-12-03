#ifndef _BITMAP_
#define _BITMAP_


struct Bitmap
{
	int width;
	int height;
	int rowSize;
	unsigned char *pixels;
	int cutting_point1;
	int cutting_point2;
	int cutting_point3;
	int cutting_point4;
};

struct Color
{
	int R, G, B, A;
	double C, M, Y, K, c, m, y;
};

int LoadBitmap(const char *fname, Bitmap &bmp);
int SaveBitmap(const char *fname, const Bitmap &bmp);
void DisposeBitmap(Bitmap &bmp);

int SetPixel(const Bitmap &bmp, int row, int col, Color color);
int GetPixel(const Bitmap &bmp, int row, int col, Color &color, int mode);
void ChangeColor(const Bitmap &bmp, int R, int G, int B);


void ReduceImage(const Bitmap &inbmp, Bitmap &outbmp);
void EnlargeImage(const Bitmap &inbmp, Bitmap &outbmp);
void CropImage(const Bitmap &inbmp, Bitmap &outbmp);
void Mirror_Mode1(const Bitmap &inbmp, Bitmap &outbmp);
void Mirror_Mode2(const Bitmap &inbmp, Bitmap &outbmp);
void Flip_ImageMode1(const Bitmap &inbmp, Bitmap &outbmp);
void Flip_ImageMode2(const Bitmap &inbmp, Bitmap &outbmp);
void BlackWhite_Convert(const Bitmap &inbmp, Bitmap &outbmp);
void GreyWhite_Convert(const Bitmap &inbmp, Bitmap &outbmp);
void Filter_RGB( const Bitmap &inbmp, Bitmap &outbmp );
void NegativeProof(const Bitmap &inbmp, Bitmap &outbmp );
void Pixel_Art_Mode( const Bitmap &inbmp, Bitmap &outbmp, Bitmap &newoutbmp);

void AdjustBrightness(const Bitmap &bmp, Bitmap &outbmp);
void AdjustContrast( const Bitmap &inbmp, Bitmap &outbmp);
void Colorful(const Bitmap &inbmp);
void Filter(const Bitmap &inbmp, int density, int colormode);


void RotateImage(const Bitmap &inbmp, Bitmap &outbmp);
void SetColor_CMYK(const Bitmap &bmp, Bitmap &outbmp);


void Grain( const Bitmap &inbmp1, const Bitmap &texture, Bitmap &outbmp);
void InsertImage(const Bitmap &inbmp1, const Bitmap &bmp2, Bitmap &outbmp);
void InsertTexture(const Bitmap &inbmp1, const Bitmap &texture, Bitmap &outbmp);


#endif
