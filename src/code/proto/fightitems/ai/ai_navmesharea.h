// Fight items of the ai group: NavMeshAreaCondition (unit 0x102432A0 - 0x10243760; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_NAVMESHAREA_H
#define PROTO_FIGHTITEMS_AI_AI_NAVMESHAREA_H

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
			// RTTI: proto::fightitems::ai::NavMeshAreaCondition (10 vftable slots, 0x18 bytes)
			class NavMeshAreaCondition : public fight::Condition
			{
			public:
				// 0x10243320
				NavMeshAreaCondition();
				virtual ~NavMeshAreaCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10204C40, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAllowedAreas(int newValue);
				bool SetVerticalTolerance(float newValue);
				bool SetRayIfNotSupported(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float rayIfNotSupported;  // +0xC
					float verticalTolerance;  // +0x10
					int allowedAreas;  // +0x14
			};

			extern fight::Property** gNavMeshAreaConditionProperties;
			fight::ConditionFactory* CreateNavMeshAreaConditionFactory(const char* name);
			void RegisterNavMeshAreaConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
