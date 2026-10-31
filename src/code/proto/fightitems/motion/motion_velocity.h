// Fight items of the motion group: VelocityYAngleCondition, VelocityAngleCondition (unit 0x101CB300 - 0x101CBD20; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_VELOCITY_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_VELOCITY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::VelocityYAngleCondition (10 vftable slots, 0x18 bytes)
			class VelocityYAngleCondition : public fight::Condition
			{
			public:
				// 0x101CB3D0
				VelocityYAngleCondition();
				virtual ~VelocityYAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1012BDF0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);
				bool SetCompare(int newValue);
				bool SetAngle(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					int compare;  // +0x10
					int type;  // +0x14
			};

			extern fight::Property** gVelocityYAngleConditionProperties;
			fight::ConditionFactory* CreateVelocityYAngleConditionFactory(const char* name);
			void RegisterVelocityYAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::VelocityAngleCondition (10 vftable slots, 0x1C bytes)
			class VelocityAngleCondition : public fight::Condition
			{
			public:
				// 0x101CB450
				VelocityAngleCondition();
				virtual ~VelocityAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1012BB60, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);
				bool SetCompareTime(int newValue);
				bool SetAngle(float newValue);
				bool SetXz(bool newValue);
				bool SetSigned(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					int compareTime;  // +0x10
					int type;  // +0x14
					bool signedValue;  // +0x18
					bool xz;  // +0x19
					unsigned char unknown1A[0x2];
			};

			extern fight::Property** gVelocityAngleConditionProperties;
			fight::ConditionFactory* CreateVelocityAngleConditionFactory(const char* name);
			void RegisterVelocityAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
