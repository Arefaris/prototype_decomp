// Fight items of the motion group: InsidePlaneCondition, DistanceToJointCondition (unit 0x10159C60 - 0x1015A810; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DISTANCE_H
#define PROTO_FIGHTITEMS_MOTION_DISTANCE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::InsidePlaneCondition (10 vftable slots, 0x40 bytes)
			class InsidePlaneCondition : public fight::Condition
			{
			public:
				// 0x10159E10
				InsidePlaneCondition();
				virtual ~InsidePlaneCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B8270, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetInside(bool newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetOrientation(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					fight::Name joint;  // +0x18
					math::Vector offset;  // +0x20
					math::Vector orientation;  // +0x2C
					bool inside;  // +0x38
					unsigned char unknown39[0x7];
			};

			extern fight::Property** gInsidePlaneConditionProperties;
			fight::ConditionFactory* CreateInsidePlaneConditionFactory(const char* name);
			void RegisterInsidePlaneConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DistanceToJointCondition (10 vftable slots, 0x38 bytes)
			class DistanceToJointCondition : public fight::Condition
			{
			public:
				// 0x10159E80
				DistanceToJointCondition();
				virtual ~DistanceToJointCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B7B10, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetJoint(const fight::Name& newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);
				bool SetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					fight::Name joint;  // +0x18
					math::Vector offset;  // +0x20
					float distance;  // +0x2C
					int compare;  // +0x30
					unsigned char unknown34[0x4];
			};

			extern fight::Property** gDistanceToJointConditionProperties;
			fight::ConditionFactory* CreateDistanceToJointConditionFactory(const char* name);
			void RegisterDistanceToJointConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
