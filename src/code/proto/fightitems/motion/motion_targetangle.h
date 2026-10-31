// Fight items of the motion group: TargetAngleCondition (unit 0x101BBA40 - 0x101BBFD0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_TARGETANGLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_TARGETANGLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction2.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::TargetAngleCondition (10 vftable slots, 0x1C bytes)
			class TargetAngleCondition : public fight::Condition
			{
			public:
				// 0x101BBAE0
				TargetAngleCondition();
				virtual ~TargetAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011E0B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompareTime(int newValue);
				bool SetAngle(float newValue);
				bool SetArc(float newValue);
				bool SetUseMovementDirection(bool newValue);
				bool SetUseInputDirection(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					float arc;  // +0x10
					int compareTime;  // +0x14
					bool useInputDirection;  // +0x18
					bool useMovementDirection;  // +0x19
					unsigned char unknown1A[0x2];
			};

			extern fight::Property** gTargetAngleConditionProperties;
			fight::ConditionFactory* CreateTargetAngleConditionFactory(const char* name);
			void RegisterTargetAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
