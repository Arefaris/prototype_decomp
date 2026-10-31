// Fight items of the motion group: JointOrientationCondition (unit 0x10183A80 - 0x10184060; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JOINTORIENTATION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JOINTORIENTATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::JointOrientationCondition (10 vftable slots, 0x38 bytes)
			class JointOrientationCondition : public fight::Condition
			{
			public:
				// 0x10183B40
				JointOrientationCondition();
				virtual ~JointOrientationCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100DEDC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetJoint(const fight::Name& newValue);
				bool SetFacing(const math::Vector& newValue);
				bool SetUp(const math::Vector& newValue);
				bool SetThreshold(float newValue);
				bool SetMatchFacing(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name joint;  // +0x10
					math::Vector facing;  // +0x18
					math::Vector up;  // +0x24
					float threshold;  // +0x30
					bool matchFacing;  // +0x34
					unsigned char unknown35[0x3];
			};

			extern fight::Property** gJointOrientationConditionProperties;
			fight::ConditionFactory* CreateJointOrientationConditionFactory(const char* name);
			void RegisterJointOrientationConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
