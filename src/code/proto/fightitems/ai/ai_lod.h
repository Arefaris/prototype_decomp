// Fight items of the ai group: CanReserveSoldierBudgetCondition, IsInLoadedCellCondition, NPCLODCondition, LodSteerTrack, ResetPhysicVelocitiesTrack, LodMoveTrack, EnableLODPatrolTrack, GameObjectOrientTrack, CharacterizeTrack, CharacterizeFromReservedTrack, SetNPCLODStateTrack, LodGotoFixedDestinationTrack, UnDowngradableTrack, UpdateSoldierReservationBudgetTrack (unit 0x10236270 - 0x10239F70; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_LOD_H
#define PROTO_FIGHTITEMS_AI_AI_LOD_H

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
			// RTTI: proto::fightitems::ai::CanReserveSoldierBudgetCondition (10 vftable slots, 0x10 bytes)
			class CanReserveSoldierBudgetCondition : public fight::Condition
			{
			public:
				// 0x10236740
				CanReserveSoldierBudgetCondition();
				virtual ~CanReserveSoldierBudgetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101FB410, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSoldiers(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int soldiers;  // +0xC
			};

			extern fight::Property** gCanReserveSoldierBudgetConditionProperties;
			fight::ConditionFactory* CreateCanReserveSoldierBudgetConditionFactory(const char* name);
			void RegisterCanReserveSoldierBudgetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::IsInLoadedCellCondition (10 vftable slots, 0xC bytes)
			class IsInLoadedCellCondition : public fight::Condition
			{
			public:
				// 0x10236810
				IsInLoadedCellCondition();
				virtual ~IsInLoadedCellCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101FB490, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gIsInLoadedCellConditionProperties;
			fight::ConditionFactory* CreateIsInLoadedCellConditionFactory(const char* name);
			void RegisterIsInLoadedCellConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::NPCLODCondition (10 vftable slots, 0x14 bytes)
			class NPCLODCondition : public fight::Condition
			{
			public:
				// 0x10236870
				NPCLODCondition();
				virtual ~NPCLODCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101FB370, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetValue(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int value;  // +0x10
			};

			extern fight::Property** gNPCLODConditionProperties;
			fight::ConditionFactory* CreateNPCLODConditionFactory(const char* name);
			void RegisterNPCLODConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::LodSteerTrack (16 vftable slots, 0x24 bytes)
			class LodSteerTrack : public fight::Track
			{
			public:
				// 0x102368E0
				LodSteerTrack();
				virtual ~LodSteerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC770, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(float newValue);
				bool SetWalkanim(int newValue);
				bool SetIdleanim(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float speed;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					int idleanim;  // +0x1C
					int walkanim;  // +0x20
			};

			extern fight::Property** gLodSteerTrackProperties;
			fight::TrackFactory* CreateLodSteerTrackFactory(const char* name);
			void RegisterLodSteerTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ResetPhysicVelocitiesTrack (16 vftable slots, 0x18 bytes)
			class ResetPhysicVelocitiesTrack : public fight::Track
			{
			public:
				// 0x102369A0
				ResetPhysicVelocitiesTrack();
				virtual ~ResetPhysicVelocitiesTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC720, another unit)
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

			extern fight::Property** gResetPhysicVelocitiesTrackProperties;
			fight::TrackFactory* CreateResetPhysicVelocitiesTrackFactory(const char* name);
			void RegisterResetPhysicVelocitiesTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::LodMoveTrack (16 vftable slots, 0x20 bytes)
			class LodMoveTrack : public fight::Track
			{
			public:
				// 0x10236A40
				LodMoveTrack();
				virtual ~LodMoveTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC7C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetWalkanim(int newValue);
				bool SetIdleanim(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int idleanim;  // +0x18
					int walkanim;  // +0x1C
			};

			extern fight::Property** gLodMoveTrackProperties;
			fight::TrackFactory* CreateLodMoveTrackFactory(const char* name);
			void RegisterLodMoveTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::EnableLODPatrolTrack (16 vftable slots, 0x20 bytes)
			class EnableLODPatrolTrack : public fight::Track
			{
			public:
				// 0x10236AF0
				EnableLODPatrolTrack();
				virtual ~EnableLODPatrolTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FCCE0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetActionOnBegin(int newValue);
				bool SetActionOnEnd(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int actionOnBegin;  // +0x18
					int actionOnEnd;  // +0x1C
			};

			extern fight::Property** gEnableLODPatrolTrackProperties;
			fight::TrackFactory* CreateEnableLODPatrolTrackFactory(const char* name);
			void RegisterEnableLODPatrolTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::GameObjectOrientTrack (16 vftable slots, 0x24 bytes)
			class GameObjectOrientTrack : public fight::Track
			{
			public:
				// 0x10236BA0
				GameObjectOrientTrack();
				virtual ~GameObjectOrientTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC6D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMaxTurnYaw(float newValue);
				bool SetMaxTurnPitch(float newValue);
				bool SetYaw(bool newValue);
				bool SetPitch(bool newValue);
				bool SetResetIfNotSetting(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float maxTurnPitch;  // +0x10
					float maxTurnYaw;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					bool pitch;  // +0x20
					bool resetIfNotSetting;  // +0x21
					bool yaw;  // +0x22
					unsigned char unknown23[0x1];
			};

			extern fight::Property** gGameObjectOrientTrackProperties;
			fight::TrackFactory* CreateGameObjectOrientTrackFactory(const char* name);
			void RegisterGameObjectOrientTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::CharacterizeTrack (16 vftable slots, 0x20 bytes)
			class CharacterizeTrack : public fight::Track
			{
			public:
				// 0x10237110
				CharacterizeTrack();
				virtual ~CharacterizeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC900, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gCharacterizeTrackProperties;
			fight::TrackFactory* CreateCharacterizeTrackFactory(const char* name);
			void RegisterCharacterizeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::CharacterizeFromReservedTrack (16 vftable slots, 0x20 bytes)
			class CharacterizeFromReservedTrack : public fight::Track
			{
			public:
				// 0x10237190
				CharacterizeFromReservedTrack();
				virtual ~CharacterizeFromReservedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC8B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gCharacterizeFromReservedTrackProperties;
			fight::TrackFactory* CreateCharacterizeFromReservedTrackFactory(const char* name);
			void RegisterCharacterizeFromReservedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SetNPCLODStateTrack (16 vftable slots, 0x1C bytes)
			class SetNPCLODStateTrack : public fight::Track
			{
			public:
				// 0x10236CC0
				SetNPCLODStateTrack();
				virtual ~SetNPCLODStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC680, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetValue(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int value;  // +0x18
			};

			extern fight::Property** gSetNPCLODStateTrackProperties;
			fight::TrackFactory* CreateSetNPCLODStateTrackFactory(const char* name);
			void RegisterSetNPCLODStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::LodGotoFixedDestinationTrack (16 vftable slots, 0x2C bytes)
			class LodGotoFixedDestinationTrack : public fight::Track
			{
			public:
				// 0x10236D70
				LodGotoFixedDestinationTrack();
				virtual ~LodGotoFixedDestinationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FCBC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(float newValue);
				bool SetVerticalSpeed(float newValue);
				bool SetTolerance(float newValue);
				bool SetFreeArea(float newValue);
				bool SetMinHeight(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float freeArea;  // +0x10
					float minHeight;  // +0x14
					float speed;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					float tolerance;  // +0x24
					float verticalSpeed;  // +0x28
			};

			extern fight::Property** gLodGotoFixedDestinationTrackProperties;
			fight::TrackFactory* CreateLodGotoFixedDestinationTrackFactory(const char* name);
			void RegisterLodGotoFixedDestinationTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::UnDowngradableTrack (16 vftable slots, 0x1C bytes)
			class UnDowngradableTrack : public fight::Track
			{
			public:
				// 0x10236E40
				UnDowngradableTrack();
				virtual ~UnDowngradableTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC810, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetClearAtEnd(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool clearAtEnd;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gUnDowngradableTrackProperties;
			fight::TrackFactory* CreateUnDowngradableTrackFactory(const char* name);
			void RegisterUnDowngradableTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::UpdateSoldierReservationBudgetTrack (16 vftable slots, 0x18 bytes)
			class UpdateSoldierReservationBudgetTrack : public fight::Track
			{
			public:
				// 0x10236EE0
				UpdateSoldierReservationBudgetTrack();
				virtual ~UpdateSoldierReservationBudgetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101FC860, another unit)
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

			extern fight::Property** gUpdateSoldierReservationBudgetTrackProperties;
			fight::TrackFactory* CreateUpdateSoldierReservationBudgetTrackFactory(const char* name);
			void RegisterUpdateSoldierReservationBudgetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::LodSteerAction (9 vftable slots, 0x2C bytes)
			class LodSteerAction : public fight::Action
			{
			public:
				// 0x101FBCE0
				LodSteerAction(LodSteerTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FABE0
				virtual ~LodSteerAction();

				// vftable slot 5 (0x101FA1F0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FA210)
				virtual void Slot6();
				// vftable slot 7 (0x101FA200)
				virtual bool Slot7(int arg, float value);

				core::Link<LodSteerTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::ResetPhysicVelocitiesAction (9 vftable slots, 0x2C bytes)
			class ResetPhysicVelocitiesAction : public fight::Action
			{
			public:
				// 0x101FBAE0
				ResetPhysicVelocitiesAction(ResetPhysicVelocitiesTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FAA40
				virtual ~ResetPhysicVelocitiesAction();

				// vftable slot 5 (0x101FBB90)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FA1E0)
				virtual void Slot6();
				// vftable slot 7 (0x101FAA70)
				virtual bool Slot7(int arg, float value);

				core::Link<ResetPhysicVelocitiesTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::LodMoveAction (9 vftable slots, 0x2C bytes)
			class LodMoveAction : public fight::Action
			{
			public:
				// 0x101FBD90
				LodMoveAction(LodMoveTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FAC30
				virtual ~LodMoveAction();

				// vftable slot 5 (0x101FA220)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FA240)
				virtual void Slot6();
				// vftable slot 7 (0x101FA230)
				virtual bool Slot7(int arg, float value);

				core::Link<LodMoveTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::EnableLODPatrolAction (9 vftable slots, 0x2C bytes)
			class EnableLODPatrolAction : public fight::Action
			{
			public:
				// 0x101FC5E0
				EnableLODPatrolAction(EnableLODPatrolTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FB340
				virtual ~EnableLODPatrolAction();

				// vftable slot 5 (0x101FA320)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FA330)
				virtual void Slot6();

				core::Link<EnableLODPatrolTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				bool unknown2C;  // +0x2C
				unsigned char unknown2D[0x3];
			};

			// RTTI: proto::fightitems::ai::GameObjectOrientAction (9 vftable slots, 0x2C bytes)
			class GameObjectOrientAction : public fight::Action
			{
			public:
				// 0x101FBA30
				GameObjectOrientAction(GameObjectOrientTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FA9F0
				virtual ~GameObjectOrientAction();

				// vftable slot 5 (0x101FA1B0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FA1D0)
				virtual void Slot6();
				// vftable slot 7 (0x101FA1C0)
				virtual bool Slot7(int arg, float value);

				core::Link<GameObjectOrientTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::SetNPCLODStateAction (9 vftable slots, 0x2C bytes)
			class SetNPCLODStateAction : public fight::Action
			{
			public:
				// 0x101FB920
				SetNPCLODStateAction(SetNPCLODStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FA9A0
				virtual ~SetNPCLODStateAction();

				// vftable slot 5 (0x101FB9D0)
				virtual bool Slot5(int arg, float value);

				core::Link<SetNPCLODStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::UnDowngradableAction (9 vftable slots, 0x2C bytes)
			class UnDowngradableAction : public fight::Action
			{
			public:
				// 0x101FBE40
				UnDowngradableAction(UnDowngradableTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FAC80
				virtual ~UnDowngradableAction();

				// vftable slot 5 (0x101FBEF0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FBFA0)
				virtual void Slot6();

				core::Link<UnDowngradableTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::UpdateSoldierReservationBudgetAction (9 vftable slots, 0x2C bytes)
			class UpdateSoldierReservationBudgetAction : public fight::Action
			{
			public:
				// 0x101FC030
				UpdateSoldierReservationBudgetAction(UpdateSoldierReservationBudgetTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FACD0
				virtual ~UpdateSoldierReservationBudgetAction();

				// vftable slot 5 (0x101FC0E0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101FA250)
				virtual void Slot6();
				// vftable slot 7 (0x101FAD00)
				virtual bool Slot7(int arg, float value);

				core::Link<UpdateSoldierReservationBudgetTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::CharacterizeAction (9 vftable slots, 0x2C bytes)
			class CharacterizeAction : public fight::Action
			{
			public:
				// 0x101FC2B0
				CharacterizeAction(CharacterizeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FADC0
				virtual ~CharacterizeAction();

				// vftable slot 5 (0x101FC360)
				virtual bool Slot5(int arg, float value);

				core::Link<CharacterizeTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::ai::CharacterizeFromReservedAction (9 vftable slots, 0x2C bytes)
			class CharacterizeFromReservedAction : public fight::Action
			{
			public:
				// 0x101FC140
				CharacterizeFromReservedAction(CharacterizeFromReservedTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101FAD70
				virtual ~CharacterizeFromReservedAction();

				// vftable slot 5 (0x101FC1F0)
				virtual bool Slot5(int arg, float value);

				core::Link<CharacterizeFromReservedTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
