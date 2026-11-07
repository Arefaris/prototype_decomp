// Fight items of the ai group: InFormationCondition, FormationReformingCondition, FollowFormationTrack, FollowTargetTrack, ReformTrack (unit 0x10232390 - 0x102338F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_FORMATION_H
#define PROTO_FIGHTITEMS_AI_AI_FORMATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::InFormationCondition (10 vftable slots, 0x10 bytes)
			class InFormationCondition : public fight::Condition
			{
			public:
				// 0x102325F0
				InFormationCondition();
				virtual ~InFormationCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101F4220, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIn(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool in;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gInFormationConditionProperties;
			fight::ConditionFactory* CreateInFormationConditionFactory(const char* name);
			void RegisterInFormationConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::FormationReformingCondition (10 vftable slots, 0x10 bytes)
			class FormationReformingCondition : public fight::Condition
			{
			public:
				// 0x10232650
				FormationReformingCondition();
				virtual ~FormationReformingCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101F4360, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetReforming(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool reforming;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gFormationReformingConditionProperties;
			fight::ConditionFactory* CreateFormationReformingConditionFactory(const char* name);
			void RegisterFormationReformingConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::FollowFormationTrack (16 vftable slots, 0x30 bytes)
			class FollowFormationTrack : public fight::Track
			{
			public:
				// 0x102326B0
				FollowFormationTrack();
				virtual ~FollowFormationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F5BB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetAcceleration(float newValue);
				bool SetBrakingDeceleration(float newValue);
				bool SetExtraBrakingDistance(float newValue);
				bool SetLookAhead(float newValue);
				bool SetMaxVelocity(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float acceleration;  // +0x10
					float brakingDeceleration;  // +0x14
					float extraBrakingDistance;  // +0x18
					float lookAhead;  // +0x1C
					float maxVelocity;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float turningVelocity;  // +0x2C
			};

			extern fight::Property** gFollowFormationTrackProperties;
			fight::TrackFactory* CreateFollowFormationTrackFactory(const char* name);
			void RegisterFollowFormationTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::FollowTargetTrack (16 vftable slots, 0x28 bytes)
			class FollowTargetTrack : public fight::Track
			{
			public:
				// 0x10232790
				FollowTargetTrack();
				virtual ~FollowTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F5B60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMaxAngleFromTargetFacing(float newValue);
				bool SetMaxMotionLengthDelta(float newValue);
				bool SetMaxRotationDelta(float newValue);
				bool SetSmoothWithLast(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float maxAngleFromTargetFacing;  // +0x10
					float maxMotionLengthDelta;  // +0x14
					float maxRotationDelta;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					bool smoothWithLast;  // +0x24
					unsigned char unknown25[0x3];
			};

			extern fight::Property** gFollowTargetTrackProperties;
			fight::TrackFactory* CreateFollowTargetTrackFactory(const char* name);
			void RegisterFollowTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ReformTrack (16 vftable slots, 0x1C bytes)
			class ReformTrack : public fight::Track
			{
			public:
				// 0x10232860
				ReformTrack();
				virtual ~ReformTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F5C00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTolerance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					float tolerance;  // +0x18
			};

			extern fight::Property** gReformTrackProperties;
			fight::TrackFactory* CreateReformTrackFactory(const char* name);
			void RegisterReformTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::ai::FollowTargetAction (9 vftable slots, 0x4C bytes)
			class FollowTargetAction : public fight::Action
			{
			public:
				// 0x101F45C0
				FollowTargetAction(FollowTargetTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101F3FA0
				virtual ~FollowTargetAction();

				// vftable slot 5 (0x101F46C0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101F3B20)
				virtual void Slot6();
				// vftable slot 7 (0x101F47C0)
				virtual bool Slot7(int arg, float value);

				core::Link<FollowTargetTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				math::Vector unknown2C;  // +0x2C
				engine::GameObjectHandle unknown38;  // +0x38
				float unknown3C;  // +0x3C
				float unknown40;  // +0x40
				float unknown44;  // +0x44
				float unknown48;  // +0x48
			};
			// RTTI: proto::fightitems::ai::FollowFormationAction (9 vftable slots, 0x70 bytes)
			class FollowFormationAction : public fight::Action
			{
			public:
				// 0x101F4850
				FollowFormationAction(FollowFormationTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101F3FF0
				virtual ~FollowFormationAction();

				// vftable slot 5 (0x101F4020)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101F3C70)
				virtual void Slot6();
				// vftable slot 7 (0x101F4960)
				virtual bool Slot7(int arg, float value);

				core::Link<FollowFormationTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				unsigned char unknown2C[0xC];
				math::Vector unknown38;  // +0x38
				math::Vector unknown44;  // +0x44
				engine::HandleBase unknown50;  // +0x50
				unsigned char unknown54[0x8];
				int unknown5C;  // +0x5C
				unsigned char unknown60[0x8];
				int unknown68;  // +0x68
				bool unknown6C;  // +0x6C
				bool unknown6D;  // +0x6D
				unsigned char unknown6E[0x2];
			};
			// RTTI: proto::fightitems::ai::ReformAction (9 vftable slots, 0x40 bytes)
			class ReformAction : public fight::Action
			{
			public:
				// 0x101F5690
				ReformAction(ReformTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101F41F0
				virtual ~ReformAction();

				// vftable slot 5 (0x101F5C50)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101F5E30)
				virtual void Slot6();
				// vftable slot 7 (0x101F5760)
				virtual bool Slot7(int arg, float value);

				core::Link<ReformTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				math::Vector unknown2C;  // +0x2C
				engine::HandleBase unknown38;  // +0x38
				bool unknown3C;  // +0x3C
				unsigned char unknown3D[0x3];
			};
			// ---- actions end
		}
	}
}

#endif
