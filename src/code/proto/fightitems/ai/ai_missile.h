// Fight items of the ai group: IsMissileTargetingPlayerCondition (unit 0x1021C6F0 - 0x1021C920; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_MISSILE_H
#define PROTO_FIGHTITEMS_AI_AI_MISSILE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::IsMissileTargetingPlayerCondition (10 vftable slots, 0xC bytes)
			class IsMissileTargetingPlayerCondition : public fight::Condition
			{
			public:
				// 0x1021C780
				IsMissileTargetingPlayerCondition();
				virtual ~IsMissileTargetingPlayerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101DF9B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gIsMissileTargetingPlayerConditionProperties;
			fight::ConditionFactory* CreateIsMissileTargetingPlayerConditionFactory(const char* name);
			void RegisterIsMissileTargetingPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
