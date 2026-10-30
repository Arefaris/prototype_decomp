// pure3d::Font and pure3d::TextureFont (unit around 0x10752120 - 0x10753D70; the directory is a guess, the file is named
// after the class). Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/font.h"
#include "code/pure3d/shader.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10752150
	bool Font::Unknown22()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10752160
	void Font::Unknown23(bool value)
	{
	}

	// FUNCTION: ENGINE 0x10752170
	void Font::Unknown24(bool value)
	{
	}

	// FUNCTION: ENGINE 0x10752250
	int TextureFont::IsSpace(unsigned short character)
	{
		if (character != 0x20 && character != 9 && character != 10 && character != 0xD)
		{
			return 0;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10752280
	// NONMATCHING: the engine adds the line advance in a copy and keeps the running height in xmm1, ours adds in place (54.8 %)
#ifdef NONMATCHING
	float TextureFont::Unknown8(const unsigned short* text)
	{
		if (text == 0)
		{
			return 0.0f;
		}
		float line = unknown20 + unknown18;
		float height = unknown18;
		for (int i = 0; text[i] != 0; i++)
		{
			if (text[i] == 10)
			{
				height = line + height;
			}
		}
		return height;
	}
#endif

	// FUNCTION: ENGINE 0x107522E0
	float TextureFont::Unknown9(const unsigned short* text)
	{
		if (text == 0)
		{
			return 0.0f;
		}
		int i = 0;
		float widest = 0.0f;
		unsigned short character = text[0];
		while (character != 0)
		{
			float width = Unknown25(text + i);
			if (widest < width)
			{
				widest = width;
			}
			character = text[i];
			while (character != 0 && character != 10)
			{
				i++;
				character = text[i];
			}
			if (text[i] == 10)
			{
				i++;
			}
			character = text[i];
		}
		return widest;
	}

	// FUNCTION: ENGINE 0x107523F0
	int TextureFont::FindGlyph(unsigned short character)
	{
		int low = 0;
		int high = glyphCount - 1;
		if (high >= 0)
		{
			do
			{
				int middle = (high + low) >> 1;
				unsigned short code = codes[middle];
				if (character == code)
				{
					return middle;
				}
				if (character < code)
				{
					high = middle - 1;
				}
				else
				{
					low = middle + 1;
				}
			} while (low <= high);
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x107527D0
	float TextureFont::Unknown3()
	{
		return unknown10;
	}

	// FUNCTION: ENGINE 0x107527E0
	float TextureFont::Unknown4()
	{
		return unknown14;
	}

	// FUNCTION: ENGINE 0x107527F0
	float TextureFont::Unknown5()
	{
		return unknown18;
	}

	// FUNCTION: ENGINE 0x10752800
	float TextureFont::Unknown6()
	{
		return unknown1C;
	}

	// FUNCTION: ENGINE 0x10752810
	float TextureFont::Unknown12()
	{
		return unknown20;
	}

	// FUNCTION: ENGINE 0x10752820
	void TextureFont::Unknown13(float value)
	{
		unknown20 = value > 0.0f ? value : 0.0f;
	}

	// FUNCTION: ENGINE 0x10752840
	// EQUIVALENT: the same load and store; the engine loads the colour into ecx and the pointer into eax, ours the other way round (75.0 %)
	void TextureFont::Unknown14(unsigned int* out)
	{
		unsigned int value = colour;
		*out = value;
	}

	// FUNCTION: ENGINE 0x10752850
	void TextureFont::SetColour(unsigned int newColour)
	{
		colour = newColour;
	}

	// FUNCTION: ENGINE 0x10752860
	// EQUIVALENT: the same load and store; the engine loads the colour into ecx and the pointer into eax, ours the other way round (75.0 %)
	void TextureFont::Unknown15(unsigned int* out)
	{
		unsigned int value = colour;
		*out = value;
	}

	// FUNCTION: ENGINE 0x10752870
	void TextureFont::Unknown16(unsigned int value)
	{
		unknown34 = value;
	}

	// FUNCTION: ENGINE 0x10752880
	Shader* TextureFont::Unknown18()
	{
		return shader;
	}

	// FUNCTION: ENGINE 0x10752890
	bool TextureFont::Unknown20()
	{
		return unknown24;
	}

	// FUNCTION: ENGINE 0x107528A0
	float TextureFont::Unknown21()
	{
		return unknown28;
	}

	// FUNCTION: ENGINE 0x107528B0
	bool TextureFont::Unknown22()
	{
		return unknown2D;
	}

	// FUNCTION: ENGINE 0x107528C0
	void TextureFont::Unknown23(bool value)
	{
		unknown2D = value;
	}

	// FUNCTION: ENGINE 0x107528D0
	void TextureFont::Unknown24(bool value)
	{
		unknown2C = value;
	}

	// FUNCTION: ENGINE 0x10752990
	// NONMATCHING: the engine keeps the position of the last space in ebp and the characters in ebx, the running widths in xmm0 / xmm2 and the
	// line step in xmm4; ours allocates the loop differently (11.2 %)
#ifdef NONMATCHING
	float TextureFont::Unknown7(const unsigned short* text, float width)
	{
		float lineSpacing = Unknown12();
		float step = Unknown5() + lineSpacing;
		float zero = 0.0f;
		int lastSpace = -1;
		float height = 0.0f;
		float x = 0.0f;
		float result = 0.0f;
		int next = 0;
		if (text[0] != 0)
		{
			int position;
			do
			{
				position = next;
				unsigned short character = text[position];
				if (character == 10)
				{
					height = height + step;
					lastSpace = -1;
					x = zero;
				}
				else
				{
					int glyph = FindGlyph(character);
					if (glyph == 0 || glyph == -1)
					{
						glyph = defaultGlyph;
					}
					x = glyphs[glyph].advance + x;
					if (x <= width)
					{
						if (IsSpace(character))
						{
							lastSpace = position;
						}
					}
					else
					{
						height = height + step;
						if (!IsSpace(character) && lastSpace != -1)
						{
							position = lastSpace + 1;
						}
						lastSpace = -1;
						x = zero;
					}
				}
				next = position + 1;
			} while (text[next] != 0);
			result = height;
			if (next != 0 && text[position] != 10)
			{
				result = height + step;
			}
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10752A90
	void TextureFont::Unknown19(Shader* newShader)
	{
		core::RefAssign(shader, newShader);
	}

	// FUNCTION: ENGINE 0x10752AB0
	bool TextureFont::SetDefaultGlyph(unsigned short character)
	{
		int glyph = FindGlyph(character);
		if (glyph >= 0)
		{
			defaultGlyph = glyph;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10752AD0
	// NONMATCHING: register allocation of the loop (text in ebx, this in edi) differs (26.1 %)
#ifdef NONMATCHING
	float TextureFont::Unknown25(const unsigned short* text)
	{
		if (text == 0 || text[0] == 0 || text[0] == 10)
		{
			return 0.0f;
		}
		float width = 0.0f;
		int i = 0;
		unsigned short character = text[0];
		do
		{
			if (character == 10)
			{
				break;
			}
			int glyph = FindGlyph(character);
			float advance;
			if (glyph < 0)
			{
				advance = glyphs[defaultGlyph].advance;
			}
			else
			{
				advance = glyphs[glyph].advance;
			}
			character = text[i + 1];
			i++;
			width = advance + width;
		} while (character != 0);
		return width;
	}
#endif
}
