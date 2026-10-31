// Fight items of the motion group: MoveChargedTrack (unit 0x10193360 - 0x101939C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_movecharged.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gMoveChargedTrackProperties;  // 0x11254834

			// FUNCTION: ENGINE 0x10193360
			bool MoveChargedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193380
			bool MoveChargedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101933A0
			bool MoveChargedTrack::SetDistanceMin(const math::Vector& newValue)
			{
				distanceMin.x = newValue.x;
				distanceMin.y = newValue.y;
				distanceMin.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101933C0
			bool MoveChargedTrack::SetDistanceMax(const math::Vector& newValue)
			{
				distanceMax.x = newValue.x;
				distanceMax.y = newValue.y;
				distanceMax.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101933E0
			bool MoveChargedTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101933F0
			bool MoveChargedTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193410
			bool MoveChargedTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10193430
			fight::Property* MoveChargedTrack::GetProperty(int index)
			{
				return gMoveChargedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10193450
			void MoveChargedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gMoveChargedTrackProperties);
			}

			// FUNCTION: ENGINE 0x10193460
			MoveChargedTrack::MoveChargedTrack() : distanceMax(0.0f, 0.0f, 0.0f), distanceMin(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(1.0f), priority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101934E0
			float MoveChargedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101934F0
			float MoveChargedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10193500
			MoveChargedTrack::~MoveChargedTrack()
			{
			}

			// FUNCTION: ENGINE 0x101936E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MoveChargedTrack::RegisterProperties()
			{
				if (gMoveChargedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<MoveChargedTrack>("timeBegin", &MoveChargedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<MoveChargedTrack>("timeEnd", &MoveChargedTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<MoveChargedTrack>("distanceMin", &MoveChargedTrack::SetDistanceMin);
					properties[2] = property;
					property = new fight::PropertyVector<MoveChargedTrack>("distanceMax", &MoveChargedTrack::SetDistanceMax);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<MoveChargedTrack>("priority", &MoveChargedTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<MoveChargedTrack>("blendInTime", &MoveChargedTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<MoveChargedTrack>("blendOutTime", &MoveChargedTrack::SetBlendOutTime);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gMoveChargedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101936B0
			fight::TrackFactory* CreateMoveChargedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<MoveChargedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101938F0
			void RegisterMoveChargedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<MoveChargedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<MoveChargedTrack>;
			template class fight::PropertyVector<MoveChargedTrack>;
			template class fight::PropertyIntConstRange<MoveChargedTrack>;
			template class fight::TrackFactoryTemplate<MoveChargedTrack>;
			template class fight::TrackFactoryCasterTemplate<MoveChargedTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10193510
// FUNCTION: ENGINE 0x10193540
// FUNCTION: ENGINE 0x10193550
// FUNCTION: ENGINE 0x10193580
// FUNCTION: ENGINE 0x101935B0
// FUNCTION: ENGINE 0x101935E0
// FUNCTION: ENGINE 0x101935F0
// FUNCTION: ENGINE 0x10193620
// FUNCTION: ENGINE 0x10193640
// FUNCTION: ENGINE 0x10193650
// FUNCTION: ENGINE 0x10193680
// FUNCTION: ENGINE 0x101936A0
// FUNCTION: ENGINE 0x10193920
// FUNCTION: ENGINE 0x10193950
// FUNCTION: ENGINE 0x10193970
