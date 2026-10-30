// The rate the online simulation steps at (unit 0x108FEA70 - 0x108FF2C0; no assert path, file name guessed).
#include "code/engine/online/variablesimrate.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108FEC90
	void VariableSimRate::SetRate(unsigned int newRate)
	{
		maxRate = newRate;
		targetRate = newRate;
		rate = newRate;
	}

	// FUNCTION: ENGINE 0x108FF260
	VariableSimRateDefault::VariableSimRateDefault()
	{
		next = 0;
		count = 3;
	}

	// FUNCTION: ENGINE 0x108FEB80
	// EQUIVALENT: register allocation (the engine keeps the wanted rate in esi and the loop counter of the last loop in edx; 94 %)
	void VariableSimRateDefault::AddSample(core::Time sample)
	{
		samples[next].time = sample;
		next = (next + 1) % 30;
		if (rate != targetRate)
		{
			return;
		}
		unsigned int slowest = 10000;
		unsigned int oldest = (next - count + 30) % 30;
		for (unsigned int i = 0; i < count; i++)
		{
			unsigned int milliseconds = samples[(i + oldest) % 30].time.milliseconds;
			if (slowest > milliseconds)
			{
				slowest = milliseconds;
			}
		}
		if (slowest > 1000)
		{
			slowest = 1000;
		}
		unsigned int wanted = 60 / (60 / (1000 / slowest) + 1);
		if (wanted < 10)
		{
			wanted = 10;
		}
		else if (wanted > maxRate)
		{
			wanted = maxRate;
		}
		if (rate <= wanted)
		{
			if (wanted <= rate)
			{
				return;
			}
			for (unsigned int i = 0; i < 30; i++)
			{
				if (samples[i].time.milliseconds > 1000 / wanted)
				{
					return;
				}
			}
		}
		targetRate = wanted;
	}

	// FUNCTION: ENGINE 0x108FECA0
	void VariableSimRateDefault::SetRate(unsigned int newRate)
	{
		VariableSimRate::SetRate(newRate);
		next = 0;
		for (int i = 0; i < 30; i++)
		{
			samples[i].time.Set(1, 0);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108FEA70
// FUNCTION: ENGINE 0x108FEA80
// FUNCTION: ENGINE 0x108FF2A0
