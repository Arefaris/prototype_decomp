// GColor of the Scaleform GFx library inside the engine DLL: a color in four bytes (blue first in memory).
#ifndef GFX_GCOLOR_H
#define GFX_GCOLOR_H

class GColor
{
public:
	// 0x10959600 / 0x10959610 / 0x10959620 / 0x10959630: the four channels
	void SetAlpha(unsigned char alpha);
	void SetRed(unsigned char red);
	void SetGreen(unsigned char green);
	void SetBlue(unsigned char blue);
	// 0x10959640
	GColor& operator=(const GColor& other);
	// 0x1095CAA0: the four channels at once; 0x1095CAB0 - 0x1095CAE0: one channel each
	void SetRaw(unsigned int raw);
	unsigned char GetAlpha() const;
	unsigned char GetRed() const;
	unsigned char GetGreen() const;
	unsigned char GetBlue() const;
	// 0x10959650 / 0x10959670
	void SetRGB(unsigned char red, unsigned char green, unsigned char blue);
	void SetRGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

	union
	{
		unsigned int mRaw;
		struct
		{
			unsigned char mBlue;     // 0x00
			unsigned char mGreen;    // 0x01
			unsigned char mRed;      // 0x02
			unsigned char mAlpha;    // 0x03
		};
	};
};

#endif
