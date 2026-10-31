// Fight items of the ai group: InAlertModeCondition, PerceptionEventCondition, TargetFreeHeightRadiusCondition (unit 0x1022CB50 - 0x1022D810; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_alertmode.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gInAlertModeConditionProperties;  // 0x11255984

			// FUNCTION: ENGINE 0x1022CB50
			bool InAlertModeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022CB60
			bool InAlertModeCondition::SetSeconds(float newValue)
			{
				seconds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022CBF0
			fight::Property* InAlertModeCondition::GetProperty(int index)
			{
				return gInAlertModeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022CC10
			void InAlertModeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInAlertModeConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022CC20
			InAlertModeCondition::InAlertModeCondition() : fight::Condition(0), seconds(5.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x1022CC60
			InAlertModeCondition::~InAlertModeCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022D290
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InAlertModeCondition::RegisterProperties()
			{
				if (gInAlertModeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<InAlertModeCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &InAlertModeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<InAlertModeCondition>("seconds", &InAlertModeCondition::SetSeconds);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gInAlertModeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022D200
			fight::ConditionFactory* CreateInAlertModeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InAlertModeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022D5A0
			void RegisterInAlertModeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InAlertModeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPerceptionEventConditionProperties;  // 0x11255988

			// FUNCTION: ENGINE 0x1022CB80
			bool PerceptionEventCondition::SetEvent(int newValue)
			{
				event = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022CC70
			fight::Property* PerceptionEventCondition::GetProperty(int index)
			{
				return gPerceptionEventConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022CC90
			void PerceptionEventCondition::ClearProperties()
			{
				fight::FreePropertyList(&gPerceptionEventConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022CCA0
			PerceptionEventCondition::PerceptionEventCondition() : fight::Condition(0), event(0)
			{
			}

			// FUNCTION: ENGINE 0x1022CCD0
			PerceptionEventCondition::~PerceptionEventCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022D380
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PerceptionEventCondition::RegisterProperties()
			{
				if (gPerceptionEventConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<PerceptionEventCondition>("event", gPerceptionEventConditionEventTable, gPerceptionEventConditionEventCount, &PerceptionEventCondition::SetEvent);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gPerceptionEventConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022D230
			fight::ConditionFactory* CreatePerceptionEventConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PerceptionEventCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022D5D0
			void RegisterPerceptionEventConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<PerceptionEventCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetFreeHeightRadiusConditionProperties;  // 0x1125598C

			// FUNCTION: ENGINE 0x1022CB90
			bool TargetFreeHeightRadiusCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022CBA0
			bool TargetFreeHeightRadiusCondition::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022CBC0
			bool TargetFreeHeightRadiusCondition::SetHeightTolerance(float newValue)
			{
				heightTolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022CBE0
			bool TargetFreeHeightRadiusCondition::SetGroundUnit(bool newValue)
			{
				groundUnit = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022CCE0
			fight::Property* TargetFreeHeightRadiusCondition::GetProperty(int index)
			{
				return gTargetFreeHeightRadiusConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022CD00
			void TargetFreeHeightRadiusCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetFreeHeightRadiusConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022CD10
			TargetFreeHeightRadiusCondition::TargetFreeHeightRadiusCondition() : fight::Condition(0), heightTolerance(5.0f), radius(5.0f), compare(0), groundUnit(false)
			{
			}

			// FUNCTION: ENGINE 0x1022CD50
			TargetFreeHeightRadiusCondition::~TargetFreeHeightRadiusCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022D430
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetFreeHeightRadiusCondition::RegisterProperties()
			{
				if (gTargetFreeHeightRadiusConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TargetFreeHeightRadiusCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &TargetFreeHeightRadiusCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TargetFreeHeightRadiusCondition>("radius", &TargetFreeHeightRadiusCondition::SetRadius);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TargetFreeHeightRadiusCondition>("heightTolerance", &TargetFreeHeightRadiusCondition::SetHeightTolerance);
					properties[2] = property;
					property = new fight::PropertyBool<TargetFreeHeightRadiusCondition>("groundUnit", &TargetFreeHeightRadiusCondition::SetGroundUnit);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gTargetFreeHeightRadiusConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022D260
			fight::ConditionFactory* CreateTargetFreeHeightRadiusConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetFreeHeightRadiusCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022D600
			void RegisterTargetFreeHeightRadiusConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetFreeHeightRadiusCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<InAlertModeCondition>;
			template class fight::PropertyFloatConstRange<InAlertModeCondition>;
			template class fight::ConditionFactoryTemplate<InAlertModeCondition>;
			template class fight::ConditionFactoryCasterTemplate<InAlertModeCondition>;
			template class fight::PropertyEnumConstList<PerceptionEventCondition>;
			template class fight::ConditionFactoryTemplate<PerceptionEventCondition>;
			template class fight::ConditionFactoryCasterTemplate<PerceptionEventCondition>;
			template class fight::PropertyEnumConstList<TargetFreeHeightRadiusCondition>;
			template class fight::PropertyFloatConstRange<TargetFreeHeightRadiusCondition>;
			template class fight::PropertyBool<TargetFreeHeightRadiusCondition>;
			template class fight::ConditionFactoryTemplate<TargetFreeHeightRadiusCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetFreeHeightRadiusCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1022CD60
// FUNCTION: ENGINE 0x1022CD90
// FUNCTION: ENGINE 0x1022CDC0
// FUNCTION: ENGINE 0x1022CDF0
// FUNCTION: ENGINE 0x1022CE00
// FUNCTION: ENGINE 0x1022CE30
// FUNCTION: ENGINE 0x1022CE40
// FUNCTION: ENGINE 0x1022CE70
// FUNCTION: ENGINE 0x1022CE80
// FUNCTION: ENGINE 0x1022CEB0
// FUNCTION: ENGINE 0x1022CEF0
// FUNCTION: ENGINE 0x1022CF00
// FUNCTION: ENGINE 0x1022CF30
// FUNCTION: ENGINE 0x1022CF50
// FUNCTION: ENGINE 0x1022CF60
// FUNCTION: ENGINE 0x1022CF90
// FUNCTION: ENGINE 0x1022CFC0
// FUNCTION: ENGINE 0x1022CFD0
// FUNCTION: ENGINE 0x1022D010
// FUNCTION: ENGINE 0x1022D020
// FUNCTION: ENGINE 0x1022D050
// FUNCTION: ENGINE 0x1022D070
// FUNCTION: ENGINE 0x1022D080
// FUNCTION: ENGINE 0x1022D0C0
// FUNCTION: ENGINE 0x1022D0D0
// FUNCTION: ENGINE 0x1022D100
// FUNCTION: ENGINE 0x1022D120
// FUNCTION: ENGINE 0x1022D130
// FUNCTION: ENGINE 0x1022D160
// FUNCTION: ENGINE 0x1022D190
// FUNCTION: ENGINE 0x1022D1A0
// FUNCTION: ENGINE 0x1022D1D0
// FUNCTION: ENGINE 0x1022D1F0
// FUNCTION: ENGINE 0x1022D630
// FUNCTION: ENGINE 0x1022D660
// FUNCTION: ENGINE 0x1022D680
// FUNCTION: ENGINE 0x1022D6B0
// FUNCTION: ENGINE 0x1022D6D0
// FUNCTION: ENGINE 0x1022D700
// FUNCTION: ENGINE 0x1022D720
// FUNCTION: ENGINE 0x1022D770
// FUNCTION: ENGINE 0x1022D7C0
