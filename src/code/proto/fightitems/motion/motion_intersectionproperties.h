// Fight items of the motion group: IntersectionPropertiesCondition (unit 0x10181350 - 0x10181890; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_INTERSECTIONPROPERTIES_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_INTERSECTIONPROPERTIES_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::IntersectionPropertiesCondition (10 vftable slots, 0x18 bytes)
			class IntersectionPropertiesCondition : public fight::Condition
			{
			public:
				// 0x101813B0
				IntersectionPropertiesCondition();
				virtual ~IntersectionPropertiesCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100DB800, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);
				bool SetColliderBits(int newValue);
				bool SetMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int type;  // +0xC
					int colliderBits;  // +0x10
					bool match;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gIntersectionPropertiesConditionProperties;
			fight::ConditionFactory* CreateIntersectionPropertiesConditionFactory(const char* name);
			void RegisterIntersectionPropertiesConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
