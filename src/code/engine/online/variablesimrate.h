// engine::VariableSimRate and engine::VariableSimRateDefault (RTTI names): how often the online simulation steps. The rate is
// lowered when the machines send their updates slowly and raised again when they keep up. Unit 0x108FEA70 - 0x108FF2C0 (no
// assert path; file name guessed, the unit lies between the sync manager and the replay driver); names other than the
// RTTI ones are guesses.
#ifndef ENGINE_ONLINE_VARIABLESIMRATE_H
#define ENGINE_ONLINE_VARIABLESIMRATE_H

#include "code/core/time.h"

namespace engine
{
	// RTTI: engine::VariableSimRate (3 vftable slots, 0x10 bytes)
	class VariableSimRate
	{
	public:
		// The constructor and the destructor are inline (0x108FEB50 and 0x108FEA70 are the engine's copies)
		VariableSimRate()
		{
		}
		virtual ~VariableSimRate()
		{
		}
		// vftable slot 1: takes the time the last update took (pure)
		virtual void AddSample(core::Time sample) = 0;
		// vftable slot 2 (0x108FEC90): every rate is the given one
		virtual void SetRate(unsigned int newRate);

		unsigned int maxRate;  // +4
		unsigned int rate;  // +8
		unsigned int targetRate;  // +0xC
	};

	// RTTI: engine::VariableSimRateDefault (3 vftable slots, 0x180 bytes): averages the last updates
	class VariableSimRateDefault : public VariableSimRate
	{
	public:
		// 0x108FF260
		VariableSimRateDefault();

		// vftable slot 1 (0x108FEB80) and slot 2 (0x108FECA0)
		virtual void AddSample(core::Time sample);
		virtual void SetRate(unsigned int newRate);

		// One of the times the updates took (the constructor makes them zero)
		struct Sample
		{
			Sample() : time(0, 0)
			{
			}

			core::Time time;
		};

		Sample samples[30];  // +0x10
		unsigned int next;  // +0x178: the sample that is written next
		unsigned int count;  // +0x17C: how many of the newest samples the rate is chosen from
	};
}

#endif
