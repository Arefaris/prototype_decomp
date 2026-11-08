// The counters of the particle profiler (pure3d::particles::profiler; unit around 0x1075D210 - 0x1075D4E0, the file name
// is a guess): the particle code adds to them while it runs. Names are guesses.
#include "code/core/time.h"
#include "code/pure3d/effects/particleprofiler.h"

namespace pure3d
{
	namespace particles
	{
		namespace profiler
		{
			// 0x11282BA0, 0x11282BAC, 0x11282BB0, 0x11282BB4, 0x11282BB8
			int gCounter0;
			int gCounter1;
			int gCounter2;
			int gCounter3;
			int gCounter4;

			// FUNCTION: ENGINE 0x1075CD10
			ScopedTimer::ScopedTimer(TimerRecord* newRecord)
			{
				record = newRecord;
				start = core::GetElapsedMicroseconds();
			}

			// FUNCTION: ENGINE 0x1075CD40
			ScopedTimer::~ScopedTimer()
			{
				unsigned __int64 now = core::GetElapsedMicroseconds();
				if (start < now)
				{
					record->frame += now - start;
					record->total += now - start;
				}
			}

			// FUNCTION: ENGINE 0x1075D180
			ScopedParticleUpdateTimer::ScopedParticleUpdateTimer() : ScopedTimer(&gUpdateRecord)
			{
			}

			// FUNCTION: ENGINE 0x1075D1B0
			ScopedCPURenderTimer::ScopedCPURenderTimer() : ScopedTimer(&gCpuRenderRecord)
			{
			}

			// FUNCTION: ENGINE 0x1075D1E0
			ScopedGenericTimer::ScopedGenericTimer(int index) : ScopedTimer(&gGenericRecords[index])
			{
			}

			// FUNCTION: ENGINE 0x1075D2E0
			void AddCounter0(int count)
			{
				gCounter0 += count;
			}

			// FUNCTION: ENGINE 0x1075D2F0
			void AddCounter1(int count)
			{
				gCounter1 += count;
			}

			// FUNCTION: ENGINE 0x1075D300
			void AddCounter2(int count)
			{
				gCounter2 += count;
			}

			// FUNCTION: ENGINE 0x1075D310
			void AddCounter3(int count)
			{
				gCounter3 += count;
			}

			// FUNCTION: ENGINE 0x1075D320
			void AddCounter4(int count)
			{
				gCounter4 += count;
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1075D1A0
// FUNCTION: ENGINE 0x1075D1D0
// FUNCTION: ENGINE 0x1075D210
// FUNCTION: ENGINE 0x1075D360
// FUNCTION: ENGINE 0x1075D480
// FUNCTION: ENGINE 0x1075D4A0
// FUNCTION: ENGINE 0x1075D4C0
