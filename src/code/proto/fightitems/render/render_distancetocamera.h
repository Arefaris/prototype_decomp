// Fight items of the render group: DistanceToCameraCondition (unit 0x10262C90 - 0x102630C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_RENDER_RENDER_DISTANCETOCAMERA_H
#define PROTO_FIGHTITEMS_RENDER_RENDER_DISTANCETOCAMERA_H

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
			// RTTI: proto::fightitems::render::DistanceToCameraCondition (10 vftable slots, 0x14 bytes)
			class DistanceToCameraCondition : public fight::Condition
			{
			public:
				// 0x10262CF0
				DistanceToCameraCondition();
				virtual ~DistanceToCameraCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102608B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gDistanceToCameraConditionProperties;
			fight::ConditionFactory* CreateDistanceToCameraConditionFactory(const char* name);
			void RegisterDistanceToCameraConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
