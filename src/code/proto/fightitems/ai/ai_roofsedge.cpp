// Fight items of the ai group: NearRoofsEdgeCondition, AtRoofsEdgeCondition (unit 0x10246F80 - 0x10247690; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_roofsedge.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gNearRoofsEdgeConditionProperties;  // 0x11255B58

			// FUNCTION: ENGINE 0x10246F80
			bool NearRoofsEdgeCondition::SetNearEdge(bool newValue)
			{
				nearEdge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246FC0
			fight::Property* NearRoofsEdgeCondition::GetProperty(int index)
			{
				return gNearRoofsEdgeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10246FE0
			void NearRoofsEdgeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gNearRoofsEdgeConditionProperties);
			}

			// FUNCTION: ENGINE 0x10246FF0
			NearRoofsEdgeCondition::NearRoofsEdgeCondition() : fight::Condition(0), nearEdge(true)
			{
			}

			// FUNCTION: ENGINE 0x10247010
			NearRoofsEdgeCondition::~NearRoofsEdgeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10247360
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void NearRoofsEdgeCondition::RegisterProperties()
			{
				if (gNearRoofsEdgeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<NearRoofsEdgeCondition>("nearEdge", &NearRoofsEdgeCondition::SetNearEdge);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gNearRoofsEdgeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10247300
			fight::ConditionFactory* CreateNearRoofsEdgeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<NearRoofsEdgeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102474F0
			void RegisterNearRoofsEdgeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<NearRoofsEdgeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAtRoofsEdgeConditionProperties;  // 0x11255B5C

			// FUNCTION: ENGINE 0x10246F90
			bool AtRoofsEdgeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246FA0
			bool AtRoofsEdgeCondition::SetTimeAtEdge(float newValue)
			{
				timeAtEdge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247020
			fight::Property* AtRoofsEdgeCondition::GetProperty(int index)
			{
				return gAtRoofsEdgeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10247040
			void AtRoofsEdgeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAtRoofsEdgeConditionProperties);
			}

			// FUNCTION: ENGINE 0x10247050
			AtRoofsEdgeCondition::AtRoofsEdgeCondition() : fight::Condition(0), timeAtEdge(-1.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10247090
			AtRoofsEdgeCondition::~AtRoofsEdgeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10247400
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AtRoofsEdgeCondition::RegisterProperties()
			{
				if (gAtRoofsEdgeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AtRoofsEdgeCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &AtRoofsEdgeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AtRoofsEdgeCondition>("timeAtEdge", &AtRoofsEdgeCondition::SetTimeAtEdge);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gAtRoofsEdgeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10247330
			fight::ConditionFactory* CreateAtRoofsEdgeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AtRoofsEdgeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10247520
			void RegisterAtRoofsEdgeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AtRoofsEdgeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyBool<NearRoofsEdgeCondition>;
			template class fight::ConditionFactoryTemplate<NearRoofsEdgeCondition>;
			template class fight::ConditionFactoryCasterTemplate<NearRoofsEdgeCondition>;
			template class fight::PropertyEnumConstList<AtRoofsEdgeCondition>;
			template class fight::PropertyFloatConstRange<AtRoofsEdgeCondition>;
			template class fight::ConditionFactoryTemplate<AtRoofsEdgeCondition>;
			template class fight::ConditionFactoryCasterTemplate<AtRoofsEdgeCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102470A0
// FUNCTION: ENGINE 0x102470D0
// FUNCTION: ENGINE 0x10247100
// FUNCTION: ENGINE 0x10247110
// FUNCTION: ENGINE 0x10247140
// FUNCTION: ENGINE 0x10247150
// FUNCTION: ENGINE 0x10247180
// FUNCTION: ENGINE 0x102471B0
// FUNCTION: ENGINE 0x102471D0
// FUNCTION: ENGINE 0x102471E0
// FUNCTION: ENGINE 0x10247220
// FUNCTION: ENGINE 0x10247230
// FUNCTION: ENGINE 0x10247260
// FUNCTION: ENGINE 0x10247280
// FUNCTION: ENGINE 0x10247290
// FUNCTION: ENGINE 0x102472C0
// FUNCTION: ENGINE 0x102472F0
// FUNCTION: ENGINE 0x10247550
// FUNCTION: ENGINE 0x10247580
// FUNCTION: ENGINE 0x102475A0
// FUNCTION: ENGINE 0x102475D0
// FUNCTION: ENGINE 0x102475F0
// FUNCTION: ENGINE 0x10247640
