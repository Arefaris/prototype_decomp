// Fight items of the render group: GPUFillCondition (unit 0x102640B0 - 0x102643C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/render/render_gpufill.h"

namespace proto
{
	namespace fightitems
	{
		namespace render
		{
			fight::Property** gGPUFillConditionProperties;  // 0x11255DD4

			// FUNCTION: ENGINE 0x102640B0
			bool GPUFillCondition::SetRatio(float newValue)
			{
				ratio = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102640D0
			fight::Property* GPUFillCondition::GetProperty(int index)
			{
				return gGPUFillConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102640F0
			void GPUFillCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGPUFillConditionProperties);
			}

			// FUNCTION: ENGINE 0x10264100
			GPUFillCondition::GPUFillCondition() : fight::Condition(0), ratio(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x10264130
			GPUFillCondition::~GPUFillCondition()
			{
			}

			// FUNCTION: ENGINE 0x10264250
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GPUFillCondition::RegisterProperties()
			{
				if (gGPUFillConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GPUFillCondition>("ratio", &GPUFillCondition::SetRatio);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGPUFillConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10264220
			fight::ConditionFactory* CreateGPUFillConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GPUFillCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102642F0
			void RegisterGPUFillConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GPUFillCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<GPUFillCondition>;
			template class fight::ConditionFactoryTemplate<GPUFillCondition>;
			template class fight::ConditionFactoryCasterTemplate<GPUFillCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10264140
// FUNCTION: ENGINE 0x10264170
// FUNCTION: ENGINE 0x10264180
// FUNCTION: ENGINE 0x102641B0
// FUNCTION: ENGINE 0x102641E0
// FUNCTION: ENGINE 0x10264210
// FUNCTION: ENGINE 0x10264320
// FUNCTION: ENGINE 0x10264350
// FUNCTION: ENGINE 0x10264370
