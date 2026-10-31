// Fight items of the motion group: DetectedObjectFacingCondition, DetectedObjectAngleCondition, DetectedObjectDistanceCondition, DetectedObjectIsTargetCondition, DetectedObjectConditionGroupCondition, DetectedObjectIsSeenCondition, DetectTrack (unit 0x10154030 - 0x101561B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DETECT_H
#define PROTO_FIGHTITEMS_MOTION_DETECT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DetectedObjectFacingCondition (10 vftable slots, 0x14 bytes)
			class DetectedObjectFacingCondition : public fight::Condition
			{
			public:
				// 0x101542E0
				DetectedObjectFacingCondition();
				virtual ~DetectedObjectFacingCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B1A90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAngle(float newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					float arc;  // +0x10
			};

			extern fight::Property** gDetectedObjectFacingConditionProperties;
			fight::ConditionFactory* CreateDetectedObjectFacingConditionFactory(const char* name);
			void RegisterDetectedObjectFacingConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DetectedObjectAngleCondition (10 vftable slots, 0x18 bytes)
			class DetectedObjectAngleCondition : public fight::Condition
			{
			public:
				// 0x10154350
				DetectedObjectAngleCondition();
				virtual ~DetectedObjectAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B1CF0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);
				bool SetAngle(float newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					float arc;  // +0x10
					int type;  // +0x14
			};

			extern fight::Property** gDetectedObjectAngleConditionProperties;
			fight::ConditionFactory* CreateDetectedObjectAngleConditionFactory(const char* name);
			void RegisterDetectedObjectAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DetectedObjectDistanceCondition (10 vftable slots, 0x18 bytes)
			class DetectedObjectDistanceCondition : public fight::Condition
			{
			public:
				// 0x101543D0
				DetectedObjectDistanceCondition();
				virtual ~DetectedObjectDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B2080, another unit)
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

			extern fight::Property** gDetectedObjectDistanceConditionProperties;
			fight::ConditionFactory* CreateDetectedObjectDistanceConditionFactory(const char* name);
			void RegisterDetectedObjectDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DetectedObjectIsTargetCondition (10 vftable slots, 0x10 bytes)
			class DetectedObjectIsTargetCondition : public fight::Condition
			{
			public:
				// 0x10154450
				DetectedObjectIsTargetCondition();
				virtual ~DetectedObjectIsTargetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B19C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsTarget(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isTarget;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gDetectedObjectIsTargetConditionProperties;
			fight::ConditionFactory* CreateDetectedObjectIsTargetConditionFactory(const char* name);
			void RegisterDetectedObjectIsTargetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DetectedObjectConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class DetectedObjectConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x101544B0
				DetectedObjectConditionGroupCondition();
				virtual ~DetectedObjectConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B18A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gDetectedObjectConditionGroupConditionProperties;
			fight::ConditionFactory* CreateDetectedObjectConditionGroupConditionFactory(const char* name);
			void RegisterDetectedObjectConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DetectedObjectIsSeenCondition (10 vftable slots, 0x1C bytes)
			class DetectedObjectIsSeenCondition : public fight::Condition
			{
			public:
				// 0x10154530
				DetectedObjectIsSeenCondition();
				virtual ~DetectedObjectIsSeenCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B21B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSeen(bool newValue);
				bool SetMaxDistanceFactor(float newValue);
				bool SetMaxAngle(float newValue);
				bool SetOnlyMilitary(bool newValue);
				bool SetExcludeIfCantReport(bool newValue);
				bool SetMaxDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float maxAngle;  // +0xC
					float maxDistance;  // +0x10
					float maxDistanceFactor;  // +0x14
					bool excludeIfCantReport;  // +0x18
					bool onlyMilitary;  // +0x19
					bool seen;  // +0x1A
					unsigned char unknown1B[0x1];
			};

			extern fight::Property** gDetectedObjectIsSeenConditionProperties;
			fight::ConditionFactory* CreateDetectedObjectIsSeenConditionFactory(const char* name);
			void RegisterDetectedObjectIsSeenConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DetectTrack (16 vftable slots, 0x70 bytes)
			class DetectTrack : public fight::Track
			{
			public:
				// 0x10154710
				DetectTrack();
				virtual ~DetectTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B26D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetRadius(float newValue);
				bool SetArcOffset(float newValue);
				bool SetArcRange(float newValue);
				bool SetCollideWith(int newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name joint;  // +0x38
					math::Vector offset;  // +0x40
					fight::ConditionList conditions;  // +0x4C
					float arcOffset;  // +0x50
					float arcRange;  // +0x54
					float radius;  // +0x58
					float timeBegin;  // +0x5C
					float timeEnd;  // +0x60
					int priority;  // +0x64
					int collideWith;  // +0x68
					unsigned char unknown6C[0x4];
			};

			extern fight::Property** gDetectTrackProperties;
			fight::TrackFactory* CreateDetectTrackFactory(const char* name);
			void RegisterDetectTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
