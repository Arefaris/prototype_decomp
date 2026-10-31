// Fight items of the motion group: TargetDistanceCondition, TargetCanJumpToCondition, TargetDistanceWithOffsetCondition, AutoTargetDistanceCondition (unit 0x101BBFD0 - 0x101BD3C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_TARGETDISTANCE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_TARGETDISTANCE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::TargetDistanceCondition (10 vftable slots, 0x18 bytes)
			class TargetDistanceCondition : public fight::Condition
			{
			public:
				// 0x101BC190
				TargetDistanceCondition();
				virtual ~TargetDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011E660, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
			};

			extern fight::Property** gTargetDistanceConditionProperties;
			fight::ConditionFactory* CreateTargetDistanceConditionFactory(const char* name);
			void RegisterTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TargetCanJumpToCondition (10 vftable slots, 0x24 bytes)
			class TargetCanJumpToCondition : public fight::Condition
			{
			public:
				// 0x101BC210
				TargetCanJumpToCondition();
				virtual ~TargetCanJumpToCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011EB00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetLaunchAngle(float newValue);
				bool SetMinLaunchAngle(float newValue);
				bool SetGravity(float newValue);
				bool SetMaxInitialVelocity(float newValue);
				bool SetUseStoredValues(bool newValue);
				bool SetMargin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float gravity;  // +0xC
					float launchAngle;  // +0x10
					float margin;  // +0x14
					float maxInitialVelocity;  // +0x18
					float minLaunchAngle;  // +0x1C
					bool useStoredValues;  // +0x20
					unsigned char unknown21[0x3];
			};

			extern fight::Property** gTargetCanJumpToConditionProperties;
			fight::ConditionFactory* CreateTargetCanJumpToConditionFactory(const char* name);
			void RegisterTargetCanJumpToConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TargetDistanceWithOffsetCondition (10 vftable slots, 0x24 bytes)
			class TargetDistanceWithOffsetCondition : public fight::Condition
			{
			public:
				// 0x101BC2B0
				TargetDistanceWithOffsetCondition();
				virtual ~TargetDistanceWithOffsetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011E7D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);
				bool SetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0xC
					float distance;  // +0x18
					int compare;  // +0x1C
					int direction;  // +0x20
			};

			extern fight::Property** gTargetDistanceWithOffsetConditionProperties;
			fight::ConditionFactory* CreateTargetDistanceWithOffsetConditionFactory(const char* name);
			void RegisterTargetDistanceWithOffsetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AutoTargetDistanceCondition (10 vftable slots, 0x18 bytes)
			class AutoTargetDistanceCondition : public fight::Condition
			{
			public:
				// 0x101BC350
				AutoTargetDistanceCondition();
				virtual ~AutoTargetDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011E960, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
			};

			extern fight::Property** gAutoTargetDistanceConditionProperties;
			fight::ConditionFactory* CreateAutoTargetDistanceConditionFactory(const char* name);
			void RegisterAutoTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
