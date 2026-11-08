// proto::FlashValue: see flashvalue.h. Unit 0x104C2170 - 0x104C2610 (no assert path; the file name is a guess).
#include "code/proto/frontend/flashvalue.h"

#include <string.h>
#include <wchar.h>

namespace ATL
{
	template<class T> class ChTraitsOS;

	// The library's string comparison (strcmp and wcscmp compiled out of line)
	template<> class ChTraitsOS<char>
	{
	public:
		// 0x104C21A0
		static int StringCompare(const char* a, const char* b);
	};
	template<> class ChTraitsOS<wchar_t>
	{
	public:
		// 0x1095CA60
		static int StringCompare(const wchar_t* a, const wchar_t* b);
	};

	// FUNCTION: ENGINE 0x104C21A0
	int ChTraitsOS<char>::StringCompare(const char* a, const char* b)
	{
		return strcmp(a, b);
	}

	// FUNCTION: ENGINE 0x1095CA60
	int ChTraitsOS<wchar_t>::StringCompare(const wchar_t* a, const wchar_t* b)
	{
		return wcscmp(a, b);
	}
}

namespace proto
{
	static __forceinline double Abs(double number)
	{
		return number >= 0.0 ? number : -number;
	}

	// FUNCTION: ENGINE 0x104C24B0
	// NONMATCHING: the wide string call loads its operands into eax and ecx, 97 %
#ifdef NONMATCHING
	bool FlashValue::operator==(const FlashValue& other) const
	{
		if (type == other.type)
		{
			switch (type)
			{
			case FLASHVALUE_UNDEFINED:
			case FLASHVALUE_NULL:
				return true;
			case FLASHVALUE_BOOLEAN:
				if (value.boolean == other.value.boolean)
				{
					return true;
				}
				break;
			case FLASHVALUE_NUMBER:
			{
				if (Abs(value.number - other.value.number) <= 9.999999747378752e-06)
				{
					return true;
				}
				break;
			}
			case FLASHVALUE_STRING:
				if (ATL::ChTraitsOS<char>::StringCompare(value.string, other.value.string) == 0)
				{
					return true;
				}
				break;
			case FLASHVALUE_WIDESTRING:
				if (ATL::ChTraitsOS<wchar_t>::StringCompare(value.wideString, other.value.wideString) == 0)
				{
					return true;
				}
				break;
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x104C2570
	bool FlashValue::operator!=(const FlashValue& other) const
	{
		return !(*this == other);
	}

	// FUNCTION: ENGINE 0x104C2300
	FlashValue& FlashValue::operator=(const FlashValue& other)
	{
		switch (other.type)
		{
		case FLASHVALUE_UNDEFINED:
		case FLASHVALUE_NULL:
		case FLASHVALUE_BOOLEAN:
		case FLASHVALUE_NUMBER:
			type = other.type;
			value = other.value;
			break;
		case FLASHVALUE_STRING:
			SetString(other.value.string);
			break;
		case FLASHVALUE_WIDESTRING:
			SetWideString(other.value.wideString);
			break;
		}
		return *this;
	}
}
