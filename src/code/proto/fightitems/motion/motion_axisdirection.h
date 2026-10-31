// Fight items of the motion group: AxisDirectionCondition (unit 0x10180EC0 - 0x10181350; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_AXISDIRECTION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_AXISDIRECTION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::AxisDirectionCondition (10 vftable slots, 0x18 bytes)
			class AxisDirectionCondition : public fight::Condition
			{
			public:
				// 0x10180F40
				AxisDirectionCondition();
				virtual ~AxisDirectionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100DB540, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAxis(int newValue);
				bool SetDirection(float newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float arc;  // +0xC
					float direction;  // +0x10
					int axis;  // +0x14
			};

			extern fight::Property** gAxisDirectionConditionProperties;
			fight::ConditionFactory* CreateAxisDirectionConditionFactory(const char* name);
			void RegisterAxisDirectionConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
