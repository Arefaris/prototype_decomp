// Fight items of the motion group: MoveAtVelocityTrack (unit 0x10192C50 - 0x10193360; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_moveatvelocity.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gMoveAtVelocityTrackProperties;  // 0x11254830

			// FUNCTION: ENGINE 0x10192C50
			bool MoveAtVelocityTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192C70
			bool MoveAtVelocityTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192C90
			bool MoveAtVelocityTrack::SetVelocityBegin(const math::Vector& newValue)
			{
				velocityBegin.x = newValue.x;
				velocityBegin.y = newValue.y;
				velocityBegin.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10192CB0
			bool MoveAtVelocityTrack::SetVelocityEnd(const math::Vector& newValue)
			{
				velocityEnd.x = newValue.x;
				velocityEnd.y = newValue.y;
				velocityEnd.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10192CD0
			bool MoveAtVelocityTrack::SetUseInput(bool newValue)
			{
				useInput = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192CE0
			bool MoveAtVelocityTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192CF0
			bool MoveAtVelocityTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192D10
			bool MoveAtVelocityTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10192D30
			fight::Property* MoveAtVelocityTrack::GetProperty(int index)
			{
				return gMoveAtVelocityTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10192D50
			void MoveAtVelocityTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMoveAtVelocityTrackProperties);
			}

			// FUNCTION: ENGINE 0x10192D60
			MoveAtVelocityTrack::MoveAtVelocityTrack() : velocityBegin(0.0f, 0.0f, 0.0f), velocityEnd(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(1.0f), priority(-5), useInput(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10192DE0
			float MoveAtVelocityTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10192DF0
			float MoveAtVelocityTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10192E00
			MoveAtVelocityTrack::~MoveAtVelocityTrack()
			{
			}

			// FUNCTION: ENGINE 0x10193040
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MoveAtVelocityTrack::RegisterProperties()
			{
				if (gMoveAtVelocityTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MoveAtVelocityTrack>("timeBegin", &MoveAtVelocityTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MoveAtVelocityTrack>("timeEnd", &MoveAtVelocityTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<MoveAtVelocityTrack>("velocityBegin", &MoveAtVelocityTrack::SetVelocityBegin);
					properties[2] = property;
					property = new fight::PropertyVector<MoveAtVelocityTrack>("velocityEnd", &MoveAtVelocityTrack::SetVelocityEnd);
					properties[3] = property;
					property = new fight::PropertyBool<MoveAtVelocityTrack>("useInput", &MoveAtVelocityTrack::SetUseInput);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<MoveAtVelocityTrack>("priority", &MoveAtVelocityTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<MoveAtVelocityTrack>("blendInTime", &MoveAtVelocityTrack::SetBlendInTime);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<MoveAtVelocityTrack>("blendOutTime", &MoveAtVelocityTrack::SetBlendOutTime);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gMoveAtVelocityTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10193010
			fight::TrackFactory* CreateMoveAtVelocityTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MoveAtVelocityTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10193290
			void RegisterMoveAtVelocityTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MoveAtVelocityTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<MoveAtVelocityTrack>;
			template class fight::PropertyVector<MoveAtVelocityTrack>;
			template class fight::PropertyBool<MoveAtVelocityTrack>;
			template class fight::PropertyIntConstRange<MoveAtVelocityTrack>;
			template class fight::TrackFactoryTemplate<MoveAtVelocityTrack>;
			template class fight::TrackFactoryCasterTemplate<MoveAtVelocityTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10192E10
// FUNCTION: ENGINE 0x10192E40
// FUNCTION: ENGINE 0x10192E50
// FUNCTION: ENGINE 0x10192E80
// FUNCTION: ENGINE 0x10192EB0
// FUNCTION: ENGINE 0x10192EE0
// FUNCTION: ENGINE 0x10192EF0
// FUNCTION: ENGINE 0x10192F20
// FUNCTION: ENGINE 0x10192F40
// FUNCTION: ENGINE 0x10192F50
// FUNCTION: ENGINE 0x10192F80
// FUNCTION: ENGINE 0x10192FA0
// FUNCTION: ENGINE 0x10192FB0
// FUNCTION: ENGINE 0x10192FE0
// FUNCTION: ENGINE 0x10193000
// FUNCTION: ENGINE 0x101932C0
// FUNCTION: ENGINE 0x101932F0
// FUNCTION: ENGINE 0x10193310
