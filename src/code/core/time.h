// Time value used by the core timing code (class association, method, member and file names guessed).
// Layout inferred from 0x1063CBE0 - 0x1063CDCD; core::Time appears in the engine's RTTI names.
#ifndef CORE_TIME_H
#define CORE_TIME_H

namespace core
{
	class Time
	{
	public:
		// Stores both parts as supplied; unlike Add, this does not normalize microseconds.
		void Set(unsigned int milliseconds, unsigned int microseconds);
		void SetMicroseconds(unsigned __int64 value);
		void SetSeconds(float value);
		void Clear();
		void Add(unsigned int milliseconds, unsigned int microseconds);
		void AddMicroseconds(unsigned __int64 value);
		// Saturates at zero when value is at least the current time.
		void SubtractMicroseconds(unsigned __int64 value);

		unsigned int microseconds;
		unsigned int milliseconds;
		float seconds;
	};

	// Computes (value / divisor) * multiplier + ((value % divisor) * multiplier) / divisor.
	// Name guessed; preserves the original's unsigned 64-bit intermediate arithmetic.
	unsigned __int64 ScaleTime(unsigned __int64 value, unsigned __int64 multiplier, unsigned __int64 divisor);
}

#endif
