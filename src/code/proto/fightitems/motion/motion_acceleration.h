// Fight items of the motion group: AccelerationCondition (unit 0x1013C010 - 0x1013C5B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_ACCELERATION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_ACCELERATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::AccelerationCondition (10 vftable slots, 0x1C bytes)
			class AccelerationCondition : public fight::Condition
			{
			public:
				// 0x1013C0A0
				AccelerationCondition();
				virtual ~AccelerationCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10094730, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetAcceleration(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float acceleration;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
					int type;  // +0x18
			};

			extern fight::Property** gAccelerationConditionProperties;
			fight::ConditionFactory* CreateAccelerationConditionFactory(const char* name);

		}

		void RegisterAccelerationFactory(fight::TrackRegistry* registry, const char* name);
	}
}

#endif
