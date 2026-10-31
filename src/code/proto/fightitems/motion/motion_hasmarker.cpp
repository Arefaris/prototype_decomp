// Fight items of the motion group: HasMarkerCondition, HideHUDTrack (unit 0x10161F50 - 0x10162970; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_hasmarker.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			extern const int gHideHUDTrackHideIndividualElementsMembers[];  // 0x1100C66C

			fight::Property** gHasMarkerConditionProperties;  // 0x11254548

			// FUNCTION: ENGINE 0x10161F50
			bool HasMarkerCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161FB0
			fight::Property* HasMarkerCondition::GetProperty(int index)
			{
				return gHasMarkerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10161FD0
			void HasMarkerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasMarkerConditionProperties);
			}

			// FUNCTION: ENGINE 0x10161FE0
			HasMarkerCondition::HasMarkerCondition() : fight::Condition(0), type(0)
			{
			}

			// FUNCTION: ENGINE 0x10162010
			HasMarkerCondition::~HasMarkerCondition()
			{
			}

			// FUNCTION: ENGINE 0x101625B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasMarkerCondition::RegisterProperties()
			{
				if (gHasMarkerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HasMarkerCondition>("type", gHaveIconTypeConditionTypeTable, gHaveIconTypeConditionTypeCount, &HasMarkerCondition::SetType);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHasMarkerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10162550
			fight::ConditionFactory* CreateHasMarkerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasMarkerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101627D0
			void RegisterHasMarkerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasMarkerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHideHUDTrackProperties;  // 0x1125454C

			// FUNCTION: ENGINE 0x10161F60
			bool HideHUDTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161F80
			bool HideHUDTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161FA0
			bool HideHUDTrack::SetHideIndividualElementsHideElements(int newValue)
			{
				hideIndividualElementsHideElements = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162020
			fight::Property* HideHUDTrack::GetProperty(int index)
			{
				return gHideHUDTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10162040
			void HideHUDTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHideHUDTrackProperties);
			}

			// FUNCTION: ENGINE 0x10162050
			HideHUDTrack::HideHUDTrack() : timeBegin(0.0f), timeEnd(-1.0f), hideIndividualElementsHideElements(0), hideIndividualElements(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101620A0
			float HideHUDTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101620F0
			float HideHUDTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101620B0
			bool HideHUDTrack::Slot16(int index)
			{
				return (overrideMask & (1ui64 << index)) != 0;
			}

			// FUNCTION: ENGINE 0x10162100
			HideHUDTrack::~HideHUDTrack()
			{
			}

			// FUNCTION: ENGINE 0x10162110
			// NONMATCHING: the engine keeps the group flag's result only in the argument slot and pushes a register copy for the recursive call; ours holds it in bl (best 35%)
#ifdef NONMATCHING
			void HideHUDTrack::ApplyGroup(int group, bool value)
			{
				if (group != 0)
				{
					return;
				}
				if (value && !hideIndividualElements)
				{
					value = false;
				}
				for (int i = 0; gHideHUDTrackHideIndividualElementsMembers[i] != -1; i++)
				{
					const int* member = &gHideHUDTrackHideIndividualElementsMembers[i];
					unsigned __int64 bit = 1ui64 << *member;
					if (value)
					{
						overrideMask |= bit;
					}
					else
					{
						overrideMask &= ~bit;
					}
					ApplyGroup(*member, value);
				}
			}
#endif

			// FUNCTION: ENGINE 0x10162220
			bool HideHUDTrack::SetHideIndividualElements(bool newValue)
			{
				hideIndividualElements = newValue;
				ApplyGroup(0, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x10162660
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HideHUDTrack::RegisterProperties()
			{
				if (gHideHUDTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HideHUDTrack>("timeBegin", &HideHUDTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HideHUDTrack>("timeEnd", &HideHUDTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyGroup<HideHUDTrack>("hideIndividualElements", &HideHUDTrack::SetHideIndividualElements, gHideHUDTrackHideIndividualElementsMembers);
					properties[2] = property;
					property = new fight::PropertyBitfieldConstList<HideHUDTrack>("hideIndividualElementsHideElements", gHideHUDTrackHideIndividualElementsHideElementsTable, gHideHUDTrackHideIndividualElementsHideElementsCount, &HideHUDTrack::SetHideIndividualElementsHideElements);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gHideHUDTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10162580
			fight::TrackFactory* CreateHideHUDTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HideHUDTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10162800
			void RegisterHideHUDTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HideHUDTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<HasMarkerCondition>;
			template class fight::ConditionFactoryTemplate<HasMarkerCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasMarkerCondition>;
			template class fight::PropertyFloatConstRange<HideHUDTrack>;
			template class fight::PropertyGroup<HideHUDTrack>;
			template class fight::PropertyBitfieldConstList<HideHUDTrack>;
			template class fight::TrackFactoryTemplate<HideHUDTrack>;
			template class fight::TrackFactoryCasterTemplate<HideHUDTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101621C0
// FUNCTION: ENGINE 0x101621F0
// FUNCTION: ENGINE 0x10162250
// FUNCTION: ENGINE 0x10162260
// FUNCTION: ENGINE 0x10162290
// FUNCTION: ENGINE 0x101622A0
// FUNCTION: ENGINE 0x101622D0
// FUNCTION: ENGINE 0x10162310
// FUNCTION: ENGINE 0x10162320
// FUNCTION: ENGINE 0x10162350
// FUNCTION: ENGINE 0x10162370
// FUNCTION: ENGINE 0x10162380
// FUNCTION: ENGINE 0x101623B0
// FUNCTION: ENGINE 0x101623E0
// FUNCTION: ENGINE 0x101623F0
// FUNCTION: ENGINE 0x10162430
// FUNCTION: ENGINE 0x10162450
// FUNCTION: ENGINE 0x10162460
// FUNCTION: ENGINE 0x10162470
// FUNCTION: ENGINE 0x101624B0
// FUNCTION: ENGINE 0x101624C0
// FUNCTION: ENGINE 0x101624E0
// FUNCTION: ENGINE 0x101624F0
// FUNCTION: ENGINE 0x10162830
// FUNCTION: ENGINE 0x10162860
// FUNCTION: ENGINE 0x10162880
// FUNCTION: ENGINE 0x101628B0
// FUNCTION: ENGINE 0x101628D0
// FUNCTION: ENGINE 0x10162920
