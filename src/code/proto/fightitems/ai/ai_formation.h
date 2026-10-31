// Fight items of the ai group: InFormationCondition, FormationReformingCondition, FollowFormationTrack, FollowTargetTrack, ReformTrack (unit 0x10232390 - 0x102338F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_FORMATION_H
#define PROTO_FIGHTITEMS_AI_AI_FORMATION_H

#include "code/engine/fight/bitfieldproperty.h"
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

		}
	}
}

#endif
