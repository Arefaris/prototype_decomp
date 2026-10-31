// Fight items of the playback group: SuckIntoPlayerTrack (unit 0x102573D0 - 0x1025BC30; no assert path, the file name is a guess).
#include "code/proto/fightitems/playback/playback_suckintoplayer.h"

namespace proto
{
	namespace fightitems
	{
		namespace playback
		{
			fight::Property** gSuckIntoPlayerTrackProperties;  // 0x11255CEC

			// FUNCTION: ENGINE 0x1025B4B0
			bool SuckIntoPlayerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B4D0
			bool SuckIntoPlayerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B4F0
			bool SuckIntoPlayerTrack::SetInitialVelocity(float newValue)
			{
				initialVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B510
			bool SuckIntoPlayerTrack::SetMaxVelocity(float newValue)
			{
				maxVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B530
			bool SuckIntoPlayerTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B550
			bool SuckIntoPlayerTrack::SetFadeDistStart(float newValue)
			{
				fadeDistStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B570
			bool SuckIntoPlayerTrack::SetScaleDistStart(float newValue)
			{
				scaleDistStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B590
			bool SuckIntoPlayerTrack::SetScaleEnd(float newValue)
			{
				scaleEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B5B0
			bool SuckIntoPlayerTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1025B5D0
			fight::BranchHolder* SuckIntoPlayerTrack::SetWhenFinished()
			{
				return &whenFinished;
			}

			// FUNCTION: ENGINE 0x1025B5E0
			fight::Property* SuckIntoPlayerTrack::GetProperty(int index)
			{
				return gSuckIntoPlayerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1025B600
			void SuckIntoPlayerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSuckIntoPlayerTrackProperties);
			}

			// FUNCTION: ENGINE 0x1025B610
			SuckIntoPlayerTrack::SuckIntoPlayerTrack() : whenFinished("Motion"), offset(0.0f, 0.0f, 0.0f), acceleration(1e+01f), fadeDistStart(1.0f), initialVelocity(0.0f), maxVelocity(-1.0f), scaleDistStart(1.0f), scaleEnd(1.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1025B6A0
			float SuckIntoPlayerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1025B6B0
			float SuckIntoPlayerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1025B6C0
			SuckIntoPlayerTrack::~SuckIntoPlayerTrack()
			{
			}

			// FUNCTION: ENGINE 0x1025B8A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SuckIntoPlayerTrack::RegisterProperties()
			{
				if (gSuckIntoPlayerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SuckIntoPlayerTrack>("timeBegin", &SuckIntoPlayerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SuckIntoPlayerTrack>("timeEnd", &SuckIntoPlayerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SuckIntoPlayerTrack>("initialVelocity", &SuckIntoPlayerTrack::SetInitialVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SuckIntoPlayerTrack>("maxVelocity", &SuckIntoPlayerTrack::SetMaxVelocity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<SuckIntoPlayerTrack>("acceleration", &SuckIntoPlayerTrack::SetAcceleration);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<SuckIntoPlayerTrack>("fadeDistStart", &SuckIntoPlayerTrack::SetFadeDistStart);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<SuckIntoPlayerTrack>("scaleDistStart", &SuckIntoPlayerTrack::SetScaleDistStart);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<SuckIntoPlayerTrack>("scaleEnd", &SuckIntoPlayerTrack::SetScaleEnd);
					properties[7] = property;
					property = new fight::PropertyVector<SuckIntoPlayerTrack>("offset", &SuckIntoPlayerTrack::SetOffset);
					properties[8] = property;
					property = new fight::PropertyBranch<SuckIntoPlayerTrack>("whenFinished", &SuckIntoPlayerTrack::SetWhenFinished);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gSuckIntoPlayerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1025B870
			fight::TrackFactory* CreateSuckIntoPlayerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SuckIntoPlayerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1025BB60
			void RegisterSuckIntoPlayerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SuckIntoPlayerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<SuckIntoPlayerTrack>;
			template class fight::PropertyVector<SuckIntoPlayerTrack>;
			template class fight::PropertyBranch<SuckIntoPlayerTrack>;
			template class fight::TrackFactoryTemplate<SuckIntoPlayerTrack>;
			template class fight::TrackFactoryCasterTemplate<SuckIntoPlayerTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1025B6E0
// FUNCTION: ENGINE 0x1025B710
// FUNCTION: ENGINE 0x1025B720
// FUNCTION: ENGINE 0x1025B750
// FUNCTION: ENGINE 0x1025B780
// FUNCTION: ENGINE 0x1025B7B0
// FUNCTION: ENGINE 0x1025B7C0
// FUNCTION: ENGINE 0x1025B7F0
// FUNCTION: ENGINE 0x1025B810
// FUNCTION: ENGINE 0x1025B820
// FUNCTION: ENGINE 0x1025B850
// FUNCTION: ENGINE 0x1025BB90
// FUNCTION: ENGINE 0x1025BBC0
// FUNCTION: ENGINE 0x1025BBE0
