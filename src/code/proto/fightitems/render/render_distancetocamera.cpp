// Fight items of the render group: DistanceToCameraCondition (unit 0x10262C90 - 0x102630C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/render/render_distancetocamera.h"

namespace proto
{
	namespace fightitems
	{
		namespace render
		{
			fight::Property** gDistanceToCameraConditionProperties;  // 0x11255DCC

			// FUNCTION: ENGINE 0x10262C90
			bool DistanceToCameraCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10262CA0
			bool DistanceToCameraCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10262CC0
			fight::Property* DistanceToCameraCondition::GetProperty(int index)
			{
				return gDistanceToCameraConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10262CE0
			void DistanceToCameraCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDistanceToCameraConditionProperties);
			}

			// FUNCTION: ENGINE 0x10262CF0
			DistanceToCameraCondition::DistanceToCameraCondition() : fight::Condition(0), distance(1.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10262D30
			DistanceToCameraCondition::~DistanceToCameraCondition()
			{
			}

			// FUNCTION: ENGINE 0x10262F00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DistanceToCameraCondition::RegisterProperties()
			{
				if (gDistanceToCameraConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DistanceToCameraCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &DistanceToCameraCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DistanceToCameraCondition>("distance", &DistanceToCameraCondition::SetDistance);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDistanceToCameraConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10262ED0
			fight::ConditionFactory* CreateDistanceToCameraConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DistanceToCameraCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10262FF0
			void RegisterDistanceToCameraConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DistanceToCameraCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<DistanceToCameraCondition>;
			template class fight::PropertyFloatConstRange<DistanceToCameraCondition>;
			template class fight::ConditionFactoryTemplate<DistanceToCameraCondition>;
			template class fight::ConditionFactoryCasterTemplate<DistanceToCameraCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10262D40
// FUNCTION: ENGINE 0x10262D70
// FUNCTION: ENGINE 0x10262D80
// FUNCTION: ENGINE 0x10262DB0
// FUNCTION: ENGINE 0x10262DF0
// FUNCTION: ENGINE 0x10262E00
// FUNCTION: ENGINE 0x10262E30
// FUNCTION: ENGINE 0x10262E50
// FUNCTION: ENGINE 0x10262E60
// FUNCTION: ENGINE 0x10262E90
// FUNCTION: ENGINE 0x10262EC0
// FUNCTION: ENGINE 0x10263020
// FUNCTION: ENGINE 0x10263050
// FUNCTION: ENGINE 0x10263070
