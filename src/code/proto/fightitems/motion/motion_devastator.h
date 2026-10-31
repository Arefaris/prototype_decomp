// Fight items of the motion group: DevastatorTargetConditionGroupCondition, DevastatorAvailableCondition, DevastatorTargetDistanceCondition, DevastatorTargetGroundSpikeTrack, DevastatorTrack, DevastatorUsedTrack, DevastatorTargetExecuteTrack, TendrilDevastatorTrack, DevastatorTargetHitTrack (unit 0x101561B0 - 0x101598C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DEVASTATOR_H
#define PROTO_FIGHTITEMS_MOTION_DEVASTATOR_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DevastatorTargetConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class DevastatorTargetConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x10156810
				DevastatorTargetConditionGroupCondition();
				virtual ~DevastatorTargetConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B2CD0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gDevastatorTargetConditionGroupConditionProperties;
			fight::ConditionFactory* CreateDevastatorTargetConditionGroupConditionFactory(const char* name);
			void RegisterDevastatorTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DevastatorAvailableCondition (10 vftable slots, 0x10 bytes)
			class DevastatorAvailableCondition : public fight::Condition
			{
			public:
				// 0x10156890
				DevastatorAvailableCondition();
				virtual ~DevastatorAvailableCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B3C60, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAvailable(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool available;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gDevastatorAvailableConditionProperties;
			fight::ConditionFactory* CreateDevastatorAvailableConditionFactory(const char* name);
			void RegisterDevastatorAvailableConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DevastatorTargetDistanceCondition (10 vftable slots, 0x18 bytes)
			class DevastatorTargetDistanceCondition : public fight::Condition
			{
			public:
				// 0x101568F0
				DevastatorTargetDistanceCondition();
				virtual ~DevastatorTargetDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B3B10, another unit)
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

			extern fight::Property** gDevastatorTargetDistanceConditionProperties;
			fight::ConditionFactory* CreateDevastatorTargetDistanceConditionFactory(const char* name);
			void RegisterDevastatorTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DevastatorTargetGroundSpikeTrack (16 vftable slots, 0x28 bytes)
			class DevastatorTargetGroundSpikeTrack : public fight::Track
			{
			public:
				// 0x10156F40
				DevastatorTargetGroundSpikeTrack();
				virtual ~DevastatorTargetGroundSpikeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B75A0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTemplate(const fight::Name& newValue);
				bool SetParameter(int newValue);
				bool SetRandom(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name templateValue;  // +0x10
					float timeBegin;  // +0x18
					int parameter;  // +0x1C
					bool random;  // +0x20
					unsigned char unknown21[0x7];
			};

			extern fight::Property** gDevastatorTargetGroundSpikeTrackProperties;
			fight::TrackFactory* CreateDevastatorTargetGroundSpikeTrackFactory(const char* name);
			void RegisterDevastatorTargetGroundSpikeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DevastatorTrack (16 vftable slots, 0xB4 bytes)
			class DevastatorTrack : public fight::Track
			{
			public:
				// 0x101569A0
				DevastatorTrack();
				virtual ~DevastatorTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B75F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRadius(float newValue);
				bool SetTargetCount(int newValue);
				fight::BranchHolder* SetTargetBranch();
				fight::BranchHolder* SetRandomTargetBranch();
				bool SetMinTargetCount(int newValue);
				bool SetRandomHeightArc(float newValue);
				bool SetRandomMinRadius(float newValue);
				bool SetMinHeightArcOnGround(float newValue);
				bool SetMinTargetCategory(int newValue);
				bool SetMinTargetPriority(int newValue);
				bool SetAttackTimeBeginStart(float newValue);
				bool SetAttackTimeBeginStop(float newValue);
				bool SetAttackTimeBeginRandom(bool newValue);
				bool SetAttackTimeDuration(float newValue);
				bool SetAttackDamage(float newValue);
				bool SetRandomDamage(float newValue);
				bool SetCameraMaxArc(float newValue);
				bool SetCameraMaxTargets(int newValue);
				bool SetCameraMinTargetCategory(int newValue);
				bool SetCameraMinTargetPriority(int newValue);
				bool SetCameraLookAtTargetArc(float newValue);
				bool SetCameraLookAtTargetTime(float newValue);
				bool SetCameraSwitchTargetTime(float newValue);
				bool SetUseCharacterHeap(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder randomTargetBranch;  // +0x10
					fight::BranchHolder targetBranch;  // +0x34
					float attackDamage;  // +0x58
					float attackTimeBeginStart;  // +0x5C
					float attackTimeBeginStop;  // +0x60
					float attackTimeDuration;  // +0x64
					float cameraLookAtTargetArc;  // +0x68
					float cameraLookAtTargetTime;  // +0x6C
					float cameraMaxArc;  // +0x70
					float cameraSwitchTargetTime;  // +0x74
					float minHeightArcOnGround;  // +0x78
					float radius;  // +0x7C
					float randomDamage;  // +0x80
					float randomHeightArc;  // +0x84
					float randomMinRadius;  // +0x88
					float timeBegin;  // +0x8C
					float timeEnd;  // +0x90
					int cameraMaxTargets;  // +0x94
					int cameraMinTargetCategory;  // +0x98
					int cameraMinTargetPriority;  // +0x9C
					int minTargetCategory;  // +0xA0
					int minTargetCount;  // +0xA4
					int minTargetPriority;  // +0xA8
					int targetCount;  // +0xAC
					bool attackTimeBeginRandom;  // +0xB0
					bool useCharacterHeap;  // +0xB1
					unsigned char unknownB2[0x2];
			};

			extern fight::Property** gDevastatorTrackProperties;
			fight::TrackFactory* CreateDevastatorTrackFactory(const char* name);
			void RegisterDevastatorTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DevastatorUsedTrack (16 vftable slots, 0x14 bytes)
			class DevastatorUsedTrack : public fight::Track
			{
			public:
				// 0x10156B80
				DevastatorUsedTrack();
				virtual ~DevastatorUsedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B3400, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gDevastatorUsedTrackProperties;
			fight::TrackFactory* CreateDevastatorUsedTrackFactory(const char* name);
			void RegisterDevastatorUsedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DevastatorTargetExecuteTrack (16 vftable slots, 0x44 bytes)
			class DevastatorTargetExecuteTrack : public fight::Track
			{
			public:
				// 0x10156C10
				DevastatorTargetExecuteTrack();
				virtual ~DevastatorTargetExecuteTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B7500, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetUseAttackTimeBegin(bool newValue);
				bool SetUseAttackTimeEnd(bool newValue);
				bool SetSetTarget(bool newValue);
				fight::BranchHolder* SetReceiverBranch();
				bool SetInterruptPriority(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder receiverBranch;  // +0x10
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
					int interruptPriority;  // +0x3C
					bool setTarget;  // +0x40
					bool useAttackTimeBegin;  // +0x41
					bool useAttackTimeEnd;  // +0x42
					unsigned char unknown43[0x1];
			};

			extern fight::Property** gDevastatorTargetExecuteTrackProperties;
			fight::TrackFactory* CreateDevastatorTargetExecuteTrackFactory(const char* name);
			void RegisterDevastatorTargetExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TendrilDevastatorTrack (16 vftable slots, 0x54 bytes)
			class TendrilDevastatorTrack : public fight::Track
			{
			public:
				// 0x10156CE0
				TendrilDevastatorTrack();
				virtual ~TendrilDevastatorTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B70D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDistance(float newValue);
				fight::BranchHolder* SetTargetBranch();
				bool SetTendrilCount(int newValue);
				bool SetAttackTimeBegin(float newValue);
				bool SetAttackTimeDuration(float newValue);
				bool SetAttackType(int newValue);
				bool SetAttackDamage(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder targetBranch;  // +0x10
					float attackDamage;  // +0x34
					float attackTimeBegin;  // +0x38
					float attackTimeDuration;  // +0x3C
					float distance;  // +0x40
					float timeBegin;  // +0x44
					float timeEnd;  // +0x48
					int attackType;  // +0x4C
					int tendrilCount;  // +0x50
			};

			extern fight::Property** gTendrilDevastatorTrackProperties;
			fight::TrackFactory* CreateTendrilDevastatorTrackFactory(const char* name);
			void RegisterTendrilDevastatorTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DevastatorTargetHitTrack (16 vftable slots, 0x34 bytes)
			class DevastatorTargetHitTrack : public fight::Track
			{
			public:
				// 0x10156DF0
				DevastatorTargetHitTrack();
				virtual ~DevastatorTargetHitTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B7550, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetUseAttackTimeBegin(bool newValue);
				bool SetUseAttackTimeEnd(bool newValue);
				bool SetDamage(float newValue);
				bool SetImpulse(const math::Vector& newValue);
				bool SetAttackType(int newValue);
				bool SetDamageType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector impulse;  // +0x10
					float damage;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					int attackType;  // +0x28
					int damageType;  // +0x2C
					bool useAttackTimeBegin;  // +0x30
					bool useAttackTimeEnd;  // +0x31
					unsigned char unknown32[0x2];
			};

			extern fight::Property** gDevastatorTargetHitTrackProperties;
			fight::TrackFactory* CreateDevastatorTargetHitTrackFactory(const char* name);
			void RegisterDevastatorTargetHitTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
