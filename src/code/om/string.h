// The om library's string (RTTI: om::String; names guessed): a reference to shared character data that points at a
// common empty buffer when there is no text. Only construction, destruction and reading the text are described.
#ifndef OM_STRING_H
#define OM_STRING_H

namespace om
{
	// 0x110B63B8: the data every empty string points at
	extern char* gEmptyStringData;

	class String
	{
	public:
		// 0x105B3D50: a string of the text (the flag asks for a copy)
		String(const char* text, bool copy);
		// 0x105B3E00: the first characters of a text
		String(const char* text, unsigned int count);
		// 0x105B4070 (the engine's copy of the text is shared)
		String(const String& other);
		// 0x105B3FF0
		~String();

		const char* GetText() const
		{
			return data == gEmptyStringData ? "" : data;
		}

		// 0x105B4160
		String& operator=(const String& other);
		// 0x105B41F0: a copy with the capital letters made small
		String ToLower() const;
		// 0x105B3CD0: the characters, made writable (a copy when they are shared)
		char* GetWritableText();
		// 0x105B38B0: tells the string how long its text now is
		void SetLength(unsigned int newLength);

		char* data;
		unsigned short unknown4;
		unsigned short unknown6;
		unsigned short length;  // 8
		unsigned short unknownA;
	};
}

#endif
