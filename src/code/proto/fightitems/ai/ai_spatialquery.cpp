// Fight items of the ai group: SpatialQueryCondition, SoldierWithinDistanceCondition (unit 0x10249200 - 0x10249C30; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_spatialquery.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gSpatialQueryConditionProperties;  // 0x11255B88

			// FUNCTION: ENGINE 0x10249200
			bool SpatialQueryCondition::SetWhat(int newValue)
			{
				what = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249330
			bool SpatialQueryCondition::SetWhatData(const fight::Name& newValue)
			{
				whatData = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249210
			bool SpatialQueryCondition::SetWhere(int newValue)
			{
				where = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249220
			bool SpatialQueryCondition::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249240
			bool SpatialQueryCondition::SetExcludeSelf(bool newValue)
			{
				excludeSelf = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249250
			bool SpatialQueryCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249260
			bool SpatialQueryCondition::SetInside(int newValue)
			{
				inside = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10249290
			fight::Property* SpatialQueryCondition::GetProperty(int index)
			{
				return gSpatialQueryConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102492B0
			void SpatialQueryCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSpatialQueryConditionProperties);
			}

			// FUNCTION: ENGINE 0x10249350
			SpatialQueryCondition::SpatialQueryCondition() : fight::Condition(0), maxDistance(2e+01f), compare(4), inside(1), what(0), where(0), excludeSelf(true)
			{
			}

			// FUNCTION: ENGINE 0x102493B0
			SpatialQueryCondition::~SpatialQueryCondition()
			{
			}

			// FUNCTION: ENGINE 0x102498F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpatialQueryCondition::RegisterProperties()
			{
				if (gSpatialQueryConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<SpatialQueryCondition>("what", gSpatialQueryConditionWhatTable, gSpatialQueryConditionWhatCount, &SpatialQueryCondition::SetWhat);
					properties[0] = property;
					property = new fight::PropertyName<SpatialQueryCondition>("whatData", &SpatialQueryCondition::SetWhatData);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<SpatialQueryCondition>("where", gSpatialQueryConditionWhereTable, gSpatialQueryConditionWhereCount, &SpatialQueryCondition::SetWhere);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SpatialQueryCondition>("maxDistance", &SpatialQueryCondition::SetMaxDistance);
					properties[3] = property;
					property = new fight::PropertyBool<SpatialQueryCondition>("excludeSelf", &SpatialQueryCondition::SetExcludeSelf);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<SpatialQueryCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &SpatialQueryCondition::SetCompare);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<SpatialQueryCondition>("inside", &SpatialQueryCondition::SetInside);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gSpatialQueryConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102496F0
			fight::ConditionFactory* CreateSpatialQueryConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SpatialQueryCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102497F0
			void RegisterSpatialQueryConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SpatialQueryCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSoldierWithinDistanceConditionProperties;  // 0x11255B8C

			// FUNCTION: ENGINE 0x10249270
			bool SoldierWithinDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102492C0
			fight::Property* SoldierWithinDistanceCondition::GetProperty(int index)
			{
				return gSoldierWithinDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102492E0
			void SoldierWithinDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSoldierWithinDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x102492F0
			SoldierWithinDistanceCondition::SoldierWithinDistanceCondition() : fight::Condition(0), distance(2e+01f)
			{
			}

			// FUNCTION: ENGINE 0x10249320
			SoldierWithinDistanceCondition::~SoldierWithinDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10249750
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SoldierWithinDistanceCondition::RegisterProperties()
			{
				if (gSoldierWithinDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SoldierWithinDistanceCondition>("distance", &SoldierWithinDistanceCondition::SetDistance);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gSoldierWithinDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10249720
			fight::ConditionFactory* CreateSoldierWithinDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SoldierWithinDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10249820
			void RegisterSoldierWithinDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SoldierWithinDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<SpatialQueryCondition>;
			template class fight::PropertyName<SpatialQueryCondition>;
			template class fight::PropertyFloatConstRange<SpatialQueryCondition>;
			template class fight::PropertyBool<SpatialQueryCondition>;
			template class fight::PropertyIntConstRange<SpatialQueryCondition>;
			template class fight::ConditionFactoryTemplate<SpatialQueryCondition>;
			template class fight::ConditionFactoryCasterTemplate<SpatialQueryCondition>;
			template class fight::PropertyFloatConstRange<SoldierWithinDistanceCondition>;
			template class fight::ConditionFactoryTemplate<SoldierWithinDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<SoldierWithinDistanceCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102493C0
// FUNCTION: ENGINE 0x102493F0
// FUNCTION: ENGINE 0x10249400
// FUNCTION: ENGINE 0x10249430
// FUNCTION: ENGINE 0x10249440
// FUNCTION: ENGINE 0x10249470
// FUNCTION: ENGINE 0x102494A0
// FUNCTION: ENGINE 0x102494E0
// FUNCTION: ENGINE 0x102494F0
// FUNCTION: ENGINE 0x10249520
// FUNCTION: ENGINE 0x10249540
// FUNCTION: ENGINE 0x10249550
// FUNCTION: ENGINE 0x10249580
// FUNCTION: ENGINE 0x102495B0
// FUNCTION: ENGINE 0x102495C0
// FUNCTION: ENGINE 0x102495F0
// FUNCTION: ENGINE 0x10249610
// FUNCTION: ENGINE 0x10249620
// FUNCTION: ENGINE 0x10249650
// FUNCTION: ENGINE 0x10249670
// FUNCTION: ENGINE 0x10249680
// FUNCTION: ENGINE 0x102496B0
// FUNCTION: ENGINE 0x102496E0
// FUNCTION: ENGINE 0x10249850
// FUNCTION: ENGINE 0x10249880
// FUNCTION: ENGINE 0x102498A0
// FUNCTION: ENGINE 0x102498D0
// FUNCTION: ENGINE 0x10249B40
// FUNCTION: ENGINE 0x10249B90
// FUNCTION: ENGINE 0x10249BC0
// FUNCTION: ENGINE 0x10249BE0
