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
		// 0x105B3FF0
		~String();

		const char* GetText() const
		{
			return data == gEmptyStringData ? "" : data;
		}

		char* data;
		unsigned short unknown4;
		unsigned short unknown6;
		unsigned short unknown8;
		unsigned short unknownA;
	};
}

#endif
