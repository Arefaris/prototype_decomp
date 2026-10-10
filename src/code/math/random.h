// math::Random: Marsaglia's multiply-with-carry generator (two 16-bit lagged states, multipliers 36969 and
// 18000). The class name and the member names are guesses; the constants and the default seeds are the binary's.
#ifndef MATH_RANDOM_H
#define MATH_RANDOM_H

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

	private:
		// One multiply-with-carry step of a state. Taking the state by reference is what the compiler saw: every
		// step stores to the member and reloads it (the inlined code does not keep the states in registers).
		static inline void Step(unsigned int& state, unsigned int multiplier)
		{
			state = multiplier * (state & 0xFFFF) + (state >> 16);
		}
	};
}

#endif
