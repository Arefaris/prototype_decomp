// The value a head-up display variable hands to the front end's movie (no RTTI: the class and member names are guesses,
// the layouts are the engine's). A FlashVariant is the sixteen bytes the movie takes (its kind, then the value); a
// FlashValue keeps a string it owns behind them. The kinds are 0 undefined, 1 null, 2 boolean, 3 number, 4 string
// (copied into the value's own buffer) and 5 wide string (borrowed). Unit 0x104C2170 - 0x104C2610 (no assert path; the
// file name is a guess).
#ifndef PROTO_FRONTEND_FLASHVALUE_H
#define PROTO_FRONTEND_FLASHVALUE_H

#include <string.h>

namespace proto
{
	enum FlashValueType
	{
		FLASHVALUE_UNDEFINED = 0,
		FLASHVALUE_NULL = 1,
		FLASHVALUE_BOOLEAN = 2,
		FLASHVALUE_NUMBER = 3,
		FLASHVALUE_STRING = 4,
		FLASHVALUE_WIDESTRING = 5
	};

	struct FlashVariant
	{
		FlashVariant()
		{
		}
		explicit FlashVariant(int newType)
		{
			type = newType;
		}
		// 0x104C21E0 / 0x104C2280: the kind and the value; the word between them is left alone
		FlashVariant(const FlashVariant& other)
		{
			type = other.type;
			value = other.value;
		}

		int type;
		int unknown4;
		union
		{
			bool boolean;
			double number;
			const char* string;
			const wchar_t* wideString;
		} value;
	};

	struct FlashValue : public FlashVariant
	{
		FlashValue() : FlashVariant(FLASHVALUE_UNDEFINED)
		{
		}
		explicit FlashValue(bool newBoolean) : FlashVariant(FLASHVALUE_UNDEFINED)
		{
			type = FLASHVALUE_BOOLEAN;
			value.boolean = newBoolean;
		}

		// 0x104A9C60 / 0x104A9C80
		explicit FlashValue(double newNumber)
		{
			value.number = newNumber;
			type = FLASHVALUE_NUMBER;
		}
		// 0x104C22A0: keeps a copy of the text
		void SetString(const char* text)
		{
			type = FLASHVALUE_STRING;
			strcpy_s(buffer, sizeof(buffer), text);
			value.string = buffer;
		}
		// 0x104C2250 / 0x104C22E0: refers to the text
		void SetWideString(const wchar_t* text)
		{
			type = FLASHVALUE_WIDESTRING;
			value.wideString = text;
		}
		// 0x104C24B0: the same kind and the same value (numbers differ by no more than a small error; strings by content)
		bool operator==(const FlashValue& other) const;
		// 0x104C2570
		bool operator!=(const FlashValue& other) const;
		// 0x104C2300: copies the kind and the value (a string into the value's own buffer)
		FlashValue& operator=(const FlashValue& other);

		char buffer[0x80];  // +0x10
	};
}

#endif
