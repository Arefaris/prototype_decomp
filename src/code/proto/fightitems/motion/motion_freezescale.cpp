// Fight items of the motion group: FreezeScaleTrack (unit 0x10161980 - 0x10161F50; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_freezescale.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFreezeScaleTrackProperties;  // 0x11254544

			// FUNCTION: ENGINE 0x10161980
			bool FreezeScaleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101619A0
			bool FreezeScaleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161A40
			bool FreezeScaleTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101619C0
			bool FreezeScaleTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101619D0
			bool FreezeScaleTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101619F0
			bool FreezeScaleTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161A10
			fight::Property* FreezeScaleTrack::GetProperty(int index)
			{
				return gFreezeScaleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10161A30
			void FreezeScaleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFreezeScaleTrackProperties);
			}

			// FUNCTION: ENGINE 0x10161A60
			FreezeScaleTrack::FreezeScaleTrack() : blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-1)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10161AC0
			float FreezeScaleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10161AD0
			float FreezeScaleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10161AE0
			FreezeScaleTrack::~FreezeScaleTrack()
			{
			}

			// FUNCTION: ENGINE 0x10161CE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FreezeScaleTrack::RegisterProperties()
			{
				if (gFreezeScaleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FreezeScaleTrack>("timeBegin", &FreezeScaleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FreezeScaleTrack>("timeEnd", &FreezeScaleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<FreezeScaleTrack>("partition", &FreezeScaleTrack::SetPartition);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<FreezeScaleTrack>("priority", &FreezeScaleTrack::SetPriority);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FreezeScaleTrack>("blendInTime", &FreezeScaleTrack::SetBlendInTime);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FreezeScaleTrack>("blendOutTime", &FreezeScaleTrack::SetBlendOutTime);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gFreezeScaleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10161C30
			fight::TrackFactory* CreateFreezeScaleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FreezeScaleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10161C60
			void RegisterFreezeScaleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FreezeScaleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<FreezeScaleTrack>;
			template class fight::PropertyName<FreezeScaleTrack>;
			template class fight::PropertyIntConstRange<FreezeScaleTrack>;
			template class fight::TrackFactoryTemplate<FreezeScaleTrack>;
			template class fight::TrackFactoryCasterTemplate<FreezeScaleTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10161AF0
// FUNCTION: ENGINE 0x10161B00
// FUNCTION: ENGINE 0x10161B30
// FUNCTION: ENGINE 0x10161B60
// FUNCTION: ENGINE 0x10161B90
// FUNCTION: ENGINE 0x10161BC0
// FUNCTION: ENGINE 0x10161BD0
// FUNCTION: ENGINE 0x10161C00
// FUNCTION: ENGINE 0x10161C20
// FUNCTION: ENGINE 0x10161C90
// FUNCTION: ENGINE 0x10161CC0
// FUNCTION: ENGINE 0x10161EB0
// FUNCTION: ENGINE 0x10161EE0
// FUNCTION: ENGINE 0x10161F00
