// Fight items of the ai group: NavMeshAreaCondition (unit 0x102432A0 - 0x10243760; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_navmesharea.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gNavMeshAreaConditionProperties;  // 0x11255B0C

			// FUNCTION: ENGINE 0x102432A0
			bool NavMeshAreaCondition::SetAllowedAreas(int newValue)
			{
				allowedAreas = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102432B0
			bool NavMeshAreaCondition::SetVerticalTolerance(float newValue)
			{
				verticalTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102432D0
			bool NavMeshAreaCondition::SetRayIfNotSupported(float newValue)
			{
				rayIfNotSupported = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102432F0
			fight::Property* NavMeshAreaCondition::GetProperty(int index)
			{
				return gNavMeshAreaConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10243310
			void NavMeshAreaCondition::ClearProperties()
			{
				fight::FreePropertyList(&gNavMeshAreaConditionProperties);
			}

			// FUNCTION: ENGINE 0x10243320
			NavMeshAreaCondition::NavMeshAreaCondition() : fight::Condition(0), rayIfNotSupported(0.0f), verticalTolerance(2.0f), allowedAreas(gCombatDestinationFindTrackAllowedAreasDefault)
			{
			}

			// FUNCTION: ENGINE 0x10243360
			NavMeshAreaCondition::~NavMeshAreaCondition()
			{
			}

			// FUNCTION: ENGINE 0x10243560
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void NavMeshAreaCondition::RegisterProperties()
			{
				if (gNavMeshAreaConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBitfieldConstList<NavMeshAreaCondition>("allowedAreas", gCombatDestinationFindTrackAllowedAreasTable, gCombatDestinationFindTrackAllowedAreasCount, &NavMeshAreaCondition::SetAllowedAreas);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<NavMeshAreaCondition>("verticalTolerance", &NavMeshAreaCondition::SetVerticalTolerance);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<NavMeshAreaCondition>("rayIfNotSupported", &NavMeshAreaCondition::SetRayIfNotSupported);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gNavMeshAreaConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10243530
			fight::ConditionFactory* CreateNavMeshAreaConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<NavMeshAreaCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10243690
			void RegisterNavMeshAreaConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<NavMeshAreaCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyBitfieldConstList<NavMeshAreaCondition>;
			template class fight::PropertyFloatConstRange<NavMeshAreaCondition>;
			template class fight::ConditionFactoryTemplate<NavMeshAreaCondition>;
			template class fight::ConditionFactoryCasterTemplate<NavMeshAreaCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10243370
// FUNCTION: ENGINE 0x102433A0
// FUNCTION: ENGINE 0x102433B0
// FUNCTION: ENGINE 0x102433E0
// FUNCTION: ENGINE 0x10243420
// FUNCTION: ENGINE 0x10243430
// FUNCTION: ENGINE 0x10243450
// FUNCTION: ENGINE 0x10243460
// FUNCTION: ENGINE 0x102434C0
// FUNCTION: ENGINE 0x102434F0
// FUNCTION: ENGINE 0x10243520
// FUNCTION: ENGINE 0x102436C0
// FUNCTION: ENGINE 0x102436F0
// FUNCTION: ENGINE 0x10243710
