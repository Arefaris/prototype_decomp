// The reader of the om library's text formats (0x105BEA40 - 0x105BF5C0; names guessed).
#include "code/om/textscanner.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace om
{
	// FUNCTION: ENGINE 0x105BEA40
	unsigned int TextScanner::GetPosition() const
	{
		return position;
	}

	// FUNCTION: ENGINE 0x105BEA50
	int TextScanner::GetLine() const
	{
		return line;
	}

	// FUNCTION: ENGINE 0x105BEA60
	int ParseUnsigned(const char* digits, int count)
	{
		int result = 0;
		int scale = 1;
		for (const char* digit = digits + count - 1; digit >= digits; digit--)
		{
			result += (*digit - '0') * scale;
			scale *= 10;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105BEAA0
	int ParseNegative(const char* digits, int count)
	{
		int result = 0;
		int scale = 1;
		const char* first = digits + 1;
		for (const char* digit = digits + count - 1; digit >= first; digit--)
		{
			result += (*digit - '0') * scale;
			scale *= 10;
		}
		return -result;
	}

	// FUNCTION: ENGINE 0x105BEAE0
	int ParseSigned(const char* digits, int count)
	{
		if (*digits == '-')
		{
			return ParseNegative(digits, count);
		}
		return ParseUnsigned(digits, count);
	}

	// FUNCTION: ENGINE 0x105BEB00
	TextScanner::TextScanner(Stream* newStream)
	{
		stream = newStream;
		windowStart = 0;
		windowCount = 0;
		windowOffset = 0;
		line = 1;
		position = 0;
		bytesRead = 0;
		unsigned int size = 0;
		unsigned int start = 0;
		if (newStream->GetPosition(&start) && newStream->GetSize(&size))
		{
			length = size - start;
		}
		else
		{
			length = 0;
		}
	}

	// FUNCTION: ENGINE 0x105BEB90
	bool TextScanner::IsBuffered(unsigned int index) const
	{
		if (index >= windowStart && index < windowOffset + windowCount)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BEBC0
	char TextScanner::GetBuffered(unsigned int index) const
	{
		return window[(windowStart - windowOffset + index) & 0x7F];
	}

	// FUNCTION: ENGINE 0x105BEBE0
	// NONMATCHING: the engine stores the new start of the window behind the increment of the offset (87.8 %)
#ifdef NONMATCHING
	void TextScanner::Fill()
	{
		char* target = &window[(windowStart + windowCount) & 0x7F];
		if (stream->Read(target, 1))
		{
			bytesRead++;
			if (windowCount < 0x80)
			{
				windowCount++;
			}
			else
			{
				unsigned int next = (windowStart + 1) & 0x7F;
				windowOffset++;
				windowStart = next;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x105BEC50
	bool IsDigit(char character)
	{
		if ((unsigned char)(character - '0') <= 9)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BEC60
	bool IsWhitespace(char character)
	{
		if (character == '\t' || character == ' ' || character == '\n' || character == '\r')
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BEC80
	bool IsLetter(char character)
	{
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BECA0
	bool IsUpper(unsigned char character)
	{
		return character >= 'A' && character <= 'Z';
	}

	// FUNCTION: ENGINE 0x105BECC0
	// NONMATCHING: the engine keeps the output pointer in esi and the input in ecx (57.5 %)
#ifdef NONMATCHING
	void StripQuotes(char* text)
	{
		char* out = text;
		const char* in = text;
		if (*in != 0)
		{
			do
			{
				if (*in != '"')
				{
					*out = *in;
					out++;
				}
				in++;
			}
			while (*in != 0);
		}
		*out = 0;
	}
#endif

	// FUNCTION: ENGINE 0x105BECF0
	bool CharacterIn(char character, const char* set)
	{
		for (; *set != 0; set++)
		{
			if (character == *set)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BED20
	bool ReportError(TextScanner* scanner, Stream* stream, const char* format, ...)
	{
		char message[0x1000];
		va_list arguments;
		va_start(arguments, format);
		_vsnprintf_s(message, 0x1000, -1, format, arguments);
		message[0xFFF] = 0;
		StreamPrintf(stream, message);
		StreamPrintf(stream, "\nError Line: [%d]\n", scanner->line);
		return false;
	}

	// FUNCTION: ENGINE 0x105BED90
	// NONMATCHING: the engine pushes the index once for the test and the getter (96.4 %)
#ifdef NONMATCHING
	char TextScanner::CharAt(unsigned int index)
	{
		if (index >= length)
		{
			return 0;
		}
		if (index < windowOffset)
		{
			return 0;
		}
		if (!IsBuffered(index))
		{
			while (!IsBuffered(index))
			{
				Fill();
			}
		}
		return GetBuffered(index);
	}
#endif

	// FUNCTION: ENGINE 0x105BEDF0
	bool IsIdentifierStart(char character)
	{
		if (IsLetter(character) || character == '_')
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BEE10
	bool IsIdentifierPart(char character)
	{
		if (IsIdentifierStart(character) || IsDigit(character))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BEE40
	bool Matches(TextScanner* scanner, const char* text)
	{
		unsigned int index = scanner->position;
		unsigned int count = strlen(text);
		while (index - scanner->position < count)
		{
			if (scanner->position >= scanner->length)
			{
				return false;
			}
			if (scanner->CharAt(index) != *text)
			{
				return false;
			}
			index++;
			text++;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105BEEB0
	char TextScanner::Peek()
	{
		return CharAt(position);
	}

	// FUNCTION: ENGINE 0x105BEEC0
	void TextScanner::Advance()
	{
		if (position < length)
		{
			if (Peek() == '\n')
			{
				line++;
			}
			position++;
		}
	}

	// FUNCTION: ENGINE 0x105BEEF0
	void TextScanner::Skip(unsigned int count)
	{
		for (; count != 0; count--)
		{
			Advance();
		}
	}

	// FUNCTION: ENGINE 0x105BEF20
	void SkipWhitespace(TextScanner* scanner)
	{
		while (scanner->position < scanner->length)
		{
			if (!IsWhitespace(scanner->Peek()))
			{
				return;
			}
			scanner->Advance();
		}
	}

	// FUNCTION: ENGINE 0x105BEF60
	bool AtEnd(TextScanner* scanner)
	{
		SkipWhitespace(scanner);
		return scanner->position >= scanner->length;
	}

	// FUNCTION: ENGINE 0x105BEF90
	bool MatchesAfterWhitespace(TextScanner* scanner, const char* text)
	{
		SkipWhitespace(scanner);
		return Matches(scanner, text);
	}

	// FUNCTION: ENGINE 0x105BEFB0
	void SkipWord(TextScanner* scanner)
	{
		SkipWhitespace(scanner);
		while (scanner->position < scanner->length)
		{
			if (IsWhitespace(scanner->Peek()))
			{
				return;
			}
			scanner->Peek();
		}
	}

	// FUNCTION: ENGINE 0x105BF000
	bool Consume(TextScanner* scanner, const char* text)
	{
		if (Matches(scanner, text))
		{
			scanner->Skip(strlen(text));
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BF040
	bool ConsumeCharacter(TextScanner* scanner, char character)
	{
		SkipWhitespace(scanner);
		if (scanner->Peek() == character)
		{
			scanner->Advance();
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BF070
	void SkipLine(TextScanner* scanner)
	{
		while (scanner->position < scanner->length)
		{
			if (scanner->Peek() == '\n')
			{
				scanner->Advance();
				return;
			}
			scanner->Advance();
		}
	}

	// FUNCTION: ENGINE 0x105BF0B0
	bool ReadWord(TextScanner* scanner, char* buffer)
	{
		SkipWhitespace(scanner);
		char* start = buffer;
		while (scanner->position < scanner->length)
		{
			if (IsWhitespace(scanner->Peek()))
			{
				break;
			}
			*buffer = scanner->Peek();
			buffer++;
			scanner->Advance();
		}
		bool any = start != buffer;
		*buffer = 0;
		return any;
	}

	// FUNCTION: ENGINE 0x105BF120
	bool ReadQuoted(TextScanner* scanner, char* buffer, int size)
	{
		SkipWhitespace(scanner);
		char* end = buffer + size;
		if (scanner->position < scanner->length && scanner->Peek() == '"')
		{
			scanner->Advance();
			while (scanner->position < scanner->length && buffer < end)
			{
				if (scanner->Peek() == '"')
				{
					*buffer = 0;
					scanner->Advance();
					return true;
				}
				*buffer = scanner->Peek();
				buffer++;
				scanner->Advance();
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BF1C0
	int ReadSignedDigits(TextScanner* scanner)
	{
		char digits[0x80];
		SkipWhitespace(scanner);
		char* out = digits;
		if (scanner->Peek() == '-')
		{
			digits[0] = scanner->Peek();
			scanner->Advance();
			out = digits + 1;
		}
		while (scanner->Peek() >= '0' && scanner->Peek() <= '9')
		{
			*out = scanner->Peek();
			scanner->Advance();
			out++;
		}
		*out = 0;
		return ParseSigned(digits, out - digits);
	}

	// FUNCTION: ENGINE 0x105BF250
	bool ReadUnsigned(TextScanner* scanner, int* value)
	{
		SkipWhitespace(scanner);
		int result = 0;
		if (scanner->position < scanner->length)
		{
			while (!IsWhitespace(scanner->Peek()) && scanner->position < scanner->length)
			{
				char character = scanner->Peek();
				if ((unsigned char)(character - '0') > 9)
				{
					*value = 0;
					return false;
				}
				result = result * 10 + (character - '0');
				scanner->Advance();
			}
			*value = result;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BF2F0
	bool ReadInt(TextScanner* scanner, int* value)
	{
		*value = ReadSignedDigits(scanner);
		return true;
	}

	// FUNCTION: ENGINE 0x105BF310
	bool ReadSignedByte(TextScanner* scanner, char* value)
	{
		*value = (char)ReadSignedDigits(scanner);
		return true;
	}

	// FUNCTION: ENGINE 0x105BF330
	bool ReadUnsignedByte(TextScanner* scanner, char* value)
	{
		int number;
		if (!ReadUnsigned(scanner, &number))
		{
			return false;
		}
		*value = (char)number;
		return true;
	}

	// FUNCTION: ENGINE 0x105BF360
	float ReadFloatText(TextScanner* scanner)
	{
		char text[0x80];
		SkipWhitespace(scanner);
		char* out = text;
		if (scanner->Peek() == '-' || (scanner->Peek() >= '0' && scanner->Peek() <= '9') || scanner->Peek() == '.')
		{
			do
			{
				*out = scanner->Peek();
				scanner->Advance();
				out++;
			}
			while ((scanner->Peek() >= '0' && scanner->Peek() <= '9') || scanner->Peek() == '.');
		}
		*out = 0;
		return (float)atof(text);
	}

	// FUNCTION: ENGINE 0x105BF400
	bool AtDigit(TextScanner* scanner)
	{
		SkipWhitespace(scanner);
		return IsDigit(scanner->Peek());
	}

	// FUNCTION: ENGINE 0x105BF420
	bool ReadIdentifier(TextScanner* scanner, char* buffer)
	{
		SkipWhitespace(scanner);
		if (!IsIdentifierStart(scanner->Peek()))
		{
			return false;
		}
		*buffer = scanner->Peek();
		scanner->Advance();
		buffer++;
		while (IsIdentifierPart(scanner->Peek()))
		{
			*buffer = scanner->Peek();
			scanner->Advance();
			buffer++;
		}
		*buffer = 0;
		return true;
	}

	// FUNCTION: ENGINE 0x105BF4A0
	bool AtIdentifierStart(TextScanner* scanner)
	{
		SkipWhitespace(scanner);
		return IsIdentifierStart(scanner->Peek());
	}

	// FUNCTION: ENGINE 0x105BF4C0
	// NONMATCHING: the engine keeps the two flags in the homes of the arguments (frame layout, 13.9 %)
#ifdef NONMATCHING
	void ReadUntil(TextScanner* scanner, char* buffer, int size, const char* set)
	{
		bool quoted = false;
		if (scanner->position < scanner->length)
		{
			char* end = buffer + size - 1;
			while (buffer < end)
			{
				char character = scanner->Peek();
				if (character == '"')
				{
					quoted = !quoted;
				}
				else if (CharacterIn(character, set) && !quoted)
				{
					*buffer = 0;
					scanner->Advance();
					return;
				}
				*buffer = character;
				buffer++;
				scanner->Advance();
				if (scanner->position >= scanner->length)
				{
					break;
				}
			}
		}
		*buffer = 0;
	}
#endif

	// FUNCTION: ENGINE 0x105BF560
	char SkipAndConsume(TextScanner* scanner, const char* text)
	{
		SkipWhitespace(scanner);
		return Consume(scanner, text);
	}

	// FUNCTION: ENGINE 0x105BF580
	bool ReadFloat(TextScanner* scanner, float* value)
	{
		if (!AtDigit(scanner) && scanner->Peek() != '-')
		{
			return false;
		}
		*value = ReadFloatText(scanner);
		return true;
	}
}
