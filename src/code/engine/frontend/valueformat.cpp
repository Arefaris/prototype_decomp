// The text forms of the numbers the front end's movie asks for (a FEMovie::Value holds a number or a string): whole
// numbers, floats, money and the time of day, and the names of the mouse buttons. The file name is a guess; the unit
// is 0x10883560 - 0x10883720.
#include "code/core/language.h"
#include "code/core/strings.h"
#include "code/core/textcodec.h"
#include "code/core/textconvert.h"
#include "code/engine/frontend/femovie.h"
#include <string.h>

namespace engine
{
	// 0x10873F30 (another unit): the text a localization id ("Exception", ...) stands for, null for none
	const char* GetLocalizedText(const char* id);

	// The text forms a message can ask for (%0:NUMBER, %1:TIME, ...): the name and the function that writes the form of
	// a value (0x111D2D50, ended by an entry without a function)
	struct ValueFormat
	{
		const char* name;
		void (*format)(const FEMovie::Value* value, char* buffer, int size, const char* name);
	};
	extern ValueFormat gValueFormats[];

	// FUNCTION: ENGINE 0x10883560
	void FormatInteger(const FEMovie::Value* value, char* buffer, int size)
	{
		core::SNPrintf(buffer, size, "%d", (int)value->number);
	}

	// FUNCTION: ENGINE 0x10883590
	void FormatFloat2(const FEMovie::Value* value, char* buffer, int size)
	{
		core::SNPrintf(buffer, size, "%.2f", value->number);
	}

	// FUNCTION: ENGINE 0x108835C0
	void FormatFloat5(const FEMovie::Value* value, char* buffer, int size)
	{
		core::SNPrintf(buffer, size, "%.5f", value->number);
	}

	// FUNCTION: ENGINE 0x108835F0
	void FormatMoney(const FEMovie::Value* value, char* buffer, int size)
	{
		core::SNPrintf(buffer, size, "$%.0f", value->number);
	}

	// FUNCTION: ENGINE 0x10883620
	void FormatMoneyCents(const FEMovie::Value* value, char* buffer, int size)
	{
		core::SNPrintf(buffer, size, "$%.2f", value->number);
	}

	// FUNCTION: ENGINE 0x10883650
	// EQUIVALENT: the engine puts the chain for the hours after the first noon at the end of the function, after the
	// return, ours puts it in line and jumps over it (same operations, different block order), 72.7 %
	// The minutes of the day as a twelve-hour clock
	void FormatTimeOfDay(const FEMovie::Value* value, char* buffer, int size)
	{
		unsigned int minutes = (unsigned int)value->number;
		unsigned int hour = minutes / 60;
		unsigned int minute = minutes % 60;
		const char* suffix;
		if (hour == 0)
		{
			hour = 12;
			suffix = "AM";
		}
		else
		{
			if (hour < 12)
			{
				suffix = "AM";
			}
			else
			{
				if (hour > 12)
				{
					hour -= 12;
				}
				suffix = "PM";
			}
		}
		core::SNPrintf(buffer, size, "%d:%.2d%s", hour, minute, suffix);
	}

	// FUNCTION: ENGINE 0x108836F0
	const char* GetMouseButtonName(unsigned int button)
	{
		const char* names[3] = { "LEFT_MOUSE", "RIGHT_MOUSE", "MIDDLE_MOUSE" };
		if (button <= 2)
		{
			return names[button];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x108836D0
	void FormatDateShort(const FEMovie::Value* value, char* buffer, int size, const char* name)
	{
	}

	// FUNCTION: ENGINE 0x108836E0
	void FormatDateLong(const FEMovie::Value* value, char* buffer, int size, const char* name)
	{
	}

	// FUNCTION: ENGINE 0x108838C0
	// EQUIVALENT: the engine keeps the value in eax and its type in ecx (ours the other way round), so the loads of the
	// arguments use other registers, 83.7 %
	// The text of a string value (type 4) or a wide string value (type 5)
	bool GetValueText(const FEMovie::Value* value, char* buffer, unsigned int size)
	{
		if (value->type == 4)
		{
			core::StrNCpy(buffer, value->string, size);
			return true;
		}
		if (value->type == 5)
		{
			return core::ConvertText(buffer, 0, value->string, 2, 0, size, 0, 0, 0) == 0;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108833E0
	// Makes the text of a message: the places in it (a percent sign, the number of the value, a separator and the name
	// of a form) are filled with the value in that form. The result is a wide string value at the target.
	void FormatMessage(const FEMovie::Value* values, int unused, FEMovie::Value* result, char* target, int size,
		const char* text)
	{
		char output[0x800];
		char converted[0x800];
		int out = 0;
		int in = 0;
		if (core::ConvertText(converted, 0, text, 1, 0, 0x800, 0, 0, 0) == 0 && strchr(converted, '%') == 0)
		{
			core::Utf8CopyString(output, text, 0x800);
		}
		else
		{
			while (true)
			{
				char c = text[in];
				in++;
				if (c != '%')
				{
					output[out] = c;
					out++;
					if (c == 0)
					{
						break;
					}
				}
				else
				{
					unsigned int index = (unsigned char)text[in] - '0';
					if (index <= 9)
					{
						in += 2;
						for (const ValueFormat* form = gValueFormats; form->format != 0; form++)
						{
							if (core::StrNCmp(form->name, text + in, core::StrLen(form->name)) == 0)
							{
								form->format(&values[index], output + out, 0x800 - out, form->name);
								in += core::StrLen(form->name);
								unsigned int bytes;
								core::Utf8Count(output + out, &bytes);
								out += bytes;
								break;
							}
						}
					}
					else
					{
						output[out] = '%';
						out++;
					}
				}
			}
		}
		core::ConvertText(target, 2, output, 1, 0, size, 0, 0, 0);
		result->string = target;
		result->type = 5;
	}

	// FUNCTION: ENGINE 0x10883790
	// Writes the text between brackets; the text is in capitals in this language
	void FormatBracketed(char* buffer, const char* text)
	{
		if (core::LanguageGet() == 0x45)
		{
			char upper[0x20];
			unsigned int length = 0;
			core::StrNCpy(upper, text, 0x20, &length);
			for (unsigned int i = 0; i < length; i++)
			{
				upper[i] = core::ToUpperChar(upper[i]);
			}
			core::FormatValue(buffer, 0x20, "[%s]", (int)upper);
			return;
		}
		core::FormatValue(buffer, 0x20, "[%s]", (int)text);
	}

	// FUNCTION: ENGINE 0x10883920
	// A string value that starts with a dollar sign is the id of a message: the result is the message with its places
	// filled; any other value is the result as it is
	bool TranslateValue(const FEMovie::Value* value, int unused, FEMovie::Value* result, char* target, int size)
	{
		char id[0x100];
		if (!GetValueText(value, id, 0x100))
		{
			result->type = value->type;
			result->bits = value->bits;
			return false;
		}
		if (id[0] != '$')
		{
			result->type = value->type;
			result->bits = value->bits;
			return false;
		}
		const char* text = GetLocalizedText(id + 1);
		if (text == 0)
		{
			result->type = value->type;
			result->bits = value->bits;
			return false;
		}
		FormatMessage(value, unused, result, target, size, text);
		return true;
	}

	// FUNCTION: ENGINE 0x108839E0
	void FormatString(const FEMovie::Value* value, char* buffer, int size, const char* name)
	{
		if (value->type == 4)
		{
			char id[0x100];
			if (GetValueText(value, id, 0x100) && id[0] == '$')
			{
				const char* text = GetLocalizedText(id + 1);
				if (text != 0)
				{
					core::Utf8CopyString(buffer, text, size);
					return;
				}
			}
			core::ConvertText(buffer, 1, value->string, 0, 0, size, 0, 0, 0);
		}
		else if (value->type == 5)
		{
			core::ConvertText(buffer, 1, value->string, 2, 0, size, 0, 0, 0);
		}
	}
}
