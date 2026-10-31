// Fight items of the scenario group: TransformationDescriptionNameCondition, AlertStatusCondition, InMissionCondition, IsPlayerCharacterCondition, TriggerVolumeEventCondition, MissionCondition (unit 0x101DBA70 - 0x101DD720; no assert path, the file name is a guess).
#include "code/proto/fightitems/scenario/scenario_conditions.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			fight::Property** gTransformationDescriptionNameConditionProperties;  // 0x11254DE0

			// FUNCTION: ENGINE 0x101DBA70
			bool TransformationDescriptionNameCondition::SetAffiliate(int newValue)
			{
				affiliate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DC1A0
			bool TransformationDescriptionNameCondition::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DBA80
			bool TransformationDescriptionNameCondition::SetIsActive(bool newValue)
			{
				isActive = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DBAF0
			fight::Property* TransformationDescriptionNameCondition::GetProperty(int index)
			{
				return gTransformationDescriptionNameConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101DBB10
			void TransformationDescriptionNameCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTransformationDescriptionNameConditionProperties);
			}

			// FUNCTION: ENGINE 0x101DC1C0
			TransformationDescriptionNameCondition::TransformationDescriptionNameCondition() : fight::Condition(0), affiliate(0), isActive(true)
			{
			}

			// FUNCTION: ENGINE 0x101DC1F0
			TransformationDescriptionNameCondition::~TransformationDescriptionNameCondition()
			{
			}

			// FUNCTION: ENGINE 0x101DD420
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TransformationDescriptionNameCondition::RegisterProperties()
			{
				if (gTransformationDescriptionNameConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumListObject<TransformationDescriptionNameCondition>("affiliate", &engine::scenario::gAffiliateLister, &TransformationDescriptionNameCondition::SetAffiliate);
					properties[0] = property;
					property = new fight::PropertyName<TransformationDescriptionNameCondition>("name", &TransformationDescriptionNameCondition::SetName);
					properties[1] = property;
					property = new fight::PropertyBool<TransformationDescriptionNameCondition>("isActive", &TransformationDescriptionNameCondition::SetIsActive);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gTransformationDescriptionNameConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DC9D0
			fight::ConditionFactory* CreateTransformationDescriptionNameConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationDescriptionNameCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DD170
			void RegisterTransformationDescriptionNameConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TransformationDescriptionNameCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAlertStatusConditionProperties;  // 0x11254DE4

			// FUNCTION: ENGINE 0x101DBA90
			bool AlertStatusCondition::SetAffiliate(int newValue)
			{
				affiliate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DBAA0
			bool AlertStatusCondition::SetAlert(bool newValue)
			{
				alert = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DBB20
			fight::Property* AlertStatusCondition::GetProperty(int index)
			{
				return gAlertStatusConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101DBB40
			void AlertStatusCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAlertStatusConditionProperties);
			}

			// FUNCTION: ENGINE 0x101DBB50
			AlertStatusCondition::AlertStatusCondition() : fight::Condition(0), affiliate(0), alert(true)
			{
			}

			// FUNCTION: ENGINE 0x101DBB80
			AlertStatusCondition::~AlertStatusCondition()
			{
			}

			// FUNCTION: ENGINE 0x101DCAF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AlertStatusCondition::RegisterProperties()
			{
				if (gAlertStatusConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumListObject<AlertStatusCondition>("affiliate", &engine::scenario::gAffiliateLister, &AlertStatusCondition::SetAffiliate);
					properties[0] = property;
					property = new fight::PropertyBool<AlertStatusCondition>("alert", &AlertStatusCondition::SetAlert);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gAlertStatusConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DCA00
			fight::ConditionFactory* CreateAlertStatusConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AlertStatusCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DD1A0
			void RegisterAlertStatusConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AlertStatusCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gInMissionConditionProperties;  // 0x11254DE8

			// FUNCTION: ENGINE 0x101DBBF0
			fight::Property* InMissionCondition::GetProperty(int index)
			{
				return gInMissionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101DBC10
			void InMissionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInMissionConditionProperties);
			}

			// FUNCTION: ENGINE 0x101DBC20
			InMissionCondition::InMissionCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101DBC40
			InMissionCondition::~InMissionCondition()
			{
			}

			// FUNCTION: ENGINE 0x101DBB90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InMissionCondition::RegisterProperties()
			{
				if (gInMissionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gInMissionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DCA30
			fight::ConditionFactory* CreateInMissionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InMissionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DD1D0
			void RegisterInMissionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InMissionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gIsPlayerCharacterConditionProperties;  // 0x11254DEC

			// FUNCTION: ENGINE 0x101DBAB0
			bool IsPlayerCharacterCondition::SetAffiliate(int newValue)
			{
				affiliate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DBC50
			fight::Property* IsPlayerCharacterCondition::GetProperty(int index)
			{
				return gIsPlayerCharacterConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101DBC70
			void IsPlayerCharacterCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsPlayerCharacterConditionProperties);
			}

			// FUNCTION: ENGINE 0x101DBC80
			IsPlayerCharacterCondition::IsPlayerCharacterCondition() : fight::Condition(0), affiliate(0)
			{
			}

			// FUNCTION: ENGINE 0x101DBCB0
			IsPlayerCharacterCondition::~IsPlayerCharacterCondition()
			{
			}

			// FUNCTION: ENGINE 0x101DCBD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsPlayerCharacterCondition::RegisterProperties()
			{
				if (gIsPlayerCharacterConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumListObject<IsPlayerCharacterCondition>("affiliate", &engine::scenario::gAffiliateLister, &IsPlayerCharacterCondition::SetAffiliate);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gIsPlayerCharacterConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DCA60
			fight::ConditionFactory* CreateIsPlayerCharacterConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsPlayerCharacterCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DD200
			void RegisterIsPlayerCharacterConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsPlayerCharacterCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTriggerVolumeEventConditionProperties;  // 0x11254DF0

			// FUNCTION: ENGINE 0x101DBAC0
			bool TriggerVolumeEventCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DBEF0
			bool TriggerVolumeEventCondition::SetTriggerVolumeName(const char* newValue)
			{
				triggerVolumeName = fight::ReplaceString(triggerVolumeName, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DC2C0
			bool TriggerVolumeEventCondition::SetTriggerVolumeAttributesTags(bool newValue)
			{
				triggerVolumeAttributesTags = newValue;
				ApplyGroup(0, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DBF20
			bool TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerAttributeKey1(const char* newValue)
			{
				triggerVolumeAttributesTagsTriggerAttributeKey1 = fight::ReplaceString(triggerVolumeAttributesTagsTriggerAttributeKey1, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DBF50
			bool TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerAttributeValue1(const char* newValue)
			{
				triggerVolumeAttributesTagsTriggerAttributeValue1 = fight::ReplaceString(triggerVolumeAttributesTagsTriggerAttributeValue1, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DBF80
			bool TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerAttributeKey2(const char* newValue)
			{
				triggerVolumeAttributesTagsTriggerAttributeKey2 = fight::ReplaceString(triggerVolumeAttributesTagsTriggerAttributeKey2, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DBFB0
			bool TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerAttributeValue2(const char* newValue)
			{
				triggerVolumeAttributesTagsTriggerAttributeValue2 = fight::ReplaceString(triggerVolumeAttributesTagsTriggerAttributeValue2, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DBFE0
			bool TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerTagList(const char* newValue)
			{
				triggerVolumeAttributesTagsTriggerTagList = fight::ReplaceString(triggerVolumeAttributesTagsTriggerTagList, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DC010
			bool TriggerVolumeEventCondition::SetTouchName(const char* newValue)
			{
				touchName = fight::ReplaceString(touchName, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DC2E0
			bool TriggerVolumeEventCondition::SetTouchAttributesTags(bool newValue)
			{
				touchAttributesTags = newValue;
				ApplyGroup(1, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DC040
			bool TriggerVolumeEventCondition::SetTouchAttributesTagsTouchAttributeKey1(const char* newValue)
			{
				touchAttributesTagsTouchAttributeKey1 = fight::ReplaceString(touchAttributesTagsTouchAttributeKey1, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DC070
			bool TriggerVolumeEventCondition::SetTouchAttributesTagsTouchAttributeValue1(const char* newValue)
			{
				touchAttributesTagsTouchAttributeValue1 = fight::ReplaceString(touchAttributesTagsTouchAttributeValue1, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DC0A0
			bool TriggerVolumeEventCondition::SetTouchAttributesTagsTouchAttributeKey2(const char* newValue)
			{
				touchAttributesTagsTouchAttributeKey2 = fight::ReplaceString(touchAttributesTagsTouchAttributeKey2, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DC0D0
			bool TriggerVolumeEventCondition::SetTouchAttributesTagsTouchAttributeValue2(const char* newValue)
			{
				touchAttributesTagsTouchAttributeValue2 = fight::ReplaceString(touchAttributesTagsTouchAttributeValue2, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DC100
			bool TriggerVolumeEventCondition::SetTouchAttributesTagsTouchTagList(const char* newValue)
			{
				touchAttributesTagsTouchTagList = fight::ReplaceString(touchAttributesTagsTouchTagList, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DBCC0
			fight::Property* TriggerVolumeEventCondition::GetProperty(int index)
			{
				return gTriggerVolumeEventConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101DBCE0
			void TriggerVolumeEventCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTriggerVolumeEventConditionProperties);
			}

			// FUNCTION: ENGINE 0x101DBCF0
			TriggerVolumeEventCondition::TriggerVolumeEventCondition() : fight::Condition(0), touchAttributesTagsTouchAttributeKey1(0), touchAttributesTagsTouchAttributeKey2(0), touchAttributesTagsTouchAttributeValue1(0), touchAttributesTagsTouchAttributeValue2(0), touchAttributesTagsTouchTagList(0), touchName(0), triggerVolumeAttributesTagsTriggerAttributeKey1(0), triggerVolumeAttributesTagsTriggerAttributeKey2(0), triggerVolumeAttributesTagsTriggerAttributeValue1(0), triggerVolumeAttributesTagsTriggerAttributeValue2(0), triggerVolumeAttributesTagsTriggerTagList(0), triggerVolumeName(0), type(0), touchAttributesTags(false), triggerVolumeAttributesTags(false)
			{
			}

			// FUNCTION: ENGINE 0x101DBD50
			bool TriggerVolumeEventCondition::Slot10(int index)
			{
				return (overrideMask & (1ui64 << index)) != 0;
			}

			// FUNCTION: ENGINE 0x101DBE30
			void TriggerVolumeEventCondition::ApplyGroup(int group, bool value)
			{
				const int* members;
				switch (group)
				{
				case 0:
					members = gTriggerVolumeEventConditionTriggerVolumeAttributesTagsMembers;
					value = value && triggerVolumeAttributesTags;
					break;
				case 1:
					members = gTriggerVolumeEventConditionTouchAttributesTagsMembers;
					value = value && touchAttributesTags;
					break;
				default:
					return;
				}
				for (int i = 0; members[i] != -1; i++)
				{
					unsigned __int64 bit = 1ui64 << members[i];
					if (value)
					{
						overrideMask |= bit;
					}
					else
					{
						overrideMask &= ~bit;
					}
					ApplyGroup(members[i], value);
				}
			}

			// FUNCTION: ENGINE 0x101DBD90
			TriggerVolumeEventCondition::~TriggerVolumeEventCondition()
			{
				delete[] triggerVolumeName;
				delete[] triggerVolumeAttributesTagsTriggerAttributeKey1;
				delete[] triggerVolumeAttributesTagsTriggerAttributeValue1;
				delete[] triggerVolumeAttributesTagsTriggerAttributeKey2;
				delete[] triggerVolumeAttributesTagsTriggerAttributeValue2;
				delete[] triggerVolumeAttributesTagsTriggerTagList;
				delete[] touchName;
				delete[] touchAttributesTagsTouchAttributeKey1;
				delete[] touchAttributesTagsTouchAttributeValue1;
				delete[] touchAttributesTagsTouchAttributeKey2;
				delete[] touchAttributesTagsTouchAttributeValue2;
				delete[] touchAttributesTagsTouchTagList;
			}

			// FUNCTION: ENGINE 0x101DCC70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TriggerVolumeEventCondition::RegisterProperties()
			{
				if (gTriggerVolumeEventConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TriggerVolumeEventCondition>("type", gTriggerVolumeEventConditionTypeTable, gTriggerVolumeEventConditionTypeCount, &TriggerVolumeEventCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("triggerVolumeName", &TriggerVolumeEventCondition::SetTriggerVolumeName);
					properties[1] = property;
					property = new fight::PropertyGroup<TriggerVolumeEventCondition>("triggerVolumeAttributesTags", &TriggerVolumeEventCondition::SetTriggerVolumeAttributesTags, gTriggerVolumeEventConditionTriggerVolumeAttributesTagsMembers);
					properties[2] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("triggerVolumeAttributesTagsTriggerAttributeKey1", &TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerAttributeKey1);
					properties[3] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("triggerVolumeAttributesTagsTriggerAttributeValue1", &TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerAttributeValue1);
					properties[4] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("triggerVolumeAttributesTagsTriggerAttributeKey2", &TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerAttributeKey2);
					properties[5] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("triggerVolumeAttributesTagsTriggerAttributeValue2", &TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerAttributeValue2);
					properties[6] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("triggerVolumeAttributesTagsTriggerTagList", &TriggerVolumeEventCondition::SetTriggerVolumeAttributesTagsTriggerTagList);
					properties[7] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("touchName", &TriggerVolumeEventCondition::SetTouchName);
					properties[8] = property;
					property = new fight::PropertyGroup<TriggerVolumeEventCondition>("touchAttributesTags", &TriggerVolumeEventCondition::SetTouchAttributesTags, gTriggerVolumeEventConditionTouchAttributesTagsMembers);
					properties[9] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("touchAttributesTagsTouchAttributeKey1", &TriggerVolumeEventCondition::SetTouchAttributesTagsTouchAttributeKey1);
					properties[10] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("touchAttributesTagsTouchAttributeValue1", &TriggerVolumeEventCondition::SetTouchAttributesTagsTouchAttributeValue1);
					properties[11] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("touchAttributesTagsTouchAttributeKey2", &TriggerVolumeEventCondition::SetTouchAttributesTagsTouchAttributeKey2);
					properties[12] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("touchAttributesTagsTouchAttributeValue2", &TriggerVolumeEventCondition::SetTouchAttributesTagsTouchAttributeValue2);
					properties[13] = property;
					property = new fight::PropertyString<TriggerVolumeEventCondition>("touchAttributesTagsTouchTagList", &TriggerVolumeEventCondition::SetTouchAttributesTagsTouchTagList);
					properties[14] = property;
					fight::RegisterPropertyList(properties, &gTriggerVolumeEventConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DCA90
			fight::ConditionFactory* CreateTriggerVolumeEventConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TriggerVolumeEventCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DD230
			void RegisterTriggerVolumeEventConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TriggerVolumeEventCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gMissionConditionProperties;  // 0x11254DF4

			// FUNCTION: ENGINE 0x101DBAD0
			bool MissionCondition::SetEpisode(int newValue)
			{
				episode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DBAE0
			bool MissionCondition::SetMission(int newValue)
			{
				mission = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DC130
			fight::Property* MissionCondition::GetProperty(int index)
			{
				return gMissionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101DC150
			void MissionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gMissionConditionProperties);
			}

			// FUNCTION: ENGINE 0x101DC160
			MissionCondition::MissionCondition() : fight::Condition(0), episode(0), mission(0)
			{
			}

			// FUNCTION: ENGINE 0x101DC190
			MissionCondition::~MissionCondition()
			{
			}

			// FUNCTION: ENGINE 0x101DD090
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void MissionCondition::RegisterProperties()
			{
				if (gMissionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyIntConstRange<MissionCondition>("episode", &MissionCondition::SetEpisode);
					properties[0] = property;
					property = new fight::PropertyIntConstRange<MissionCondition>("mission", &MissionCondition::SetMission);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gMissionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DCAC0
			fight::ConditionFactory* CreateMissionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<MissionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DD260
			void RegisterMissionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<MissionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumListObject<TransformationDescriptionNameCondition>;
			template class fight::PropertyName<TransformationDescriptionNameCondition>;
			template class fight::PropertyBool<TransformationDescriptionNameCondition>;
			template class fight::ConditionFactoryTemplate<TransformationDescriptionNameCondition>;
			template class fight::ConditionFactoryCasterTemplate<TransformationDescriptionNameCondition>;
			template class fight::PropertyEnumListObject<AlertStatusCondition>;
			template class fight::PropertyBool<AlertStatusCondition>;
			template class fight::ConditionFactoryTemplate<AlertStatusCondition>;
			template class fight::ConditionFactoryCasterTemplate<AlertStatusCondition>;
			template class fight::ConditionFactoryTemplate<InMissionCondition>;
			template class fight::ConditionFactoryCasterTemplate<InMissionCondition>;
			template class fight::PropertyEnumListObject<IsPlayerCharacterCondition>;
			template class fight::ConditionFactoryTemplate<IsPlayerCharacterCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsPlayerCharacterCondition>;
			template class fight::PropertyEnumConstList<TriggerVolumeEventCondition>;
			template class fight::PropertyString<TriggerVolumeEventCondition>;
			template class fight::PropertyGroup<TriggerVolumeEventCondition>;
			template class fight::ConditionFactoryTemplate<TriggerVolumeEventCondition>;
			template class fight::ConditionFactoryCasterTemplate<TriggerVolumeEventCondition>;
			template class fight::PropertyIntConstRange<MissionCondition>;
			template class fight::ConditionFactoryTemplate<MissionCondition>;
			template class fight::ConditionFactoryCasterTemplate<MissionCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DC200
// FUNCTION: ENGINE 0x101DC230
// FUNCTION: ENGINE 0x101DC260
// FUNCTION: ENGINE 0x101DC290
// FUNCTION: ENGINE 0x101DC300
// FUNCTION: ENGINE 0x101DC330
// FUNCTION: ENGINE 0x101DC340
// FUNCTION: ENGINE 0x101DC370
// FUNCTION: ENGINE 0x101DC380
// FUNCTION: ENGINE 0x101DC3B0
// FUNCTION: ENGINE 0x101DC3C0
// FUNCTION: ENGINE 0x101DC3F0
// FUNCTION: ENGINE 0x101DC420
// FUNCTION: ENGINE 0x101DC440
// FUNCTION: ENGINE 0x101DC490
// FUNCTION: ENGINE 0x101DC4A0
// FUNCTION: ENGINE 0x101DC4D0
// FUNCTION: ENGINE 0x101DC4E0
// FUNCTION: ENGINE 0x101DC510
// FUNCTION: ENGINE 0x101DC520
// FUNCTION: ENGINE 0x101DC550
// FUNCTION: ENGINE 0x101DC580
// FUNCTION: ENGINE 0x101DC5B0
// FUNCTION: ENGINE 0x101DC5C0
// FUNCTION: ENGINE 0x101DC5E0
// FUNCTION: ENGINE 0x101DC600
// FUNCTION: ENGINE 0x101DC610
// FUNCTION: ENGINE 0x101DC640
// FUNCTION: ENGINE 0x101DC660
// FUNCTION: ENGINE 0x101DC670
// FUNCTION: ENGINE 0x101DC6A0
// FUNCTION: ENGINE 0x101DC6B0
// FUNCTION: ENGINE 0x101DC6D0
// FUNCTION: ENGINE 0x101DC6F0
// FUNCTION: ENGINE 0x101DC700
// FUNCTION: ENGINE 0x101DC730
// FUNCTION: ENGINE 0x101DC750
// FUNCTION: ENGINE 0x101DC760
// FUNCTION: ENGINE 0x101DC790
// FUNCTION: ENGINE 0x101DC7A0
// FUNCTION: ENGINE 0x101DC7C0
// FUNCTION: ENGINE 0x101DC7E0
// FUNCTION: ENGINE 0x101DC7F0
// FUNCTION: ENGINE 0x101DC830
// FUNCTION: ENGINE 0x101DC840
// FUNCTION: ENGINE 0x101DC870
// FUNCTION: ENGINE 0x101DC890
// FUNCTION: ENGINE 0x101DC8A0
// FUNCTION: ENGINE 0x101DC8D0
// FUNCTION: ENGINE 0x101DC8F0
// FUNCTION: ENGINE 0x101DC900
// FUNCTION: ENGINE 0x101DC930
// FUNCTION: ENGINE 0x101DC950
// FUNCTION: ENGINE 0x101DC960
// FUNCTION: ENGINE 0x101DC970
// FUNCTION: ENGINE 0x101DC9A0
// FUNCTION: ENGINE 0x101DC9C0
// FUNCTION: ENGINE 0x101DD290
// FUNCTION: ENGINE 0x101DD2C0
// FUNCTION: ENGINE 0x101DD2E0
// FUNCTION: ENGINE 0x101DD310
// FUNCTION: ENGINE 0x101DD330
// FUNCTION: ENGINE 0x101DD360
// FUNCTION: ENGINE 0x101DD380
// FUNCTION: ENGINE 0x101DD3B0
// FUNCTION: ENGINE 0x101DD3D0
// FUNCTION: ENGINE 0x101DD400
// FUNCTION: ENGINE 0x101DD540
// FUNCTION: ENGINE 0x101DD590
// FUNCTION: ENGINE 0x101DD5E0
// FUNCTION: ENGINE 0x101DD630
// FUNCTION: ENGINE 0x101DD680
// FUNCTION: ENGINE 0x101DD6B0
// FUNCTION: ENGINE 0x101DD6D0
