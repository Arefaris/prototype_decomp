// GImage of the Scaleform GFx library inside the engine DLL (the unit starting at 0x10959600; file name guessed).
#include "code/gfx/gimage.h"
#include <string.h>

static inline unsigned int GMaxValue(unsigned int a, unsigned int b)
{
	if (b < a)
	{
		b = a;
	}
	return b;
}

// The hash of bytes, from the last to the first, which the engine expands in the hash of the image and keeps a copy of
__forceinline unsigned int GHashBytes(const void* data, unsigned int size, unsigned int seed)
{
	const unsigned char* bytes = (const unsigned char*)data;
	unsigned int hash = seed;
	if (size > 0)
	{
		do
		{
			size--;
			hash = bytes[size] ^ (hash * 33);
		}
		while (size > 0);
	}
	return hash;
}

// FUNCTION: ENGINE 0x10959B50 ; GHashBytes
unsigned int (*gKeepHashBytes)(const void*, unsigned int, unsigned int) = &GHashBytes;

// FUNCTION: ENGINE 0x10959B80
unsigned int GImageBase::GetHash() const
{
	if (mData == 0 || mDataSize == 0)
	{
		return 0;
	}
	unsigned int hash = 5381;
	hash = GHashBytes(&mWidth, 4, hash);
	hash = GHashBytes(&mHeight, 4, hash);
	hash = GHashBytes(&mMipMapCount, 4, hash);
	return GHashBytes(mData, mDataSize, hash);
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

// FUNCTION: ENGINE 0x1095CAA0
void GColor::SetRaw(unsigned int raw)
{
	mRaw = raw;
}

// FUNCTION: ENGINE 0x1095CAB0
unsigned char GColor::GetAlpha() const
{
	return mAlpha;
}

// FUNCTION: ENGINE 0x1095CAC0
unsigned char GColor::GetRed() const
{
	return mRed;
}

// FUNCTION: ENGINE 0x1095CAD0
unsigned char GColor::GetGreen() const
{
	return mGreen;
}

// FUNCTION: ENGINE 0x1095CAE0
unsigned char GColor::GetBlue() const
{
	return mBlue;
}

// FUNCTION: ENGINE 0x1095A610
unsigned int GImageBase::GetBytesPerPixel() const
{
	return GetBytesPerPixel(mFormat);
}

// FUNCTION: ENGINE 0x1095ABD0
// NONMATCHING: the engine reads the palette's capacity after the stores of the image's fields and tests its flag bits through a
// shifted copy (13.8 %)
#ifdef NONMATCHING
void GImageBase::Clear()
{
	mFormat = Image_None;
	mPitch = 0;
	mHeight = 0;
	mWidth = 0;
	mData = 0;
	mDataSize = 0;
	mMipMapCount = 1;
	unsigned int capacity = mPalette.mCapacity;
	unsigned int flags = capacity >> 0x1E;
	mPalette.mSize = 0;
	if (flags == 0 || ((((flags >> 1) & 1) == 0 || (capacity & 0x3FFFFFFF) == 0) && (flags & 1) == 0))
	{
		mPalette.mCapacity = capacity & 0xC0000000;
		if (mPalette.mData)
		{
			GMemory::Free(mPalette.mData);
		}
		mPalette.mData = 0;
	}
}
#endif

// FUNCTION: ENGINE 0x1095AC30
void GImage::ReleaseData()
{
	if (mData)
	{
		GMemory::Free(mData);
	}
	Clear();
}

// FUNCTION: ENGINE 0x1095AD40
GImage::GImage()
{
	mFormat = Image_None;
	mPitch = 0;
	mHeight = 0;
	mWidth = 0;
	mData = 0;
	mDataSize = 0;
	mMipMapCount = 1;
}

// FUNCTION: ENGINE 0x1095AD80
GImage::GImage(ImageFormat format, unsigned long width, unsigned long height)
{
	mPitch = GetPitch(format, width);
	mDataSize = GetImageSize(format, width, height);
	mData = (unsigned char*)GMemory::Alloc(mDataSize);
	if (mData)
	{
		mFormat = format;
		mWidth = width;
		mHeight = height;
		memset(mData, 0, mDataSize);
	}
	else
	{
		Clear();
	}
	mMipMapCount = 1;
}

// FUNCTION: ENGINE 0x1095AE10
GImage::~GImage()
{
	if (mData)
	{
		GMemory::Free(mData);
	}
}

// FUNCTION: ENGINE 0x1095AE40
GImage* __stdcall GImage::CreateImage(ImageFormat format, unsigned long width, unsigned long height)
{
	GImage* image = new GImage(format, width, height);
	if (image->mData == 0 || width == 0 || height == 0)
	{
		image->Release();
		return 0;
	}
	return image;
}
