// Fight items of the ai group: ThreatCondition, ThreatInMemoryCondition, ThreatCanSeeCondition, LastThreatConditionGroupCondition, ThreatCanGrabCondition, ThreatStoreCondition, ThreatBallTrack, ThreatDodgeTrack, ThreatMemoryResetTrack, ThreatSendToTargetTrack (unit 0x10253340 - 0x10255E00; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_THREAT_H
#define PROTO_FIGHTITEMS_AI_AI_THREAT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::ThreatCondition (10 vftable slots, 0x18 bytes)
			class ThreatCondition : public fight::Condition
			{
			public:
				// 0x102539A0
				ThreatCondition();
				virtual ~ThreatCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10218020, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name name;  // +0x10
			};

			extern fight::Property** gThreatConditionProperties;
			fight::ConditionFactory* CreateThreatConditionFactory(const char* name);
			void RegisterThreatConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ThreatInMemoryCondition (10 vftable slots, 0xC bytes)
			class ThreatInMemoryCondition : public fight::Condition
			{
			public:
				// 0x10253620
				ThreatInMemoryCondition();
				virtual ~ThreatInMemoryCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102181E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gThreatInMemoryConditionProperties;
			fight::ConditionFactory* CreateThreatInMemoryConditionFactory(const char* name);
			void RegisterThreatInMemoryConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ThreatCanSeeCondition (10 vftable slots, 0x30 bytes)
			class ThreatCanSeeCondition : public fight::Condition
			{
			public:
				// 0x10253A10
				ThreatCanSeeCondition();
				virtual ~ThreatCanSeeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10218930, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetName(const fight::Name& newValue);
				bool SetFOV(float newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetIgnoreY(bool newValue);
				bool SetGiversPerspective(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name name;  // +0x10
					math::Vector direction;  // +0x18
					float fOV;  // +0x24
					bool giversPerspective;  // +0x28
					bool ignoreY;  // +0x29
					unsigned char unknown2A[0x6];
			};

			extern fight::Property** gThreatCanSeeConditionProperties;
			fight::ConditionFactory* CreateThreatCanSeeConditionFactory(const char* name);
			void RegisterThreatCanSeeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::LastThreatConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class LastThreatConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x102536B0
				LastThreatConditionGroupCondition();
				virtual ~LastThreatConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10218E30, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gLastThreatConditionGroupConditionProperties;
			fight::ConditionFactory* CreateLastThreatConditionGroupConditionFactory(const char* name);
			void RegisterLastThreatConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ThreatCanGrabCondition (10 vftable slots, 0x20 bytes)
			class ThreatCanGrabCondition : public fight::Condition
			{
			public:
				// 0x10253AB0
				ThreatCanGrabCondition();
				virtual ~ThreatCanGrabCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102183F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetName(const fight::Name& newValue);
				bool SetSetGrabTarget(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name name;  // +0x10
					bool setGrabTarget;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gThreatCanGrabConditionProperties;
			fight::ConditionFactory* CreateThreatCanGrabConditionFactory(const char* name);
			void RegisterThreatCanGrabConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ThreatStoreCondition (10 vftable slots, 0x20 bytes)
			class ThreatStoreCondition : public fight::Condition
			{
			public:
				// 0x10253AF0
				ThreatStoreCondition();
				virtual ~ThreatStoreCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102186B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetName(const fight::Name& newValue);
				bool SetThreatObject(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name name;  // +0x10
					int threatObject;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gThreatStoreConditionProperties;
			fight::ConditionFactory* CreateThreatStoreConditionFactory(const char* name);
			void RegisterThreatStoreConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ThreatBallTrack (16 vftable slots, 0x40 bytes)
			class ThreatBallTrack : public fight::Track
			{
			public:
				// 0x10253B30
				ThreatBallTrack();
				virtual ~ThreatBallTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10219930, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetRadius(float newValue);
				bool SetTimeToLive(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetThreatName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					fight::Name threatName;  // +0x18
					math::Vector offset;  // +0x20
					float radius;  // +0x2C
					float timeBegin;  // +0x30
					float timeEnd;  // +0x34
					float timeToLive;  // +0x38
					unsigned char unknown3C[0x4];
			};

			extern fight::Property** gThreatBallTrackProperties;
			fight::TrackFactory* CreateThreatBallTrackFactory(const char* name);
			void RegisterThreatBallTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ThreatDodgeTrack (16 vftable slots, 0x58 bytes)
			class ThreatDodgeTrack : public fight::Track
			{
			public:
				// 0x10253BD0
				ThreatDodgeTrack();
				virtual ~ThreatDodgeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10219B90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDistanceToThreat(float newValue);
				bool SetName(const fight::Name& newValue);
				fight::BranchHolder* SetDodgeBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder dodgeBranch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name name;  // +0x38
					fight::ConditionList conditions;  // +0x40
					float distanceToThreat;  // +0x44
					float timeBegin;  // +0x48
					float timeEnd;  // +0x4C
					int priority;  // +0x50
					unsigned char unknown54[0x4];
			};

			extern fight::Property** gThreatDodgeTrackProperties;
			fight::TrackFactory* CreateThreatDodgeTrackFactory(const char* name);
			void RegisterThreatDodgeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ThreatMemoryResetTrack (16 vftable slots, 0x14 bytes)
			class ThreatMemoryResetTrack : public fight::Track
			{
			public:
				// 0x102537F0
				ThreatMemoryResetTrack();
				virtual ~ThreatMemoryResetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10219AF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gThreatMemoryResetTrackProperties;
			fight::TrackFactory* CreateThreatMemoryResetTrackFactory(const char* name);
			void RegisterThreatMemoryResetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ThreatSendToTargetTrack (16 vftable slots, 0x28 bytes)
			class ThreatSendToTargetTrack : public fight::Track
			{
			public:
				// 0x10253CC0
				ThreatSendToTargetTrack();
				virtual ~ThreatSendToTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10219B40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetThreatName(const fight::Name& newValue);
				bool SetThrownObjectFromGrabSlot(const fight::Name& newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name threatName;  // +0x10
					fight::Name thrownObjectFromGrabSlot;  // +0x18
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
			};

			extern fight::Property** gThreatSendToTargetTrackProperties;
			fight::TrackFactory* CreateThreatSendToTargetTrackFactory(const char* name);
			void RegisterThreatSendToTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::ThreatMemoryResetAction (9 vftable slots, 0x2C bytes)
			class ThreatMemoryResetAction : public fight::Action
			{
			public:
				// 0x10219400
				ThreatMemoryResetAction(ThreatMemoryResetTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10217DD0
				virtual ~ThreatMemoryResetAction();

				// vftable slot 5 (0x10217E00)
				virtual bool Slot5(int arg, float value);

				core::Link<ThreatMemoryResetTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
