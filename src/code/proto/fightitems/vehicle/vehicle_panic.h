// Fight items of the vehicle group: SetPanicStateTrack, PanicTrack, SpawnCopsBesideCarTrack, SpawnCopsOffScreenTrack, TerminateTrack, ReturnToNormalTrack (unit 0x1027BF20 - 0x1027D9F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_VEHICLE_VEHICLE_PANIC_H
#define PROTO_FIGHTITEMS_VEHICLE_VEHICLE_PANIC_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/vehicle/vehicledata.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			// RTTI: proto::fightitems::vehicle::SetPanicStateTrack (16 vftable slots, 0x1C bytes)
			class SetPanicStateTrack : public fight::Track
			{
			public:
				// 0x1027C1E0
				SetPanicStateTrack();
				virtual ~SetPanicStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10279FB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetPanicType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int panicType;  // +0x18
			};

			extern fight::Property** gSetPanicStateTrackProperties;
			fight::TrackFactory* CreateSetPanicStateTrackFactory(const char* name);
			void RegisterSetPanicStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::vehicle::PanicTrack (16 vftable slots, 0x50 bytes)
			class PanicTrack : public fight::Track
			{
			public:
				// 0x1027C280
				PanicTrack();
				virtual ~PanicTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10279EC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinTimeDelay(float newValue);
				bool SetMaxTimeDelay(float newValue);
				bool SetMaxVelocity(float newValue);
				bool SetAccelration(float newValue);
				bool SetBraking(float newValue);
				fight::BranchHolder* SetMyBranch();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder myBranch;  // +0x10
					float accelration;  // +0x34
					float braking;  // +0x38
					float maxTimeDelay;  // +0x3C
					float maxVelocity;  // +0x40
					float minTimeDelay;  // +0x44
					float timeBegin;  // +0x48
					float timeEnd;  // +0x4C
			};

			extern fight::Property** gPanicTrackProperties;
			fight::TrackFactory* CreatePanicTrackFactory(const char* name);
			void RegisterPanicTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::vehicle::SpawnCopsBesideCarTrack (16 vftable slots, 0x1C bytes)
			class SpawnCopsBesideCarTrack : public fight::Track
			{
			public:
				// 0x1027C360
				SpawnCopsBesideCarTrack();
				virtual ~SpawnCopsBesideCarTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1027A050, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetXOffset(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					float xOffset;  // +0x18
			};

			extern fight::Property** gSpawnCopsBesideCarTrackProperties;
			fight::TrackFactory* CreateSpawnCopsBesideCarTrackFactory(const char* name);
			void RegisterSpawnCopsBesideCarTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::vehicle::SpawnCopsOffScreenTrack (16 vftable slots, 0x1C bytes)
			class SpawnCopsOffScreenTrack : public fight::Track
			{
			public:
				// 0x1027C410
				SpawnCopsOffScreenTrack();
				virtual ~SpawnCopsOffScreenTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1027A000, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetNumCops(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int numCops;  // +0x18
			};

			extern fight::Property** gSpawnCopsOffScreenTrackProperties;
			fight::TrackFactory* CreateSpawnCopsOffScreenTrackFactory(const char* name);
			void RegisterSpawnCopsOffScreenTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::vehicle::TerminateTrack (16 vftable slots, 0x18 bytes)
			class TerminateTrack : public fight::Track
			{
			public:
				// 0x1027C4B0
				TerminateTrack();
				virtual ~TerminateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10279F10, another unit)
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

			extern fight::Property** gTerminateTrackProperties;
			fight::TrackFactory* CreateTerminateTrackFactory(const char* name);
			void RegisterTerminateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::vehicle::ReturnToNormalTrack (16 vftable slots, 0x1C bytes)
			class ReturnToNormalTrack : public fight::Track
			{
			public:
				// 0x1027C540
				ReturnToNormalTrack();
				virtual ~ReturnToNormalTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10279F60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTimeTillReturn(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					float timeTillReturn;  // +0x18
			};

			extern fight::Property** gReturnToNormalTrackProperties;
			fight::TrackFactory* CreateReturnToNormalTrackFactory(const char* name);
			void RegisterReturnToNormalTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::vehicle::SetPanicStateAction (9 vftable slots, 0x2C bytes)
			class SetPanicStateAction : public fight::Action
			{
			public:
				// 0x10279B30
				SetPanicStateAction(SetPanicStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x102791B0
				virtual ~SetPanicStateAction();

				// vftable slot 7 (0x10279BE0)
				virtual bool Slot7(int arg, float value);

				core::Link<SetPanicStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::vehicle::PanicAction (9 vftable slots, 0x2C bytes)
			class PanicAction : public fight::Action
			{
			public:
				// 0x10279500
				PanicAction(PanicTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10279020
				virtual ~PanicAction();

				// vftable slot 5 (0x102795E0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10278BB0)
				virtual void Slot6();
				// vftable slot 7 (0x10279760)
				virtual bool Slot7(int arg, float value);

				core::Link<PanicTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				math::Vector unknown2C;  // +0x2C
				float unknown38;  // +0x38
			};

			// RTTI: proto::fightitems::vehicle::SpawnCopsBesideCarAction (9 vftable slots, 0x2C bytes)
			class SpawnCopsBesideCarAction : public fight::Action
			{
			public:
				// 0x10279D50
				SpawnCopsBesideCarAction(SpawnCopsBesideCarTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10279250
				virtual ~SpawnCopsBesideCarAction();

				// vftable slot 7 (0x10279E00)
				virtual bool Slot7(int arg, float value);

				core::Link<SpawnCopsBesideCarTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::vehicle::SpawnCopsOffScreenAction (9 vftable slots, 0x2C bytes)
			class SpawnCopsOffScreenAction : public fight::Action
			{
			public:
				// 0x10279C70
				SpawnCopsOffScreenAction(SpawnCopsOffScreenTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10279200
				virtual ~SpawnCopsOffScreenAction();

				// vftable slot 7 (0x10279D10)
				virtual bool Slot7(int arg, float value);

				core::Link<SpawnCopsOffScreenTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				int unknown2C;  // +0x2C
			};

			// RTTI: proto::fightitems::vehicle::TerminateAction (9 vftable slots, 0x2C bytes)
			class TerminateAction : public fight::Action
			{
			public:
				// 0x10279910
				TerminateAction(TerminateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10279070
				virtual ~TerminateAction();

				// vftable slot 5 (0x10278BC0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10278BD0)
				virtual void Slot6();
				// vftable slot 7 (0x102790A0)
				virtual bool Slot7(int arg, float value);

				core::Link<TerminateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// RTTI: proto::fightitems::vehicle::ReturnToNormalAction (9 vftable slots, 0x2C bytes)
			class ReturnToNormalAction : public fight::Action
			{
			public:
				// 0x102799C0
				ReturnToNormalAction(ReturnToNormalTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10279160
				virtual ~ReturnToNormalAction();

				// vftable slot 5 (0x10278BE0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10278BF0)
				virtual void Slot6();
				// vftable slot 7 (0x10279A70)
				virtual bool Slot7(int arg, float value);

				core::Link<ReturnToNormalTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
