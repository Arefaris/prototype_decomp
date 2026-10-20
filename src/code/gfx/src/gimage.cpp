// GImage of the Scaleform GFx library inside the engine DLL (the unit starting at 0x10959600; file name guessed).
#include "code/gfx/gimage.h"

static inline unsigned int GMaxValue(unsigned int a, unsigned int b)
{
	if (b < a)
	{
		b = a;
	}
	return b;
}

// The functions of GColor, which the engine has on their own (the unit has no other use of them)
// FUNCTION: ENGINE 0x10959600
void GColor::SetAlpha(unsigned char alpha)
{
	mAlpha = alpha;
}

// FUNCTION: ENGINE 0x10959610
void GColor::SetRed(unsigned char red)
{
	mRed = red;
}

// FUNCTION: ENGINE 0x10959620
void GColor::SetGreen(unsigned char green)
{
	mGreen = green;
}

// FUNCTION: ENGINE 0x10959630
void GColor::SetBlue(unsigned char blue)
{
	mBlue = blue;
}

// FUNCTION: ENGINE 0x10959640
GColor& GColor::operator=(const GColor& other)
{
	mRaw = other.mRaw;
	return *this;
}

// FUNCTION: ENGINE 0x10959650
void GColor::SetRGB(unsigned char red, unsigned char green, unsigned char blue)
{
	mRed = red;
	mGreen = green;
	mBlue = blue;
}

// FUNCTION: ENGINE 0x10959670
void GColor::SetRGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	mRed = red;
	mGreen = green;
	mBlue = blue;
	mAlpha = alpha;
}

// FUNCTION: ENGINE 0x10959690
unsigned char* GImageBase::GetScanline(unsigned int y) const
{
	return mData + mPitch * y;
}

// FUNCTION: ENGINE 0x109596A0
unsigned int GImageBase::GetPitch() const
{
	return mPitch;
}

// FUNCTION: ENGINE 0x109596B0
bool GImageBase::IsDataCompressed() const
{
	return mFormat >= Image_DXT1 && mFormat <= Image_DXT5;
}

// FUNCTION: ENGINE 0x10959880
void GImageBase::SetPixel(unsigned int x, unsigned int y, unsigned int color)
{
	if (x < mWidth && y < mHeight && mFormat < Image_DXT1)
	{
		unsigned char* row = mData + mPitch * y;
		switch (mFormat)
		{
		case Image_ARGB_8888:
			((unsigned int*)row)[x] = color;
			break;
		case Image_RGB_888:
			row[x * 3] = (unsigned char)color;
			row[x * 3 + 1] = (unsigned char)(color >> 8);
			row[x * 3 + 2] = (unsigned char)(color >> 16);
			break;
		case Image_Alpha_8:
			row[x] = (unsigned char)(color >> 24);
			break;
		case Image_Gray_8:
			row[x] = (unsigned char)color;
			break;
		}
	}
}

// FUNCTION: ENGINE 0x10959970
void GImageBase::SetPixelGray(unsigned int x, unsigned int y, unsigned char gray)
{
	if (x < mWidth && y < mHeight && mFormat < Image_DXT1)
	{
		unsigned char* row = mData + mPitch * y;
		switch (mFormat)
		{
		case Image_Gray_8:
			row[x] = gray;
			break;
		case Image_RGB_888:
			row[x * 3] = gray;
			row[x * 3 + 1] = gray;
			row[x * 3 + 2] = gray;
			break;
		case Image_ARGB_8888:
			row[x * 4] = gray;
			row[x * 4 + 1] = gray;
			row[x * 4 + 2] = gray;
			break;
		}
	}
}

// FUNCTION: ENGINE 0x109599E0
unsigned int GImageBase::GetBytesPerPixel(int format)
{
	switch (format)
	{
	case Image_Gray_8:
	case Image_Alpha_8:
	case Image_P8:
		return 1;
	case Image_ARGB_8888:
		return 4;
	case Image_RGB_888:
		return 3;
	}
	return 0;
}

// FUNCTION: ENGINE 0x10959A90
unsigned int GImageBase::GetPitch(int format, unsigned int width)
{
	switch (format)
	{
	case Image_Gray_8:
	case Image_Alpha_8:
	case Image_P8:
		return width;
	case Image_ARGB_8888:
		return width * 4;
	case Image_RGB_888:
		return (width * 3 + 3) & ~3;
	}
	return 0;
}

// FUNCTION: ENGINE 0x1095A660
// EQUIVALENT: register allocation of the block counts (the engine keeps them in ecx / eax and loads the 1 with a mov), 17.8 %
unsigned int GImageBase::GetImageSize(int format, unsigned int width, unsigned int height)
{
	if (format == Image_DXT1)
	{
		unsigned int blocksWide = GMaxValue(1u, (width + 3) >> 2);
		unsigned int blocksHigh = GMaxValue(1u, (height + 3) >> 2);
		return blocksWide * blocksHigh * 8;
	}
	if (format >= Image_DXT3 && format <= Image_DXT5)
	{
		unsigned int blocksWide = GMaxValue(1u, (width + 3) >> 2);
		unsigned int blocksHigh = GMaxValue(1u, (height + 3) >> 2);
		return blocksWide * blocksHigh * 0x10;
	}
	return GetPitch(format, width) * height;
}
