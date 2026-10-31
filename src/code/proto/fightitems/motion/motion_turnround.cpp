// Fight items of the motion group: TurnRoundTrack (unit 0x101C2D60 - 0x101C3390; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_turnround.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gTurnRoundTrackProperties;  // 0x11254BF8

			// FUNCTION: ENGINE 0x101C2D60
			bool TurnRoundTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C2D80
			bool TurnRoundTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C2DA0
			bool TurnRoundTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101C2DC0
			bool TurnRoundTrack::SetIncludeAutoTarget(bool newValue)
			{
				includeAutoTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C2DD0
			bool TurnRoundTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C2DE0
			bool TurnRoundTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C2E00
			bool TurnRoundTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C2E20
			fight::Property* TurnRoundTrack::GetProperty(int index)
			{
				return gTurnRoundTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C2E40
			void TurnRoundTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTurnRoundTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C2E50
			TurnRoundTrack::TurnRoundTrack() : blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.0f), priority(-5), includeAutoTarget(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C2EB0
			float TurnRoundTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C2EC0
			float TurnRoundTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101C2ED0
			TurnRoundTrack::~TurnRoundTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C30B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TurnRoundTrack::RegisterProperties()
			{
				if (gTurnRoundTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TurnRoundTrack>("timeBegin", &TurnRoundTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TurnRoundTrack>("timeEnd", &TurnRoundTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TurnRoundTrack>("turningVelocity", &TurnRoundTrack::SetTurningVelocity);
					properties[2] = property;
					property = new fight::PropertyBool<TurnRoundTrack>("includeAutoTarget", &TurnRoundTrack::SetIncludeAutoTarget);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<TurnRoundTrack>("priority", &TurnRoundTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TurnRoundTrack>("blendInTime", &TurnRoundTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TurnRoundTrack>("blendOutTime", &TurnRoundTrack::SetBlendOutTime);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gTurnRoundTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C3080
			fight::TrackFactory* CreateTurnRoundTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TurnRoundTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C32C0
			void RegisterTurnRoundTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TurnRoundTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<TurnRoundTrack>;
			template class fight::PropertyBool<TurnRoundTrack>;
			template class fight::PropertyIntConstRange<TurnRoundTrack>;
			template class fight::TrackFactoryTemplate<TurnRoundTrack>;
			template class fight::TrackFactoryCasterTemplate<TurnRoundTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101C2EE0
// FUNCTION: ENGINE 0x101C2F10
// FUNCTION: ENGINE 0x101C2F20
// FUNCTION: ENGINE 0x101C2F50
// FUNCTION: ENGINE 0x101C2F80
// FUNCTION: ENGINE 0x101C2FB0
// FUNCTION: ENGINE 0x101C2FC0
// FUNCTION: ENGINE 0x101C2FF0
// FUNCTION: ENGINE 0x101C3010
// FUNCTION: ENGINE 0x101C3020
// FUNCTION: ENGINE 0x101C3050
// FUNCTION: ENGINE 0x101C3070
// FUNCTION: ENGINE 0x101C32F0
// FUNCTION: ENGINE 0x101C3320
// FUNCTION: ENGINE 0x101C3340
