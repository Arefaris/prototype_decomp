// pure3d::TextureFont: the text helpers of the debug font (0x1070EC40 - 0x1070ECD0; file name guessed from the class).
// Names are guesses.
#include "code/pure3d/context.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1070EC40
	int TextureFont::ToWide(const char* text, unsigned short* buffer, int capacity)
	{
		if (buffer == 0 || text == 0)
		{
			return 0;
		}
		int length = 0;
		if (text[0] != 0)
		{
			do
			{
				if (length >= capacity - 1)
				{
					break;
				}
				buffer[length] = text[length] & 0xFF;
				length++;
			} while (text[length] != 0);
		}
		buffer[length] = 0;
		return length;
	}

	// FUNCTION: ENGINE 0x1070EC90
	void TextureFont::DrawAnsi(const char* text, int unknown)
	{
		if (text != 0)
		{
			unsigned short wide[0x200];
			ToWide(text, wide, 0x200);
			Draw(wide, unknown);
		}
	}
}
