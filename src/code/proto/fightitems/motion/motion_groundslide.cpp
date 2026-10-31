// Fight items of the motion group: GroundSlideTrack (unit 0x10174CA0 - 0x101753C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_groundslide.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gGroundSlideTrackProperties;  // 0x11254698

			// FUNCTION: ENGINE 0x10174CA0
			bool GroundSlideTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174CC0
			bool GroundSlideTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174CE0
			bool GroundSlideTrack::SetFacing(float newValue)
			{
				facing = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10174D00
			bool GroundSlideTrack::SetDeceleration(float newValue)
			{
				deceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174D20
			bool GroundSlideTrack::SetMinInitVelocity(float newValue)
			{
				minInitVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174D40
			bool GroundSlideTrack::SetMinVelocity(float newValue)
			{
				minVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174D60
			bool GroundSlideTrack::SetMaxVelocity(float newValue)
			{
				maxVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174D80
			bool GroundSlideTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174D90
			bool GroundSlideTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174DB0
			bool GroundSlideTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10174DD0
			fight::Property* GroundSlideTrack::GetProperty(int index)
			{
				return gGroundSlideTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10174DF0
			void GroundSlideTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGroundSlideTrackProperties);
			}

			// FUNCTION: ENGINE 0x10174E00
			GroundSlideTrack::GroundSlideTrack() : blendInTime(0.0f), blendOutTime(0.0f), deceleration(2e+01f), facing(0.0f), maxVelocity(1e+02f), minInitVelocity(0.0f), minVelocity(1e+01f), timeBegin(0.0f), timeEnd(-1.0f), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x10174E90
			float GroundSlideTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10174EA0
			float GroundSlideTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10174EB0
			GroundSlideTrack::~GroundSlideTrack()
			{
			}

			// FUNCTION: ENGINE 0x10175030
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundSlideTrack::RegisterProperties()
			{
				if (gGroundSlideTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("timeBegin", &GroundSlideTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("timeEnd", &GroundSlideTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("facing", &GroundSlideTrack::SetFacing);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("deceleration", &GroundSlideTrack::SetDeceleration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("minInitVelocity", &GroundSlideTrack::SetMinInitVelocity);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("minVelocity", &GroundSlideTrack::SetMinVelocity);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("maxVelocity", &GroundSlideTrack::SetMaxVelocity);
					properties[6] = property;
					property = new fight::PropertyIntConstRange<GroundSlideTrack>("priority", &GroundSlideTrack::SetPriority);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("blendInTime", &GroundSlideTrack::SetBlendInTime);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<GroundSlideTrack>("blendOutTime", &GroundSlideTrack::SetBlendOutTime);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gGroundSlideTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10175000
			fight::TrackFactory* CreateGroundSlideTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSlideTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101752F0
			void RegisterGroundSlideTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSlideTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<GroundSlideTrack>;
			template class fight::PropertyIntConstRange<GroundSlideTrack>;
			template class fight::TrackFactoryTemplate<GroundSlideTrack>;
			template class fight::TrackFactoryCasterTemplate<GroundSlideTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10174EC0
// FUNCTION: ENGINE 0x10174EF0
// FUNCTION: ENGINE 0x10174F00
// FUNCTION: ENGINE 0x10174F30
// FUNCTION: ENGINE 0x10174F60
// FUNCTION: ENGINE 0x10174F90
// FUNCTION: ENGINE 0x10174FA0
// FUNCTION: ENGINE 0x10174FD0
// FUNCTION: ENGINE 0x10174FF0
// FUNCTION: ENGINE 0x10175320
// FUNCTION: ENGINE 0x10175350
// FUNCTION: ENGINE 0x10175370
