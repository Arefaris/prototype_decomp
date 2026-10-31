// Fight items of the motion group: SlaveTransformTrack (unit 0x101B3470 - 0x101B3980; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_slavetransform.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gSlaveTransformTrackProperties;  // 0x11254AD8

			// FUNCTION: ENGINE 0x101B3470
			bool SlaveTransformTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B3490
			bool SlaveTransformTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B3500
			bool SlaveTransformTrack::SetMasterObject(const fight::Name& newValue)
			{
				masterObject = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B34B0
			bool SlaveTransformTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101B34D0
			fight::Property* SlaveTransformTrack::GetProperty(int index)
			{
				return gSlaveTransformTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B34F0
			void SlaveTransformTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSlaveTransformTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B3520
			SlaveTransformTrack::SlaveTransformTrack() : offset(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x101B3570
			float SlaveTransformTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B3580
			float SlaveTransformTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B3590
			SlaveTransformTrack::~SlaveTransformTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B3790
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SlaveTransformTrack::RegisterProperties()
			{
				if (gSlaveTransformTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SlaveTransformTrack>("timeBegin", &SlaveTransformTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SlaveTransformTrack>("timeEnd", &SlaveTransformTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<SlaveTransformTrack>("masterObject", &SlaveTransformTrack::SetMasterObject);
					properties[2] = property;
					property = new fight::PropertyVector<SlaveTransformTrack>("offset", &SlaveTransformTrack::SetOffset);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gSlaveTransformTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B36E0
			fight::TrackFactory* CreateSlaveTransformTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SlaveTransformTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B3710
			void RegisterSlaveTransformTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SlaveTransformTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<SlaveTransformTrack>;
			template class fight::PropertyName<SlaveTransformTrack>;
			template class fight::PropertyVector<SlaveTransformTrack>;
			template class fight::TrackFactoryTemplate<SlaveTransformTrack>;
			template class fight::TrackFactoryCasterTemplate<SlaveTransformTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101B35A0
// FUNCTION: ENGINE 0x101B35B0
// FUNCTION: ENGINE 0x101B35E0
// FUNCTION: ENGINE 0x101B3610
// FUNCTION: ENGINE 0x101B3640
// FUNCTION: ENGINE 0x101B3670
// FUNCTION: ENGINE 0x101B3680
// FUNCTION: ENGINE 0x101B36B0
// FUNCTION: ENGINE 0x101B36D0
// FUNCTION: ENGINE 0x101B3740
// FUNCTION: ENGINE 0x101B3770
// FUNCTION: ENGINE 0x101B38E0
// FUNCTION: ENGINE 0x101B3910
// FUNCTION: ENGINE 0x101B3930
