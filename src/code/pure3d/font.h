// pure3d::Font and pure3d::TextureFont (RTTI names; TextureFont derives from Font, Font from Entity). The debug font of
// the context is a TextureFont. The slots follow the vftable at 0x10E5E42C (Font's own at 0x10E5E3BC leaves 3 - 21 and
// 25 pure); member and method names are guesses.
#ifndef PURE3D_FONT_H
#define PURE3D_FONT_H

#include "code/pure3d/entity.h"

namespace pure3d
{
	class Shader;
	class Texture;

	class Font : public Entity
	{
	public:
		virtual float Unknown3() = 0;
		virtual float Unknown4() = 0;
		virtual float Unknown5() = 0;
		// The height of a line
		virtual float Unknown6() = 0;
		virtual float Unknown7(const unsigned short* text, float width) = 0;
		virtual float Unknown8(const unsigned short* text) = 0;
		virtual float Unknown9(const unsigned short* text) = 0;
		virtual void Unknown10() = 0;
		// Draws the wide text
		virtual void Draw(const unsigned short* text, int unknown) = 0;
		virtual float Unknown12() = 0;
		virtual void Unknown13(float value) = 0;
		virtual void Unknown14(unsigned int* out) = 0;
		virtual void Unknown15(unsigned int* out) = 0;
		virtual void Unknown16(unsigned int value) = 0;
		virtual void SetColour(unsigned int colour) = 0;
		virtual Shader* Unknown18() = 0;
		virtual void Unknown19(Shader* shader) = 0;
		virtual bool Unknown20() = 0;
		virtual float Unknown21() = 0;
		// 0x10752150 / 0x10752160 / 0x10752170: the defaults of the font (true, and two that do nothing)
		virtual bool Unknown22();
		virtual void Unknown23(bool value);
		virtual void Unknown24(bool value);
		virtual float Unknown25(const unsigned short* text) = 0;
	};

	// One glyph of the font (0x28 bytes): only the advance is read so far
	struct FontGlyph
	{
		unsigned char unknown0[0xC];
		float advance;
		unsigned char unknown10[0x18];
	};

	class TextureFont : public Font
	{
	public:
		// 0x1070EC40 / 0x1070EC90 (another unit): widens a text into the buffer (as much as fits, ended); the length /
		// draws an 8-bit text (widened into a buffer of 0x200 characters first; name guess)
		int ToWide(const char* text, unsigned short* buffer, int capacity);
		void DrawAnsi(const char* text, int unknown);

		virtual float Unknown3();
		virtual float Unknown4();
		virtual float Unknown5();
		virtual float Unknown6();
		virtual float Unknown7(const unsigned short* text, float width);
		virtual float Unknown8(const unsigned short* text);
		virtual float Unknown9(const unsigned short* text);
		virtual void Unknown10();
		virtual void Draw(const unsigned short* text, int unknown);
		virtual float Unknown12();
		virtual void Unknown13(float value);
		virtual void Unknown14(unsigned int* out);
		virtual void Unknown15(unsigned int* out);
		virtual void Unknown16(unsigned int value);
		virtual void SetColour(unsigned int colour);
		virtual Shader* Unknown18();
		virtual void Unknown19(Shader* shader);
		virtual bool Unknown20();
		virtual float Unknown21();
		virtual bool Unknown22();
		virtual void Unknown23(bool value);
		virtual void Unknown24(bool value);
		virtual float Unknown25(const unsigned short* text);

		// 0x10752250: whether the character is white space (space, tab, line feed, carriage return); the engine calls
		// it as a member and never reads this
		int IsSpace(unsigned short character);
		// 0x107523F0: the index of the glyph of the character (binary search in the sorted codes), -1 when there is none
		int FindGlyph(unsigned short character);
		// 0x10752AB0: makes the glyph of the character the one shown for characters without their own
		bool SetDefaultGlyph(unsigned short character);

		float unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
		float unknown20;
		bool unknown24;
		float unknown28;
		bool unknown2C;
		bool unknown2D;
		unsigned int colour;
		unsigned int unknown34;
		Shader* shader;
		unsigned int textureCount;
		Texture** textures;
		int defaultGlyph;
		int glyphCount;
		FontGlyph* glyphs;
		unsigned char* unknown50;
		unsigned short* codes;
	};
}

#endif
