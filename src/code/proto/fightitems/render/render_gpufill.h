// Fight items of the render group: GPUFillCondition (unit 0x102640B0 - 0x102643C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_RENDER_RENDER_GPUFILL_H
#define PROTO_FIGHTITEMS_RENDER_RENDER_GPUFILL_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/render/renderdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace render
		{
			// RTTI: proto::fightitems::render::GPUFillCondition (10 vftable slots, 0x10 bytes)
			class GPUFillCondition : public fight::Condition
			{
			public:
				// 0x10264100
				GPUFillCondition();
				virtual ~GPUFillCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102612E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetRatio(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float ratio;  // +0xC
			};

			extern fight::Property** gGPUFillConditionProperties;
			fight::ConditionFactory* CreateGPUFillConditionFactory(const char* name);
			void RegisterGPUFillConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
