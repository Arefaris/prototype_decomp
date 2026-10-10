#include "code/core/time.h"

namespace core
{
	// FUNCTION: ENGINE 0x1063CBE0
	void Time::Set(unsigned int millis, unsigned int micros)
	{
		milliseconds = millis;
		microseconds = micros;
		seconds = millis * 0.001f + micros * 0.000001f;
	}

	// FUNCTION: ENGINE 0x1063CC30
	void Time::SetMicroseconds(unsigned __int64 value)
	{
		Set((unsigned int)(value / 1000), (unsigned int)(value % 1000));
	}

	// FUNCTION: ENGINE 0x1063CC60
	void Time::SetSeconds(float value)
	{
		seconds = value;
		milliseconds = (unsigned int)(value * 1000.0f);
		microseconds = (unsigned int)(value * 1000000.0f) % 1000;
	}

	// FUNCTION: ENGINE 0x1063CCE0
	void Time::Clear()
	{
		milliseconds = 0;
		microseconds = 0;
		seconds = 0.0f;
	}

	// FUNCTION: ENGINE 0x1063CD00
	// NONMATCHING: division by 1000 becomes a reciprocal multiply; the original uses div (docs/core_worklist.md).
	#ifdef NONMATCHING
	void Time::Add(unsigned int millis, unsigned int micros)
	{
		unsigned int total = microseconds + micros;
		milliseconds += millis + total / 1000;
		microseconds = total % 1000;
		seconds = milliseconds * 0.001f + microseconds * 0.000001f;
	}
	#endif

	// FUNCTION: ENGINE 0x1063CD60
	void Time::AddMicroseconds(unsigned __int64 value)
	{
		Add((unsigned int)(value / 1000), (unsigned int)(value % 1000));
	}

	// FUNCTION: ENGINE 0x1063CD90
	void Time::SubtractMicroseconds(unsigned __int64 value)
	{
		unsigned __int64 current = (unsigned __int64)milliseconds * 1000 + microseconds;
		if (current > value)
		{
			SetMicroseconds(current - value);
		}
		else
		{
			Clear();
		}
	}

	// FUNCTION: ENGINE 0x1063CDD0
	unsigned __int64 ScaleTime(unsigned __int64 value, unsigned __int64 multiplier, unsigned __int64 divisor)
	{
		return (value / divisor) * multiplier + ((value % divisor) * multiplier) / divisor;
	}
}
