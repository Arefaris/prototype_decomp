// The reader of the om library's text formats (names guessed): it looks at a stream through a window of 128
// characters, keeps the line it is on, skips white space and reads words, quoted texts, identifiers and numbers.
#ifndef OM_TEXTSCANNER_H
#define OM_TEXTSCANNER_H

#include "code/om/stream.h"

namespace om
{
	// 0x105BEC50 / 0x105BEC60 / 0x105BEC80 / 0x105BECA0: a digit, white space, a letter, a capital letter
	bool IsDigit(char character);
	bool IsWhitespace(char character);
	bool IsLetter(char character);
	bool IsUpper(unsigned char character);
	// 0x105BEDF0 / 0x105BEE10: a letter or an underscore, and a digit as well
	bool IsIdentifierStart(char character);
	bool IsIdentifierPart(char character);
	// 0x105BECC0: takes the quotation marks out of the text
	void StripQuotes(char* text);
	// 0x105BECF0: the character is in the text
	bool CharacterIn(char character, const char* set);
	// 0x105BEA60 / 0x105BEAA0 / 0x105BEAE0: the number in the digits (the second one skips a sign in front of them and
	// makes the number negative, the third one looks for the sign)
	int ParseUnsigned(const char* digits, int count);
	int ParseNegative(const char* digits, int count);
	int ParseSigned(const char* digits, int count);

	class TextScanner
	{
	public:
		// 0x105BEB00: a scanner of what is left in the stream
		explicit TextScanner(Stream* newStream);
		// 0x105BEA40 / 0x105BEA50: how many characters were passed, and the line
		unsigned int GetPosition() const;
		int GetLine() const;
		// 0x105BEB90: the window holds the character
		bool IsBuffered(unsigned int index) const;
		// 0x105BEBC0: a character of the window
		char GetBuffered(unsigned int index) const;
		// 0x105BEBE0: reads one more character into the window
		void Fill();
		// 0x105BED90: the character at that position, 0 outside of the text
		char CharAt(unsigned int index);
		// 0x105BEEB0 / 0x105BEEC0 / 0x105BEEF0: the character at the position, going on by one, going on by many
		char Peek();
		void Advance();
		void Skip(unsigned int count);

		char window[0x80];
		Stream* stream;  // 0x80
		unsigned int windowStart;  // 0x84
		unsigned int windowCount;  // 0x88
		unsigned int windowOffset;  // 0x8C
		int line;  // 0x90
		unsigned int position;  // 0x94
		unsigned int length;  // 0x98
		unsigned int bytesRead;  // 0x9C
	};

	// 0x105BED20: tells the stream what is wrong (the text and the line), answers false
	bool ReportError(TextScanner* scanner, Stream* stream, const char* format, ...);
	// 0x105BEE40: the text stands at the position
	bool Matches(TextScanner* scanner, const char* text);
	// 0x105BEF20: passes white space
	void SkipWhitespace(TextScanner* scanner);
	// 0x105BEF60: nothing but white space is left
	bool AtEnd(TextScanner* scanner);
	// 0x105BEF90: the text stands behind the white space
	bool MatchesAfterWhitespace(TextScanner* scanner, const char* text);
	// 0x105BEFB0: passes white space, then everything up to the next white space
	void SkipWord(TextScanner* scanner);
	// 0x105BF000: passes the text when it stands at the position
	bool Consume(TextScanner* scanner, const char* text);
	// 0x105BF040: passes the character when it stands behind the white space
	bool ConsumeCharacter(TextScanner* scanner, char character);
	// 0x105BF070: passes the rest of the line
	void SkipLine(TextScanner* scanner);
	// 0x105BF0B0: reads up to the next white space, false when there is nothing
	bool ReadWord(TextScanner* scanner, char* buffer);
	// 0x105BF120: reads a text in quotation marks, false when it does not fit or does not end
	bool ReadQuoted(TextScanner* scanner, char* buffer, int size);
	// 0x105BF1C0 / 0x105BF250: a number with an optional minus sign, and an unsigned one that ends at white space
	int ReadSignedDigits(TextScanner* scanner);
	bool ReadUnsigned(TextScanner* scanner, int* value);
	// 0x105BF2F0 / 0x105BF310 / 0x105BF330: the signed number as an int, as a byte, the unsigned one as a byte
	bool ReadInt(TextScanner* scanner, int* value);
	bool ReadSignedByte(TextScanner* scanner, char* value);
	bool ReadUnsignedByte(TextScanner* scanner, char* value);
	// 0x105BF360: a number with a decimal point
	float ReadFloatText(TextScanner* scanner);
	// 0x105BF400: a digit stands behind the white space
	bool AtDigit(TextScanner* scanner);
	// 0x105BF420: reads an identifier
	bool ReadIdentifier(TextScanner* scanner, char* buffer);
	// 0x105BF4A0: a letter or an underscore stands behind the white space
	bool AtIdentifierStart(TextScanner* scanner);
	// 0x105BF4C0: reads up to a character of the set that is not inside quotation marks
	void ReadUntil(TextScanner* scanner, char* buffer, int size, const char* set);
	// 0x105BF560: passes white space and the text
	char SkipAndConsume(TextScanner* scanner, const char* text);
	// 0x105BF580: reads a number that may have a decimal point or a minus sign
	bool ReadFloat(TextScanner* scanner, float* value);
}

#endif
