// Fight items of the ai group: NearRoofsEdgeCondition, AtRoofsEdgeCondition (unit 0x10246F80 - 0x10247690; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_ROOFSEDGE_H
#define PROTO_FIGHTITEMS_AI_AI_ROOFSEDGE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::NearRoofsEdgeCondition (10 vftable slots, 0x10 bytes)
			class NearRoofsEdgeCondition : public fight::Condition
			{
			public:
				// 0x10246FF0
				NearRoofsEdgeCondition();
				virtual ~NearRoofsEdgeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10208B90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetNearEdge(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool nearEdge;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gNearRoofsEdgeConditionProperties;
			fight::ConditionFactory* CreateNearRoofsEdgeConditionFactory(const char* name);
			void RegisterNearRoofsEdgeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AtRoofsEdgeCondition (10 vftable slots, 0x14 bytes)
			class AtRoofsEdgeCondition : public fight::Condition
			{
			public:
				// 0x10247050
				AtRoofsEdgeCondition();
				virtual ~AtRoofsEdgeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10208AC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetTimeAtEdge(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeAtEdge;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gAtRoofsEdgeConditionProperties;
			fight::ConditionFactory* CreateAtRoofsEdgeConditionFactory(const char* name);
			void RegisterAtRoofsEdgeConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
