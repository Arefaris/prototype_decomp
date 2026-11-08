// The timers of the particle profiler (RTTI names pure3d::particles::profiler::ScopedTimer and the three timers built on
// it): an object times its own life and adds the time to the totals of a record. Member names are guesses.
#ifndef PURE3D_EFFECTS_PARTICLEPROFILER_H
#define PURE3D_EFFECTS_PARTICLEPROFILER_H

namespace pure3d
{
	namespace particles
	{
		namespace profiler
		{
			// What a timer adds its time to (0x20 bytes; the records are the globals 0x11282AE0, 0x11282B20 and, for the
			// generic timers, the array at 0x11282B40)
			struct TimerRecord
			{
				unsigned __int64 total;
				unsigned __int64 frame;
				unsigned __int64 peak;
				float unknown18;
				int unknown1C;
			};

			extern TimerRecord gUpdateRecord;
			extern TimerRecord gCpuRenderRecord;
			extern TimerRecord gGenericRecords[];

			class ScopedTimer
			{
			public:
				// 0x1075CD10: starts the clock
				explicit ScopedTimer(TimerRecord* newRecord);
				// 0x1075CD40: adds the time since the start to the record's two totals (when the clock has moved)
				virtual ~ScopedTimer();

				unsigned __int64 start;
				TimerRecord* record;
			};

			// 0x1075D180
			class ScopedParticleUpdateTimer : public ScopedTimer
			{
			public:
				ScopedParticleUpdateTimer();
			};

			// 0x1075D1B0
			class ScopedCPURenderTimer : public ScopedTimer
			{
			public:
				ScopedCPURenderTimer();
			};

			// 0x1075D1E0
			class ScopedGenericTimer : public ScopedTimer
			{
			public:
				explicit ScopedGenericTimer(int index);
			};
		}
	}
}

#endif
