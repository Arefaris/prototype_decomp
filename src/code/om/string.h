// The om library's string (RTTI: om::String; names guessed): a reference to shared character data that points at a
// common empty buffer when there is no text. The mode says what the data is: 0 a text that stays where it is for good,
// 1 a text that is only borrowed (copying the string makes a buffer of its own), 2 a buffer that belongs to the strings
// that point at it (its reference count sits eight bytes in front of the characters).
#ifndef OM_STRING_H
#define OM_STRING_H

namespace om
{
	// 0x110B63B8: the data every empty string points at
	extern char* gEmptyStringData;

	class String
	{
	public:
		// 0x105B39F0: the empty string
		String();
		// 0x105B3D50: a string of the text in the mode (0 a text that stays, 1 a borrowed text)
		String(const char* text, int newMode);
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

		// 0x105B38C0: the data pointer (name guess)
		char* GetData() const;
		// 0x105B3A20: the engine's out of line copy of GetText, which a few members of the unit call (name guess)
		const char* GetTextOutOfLine() const;

		// 0x105B4160
		String& operator=(const String& other);
		// 0x105B3B50: the same characters
		bool operator==(const String& other) const;
		// 0x105B41F0: a copy with the capital letters made small
		String ToLower() const;
		// 0x105B3CD0: the characters, made writable (a copy when they are shared)
		char* GetWritableText();
		// 0x105B38B0: tells the string how long its text now is
		void SetLength(unsigned int newLength);

		// 0x105B3E20: an empty string with room for that many characters (the first argument is not read)
		String(int unused, unsigned int capacity);
		// 0x105B3DB0: the characters of a text (the empty string for no text), in the mode
		String(const char* text, unsigned int count, int newMode);
		// 0x105B3C60: points the string at the text (a buffer of its own for mode 2)
		void Initialize(const char* text, unsigned int count, unsigned int capacity, int newMode);
		// 0x105B4000: becomes a copy of the other string
		void Copy(const String& other);
		// 0x105B3CC0: gives a buffer of its own up
		void Release();
		// 0x105B3E40: gives the old text up and takes the characters of a text
		String& Set(const char* text, unsigned int count, int newMode);
		// 0x105B3ED0: the other string behind this one
		String& operator+=(const String& other);
		// 0x105B4310: one more character
		String& Append(char character);
		// 0x105B3A30 / 0x105B3A50: the text read as a number
		float ToFloat() const;
		unsigned int ToUnsignedInt() const;
		// 0x105B3A90: a character of the text
		char GetCharacter(int index) const;
		// 0x105B3BB0 / 0x105B3C10 / 0x105B3C30: comparisons
		bool operator==(const char* other) const;
		bool operator!=(const String& other) const;
		bool operator!=(const char* other) const;

		// 0x105B4090 / 0x105B40E0 / 0x105B4120: the text of a number
		explicit String(float value);
		explicit String(int value);
		explicit String(unsigned int value);
		// 0x105B4270 / 0x105B42C0: the text of a number behind this one
		String& operator+=(float value);
		String& operator+=(unsigned int value);
		// 0x105B43A0 / 0x105B43D0 / 0x105B43F0: this with something behind it
		String operator+(float value) const;
		String operator+(unsigned int value) const;
		String operator+(const String& other) const;
		// 0x105B4230: a copy with the small letters made capital
		String ToUpper() const;
		// 0x105B4410: count characters from the start (a string of just that part)
		String Substring(unsigned int start, unsigned int count) const;
		// 0x105B4460: from the start to the end
		String Tail(unsigned int start) const;
		// 0x105B4480: the first count characters
		String Head(unsigned int count) const;
		// 0x105B44A0: the other string is the end of this one
		bool EndsWith(const String& suffix) const;

		// A string of a text that stays where it is (the value is built in the caller's place)
		static String Wrap(const char* text)
		{
			return String(text, false);
		}

		char* data;
		unsigned short mode;  // 4
		unsigned short unknown6;
		unsigned short length;  // 8
		unsigned short unknownA;
	};

	// 0x105B3E70: the formatted text (up to 4096 characters; the first argument is not read)
	String Format(int unused, const char* format, ...);
	// 0x105B3750: formats into a buffer (the last character is always a zero); answers what the C library answers
	int FormatBuffer(char* buffer, unsigned int size, const char* format, ...);
	// 0x105B4500: the string with a space in front of every capital letter that does not follow one (up to 255 characters)
	String SpaceOutCapitals(const String& source);
	// 0x105B46B0: sets the string to the last characters of the source (a number of them, the end of the text included)
	void AssignTail(String& result, const String& source, unsigned int count);
	// 0x105B4180: sets the string to the formatted text
	String& Sprintf(String& result, const char* format, ...);
}

#endif
