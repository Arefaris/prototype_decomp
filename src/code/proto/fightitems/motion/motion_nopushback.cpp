// Fight items of the motion group: NoPushbackTrack (unit 0x101939C0 - 0x10193D60; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_nopushback.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gNoPushbackTrackProperties;  // 0x11254838

			// FUNCTION: ENGINE 0x101939C0
			bool NoPushbackTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101939E0
			bool NoPushbackTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193A00
			fight::Property* NoPushbackTrack::GetProperty(int index)
			{
				return gNoPushbackTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10193A20
			void NoPushbackTrack::ClearProperties()
			{
				fight::FreePropertyList(&gNoPushbackTrackProperties);
			}

			// FUNCTION: ENGINE 0x10193A30
			NoPushbackTrack::NoPushbackTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10193A70
			float NoPushbackTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10193A80
			float NoPushbackTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10193A90
			NoPushbackTrack::~NoPushbackTrack()
			{
			}

			// FUNCTION: ENGINE 0x10193BB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void NoPushbackTrack::RegisterProperties()
			{
				if (gNoPushbackTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<NoPushbackTrack>("timeBegin", &NoPushbackTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<NoPushbackTrack>("timeEnd", &NoPushbackTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gNoPushbackTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10193B80
			fight::TrackFactory* CreateNoPushbackTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<NoPushbackTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10193C90
			void RegisterNoPushbackTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<NoPushbackTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<NoPushbackTrack>;
			template class fight::TrackFactoryTemplate<NoPushbackTrack>;
			template class fight::TrackFactoryCasterTemplate<NoPushbackTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10193AA0
// FUNCTION: ENGINE 0x10193AD0
// FUNCTION: ENGINE 0x10193AE0
// FUNCTION: ENGINE 0x10193B10
// FUNCTION: ENGINE 0x10193B40
// FUNCTION: ENGINE 0x10193B70
// FUNCTION: ENGINE 0x10193CC0
// FUNCTION: ENGINE 0x10193CF0
// FUNCTION: ENGINE 0x10193D10
