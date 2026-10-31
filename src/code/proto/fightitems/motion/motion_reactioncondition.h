// Fight items of the motion group: ReactionEventConditionGroupCondition, ReactionHitCollisionPositionCondition, ReactionHitDamageCondition, ReactionHitChargeCondition, ReactionHitOriginatorDistanceCondition, ReactionReceiverIsTargetCondition, ReactionGiverIsBeingGrabbedCondition, ReactionEventCondition, ReactionHitCollisionNormalCondition, ReactionScriptedSubTypeCondition, ReactionHitOriginatorIsPlayerCondition, ReactionGrabTypeCondition, ReactionHitSliceAngleCondition, ReactionHitFromMuscleMassCondition, ReactionHitCollisionFlagCondition, ReactionThrowHitTypeCondition, ReactionHitImpulseCondition, ReactionHitDamageTypeCondition, ReactionHitImpulseDirectionCondition, ReactionTargetCondition, ReactionHitAttackTypeCondition, ReactionHitHeightCondition, ReactionHitHitTypeCondition, ReactionHitImpulseYAngleCondition (unit 0x101A1160 - 0x101A69E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONCONDITION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONCONDITION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/fightitems/motion/motionreaction2.h"
#include "code/proto/fightitems/motion/motioncommon.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ReactionEventConditionGroupCondition (10 vftable slots, 0x14 bytes)
			class ReactionEventConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x101A14E0
				ReactionEventConditionGroupCondition();
				virtual ~ReactionEventConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106A80, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetObject(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
					int object;  // +0x10
			};

			extern fight::Property** gReactionEventConditionGroupConditionProperties;
			fight::ConditionFactory* CreateReactionEventConditionGroupConditionFactory(const char* name);
			void RegisterReactionEventConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitCollisionPositionCondition (10 vftable slots, 0x18 bytes)
			class ReactionHitCollisionPositionCondition : public fight::Condition
			{
			public:
				// 0x101A1560
				ReactionHitCollisionPositionCondition();
				virtual ~ReactionHitCollisionPositionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106F50, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetComponent(int newValue);
				bool SetCompare(int newValue);
				bool SetPosition(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float position;  // +0xC
					int compare;  // +0x10
					int component;  // +0x14
			};

			extern fight::Property** gReactionHitCollisionPositionConditionProperties;
			fight::ConditionFactory* CreateReactionHitCollisionPositionConditionFactory(const char* name);
			void RegisterReactionHitCollisionPositionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitDamageCondition (10 vftable slots, 0x18 bytes)
			class ReactionHitDamageCondition : public fight::Condition
			{
			public:
				// 0x101A15E0
				ReactionHitDamageCondition();
				virtual ~ReactionHitDamageCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106930, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);
				bool SetCompare(int newValue);
				bool SetDamage(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float damage;  // +0xC
					int compare;  // +0x10
					int type;  // +0x14
			};

			extern fight::Property** gReactionHitDamageConditionProperties;
			fight::ConditionFactory* CreateReactionHitDamageConditionFactory(const char* name);
			void RegisterReactionHitDamageConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitChargeCondition (10 vftable slots, 0x14 bytes)
			class ReactionHitChargeCondition : public fight::Condition
			{
			public:
				// 0x101A1660
				ReactionHitChargeCondition();
				virtual ~ReactionHitChargeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101069B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetCharge(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float charge;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gReactionHitChargeConditionProperties;
			fight::ConditionFactory* CreateReactionHitChargeConditionFactory(const char* name);
			void RegisterReactionHitChargeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitOriginatorDistanceCondition (10 vftable slots, 0x18 bytes)
			class ReactionHitOriginatorDistanceCondition : public fight::Condition
			{
			public:
				// 0x101A16D0
				ReactionHitOriginatorDistanceCondition();
				virtual ~ReactionHitOriginatorDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10107720, another unit)
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

			extern fight::Property** gReactionHitOriginatorDistanceConditionProperties;
			fight::ConditionFactory* CreateReactionHitOriginatorDistanceConditionFactory(const char* name);
			void RegisterReactionHitOriginatorDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionReceiverIsTargetCondition (10 vftable slots, 0x10 bytes)
			class ReactionReceiverIsTargetCondition : public fight::Condition
			{
			public:
				// 0x101A1750
				ReactionReceiverIsTargetCondition();
				virtual ~ReactionReceiverIsTargetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10107480, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsTarget(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isTarget;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gReactionReceiverIsTargetConditionProperties;
			fight::ConditionFactory* CreateReactionReceiverIsTargetConditionFactory(const char* name);
			void RegisterReactionReceiverIsTargetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionGiverIsBeingGrabbedCondition (10 vftable slots, 0x10 bytes)
			class ReactionGiverIsBeingGrabbedCondition : public fight::Condition
			{
			public:
				// 0x101A17B0
				ReactionGiverIsBeingGrabbedCondition();
				virtual ~ReactionGiverIsBeingGrabbedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101075D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int grabType;  // +0xC
			};

			extern fight::Property** gReactionGiverIsBeingGrabbedConditionProperties;
			fight::ConditionFactory* CreateReactionGiverIsBeingGrabbedConditionFactory(const char* name);
			void RegisterReactionGiverIsBeingGrabbedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionEventCondition (10 vftable slots, 0x14 bytes)
			class ReactionEventCondition : public fight::Condition
			{
			public:
				// 0x101A1820
				ReactionEventCondition();
				virtual ~ReactionEventCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106650, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsReactionEvent(bool newValue);
				bool SetReactionType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int reactionType;  // +0xC
					bool isReactionEvent;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gReactionEventConditionProperties;
			fight::ConditionFactory* CreateReactionEventConditionFactory(const char* name);
			void RegisterReactionEventConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitCollisionNormalCondition (10 vftable slots, 0x1C bytes)
			class ReactionHitCollisionNormalCondition : public fight::Condition
			{
			public:
				// 0x101A1890
				ReactionHitCollisionNormalCondition();
				virtual ~ReactionHitCollisionNormalCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106DE0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetNormal(const math::Vector& newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector normal;  // +0xC
					float arc;  // +0x18
			};

			extern fight::Property** gReactionHitCollisionNormalConditionProperties;
			fight::ConditionFactory* CreateReactionHitCollisionNormalConditionFactory(const char* name);
			void RegisterReactionHitCollisionNormalConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionScriptedSubTypeCondition (10 vftable slots, 0x18 bytes)
			class ReactionScriptedSubTypeCondition : public fight::Condition
			{
			public:
				// 0x101A2100
				ReactionScriptedSubTypeCondition();
				virtual ~ReactionScriptedSubTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106A50, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSubType(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name subType;  // +0x10
			};

			extern fight::Property** gReactionScriptedSubTypeConditionProperties;
			fight::ConditionFactory* CreateReactionScriptedSubTypeConditionFactory(const char* name);
			void RegisterReactionScriptedSubTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitOriginatorIsPlayerCondition (10 vftable slots, 0xC bytes)
			class ReactionHitOriginatorIsPlayerCondition : public fight::Condition
			{
			public:
				// 0x101A19B0
				ReactionHitOriginatorIsPlayerCondition();
				virtual ~ReactionHitOriginatorIsPlayerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101076C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gReactionHitOriginatorIsPlayerConditionProperties;
			fight::ConditionFactory* CreateReactionHitOriginatorIsPlayerConditionFactory(const char* name);
			void RegisterReactionHitOriginatorIsPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionGrabTypeCondition (10 vftable slots, 0x10 bytes)
			class ReactionGrabTypeCondition : public fight::Condition
			{
			public:
				// 0x101A1A10
				ReactionGrabTypeCondition();
				virtual ~ReactionGrabTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101067F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsGrabbed(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isGrabbed;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gReactionGrabTypeConditionProperties;
			fight::ConditionFactory* CreateReactionGrabTypeConditionFactory(const char* name);
			void RegisterReactionGrabTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitSliceAngleCondition (10 vftable slots, 0x14 bytes)
			class ReactionHitSliceAngleCondition : public fight::Condition
			{
			public:
				// 0x101A1A70
				ReactionHitSliceAngleCondition();
				virtual ~ReactionHitSliceAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10107210, another unit)
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

			extern fight::Property** gReactionHitSliceAngleConditionProperties;
			fight::ConditionFactory* CreateReactionHitSliceAngleConditionFactory(const char* name);
			void RegisterReactionHitSliceAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitFromMuscleMassCondition (10 vftable slots, 0x10 bytes)
			class ReactionHitFromMuscleMassCondition : public fight::Condition
			{
			public:
				// 0x101A1AF0
				ReactionHitFromMuscleMassCondition();
				virtual ~ReactionHitFromMuscleMassCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106700, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMuscleMassActive(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool muscleMassActive;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gReactionHitFromMuscleMassConditionProperties;
			fight::ConditionFactory* CreateReactionHitFromMuscleMassConditionFactory(const char* name);
			void RegisterReactionHitFromMuscleMassConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitCollisionFlagCondition (10 vftable slots, 0x20 bytes)
			class ReactionHitCollisionFlagCondition : public fight::Condition
			{
			public:
				// 0x101A2200
				ReactionHitCollisionFlagCondition();
				virtual ~ReactionHitCollisionFlagCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101068E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCollisionFlag(const fight::Name& newValue);
				bool SetDoesMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name collisionFlag;  // +0x10
					bool doesMatch;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gReactionHitCollisionFlagConditionProperties;
			fight::ConditionFactory* CreateReactionHitCollisionFlagConditionFactory(const char* name);
			void RegisterReactionHitCollisionFlagConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionThrowHitTypeCondition (10 vftable slots, 0x20 bytes)
			class ReactionThrowHitTypeCondition : public fight::Condition
			{
			public:
				// 0x101A2240
				ReactionThrowHitTypeCondition();
				virtual ~ReactionThrowHitTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101068A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDoesMatch(bool newValue);
				bool SetHitType(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name hitType;  // +0x10
					bool doesMatch;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gReactionThrowHitTypeConditionProperties;
			fight::ConditionFactory* CreateReactionThrowHitTypeConditionFactory(const char* name);
			void RegisterReactionThrowHitTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitImpulseCondition (10 vftable slots, 0x18 bytes)
			class ReactionHitImpulseCondition : public fight::Condition
			{
			public:
				// 0x101A1BB0
				ReactionHitImpulseCondition();
				virtual ~ReactionHitImpulseCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106770, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetImpulse(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float impulse;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
			};

			extern fight::Property** gReactionHitImpulseConditionProperties;
			fight::ConditionFactory* CreateReactionHitImpulseConditionFactory(const char* name);
			void RegisterReactionHitImpulseConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitDamageTypeCondition (10 vftable slots, 0x14 bytes)
			class ReactionHitDamageTypeCondition : public fight::Condition
			{
			public:
				// 0x101A1C30
				ReactionHitDamageTypeCondition();
				virtual ~ReactionHitDamageTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106730, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDoesMatch(bool newValue);
				bool SetDamageType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int damageType;  // +0xC
					bool doesMatch;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gReactionHitDamageTypeConditionProperties;
			fight::ConditionFactory* CreateReactionHitDamageTypeConditionFactory(const char* name);
			void RegisterReactionHitDamageTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitImpulseDirectionCondition (10 vftable slots, 0x14 bytes)
			class ReactionHitImpulseDirectionCondition : public fight::Condition
			{
			public:
				// 0x101A1CA0
				ReactionHitImpulseDirectionCondition();
				virtual ~ReactionHitImpulseDirectionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10107120, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(float newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float arc;  // +0xC
					float direction;  // +0x10
			};

			extern fight::Property** gReactionHitImpulseDirectionConditionProperties;
			fight::ConditionFactory* CreateReactionHitImpulseDirectionConditionFactory(const char* name);
			void RegisterReactionHitImpulseDirectionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionTargetCondition (10 vftable slots, 0x10 bytes)
			class ReactionTargetCondition : public fight::Condition
			{
			public:
				// 0x101A1D20
				ReactionTargetCondition();
				virtual ~ReactionTargetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106BD0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDoesMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool doesMatch;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gReactionTargetConditionProperties;
			fight::ConditionFactory* CreateReactionTargetConditionFactory(const char* name);
			void RegisterReactionTargetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitAttackTypeCondition (10 vftable slots, 0x14 bytes)
			class ReactionHitAttackTypeCondition : public fight::Condition
			{
			public:
				// 0x101A1D80
				ReactionHitAttackTypeCondition();
				virtual ~ReactionHitAttackTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101066C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDoesMatch(bool newValue);
				bool SetAttackType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int attackType;  // +0xC
					bool doesMatch;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gReactionHitAttackTypeConditionProperties;
			fight::ConditionFactory* CreateReactionHitAttackTypeConditionFactory(const char* name);
			void RegisterReactionHitAttackTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitHeightCondition (10 vftable slots, 0x14 bytes)
			class ReactionHitHeightCondition : public fight::Condition
			{
			public:
				// 0x101A1DF0
				ReactionHitHeightCondition();
				virtual ~ReactionHitHeightCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106D20, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetHeight(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float height;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gReactionHitHeightConditionProperties;
			fight::ConditionFactory* CreateReactionHitHeightConditionFactory(const char* name);
			void RegisterReactionHitHeightConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitHitTypeCondition (10 vftable slots, 0x20 bytes)
			class ReactionHitHitTypeCondition : public fight::Condition
			{
			public:
				// 0x101A23A0
				ReactionHitHitTypeCondition();
				virtual ~ReactionHitHitTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10106860, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDoesMatch(bool newValue);
				bool SetHitType(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name hitType;  // +0x10
					bool doesMatch;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gReactionHitHitTypeConditionProperties;
			fight::ConditionFactory* CreateReactionHitHitTypeConditionFactory(const char* name);
			void RegisterReactionHitHitTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitImpulseYAngleCondition (10 vftable slots, 0x14 bytes)
			class ReactionHitImpulseYAngleCondition : public fight::Condition
			{
			public:
				// 0x101A1E90
				ReactionHitImpulseYAngleCondition();
				virtual ~ReactionHitImpulseYAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10107390, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetAngle(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gReactionHitImpulseYAngleConditionProperties;
			fight::ConditionFactory* CreateReactionHitImpulseYAngleConditionFactory(const char* name);
			void RegisterReactionHitImpulseYAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
