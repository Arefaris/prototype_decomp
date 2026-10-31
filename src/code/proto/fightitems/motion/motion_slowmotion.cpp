// Fight items of the motion group: SlowMotionTrack (unit 0x101B3980 - 0x101B3FC0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_slowmotion.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gSlowMotionTrackProperties;  // 0x11254ADC

			// FUNCTION: ENGINE 0x101B3980
			bool SlowMotionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B39A0
			bool SlowMotionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B39C0
			bool SlowMotionTrack::SetSimulationRate(float newValue)
			{
				simulationRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B39E0
			bool SlowMotionTrack::SetFadeInTime(float newValue)
			{
				fadeInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B3A00
			bool SlowMotionTrack::SetSimulationDuration(float newValue)
			{
				simulationDuration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B3A20
			bool SlowMotionTrack::SetFadeOutTime(float newValue)
			{
				fadeOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B3A40
			bool SlowMotionTrack::SetRealTime(bool newValue)
			{
				realTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B3A50
			bool SlowMotionTrack::SetAbortOnEnd(bool newValue)
			{
				abortOnEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B3A60
			fight::Property* SlowMotionTrack::GetProperty(int index)
			{
				return gSlowMotionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B3A80
			void SlowMotionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSlowMotionTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B3A90
			SlowMotionTrack::SlowMotionTrack() : fadeInTime(1.0f), fadeOutTime(1.0f), simulationDuration(-1.0f), simulationRate(0.5f), timeBegin(0.0f), timeEnd(-1.0f), abortOnEnd(true), realTime(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101B3B00
			float SlowMotionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B3B10
			float SlowMotionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B3B20
			SlowMotionTrack::~SlowMotionTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B3CA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SlowMotionTrack::RegisterProperties()
			{
				if (gSlowMotionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SlowMotionTrack>("timeBegin", &SlowMotionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SlowMotionTrack>("timeEnd", &SlowMotionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SlowMotionTrack>("simulationRate", &SlowMotionTrack::SetSimulationRate);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SlowMotionTrack>("fadeInTime", &SlowMotionTrack::SetFadeInTime);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<SlowMotionTrack>("simulationDuration", &SlowMotionTrack::SetSimulationDuration);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<SlowMotionTrack>("fadeOutTime", &SlowMotionTrack::SetFadeOutTime);
					properties[5] = property;
					property = new fight::PropertyBool<SlowMotionTrack>("realTime", &SlowMotionTrack::SetRealTime);
					properties[6] = property;
					property = new fight::PropertyBool<SlowMotionTrack>("abortOnEnd", &SlowMotionTrack::SetAbortOnEnd);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gSlowMotionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B3C70
			fight::TrackFactory* CreateSlowMotionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SlowMotionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B3EF0
			void RegisterSlowMotionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SlowMotionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<SlowMotionTrack>;
			template class fight::PropertyBool<SlowMotionTrack>;
			template class fight::TrackFactoryTemplate<SlowMotionTrack>;
			template class fight::TrackFactoryCasterTemplate<SlowMotionTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101B3B30
// FUNCTION: ENGINE 0x101B3B60
// FUNCTION: ENGINE 0x101B3B70
// FUNCTION: ENGINE 0x101B3BA0
// FUNCTION: ENGINE 0x101B3BD0
// FUNCTION: ENGINE 0x101B3C00
// FUNCTION: ENGINE 0x101B3C10
// FUNCTION: ENGINE 0x101B3C40
// FUNCTION: ENGINE 0x101B3C60
// FUNCTION: ENGINE 0x101B3F20
// FUNCTION: ENGINE 0x101B3F50
// FUNCTION: ENGINE 0x101B3F70
