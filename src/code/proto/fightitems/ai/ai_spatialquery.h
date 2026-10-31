// Fight items of the ai group: SpatialQueryCondition, SoldierWithinDistanceCondition (unit 0x10249200 - 0x10249C30; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_SPATIALQUERY_H
#define PROTO_FIGHTITEMS_AI_AI_SPATIALQUERY_H

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
			// RTTI: proto::fightitems::ai::SpatialQueryCondition (10 vftable slots, 0x30 bytes)
			class SpatialQueryCondition : public fight::Condition
			{
			public:
				// 0x10249350
				SpatialQueryCondition();
				virtual ~SpatialQueryCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1020A680, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetWhat(int newValue);
				bool SetWhatData(const fight::Name& newValue);
				bool SetWhere(int newValue);
				bool SetMaxDistance(float newValue);
				bool SetExcludeSelf(bool newValue);
				bool SetCompare(int newValue);
				bool SetInside(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name whatData;  // +0x10
					float maxDistance;  // +0x18
					int compare;  // +0x1C
					int inside;  // +0x20
					int what;  // +0x24
					int where;  // +0x28
					bool excludeSelf;  // +0x2C
					unsigned char unknown2D[0x3];
			};

			extern fight::Property** gSpatialQueryConditionProperties;
			fight::ConditionFactory* CreateSpatialQueryConditionFactory(const char* name);
			void RegisterSpatialQueryConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SoldierWithinDistanceCondition (10 vftable slots, 0x10 bytes)
			class SoldierWithinDistanceCondition : public fight::Condition
			{
			public:
				// 0x102492F0
				SoldierWithinDistanceCondition();
				virtual ~SoldierWithinDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1020A370, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
			};

			extern fight::Property** gSoldierWithinDistanceConditionProperties;
			fight::ConditionFactory* CreateSoldierWithinDistanceConditionFactory(const char* name);
			void RegisterSoldierWithinDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
