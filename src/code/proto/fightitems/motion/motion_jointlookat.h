// Fight items of the motion group: JointLookAtCondition, JointLookAtTrack (unit 0x101827B0 - 0x10183A80; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JOINTLOOKAT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JOINTLOOKAT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::JointLookAtCondition (10 vftable slots, 0x38 bytes)
			class JointLookAtCondition : public fight::Condition
			{
			public:
				// 0x10182AF0
				JointLookAtCondition();
				virtual ~JointLookAtCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100DD9B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetJoint(const fight::Name& newValue);
				bool SetHeading(const math::Vector& newValue);
				bool SetPrimaryRotationAxis(const math::Vector& newValue);
				bool SetPrimaryAngleMin(float newValue);
				bool SetPrimaryAngleMax(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name joint;  // +0x10
					math::Vector heading;  // +0x18
					math::Vector primaryRotationAxis;  // +0x24
					float primaryAngleMax;  // +0x30
					float primaryAngleMin;  // +0x34
			};

			extern fight::Property** gJointLookAtConditionProperties;
			fight::ConditionFactory* CreateJointLookAtConditionFactory(const char* name);
			void RegisterJointLookAtConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::JointLookAtTrack (16 vftable slots, 0x78 bytes)
			class JointLookAtTrack : public fight::Track
			{
			public:
				// 0x10182B90
				JointLookAtTrack();
				virtual ~JointLookAtTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DED00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetHeading(const math::Vector& newValue);
				bool SetPrimaryRotationAxis(const math::Vector& newValue);
				bool SetPrimaryTurnRate(float newValue);
				bool SetPrimaryAngleMin(float newValue);
				bool SetPrimaryAngleMax(float newValue);
				bool SetSecondaryTurnRate(float newValue);
				bool SetSecondaryAngleMin(float newValue);
				bool SetSecondaryAngleMax(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetUseGrabSlot(const fight::Name& newValue);
				bool SetWhere(int newValue);
				bool SetUseAutoTarget(bool newValue);
				bool SetUseIntentionWhenNoTarget(bool newValue);
				bool SetUseFreeAimWhenNoTarget(bool newValue);
				bool SetUseLocalAngelsInIntention(bool newValue);
				bool SetTargetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					fight::Name useGrabSlot;  // +0x18
					math::Vector heading;  // +0x20
					math::Vector primaryRotationAxis;  // +0x2C
					math::Vector targetOffset;  // +0x38
					float blendInTime;  // +0x44
					float blendOutTime;  // +0x48
					float primaryAngleMax;  // +0x4C
					float primaryAngleMin;  // +0x50
					float primaryTurnRate;  // +0x54
					float secondaryAngleMax;  // +0x58
					float secondaryAngleMin;  // +0x5C
					float secondaryTurnRate;  // +0x60
					float timeBegin;  // +0x64
					float timeEnd;  // +0x68
					int priority;  // +0x6C
					int where;  // +0x70
					bool useAutoTarget;  // +0x74
					bool useFreeAimWhenNoTarget;  // +0x75
					bool useIntentionWhenNoTarget;  // +0x76
					bool useLocalAngelsInIntention;  // +0x77
			};

			extern fight::Property** gJointLookAtTrackProperties;
			fight::TrackFactory* CreateJointLookAtTrackFactory(const char* name);
			void RegisterJointLookAtTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
