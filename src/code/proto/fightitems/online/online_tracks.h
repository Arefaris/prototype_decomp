// Fight items of the online group: OnlineFlagPlayerDeathTrack, OnlineSetPairingVolumeStateTrack, OnlineSetRespawnStateTrack, OnlineSyncLocalWorldCellStreamingTrack (unit 0x10267A90 - 0x102689E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_ONLINE_ONLINE_TRACKS_H
#define PROTO_FIGHTITEMS_ONLINE_ONLINE_TRACKS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/online/onlinedata.h"

namespace proto
{
	namespace fightitems
	{
		namespace online
		{
			// RTTI: proto::fightitems::online::OnlineFlagPlayerDeathTrack (16 vftable slots, 0x18 bytes)
			class OnlineFlagPlayerDeathTrack : public fight::Track
			{
			public:
				// 0x10267B60
				OnlineFlagPlayerDeathTrack();
				virtual ~OnlineFlagPlayerDeathTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10266340, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetPlayerToTell(int newValue);
				bool SetPlayerThatDied(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int playerThatDied;  // +0x10
					int playerToTell;  // +0x14
			};

			extern fight::Property** gOnlineFlagPlayerDeathTrackProperties;
			fight::TrackFactory* CreateOnlineFlagPlayerDeathTrackFactory(const char* name);
			void RegisterOnlineFlagPlayerDeathTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::online::OnlineSetPairingVolumeStateTrack (16 vftable slots, 0x18 bytes)
			class OnlineSetPairingVolumeStateTrack : public fight::Track
			{
			public:
				// 0x10267BF0
				OnlineSetPairingVolumeStateTrack();
				virtual ~OnlineSetPairingVolumeStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102663E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetVolumeType(int newValue);
				bool SetInVolume(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int volumeType;  // +0x10
					bool inVolume;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gOnlineSetPairingVolumeStateTrackProperties;
			fight::TrackFactory* CreateOnlineSetPairingVolumeStateTrackFactory(const char* name);
			void RegisterOnlineSetPairingVolumeStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::online::OnlineSetRespawnStateTrack (16 vftable slots, 0x18 bytes)
			class OnlineSetRespawnStateTrack : public fight::Track
			{
			public:
				// 0x10267C80
				OnlineSetRespawnStateTrack();
				virtual ~OnlineSetRespawnStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10266390, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetPlayer(int newValue);
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int player;  // +0x10
					int state;  // +0x14
			};

			extern fight::Property** gOnlineSetRespawnStateTrackProperties;
			fight::TrackFactory* CreateOnlineSetRespawnStateTrackFactory(const char* name);
			void RegisterOnlineSetRespawnStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::online::OnlineSyncLocalWorldCellStreamingTrack (16 vftable slots, 0x18 bytes)
			class OnlineSyncLocalWorldCellStreamingTrack : public fight::Track
			{
			public:
				// 0x10267D10
				OnlineSyncLocalWorldCellStreamingTrack();
				virtual ~OnlineSyncLocalWorldCellStreamingTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102662F0, another unit)
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

			extern fight::Property** gOnlineSyncLocalWorldCellStreamingTrackProperties;
			fight::TrackFactory* CreateOnlineSyncLocalWorldCellStreamingTrackFactory(const char* name);
			void RegisterOnlineSyncLocalWorldCellStreamingTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::online::OnlineFlagPlayerDeathAction (9 vftable slots, 0x2C bytes)
			class OnlineFlagPlayerDeathAction : public fight::Action
			{
			public:
				// 0x10265E30
				OnlineFlagPlayerDeathAction(OnlineFlagPlayerDeathTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10265AF0
				virtual ~OnlineFlagPlayerDeathAction();

				// vftable slot 5 (0x10265ED0)
				virtual bool Slot5(int arg, float value);

				core::Link<OnlineFlagPlayerDeathTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
