// GImageBase and GImage of the Scaleform GFx library inside the engine DLL (the exported constructors and the RTTI
// give the names; members are guesses).
#ifndef GFX_GIMAGE_H
#define GFX_GIMAGE_H

#include "code/gfx/gcolor.h"
#include "code/gfx/grefcount.h"

// The colours of a palette: a pointer, the number of them and a capacity word whose two high bits are flags (12 bytes)
class GColorArray
{
public:
	GColorArray()
	{
		mData = 0;
		mSize = 0;
		mCapacity = 0;
	}
	// 0x10062BB0 (another unit)
	~GColorArray();

	GColor* mData;
	unsigned int mSize;
	unsigned int mCapacity;
};

// The pixel formats (names guessed): 1 four bytes, 2 three bytes, 8 and 9 one byte, 10 - 12 compressed, 100 palette
class GImageBase
{
public:
	enum ImageFormat
	{
		Image_None = 0,
		Image_ARGB_8888 = 1,
		Image_RGB_888 = 2,
		Image_Gray_8 = 8,
		Image_Alpha_8 = 9,
		Image_DXT1 = 10,
		Image_DXT3 = 11,
		Image_DXT5 = 12,
		Image_P8 = 100
	};

	// 0x1095ABD0: no image and no palette (the palette's memory is given back unless it belongs to someone else)
	void Clear();
	// 0x1095A610: the bytes of a pixel of the image's format
	unsigned int GetBytesPerPixel() const;
	// 0x10959690 / 0x109596A0 / 0x109596B0
	unsigned char* GetScanline(unsigned int y) const;
	unsigned int GetPitch() const;
	bool IsDataCompressed() const;
	// 0x10959B80: a hash of the size, the mip maps and the pixels
	unsigned int GetHash() const;
	// 0x10959880 / 0x10959970: a pixel from a color / a gray value
	void SetPixel(unsigned int x, unsigned int y, unsigned int color);
	void SetPixelGray(unsigned int x, unsigned int y, unsigned char gray);
	// 0x109599E0 / 0x10959A90 / 0x1095A660: the bytes a pixel takes in a format, the bytes of a row, of the whole image
	static unsigned int __stdcall GetBytesPerPixel(int format);
	static unsigned int __stdcall GetPitch(int format, unsigned int width);
	static unsigned int __stdcall GetImageSize(int format, unsigned int width, unsigned int height);

	ImageFormat mFormat;           // 0x00
	unsigned int mWidth;           // 0x04
	unsigned int mHeight;          // 0x08
	unsigned int mPitch;           // 0x0C
	unsigned char* mData;          // 0x10
	unsigned int mDataSize;        // 0x14
	unsigned int mMipMapCount;     // 0x18
	GColorArray mPalette;          // 0x1C
};

// An image in memory (RTTI: GImage : GRefCountBase<GImage>, GImageBase at +0x10; vftable 0x10D95398, 0x38 bytes)
class GImage : public GRefCountBase<GImage>, public GImageBase
{
public:
	// 0x1095AD40 / 0x1095AD80 (exported)
	GImage();
	GImage(ImageFormat format, unsigned long width, unsigned long height);
	// 0x1095AE10 (exported)
	virtual ~GImage();
	// 0x1095AE40: a new image, or null when it could not be made
	static GImage* __stdcall CreateImage(ImageFormat format, unsigned long width, unsigned long height);
	// 0x1095AC30: gives the pixels back and clears the image
	void ReleaseData();
};

#endif
