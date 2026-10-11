// math::Random: Marsaglia's multiply-with-carry generator (two 16-bit lagged states, multipliers 36969 and
// 18000). The class name and the member names are guesses; the constants and the default seeds are the binary's.
#ifndef MATH_RANDOM_H
#define MATH_RANDOM_H

#include "code/math/vector.h"

namespace math
{
	class Random
	{
	public:
		unsigned int z;
		unsigned int w;

		// Splits seed into the two states (high and low halves) and advances twice; 0 means the default seed
		void Seed(unsigned int seed);
		// Sets both states directly and advances twice; 0 means the default seed for that state
		void Seed(unsigned int seedZ, unsigned int seedW);
		// Three uniform values in [0, 1) / [-1, 1) (the mantissa bits of Next() under the exponent of 1 / 2)
		Vector NextVector01();
		Vector NextVector11();
		// A random unit vector: NextVector11 rejected until 0.001 <= |v|^2 <= 1, then normalised (name guess)
		Vector NextUnitVector();

		// One combined step: z and w advanced, (z << 16) + low 16 bits of w (name guess)
		unsigned int Next()
		{
			Step(z, 36969);
			unsigned int low = Step(w, 18000) & 0xFFFF;
			return (z << 16) + low;
		}
		// Next() as a float in [0, 1) / [-1, 1)
		float NextFloat01()
		{
			unsigned int bits = (Next() & 0x7FFFFF) | 0x3F800000;
			return *(float*)&bits - 1.0f;
		}
		float NextFloat11()
		{
			unsigned int bits = (Next() & 0x7FFFFF) | 0x40000000;
			return *(float*)&bits - 3.0f;
		}

	private:
		// One multiply-with-carry step of a state. Taking the state by reference is what the compiler saw: every
		// step stores to the member and reloads it (the inlined code does not keep the states in registers).
		static inline unsigned int Step(unsigned int& state, unsigned int multiplier)
		{
			return state = multiplier * (state & 0xFFFF) + (state >> 16);
		}
	};
}

#endif
