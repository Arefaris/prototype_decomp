// The text forms of the numbers the front end's movie asks for (a FEMovie::Value holds a number or a string): whole
// numbers, floats, money and the time of day, and the names of the mouse buttons. The file name is a guess; the unit
// is 0x10883560 - 0x10883720.
#include "code/core/strings.h"
#include "code/core/textconvert.h"
#include "code/engine/frontend/femovie.h"

namespace engine
{
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
}
