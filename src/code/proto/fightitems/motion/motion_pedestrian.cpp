// Fight items of the motion group: NPCAnimationVersionCondition, PedestrianFirstFrameUpgradedCondition, PedestrianStateCondition, PedestrianAngleToTargetCondition, CharacterCloudStateCondition, PedestrianRequestDowngradeCondition, PedestrianLowMoraleCondition, PedestrianAlertStateCondition, SetPedestrianReadyForDowngradeTrack, SpreadPedestrianAlertStateTrack, SetPedestrianAlertStateTrack, SetPedestrianStateTrack, CharacterCloudStateTrack (unit 0x1019C4A0 - 0x1019F890; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_pedestrian.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gNPCAnimationVersionConditionProperties;  // 0x11254904

			// FUNCTION: ENGINE 0x1019C4A0
			bool NPCAnimationVersionCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C4B0
			bool NPCAnimationVersionCondition::SetVersion(int newValue)
			{
				version = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C6F0
			fight::Property* NPCAnimationVersionCondition::GetProperty(int index)
			{
				return gNPCAnimationVersionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019C710
			void NPCAnimationVersionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gNPCAnimationVersionConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019C720
			NPCAnimationVersionCondition::NPCAnimationVersionCondition() : fight::Condition(0), version(1), match(true)
			{
			}

			// FUNCTION: ENGINE 0x1019C750
			NPCAnimationVersionCondition::~NPCAnimationVersionCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019E1B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void NPCAnimationVersionCondition::RegisterProperties()
			{
				if (gNPCAnimationVersionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<NPCAnimationVersionCondition>("match", &NPCAnimationVersionCondition::SetMatch);
					properties[0] = property;
					property = new fight::PropertyIntConstRange<NPCAnimationVersionCondition>("version", &NPCAnimationVersionCondition::SetVersion);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gNPCAnimationVersionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019DF40
			fight::ConditionFactory* CreateNPCAnimationVersionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<NPCAnimationVersionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EE00
			void RegisterNPCAnimationVersionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<NPCAnimationVersionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPedestrianFirstFrameUpgradedConditionProperties;  // 0x11254908

			// FUNCTION: ENGINE 0x1019C4C0
			bool PedestrianFirstFrameUpgradedCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C760
			fight::Property* PedestrianFirstFrameUpgradedCondition::GetProperty(int index)
			{
				return gPedestrianFirstFrameUpgradedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019C780
			void PedestrianFirstFrameUpgradedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPedestrianFirstFrameUpgradedConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019C790
			PedestrianFirstFrameUpgradedCondition::PedestrianFirstFrameUpgradedCondition() : fight::Condition(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x1019C7B0
			PedestrianFirstFrameUpgradedCondition::~PedestrianFirstFrameUpgradedCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019E290
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PedestrianFirstFrameUpgradedCondition::RegisterProperties()
			{
				if (gPedestrianFirstFrameUpgradedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<PedestrianFirstFrameUpgradedCondition>("match", &PedestrianFirstFrameUpgradedCondition::SetMatch);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPedestrianFirstFrameUpgradedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019DF70
			fight::ConditionFactory* CreatePedestrianFirstFrameUpgradedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianFirstFrameUpgradedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EE30
			void RegisterPedestrianFirstFrameUpgradedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianFirstFrameUpgradedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPedestrianStateConditionProperties;  // 0x1125490C

			// FUNCTION: ENGINE 0x1019C4D0
			bool PedestrianStateCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C4E0
			bool PedestrianStateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C7C0
			fight::Property* PedestrianStateCondition::GetProperty(int index)
			{
				return gPedestrianStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019C7E0
			void PedestrianStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPedestrianStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019C7F0
			PedestrianStateCondition::PedestrianStateCondition() : fight::Condition(0), state(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x1019C820
			PedestrianStateCondition::~PedestrianStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019E330
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PedestrianStateCondition::RegisterProperties()
			{
				if (gPedestrianStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<PedestrianStateCondition>("match", &PedestrianStateCondition::SetMatch);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<PedestrianStateCondition>("state", gPedestrianStateConditionStateTable, gPedestrianStateConditionStateCount, &PedestrianStateCondition::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPedestrianStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019DFA0
			fight::ConditionFactory* CreatePedestrianStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EE60
			void RegisterPedestrianStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPedestrianAngleToTargetConditionProperties;  // 0x11254910

			// FUNCTION: ENGINE 0x1019C4F0
			bool PedestrianAngleToTargetCondition::SetCompareTime(int newValue)
			{
				compareTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C500
			bool PedestrianAngleToTargetCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C830
			fight::Property* PedestrianAngleToTargetCondition::GetProperty(int index)
			{
				return gPedestrianAngleToTargetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019C850
			void PedestrianAngleToTargetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPedestrianAngleToTargetConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019C860
			PedestrianAngleToTargetCondition::PedestrianAngleToTargetCondition() : fight::Condition(0), angle(0.0f), compareTime(4)
			{
			}

			// FUNCTION: ENGINE 0x1019C890
			PedestrianAngleToTargetCondition::~PedestrianAngleToTargetCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019E420
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PedestrianAngleToTargetCondition::RegisterProperties()
			{
				if (gPedestrianAngleToTargetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<PedestrianAngleToTargetCondition>("compareTime", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &PedestrianAngleToTargetCondition::SetCompareTime);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PedestrianAngleToTargetCondition>("angle", &PedestrianAngleToTargetCondition::SetAngle);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPedestrianAngleToTargetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019DFD0
			fight::ConditionFactory* CreatePedestrianAngleToTargetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianAngleToTargetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EE90
			void RegisterPedestrianAngleToTargetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianAngleToTargetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gCharacterCloudStateConditionProperties;  // 0x11254914

			// FUNCTION: ENGINE 0x1019C520
			bool CharacterCloudStateCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C530
			bool CharacterCloudStateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C8A0
			fight::Property* CharacterCloudStateCondition::GetProperty(int index)
			{
				return gCharacterCloudStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019C8C0
			void CharacterCloudStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gCharacterCloudStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019C8D0
			CharacterCloudStateCondition::CharacterCloudStateCondition() : fight::Condition(0), state(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x1019C900
			CharacterCloudStateCondition::~CharacterCloudStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019E510
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CharacterCloudStateCondition::RegisterProperties()
			{
				if (gCharacterCloudStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<CharacterCloudStateCondition>("match", &CharacterCloudStateCondition::SetMatch);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<CharacterCloudStateCondition>("state", gCharacterCloudStateConditionStateTable, gCharacterCloudStateConditionStateCount, &CharacterCloudStateCondition::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gCharacterCloudStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E000
			fight::ConditionFactory* CreateCharacterCloudStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CharacterCloudStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EEC0
			void RegisterCharacterCloudStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CharacterCloudStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPedestrianRequestDowngradeConditionProperties;  // 0x11254918

			// FUNCTION: ENGINE 0x1019C540
			bool PedestrianRequestDowngradeCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C910
			fight::Property* PedestrianRequestDowngradeCondition::GetProperty(int index)
			{
				return gPedestrianRequestDowngradeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019C930
			void PedestrianRequestDowngradeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPedestrianRequestDowngradeConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019C940
			PedestrianRequestDowngradeCondition::PedestrianRequestDowngradeCondition() : fight::Condition(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x1019C960
			PedestrianRequestDowngradeCondition::~PedestrianRequestDowngradeCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019E600
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PedestrianRequestDowngradeCondition::RegisterProperties()
			{
				if (gPedestrianRequestDowngradeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<PedestrianRequestDowngradeCondition>("match", &PedestrianRequestDowngradeCondition::SetMatch);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPedestrianRequestDowngradeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E030
			fight::ConditionFactory* CreatePedestrianRequestDowngradeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianRequestDowngradeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EEF0
			void RegisterPedestrianRequestDowngradeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianRequestDowngradeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPedestrianLowMoraleConditionProperties;  // 0x1125491C

			// FUNCTION: ENGINE 0x1019C550
			bool PedestrianLowMoraleCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C970
			fight::Property* PedestrianLowMoraleCondition::GetProperty(int index)
			{
				return gPedestrianLowMoraleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019C990
			void PedestrianLowMoraleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPedestrianLowMoraleConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019C9A0
			PedestrianLowMoraleCondition::PedestrianLowMoraleCondition() : fight::Condition(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x1019C9C0
			PedestrianLowMoraleCondition::~PedestrianLowMoraleCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019E6A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PedestrianLowMoraleCondition::RegisterProperties()
			{
				if (gPedestrianLowMoraleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<PedestrianLowMoraleCondition>("match", &PedestrianLowMoraleCondition::SetMatch);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPedestrianLowMoraleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E060
			fight::ConditionFactory* CreatePedestrianLowMoraleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianLowMoraleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EF20
			void RegisterPedestrianLowMoraleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianLowMoraleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPedestrianAlertStateConditionProperties;  // 0x11254920

			// FUNCTION: ENGINE 0x1019C560
			bool PedestrianAlertStateCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C570
			bool PedestrianAlertStateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C9D0
			fight::Property* PedestrianAlertStateCondition::GetProperty(int index)
			{
				return gPedestrianAlertStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1019C9F0
			void PedestrianAlertStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPedestrianAlertStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x1019CA00
			PedestrianAlertStateCondition::PedestrianAlertStateCondition() : fight::Condition(0), state(-1), match(true)
			{
			}

			// FUNCTION: ENGINE 0x1019CA30
			PedestrianAlertStateCondition::~PedestrianAlertStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x1019E740
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PedestrianAlertStateCondition::RegisterProperties()
			{
				if (gPedestrianAlertStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<PedestrianAlertStateCondition>("match", &PedestrianAlertStateCondition::SetMatch);
					properties[0] = property;
					property = new fight::PropertyBitfieldConstList<PedestrianAlertStateCondition>("state", gPedestrianAlertStateConditionStateTable, gPedestrianAlertStateConditionStateCount, &PedestrianAlertStateCondition::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPedestrianAlertStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E090
			fight::ConditionFactory* CreatePedestrianAlertStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianAlertStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EF50
			void RegisterPedestrianAlertStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PedestrianAlertStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSetPedestrianReadyForDowngradeTrackProperties;  // 0x11254924

			// FUNCTION: ENGINE 0x1019C580
			bool SetPedestrianReadyForDowngradeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C5A0
			bool SetPedestrianReadyForDowngradeTrack::SetReady(bool newValue)
			{
				ready = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019CA40
			fight::Property* SetPedestrianReadyForDowngradeTrack::GetProperty(int index)
			{
				return gSetPedestrianReadyForDowngradeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019CA60
			void SetPedestrianReadyForDowngradeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetPedestrianReadyForDowngradeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019CA70
			SetPedestrianReadyForDowngradeTrack::SetPedestrianReadyForDowngradeTrack() : timeBegin(0.0f), ready(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1019CAA0
			float SetPedestrianReadyForDowngradeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019CAB0
			float SetPedestrianReadyForDowngradeTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1019CAC0
			SetPedestrianReadyForDowngradeTrack::~SetPedestrianReadyForDowngradeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019E830
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetPedestrianReadyForDowngradeTrack::RegisterProperties()
			{
				if (gSetPedestrianReadyForDowngradeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetPedestrianReadyForDowngradeTrack>("timeBegin", &SetPedestrianReadyForDowngradeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<SetPedestrianReadyForDowngradeTrack>("ready", &SetPedestrianReadyForDowngradeTrack::SetReady);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSetPedestrianReadyForDowngradeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E0C0
			fight::TrackFactory* CreateSetPedestrianReadyForDowngradeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPedestrianReadyForDowngradeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EF80
			void RegisterSetPedestrianReadyForDowngradeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPedestrianReadyForDowngradeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSpreadPedestrianAlertStateTrackProperties;  // 0x11254928

			// FUNCTION: ENGINE 0x1019C5B0
			bool SpreadPedestrianAlertStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C5D0
			bool SpreadPedestrianAlertStateTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C5F0
			bool SpreadPedestrianAlertStateTrack::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C600
			bool SpreadPedestrianAlertStateTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C620
			bool SpreadPedestrianAlertStateTrack::SetMaxDistanceFromSource(float newValue)
			{
				maxDistanceFromSource = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C640
			bool SpreadPedestrianAlertStateTrack::SetMaxPasses(int newValue)
			{
				maxPasses = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C650
			bool SpreadPedestrianAlertStateTrack::SetAlertFrequency(int newValue)
			{
				alertFrequency = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019CAD0
			fight::Property* SpreadPedestrianAlertStateTrack::GetProperty(int index)
			{
				return gSpreadPedestrianAlertStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019CAF0
			void SpreadPedestrianAlertStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpreadPedestrianAlertStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019CB00
			SpreadPedestrianAlertStateTrack::SpreadPedestrianAlertStateTrack() : maxDistanceFromSource(3.0f), radius(3.0f), timeBegin(0.0f), timeEnd(-1.0f), alertFrequency(3), maxPasses(1), state(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1019CB70
			float SpreadPedestrianAlertStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019CB80
			float SpreadPedestrianAlertStateTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1019CB90
			SpreadPedestrianAlertStateTrack::~SpreadPedestrianAlertStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019E910
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpreadPedestrianAlertStateTrack::RegisterProperties()
			{
				if (gSpreadPedestrianAlertStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpreadPedestrianAlertStateTrack>("timeBegin", &SpreadPedestrianAlertStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SpreadPedestrianAlertStateTrack>("timeEnd", &SpreadPedestrianAlertStateTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<SpreadPedestrianAlertStateTrack>("state", gPedestrianAlertStateConditionStateTable, gPedestrianAlertStateConditionStateCount, &SpreadPedestrianAlertStateTrack::SetState);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SpreadPedestrianAlertStateTrack>("radius", &SpreadPedestrianAlertStateTrack::SetRadius);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<SpreadPedestrianAlertStateTrack>("maxDistanceFromSource", &SpreadPedestrianAlertStateTrack::SetMaxDistanceFromSource);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<SpreadPedestrianAlertStateTrack>("maxPasses", &SpreadPedestrianAlertStateTrack::SetMaxPasses);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<SpreadPedestrianAlertStateTrack>("alertFrequency", &SpreadPedestrianAlertStateTrack::SetAlertFrequency);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gSpreadPedestrianAlertStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E0F0
			fight::TrackFactory* CreateSpreadPedestrianAlertStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpreadPedestrianAlertStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EFB0
			void RegisterSpreadPedestrianAlertStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpreadPedestrianAlertStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetPedestrianAlertStateTrackProperties;  // 0x1125492C

			// FUNCTION: ENGINE 0x1019C660
			bool SetPedestrianAlertStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C680
			bool SetPedestrianAlertStateTrack::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019CBA0
			fight::Property* SetPedestrianAlertStateTrack::GetProperty(int index)
			{
				return gSetPedestrianAlertStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019CBC0
			void SetPedestrianAlertStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetPedestrianAlertStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019CBD0
			SetPedestrianAlertStateTrack::SetPedestrianAlertStateTrack() : timeBegin(0.0f), state(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1019CC10
			float SetPedestrianAlertStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019CC20
			float SetPedestrianAlertStateTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1019CC30
			SetPedestrianAlertStateTrack::~SetPedestrianAlertStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019EB30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetPedestrianAlertStateTrack::RegisterProperties()
			{
				if (gSetPedestrianAlertStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetPedestrianAlertStateTrack>("timeBegin", &SetPedestrianAlertStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SetPedestrianAlertStateTrack>("state", gPedestrianAlertStateConditionStateTable, gPedestrianAlertStateConditionStateCount, &SetPedestrianAlertStateTrack::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSetPedestrianAlertStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E120
			fight::TrackFactory* CreateSetPedestrianAlertStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPedestrianAlertStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019EFE0
			void RegisterSetPedestrianAlertStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPedestrianAlertStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetPedestrianStateTrackProperties;  // 0x11254930

			// FUNCTION: ENGINE 0x1019C690
			bool SetPedestrianStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C6B0
			bool SetPedestrianStateTrack::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019CC40
			fight::Property* SetPedestrianStateTrack::GetProperty(int index)
			{
				return gSetPedestrianStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019CC60
			void SetPedestrianStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetPedestrianStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019CC70
			SetPedestrianStateTrack::SetPedestrianStateTrack() : timeBegin(0.0f), state(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1019CCB0
			float SetPedestrianStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019CCC0
			float SetPedestrianStateTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1019CCD0
			SetPedestrianStateTrack::~SetPedestrianStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019EC20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetPedestrianStateTrack::RegisterProperties()
			{
				if (gSetPedestrianStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetPedestrianStateTrack>("timeBegin", &SetPedestrianStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SetPedestrianStateTrack>("state", gPedestrianStateConditionStateTable, gPedestrianStateConditionStateCount, &SetPedestrianStateTrack::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSetPedestrianStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E150
			fight::TrackFactory* CreateSetPedestrianStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPedestrianStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019F010
			void RegisterSetPedestrianStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetPedestrianStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCharacterCloudStateTrackProperties;  // 0x11254934

			// FUNCTION: ENGINE 0x1019C6C0
			bool CharacterCloudStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019C6E0
			bool CharacterCloudStateTrack::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019CCE0
			fight::Property* CharacterCloudStateTrack::GetProperty(int index)
			{
				return gCharacterCloudStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019CD00
			void CharacterCloudStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCharacterCloudStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019CD10
			CharacterCloudStateTrack::CharacterCloudStateTrack() : timeBegin(0.0f), state(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1019CD50
			float CharacterCloudStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019CD60
			float CharacterCloudStateTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1019CD70
			CharacterCloudStateTrack::~CharacterCloudStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x1019ED10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CharacterCloudStateTrack::RegisterProperties()
			{
				if (gCharacterCloudStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CharacterCloudStateTrack>("timeBegin", &CharacterCloudStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<CharacterCloudStateTrack>("state", gCharacterCloudStateConditionStateTable, gCharacterCloudStateConditionStateCount, &CharacterCloudStateTrack::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gCharacterCloudStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1019E180
			fight::TrackFactory* CreateCharacterCloudStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CharacterCloudStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1019F040
			void RegisterCharacterCloudStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CharacterCloudStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<NPCAnimationVersionCondition>;
			template class fight::PropertyIntConstRange<NPCAnimationVersionCondition>;
			template class fight::ConditionFactoryTemplate<NPCAnimationVersionCondition>;
			template class fight::ConditionFactoryCasterTemplate<NPCAnimationVersionCondition>;
			template class fight::PropertyBool<PedestrianFirstFrameUpgradedCondition>;
			template class fight::ConditionFactoryTemplate<PedestrianFirstFrameUpgradedCondition>;
			template class fight::ConditionFactoryCasterTemplate<PedestrianFirstFrameUpgradedCondition>;
			template class fight::PropertyBool<PedestrianStateCondition>;
			template class fight::PropertyEnumConstList<PedestrianStateCondition>;
			template class fight::ConditionFactoryTemplate<PedestrianStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<PedestrianStateCondition>;
			template class fight::PropertyEnumConstList<PedestrianAngleToTargetCondition>;
			template class fight::PropertyFloatConstRange<PedestrianAngleToTargetCondition>;
			template class fight::ConditionFactoryTemplate<PedestrianAngleToTargetCondition>;
			template class fight::ConditionFactoryCasterTemplate<PedestrianAngleToTargetCondition>;
			template class fight::PropertyBool<CharacterCloudStateCondition>;
			template class fight::PropertyEnumConstList<CharacterCloudStateCondition>;
			template class fight::ConditionFactoryTemplate<CharacterCloudStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<CharacterCloudStateCondition>;
			template class fight::PropertyBool<PedestrianRequestDowngradeCondition>;
			template class fight::ConditionFactoryTemplate<PedestrianRequestDowngradeCondition>;
			template class fight::ConditionFactoryCasterTemplate<PedestrianRequestDowngradeCondition>;
			template class fight::PropertyBool<PedestrianLowMoraleCondition>;
			template class fight::ConditionFactoryTemplate<PedestrianLowMoraleCondition>;
			template class fight::ConditionFactoryCasterTemplate<PedestrianLowMoraleCondition>;
			template class fight::PropertyBool<PedestrianAlertStateCondition>;
			template class fight::PropertyBitfieldConstList<PedestrianAlertStateCondition>;
			template class fight::ConditionFactoryTemplate<PedestrianAlertStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<PedestrianAlertStateCondition>;
			template class fight::PropertyFloatConstRange<SetPedestrianReadyForDowngradeTrack>;
			template class fight::PropertyBool<SetPedestrianReadyForDowngradeTrack>;
			template class fight::TrackFactoryTemplate<SetPedestrianReadyForDowngradeTrack>;
			template class fight::TrackFactoryCasterTemplate<SetPedestrianReadyForDowngradeTrack>;
			template class fight::PropertyFloatConstRange<SpreadPedestrianAlertStateTrack>;
			template class fight::PropertyEnumConstList<SpreadPedestrianAlertStateTrack>;
			template class fight::PropertyIntConstRange<SpreadPedestrianAlertStateTrack>;
			template class fight::TrackFactoryTemplate<SpreadPedestrianAlertStateTrack>;
			template class fight::TrackFactoryCasterTemplate<SpreadPedestrianAlertStateTrack>;
			template class fight::PropertyFloatConstRange<SetPedestrianAlertStateTrack>;
			template class fight::PropertyEnumConstList<SetPedestrianAlertStateTrack>;
			template class fight::TrackFactoryTemplate<SetPedestrianAlertStateTrack>;
			template class fight::TrackFactoryCasterTemplate<SetPedestrianAlertStateTrack>;
			template class fight::PropertyFloatConstRange<SetPedestrianStateTrack>;
			template class fight::PropertyEnumConstList<SetPedestrianStateTrack>;
			template class fight::TrackFactoryTemplate<SetPedestrianStateTrack>;
			template class fight::TrackFactoryCasterTemplate<SetPedestrianStateTrack>;
			template class fight::PropertyFloatConstRange<CharacterCloudStateTrack>;
			template class fight::PropertyEnumConstList<CharacterCloudStateTrack>;
			template class fight::TrackFactoryTemplate<CharacterCloudStateTrack>;
			template class fight::TrackFactoryCasterTemplate<CharacterCloudStateTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1019CD80
// FUNCTION: ENGINE 0x1019CDB0
// FUNCTION: ENGINE 0x1019CDE0
// FUNCTION: ENGINE 0x1019CE10
// FUNCTION: ENGINE 0x1019CE40
// FUNCTION: ENGINE 0x1019CE70
// FUNCTION: ENGINE 0x1019CEA0
// FUNCTION: ENGINE 0x1019CED0
// FUNCTION: ENGINE 0x1019CF00
// FUNCTION: ENGINE 0x1019CF30
// FUNCTION: ENGINE 0x1019CF60
// FUNCTION: ENGINE 0x1019CF90
// FUNCTION: ENGINE 0x1019CFC0
// FUNCTION: ENGINE 0x1019CFF0
// FUNCTION: ENGINE 0x1019D000
// FUNCTION: ENGINE 0x1019D030
// FUNCTION: ENGINE 0x1019D040
// FUNCTION: ENGINE 0x1019D070
// FUNCTION: ENGINE 0x1019D080
// FUNCTION: ENGINE 0x1019D0B0
// FUNCTION: ENGINE 0x1019D0C0
// FUNCTION: ENGINE 0x1019D0F0
// FUNCTION: ENGINE 0x1019D100
// FUNCTION: ENGINE 0x1019D130
// FUNCTION: ENGINE 0x1019D140
// FUNCTION: ENGINE 0x1019D170
// FUNCTION: ENGINE 0x1019D180
// FUNCTION: ENGINE 0x1019D1B0
// FUNCTION: ENGINE 0x1019D1C0
// FUNCTION: ENGINE 0x1019D1F0
// FUNCTION: ENGINE 0x1019D200
// FUNCTION: ENGINE 0x1019D230
// FUNCTION: ENGINE 0x1019D240
// FUNCTION: ENGINE 0x1019D270
// FUNCTION: ENGINE 0x1019D280
// FUNCTION: ENGINE 0x1019D2B0
// FUNCTION: ENGINE 0x1019D2C0
// FUNCTION: ENGINE 0x1019D2F0
// FUNCTION: ENGINE 0x1019D300
// FUNCTION: ENGINE 0x1019D330
// FUNCTION: ENGINE 0x1019D360
// FUNCTION: ENGINE 0x1019D380
// FUNCTION: ENGINE 0x1019D390
// FUNCTION: ENGINE 0x1019D3C0
// FUNCTION: ENGINE 0x1019D3E0
// FUNCTION: ENGINE 0x1019D3F0
// FUNCTION: ENGINE 0x1019D420
// FUNCTION: ENGINE 0x1019D440
// FUNCTION: ENGINE 0x1019D450
// FUNCTION: ENGINE 0x1019D480
// FUNCTION: ENGINE 0x1019D4A0
// FUNCTION: ENGINE 0x1019D4B0
// FUNCTION: ENGINE 0x1019D4F0
// FUNCTION: ENGINE 0x1019D500
// FUNCTION: ENGINE 0x1019D530
// FUNCTION: ENGINE 0x1019D550
// FUNCTION: ENGINE 0x1019D560
// FUNCTION: ENGINE 0x1019D5A0
// FUNCTION: ENGINE 0x1019D5B0
// FUNCTION: ENGINE 0x1019D5E0
// FUNCTION: ENGINE 0x1019D600
// FUNCTION: ENGINE 0x1019D610
// FUNCTION: ENGINE 0x1019D640
// FUNCTION: ENGINE 0x1019D670
// FUNCTION: ENGINE 0x1019D680
// FUNCTION: ENGINE 0x1019D6B0
// FUNCTION: ENGINE 0x1019D6D0
// FUNCTION: ENGINE 0x1019D6E0
// FUNCTION: ENGINE 0x1019D720
// FUNCTION: ENGINE 0x1019D730
// FUNCTION: ENGINE 0x1019D760
// FUNCTION: ENGINE 0x1019D780
// FUNCTION: ENGINE 0x1019D790
// FUNCTION: ENGINE 0x1019D7C0
// FUNCTION: ENGINE 0x1019D7E0
// FUNCTION: ENGINE 0x1019D7F0
// FUNCTION: ENGINE 0x1019D820
// FUNCTION: ENGINE 0x1019D840
// FUNCTION: ENGINE 0x1019D850
// FUNCTION: ENGINE 0x1019D880
// FUNCTION: ENGINE 0x1019D8A0
// FUNCTION: ENGINE 0x1019D8B0
// FUNCTION: ENGINE 0x1019D8F0
// FUNCTION: ENGINE 0x1019D900
// FUNCTION: ENGINE 0x1019D920
// FUNCTION: ENGINE 0x1019D930
// FUNCTION: ENGINE 0x1019D990
// FUNCTION: ENGINE 0x1019D9C0
// FUNCTION: ENGINE 0x1019D9F0
// FUNCTION: ENGINE 0x1019DA00
// FUNCTION: ENGINE 0x1019DA30
// FUNCTION: ENGINE 0x1019DA50
// FUNCTION: ENGINE 0x1019DA60
// FUNCTION: ENGINE 0x1019DA90
// FUNCTION: ENGINE 0x1019DAC0
// FUNCTION: ENGINE 0x1019DAD0
// FUNCTION: ENGINE 0x1019DB10
// FUNCTION: ENGINE 0x1019DB20
// FUNCTION: ENGINE 0x1019DB50
// FUNCTION: ENGINE 0x1019DB70
// FUNCTION: ENGINE 0x1019DB80
// FUNCTION: ENGINE 0x1019DBB0
// FUNCTION: ENGINE 0x1019DBD0
// FUNCTION: ENGINE 0x1019DBE0
// FUNCTION: ENGINE 0x1019DC10
// FUNCTION: ENGINE 0x1019DC40
// FUNCTION: ENGINE 0x1019DC50
// FUNCTION: ENGINE 0x1019DC90
// FUNCTION: ENGINE 0x1019DCA0
// FUNCTION: ENGINE 0x1019DCD0
// FUNCTION: ENGINE 0x1019DCF0
// FUNCTION: ENGINE 0x1019DD00
// FUNCTION: ENGINE 0x1019DD30
// FUNCTION: ENGINE 0x1019DD60
// FUNCTION: ENGINE 0x1019DD70
// FUNCTION: ENGINE 0x1019DDB0
// FUNCTION: ENGINE 0x1019DDC0
// FUNCTION: ENGINE 0x1019DDF0
// FUNCTION: ENGINE 0x1019DE10
// FUNCTION: ENGINE 0x1019DE20
// FUNCTION: ENGINE 0x1019DE50
// FUNCTION: ENGINE 0x1019DE80
// FUNCTION: ENGINE 0x1019DE90
// FUNCTION: ENGINE 0x1019DED0
// FUNCTION: ENGINE 0x1019DEE0
// FUNCTION: ENGINE 0x1019DF10
// FUNCTION: ENGINE 0x1019DF30
// FUNCTION: ENGINE 0x1019F070
// FUNCTION: ENGINE 0x1019F0A0
// FUNCTION: ENGINE 0x1019F0C0
// FUNCTION: ENGINE 0x1019F0F0
// FUNCTION: ENGINE 0x1019F110
// FUNCTION: ENGINE 0x1019F140
// FUNCTION: ENGINE 0x1019F160
// FUNCTION: ENGINE 0x1019F190
// FUNCTION: ENGINE 0x1019F1B0
// FUNCTION: ENGINE 0x1019F1E0
// FUNCTION: ENGINE 0x1019F200
// FUNCTION: ENGINE 0x1019F230
// FUNCTION: ENGINE 0x1019F250
// FUNCTION: ENGINE 0x1019F280
// FUNCTION: ENGINE 0x1019F2A0
// FUNCTION: ENGINE 0x1019F2D0
// FUNCTION: ENGINE 0x1019F2F0
// FUNCTION: ENGINE 0x1019F320
// FUNCTION: ENGINE 0x1019F340
// FUNCTION: ENGINE 0x1019F370
// FUNCTION: ENGINE 0x1019F390
// FUNCTION: ENGINE 0x1019F3C0
// FUNCTION: ENGINE 0x1019F3E0
// FUNCTION: ENGINE 0x1019F410
// FUNCTION: ENGINE 0x1019F430
// FUNCTION: ENGINE 0x1019F460
// FUNCTION: ENGINE 0x1019F480
// FUNCTION: ENGINE 0x1019F4D0
// FUNCTION: ENGINE 0x1019F520
// FUNCTION: ENGINE 0x1019F570
// FUNCTION: ENGINE 0x1019F5C0
// FUNCTION: ENGINE 0x1019F610
// FUNCTION: ENGINE 0x1019F660
// FUNCTION: ENGINE 0x1019F6B0
// FUNCTION: ENGINE 0x1019F700
// FUNCTION: ENGINE 0x1019F750
// FUNCTION: ENGINE 0x1019F7A0
// FUNCTION: ENGINE 0x1019F7F0
// FUNCTION: ENGINE 0x1019F840
