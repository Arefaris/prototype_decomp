// Fight items of the motion group: SpecialistDodgeTrack (unit 0x101B5700 - 0x101B5FB0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_specialistdodge.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gSpecialistDodgeTrackProperties;  // 0x11254AF0

			// FUNCTION: ENGINE 0x101B5700
			bool SpecialistDodgeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B5720
			bool SpecialistDodgeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B5740
			bool SpecialistDodgeTrack::SetMoveBegin(float newValue)
			{
				moveBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B5760
			bool SpecialistDodgeTrack::SetMoveEnd(float newValue)
			{
				moveEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B5780
			bool SpecialistDodgeTrack::SetMoveDistance(float newValue)
			{
				moveDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B57A0
			bool SpecialistDodgeTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B57B0
			bool SpecialistDodgeTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B57D0
			bool SpecialistDodgeTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B57F0
			bool SpecialistDodgeTrack::SetDistanceToAttractorWeight(float newValue)
			{
				distanceToAttractorWeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B5810
			bool SpecialistDodgeTrack::SetMaxDistanceToAttractor(float newValue)
			{
				maxDistanceToAttractor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B5830
			fight::TrackGroup* SpecialistDodgeTrack::GetLeftAnim()
			{
				return &leftAnim;
			}

			// FUNCTION: ENGINE 0x101B5840
			fight::TrackGroup* SpecialistDodgeTrack::GetRightAnim()
			{
				return &rightAnim;
			}

			// FUNCTION: ENGINE 0x101B5850
			fight::TrackGroup* SpecialistDodgeTrack::GetBackAnim()
			{
				return &backAnim;
			}

			// FUNCTION: ENGINE 0x101B5860
			fight::Property* SpecialistDodgeTrack::GetProperty(int index)
			{
				return gSpecialistDodgeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B5880
			void SpecialistDodgeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpecialistDodgeTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B5890
			SpecialistDodgeTrack::SpecialistDodgeTrack() : blendInTime(0.0f), blendOutTime(0.0f), distanceToAttractorWeight(1e+01f), maxDistanceToAttractor(5e+01f), moveBegin(0.0f), moveDistance(0.0f), moveEnd(1.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-1)
			{
			}

			// FUNCTION: ENGINE 0x101B5940
			float SpecialistDodgeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B5950
			float SpecialistDodgeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B5960
			SpecialistDodgeTrack::~SpecialistDodgeTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B5B60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpecialistDodgeTrack::RegisterProperties()
			{
				if (gSpecialistDodgeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("timeBegin", &SpecialistDodgeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("timeEnd", &SpecialistDodgeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("moveBegin", &SpecialistDodgeTrack::SetMoveBegin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("moveEnd", &SpecialistDodgeTrack::SetMoveEnd);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("moveDistance", &SpecialistDodgeTrack::SetMoveDistance);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<SpecialistDodgeTrack>("priority", &SpecialistDodgeTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("blendInTime", &SpecialistDodgeTrack::SetBlendInTime);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("blendOutTime", &SpecialistDodgeTrack::SetBlendOutTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("distanceToAttractorWeight", &SpecialistDodgeTrack::SetDistanceToAttractorWeight);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<SpecialistDodgeTrack>("maxDistanceToAttractor", &SpecialistDodgeTrack::SetMaxDistanceToAttractor);
					properties[9] = property;
					property = new fight::PropertyTrackGroup<SpecialistDodgeTrack>("leftAnim", &SpecialistDodgeTrack::GetLeftAnim);
					properties[10] = property;
					property = new fight::PropertyTrackGroup<SpecialistDodgeTrack>("rightAnim", &SpecialistDodgeTrack::GetRightAnim);
					properties[11] = property;
					property = new fight::PropertyTrackGroup<SpecialistDodgeTrack>("backAnim", &SpecialistDodgeTrack::GetBackAnim);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gSpecialistDodgeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B5B30
			fight::TrackFactory* CreateSpecialistDodgeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpecialistDodgeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B5EE0
			void RegisterSpecialistDodgeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpecialistDodgeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<SpecialistDodgeTrack>;
			template class fight::PropertyIntConstRange<SpecialistDodgeTrack>;
			template class fight::PropertyTrackGroup<SpecialistDodgeTrack>;
			template class fight::TrackFactoryTemplate<SpecialistDodgeTrack>;
			template class fight::TrackFactoryCasterTemplate<SpecialistDodgeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101B59A0
// FUNCTION: ENGINE 0x101B59D0
// FUNCTION: ENGINE 0x101B59E0
// FUNCTION: ENGINE 0x101B5A10
// FUNCTION: ENGINE 0x101B5A40
// FUNCTION: ENGINE 0x101B5A70
// FUNCTION: ENGINE 0x101B5A80
// FUNCTION: ENGINE 0x101B5AB0
// FUNCTION: ENGINE 0x101B5AD0
// FUNCTION: ENGINE 0x101B5AE0
// FUNCTION: ENGINE 0x101B5B10
// FUNCTION: ENGINE 0x101B5F10
// FUNCTION: ENGINE 0x101B5F40
// FUNCTION: ENGINE 0x101B5F60
