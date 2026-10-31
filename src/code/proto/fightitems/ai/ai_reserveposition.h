// Fight items of the ai group: CanGunButtCondition, ReservePositionTrack, CommanderInCombatTrack, EngageTrack, ReserveHydraPositionTrack, ReserveGunButtTrack, ReserveTargetsPositionTrack (unit 0x1022D810 - 0x1022F8E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_RESERVEPOSITION_H
#define PROTO_FIGHTITEMS_AI_AI_RESERVEPOSITION_H

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
			// RTTI: proto::fightitems::ai::CanGunButtCondition (10 vftable slots, 0xC bytes)
			class CanGunButtCondition : public fight::Condition
			{
			public:
				// 0x1022DC60
				CanGunButtCondition();
				virtual ~CanGunButtCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EDF30, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gCanGunButtConditionProperties;
			fight::ConditionFactory* CreateCanGunButtConditionFactory(const char* name);
			void RegisterCanGunButtConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ReservePositionTrack (16 vftable slots, 0x2C bytes)
			class ReservePositionTrack : public fight::Track
			{
			public:
				// 0x1022DCC0
				ReservePositionTrack();
				virtual ~ReservePositionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F0350, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRadius(float newValue);
				bool SetPosTolerance(float newValue);
				bool SetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0x10
					float posTolerance;  // +0x1C
					float radius;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
			};

			extern fight::Property** gReservePositionTrackProperties;
			fight::TrackFactory* CreateReservePositionTrackFactory(const char* name);
			void RegisterReservePositionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::CommanderInCombatTrack (16 vftable slots, 0x18 bytes)
			class CommanderInCombatTrack : public fight::Track
			{
			public:
				// 0x1022DD90
				CommanderInCombatTrack();
				virtual ~CommanderInCombatTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F0550, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gCommanderInCombatTrackProperties;
			fight::TrackFactory* CreateCommanderInCombatTrackFactory(const char* name);
			void RegisterCommanderInCombatTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::EngageTrack (16 vftable slots, 0x48 bytes)
			class EngageTrack : public fight::Track
			{
			public:
				// 0x1022E120
				EngageTrack();
				virtual ~EngageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101EFD00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinStopDistance(float newValue);
				bool SetMaxStopDistance(float newValue);
				bool SetExtraMoveDistance(float newValue);
				bool SetMinTimeInPosition(float newValue);
				bool SetMaxTimeInPosition(float newValue);
				bool SetMaxTimeMelee(float newValue);
				bool SetKneelingProbability(float newValue);
				bool SetMinSpeed(float newValue);
				bool SetMaxSpeed(float newValue);
				bool SetWeaponGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name weaponGrabSlot;  // +0x10
					float extraMoveDistance;  // +0x18
					float kneelingProbability;  // +0x1C
					float maxSpeed;  // +0x20
					float maxStopDistance;  // +0x24
					float maxTimeInPosition;  // +0x28
					float maxTimeMelee;  // +0x2C
					float minSpeed;  // +0x30
					float minStopDistance;  // +0x34
					float minTimeInPosition;  // +0x38
					float timeBegin;  // +0x3C
					float timeEnd;  // +0x40
					unsigned char unknown44[0x4];
			};

			extern fight::Property** gEngageTrackProperties;
			fight::TrackFactory* CreateEngageTrackFactory(const char* name);
			void RegisterEngageTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ReserveHydraPositionTrack (16 vftable slots, 0x2C bytes)
			class ReserveHydraPositionTrack : public fight::Track
			{
			public:
				// 0x1022DE60
				ReserveHydraPositionTrack();
				virtual ~ReserveHydraPositionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F0400, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRadius(float newValue);
				bool SetPosTolerance(float newValue);
				bool SetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0x10
					float posTolerance;  // +0x1C
					float radius;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
			};

			extern fight::Property** gReserveHydraPositionTrackProperties;
			fight::TrackFactory* CreateReserveHydraPositionTrackFactory(const char* name);
			void RegisterReserveHydraPositionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ReserveGunButtTrack (16 vftable slots, 0x1C bytes)
			class ReserveGunButtTrack : public fight::Track
			{
			public:
				// 0x1022DF30
				ReserveGunButtTrack();
				virtual ~ReserveGunButtTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F0500, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetReserveLength(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float reserveLength;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
			};

			extern fight::Property** gReserveGunButtTrackProperties;
			fight::TrackFactory* CreateReserveGunButtTrackFactory(const char* name);
			void RegisterReserveGunButtTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ReserveTargetsPositionTrack (16 vftable slots, 0x20 bytes)
			class ReserveTargetsPositionTrack : public fight::Track
			{
			public:
				// 0x1022DFE0
				ReserveTargetsPositionTrack();
				virtual ~ReserveTargetsPositionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F04B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRadius(float newValue);
				bool SetPosTolerance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float posTolerance;  // +0x10
					float radius;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gReserveTargetsPositionTrackProperties;
			fight::TrackFactory* CreateReserveTargetsPositionTrackFactory(const char* name);
			void RegisterReserveTargetsPositionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::CommanderInCombatAction (9 vftable slots, 0x2C bytes)
			class CommanderInCombatAction : public fight::Action
			{
			public:
				// 0x101EFC50
				CommanderInCombatAction(CommanderInCombatTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101EE280
				virtual ~CommanderInCombatAction();

				// vftable slot 5 (0x101ED780)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101ED7B0)
				virtual void Slot6();
				// vftable slot 7 (0x101ED7A0)
				virtual bool Slot7(int arg, float value);

				core::Link<CommanderInCombatTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::ReserveGunButtAction (9 vftable slots, 0x2C bytes)
			class ReserveGunButtAction : public fight::Action
			{
			public:
				// 0x101EFB20
				ReserveGunButtAction(ReserveGunButtTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101EE230
				virtual ~ReserveGunButtAction();

				// vftable slot 5 (0x101EFBD0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101ED770)
				virtual void Slot6();
				// vftable slot 7 (0x101ED760)
				virtual bool Slot7(int arg, float value);

				core::Link<ReserveGunButtTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
