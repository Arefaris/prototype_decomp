// Fight items of the online group: OnlineFlagPlayerDeathTrack, OnlineSetPairingVolumeStateTrack, OnlineSetRespawnStateTrack, OnlineSyncLocalWorldCellStreamingTrack (unit 0x10267A90 - 0x102689E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/online/online_tracks.h"

namespace proto
{
	namespace fightitems
	{
		namespace online
		{
			fight::Property** gOnlineFlagPlayerDeathTrackProperties;  // 0x11255E54

			// FUNCTION: ENGINE 0x10267A90
			bool OnlineFlagPlayerDeathTrack::SetPlayerToTell(int newValue)
			{
				playerToTell = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10267AA0
			bool OnlineFlagPlayerDeathTrack::SetPlayerThatDied(int newValue)
			{
				playerThatDied = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10267B30
			fight::Property* OnlineFlagPlayerDeathTrack::GetProperty(int index)
			{
				return gOnlineFlagPlayerDeathTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10267B50
			void OnlineFlagPlayerDeathTrack::ClearProperties()
			{
				fight::FreePropertyList(&gOnlineFlagPlayerDeathTrackProperties);
			}

			// FUNCTION: ENGINE 0x10267B60
			OnlineFlagPlayerDeathTrack::OnlineFlagPlayerDeathTrack() : playerThatDied(0), playerToTell(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10267B90
			float OnlineFlagPlayerDeathTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10267BA0
			float OnlineFlagPlayerDeathTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10267BB0
			OnlineFlagPlayerDeathTrack::~OnlineFlagPlayerDeathTrack()
			{
			}

			// FUNCTION: ENGINE 0x102682D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OnlineFlagPlayerDeathTrack::RegisterProperties()
			{
				if (gOnlineFlagPlayerDeathTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<OnlineFlagPlayerDeathTrack>("playerToTell", motion::gGrabPlayerTrackGrabbingPlayerTable, motion::gGrabPlayerTrackGrabbingPlayerCount, &OnlineFlagPlayerDeathTrack::SetPlayerToTell);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<OnlineFlagPlayerDeathTrack>("playerThatDied", motion::gGrabPlayerTrackGrabbingPlayerTable, motion::gGrabPlayerTrackGrabbingPlayerCount, &OnlineFlagPlayerDeathTrack::SetPlayerThatDied);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gOnlineFlagPlayerDeathTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10268210
			fight::TrackFactory* CreateOnlineFlagPlayerDeathTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnlineFlagPlayerDeathTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102686A0
			void RegisterOnlineFlagPlayerDeathTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnlineFlagPlayerDeathTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gOnlineSetPairingVolumeStateTrackProperties;  // 0x11255E58

			// FUNCTION: ENGINE 0x10267AB0
			bool OnlineSetPairingVolumeStateTrack::SetVolumeType(int newValue)
			{
				volumeType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10267AC0
			bool OnlineSetPairingVolumeStateTrack::SetInVolume(bool newValue)
			{
				inVolume = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10267BC0
			fight::Property* OnlineSetPairingVolumeStateTrack::GetProperty(int index)
			{
				return gOnlineSetPairingVolumeStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10267BE0
			void OnlineSetPairingVolumeStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gOnlineSetPairingVolumeStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x10267BF0
			OnlineSetPairingVolumeStateTrack::OnlineSetPairingVolumeStateTrack() : volumeType(0), inVolume(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10267C20
			float OnlineSetPairingVolumeStateTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10267C30
			float OnlineSetPairingVolumeStateTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10267C40
			OnlineSetPairingVolumeStateTrack::~OnlineSetPairingVolumeStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x102683D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OnlineSetPairingVolumeStateTrack::RegisterProperties()
			{
				if (gOnlineSetPairingVolumeStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<OnlineSetPairingVolumeStateTrack>("volumeType", gOnlineSetPairingVolumeStateTrackVolumeTypeTable, gOnlineSetPairingVolumeStateTrackVolumeTypeCount, &OnlineSetPairingVolumeStateTrack::SetVolumeType);
					properties[0] = property;
					property = new fight::PropertyBool<OnlineSetPairingVolumeStateTrack>("inVolume", &OnlineSetPairingVolumeStateTrack::SetInVolume);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gOnlineSetPairingVolumeStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10268240
			fight::TrackFactory* CreateOnlineSetPairingVolumeStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnlineSetPairingVolumeStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102686D0
			void RegisterOnlineSetPairingVolumeStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnlineSetPairingVolumeStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gOnlineSetRespawnStateTrackProperties;  // 0x11255E5C

			// FUNCTION: ENGINE 0x10267AD0
			bool OnlineSetRespawnStateTrack::SetPlayer(int newValue)
			{
				player = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10267AE0
			bool OnlineSetRespawnStateTrack::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10267C50
			fight::Property* OnlineSetRespawnStateTrack::GetProperty(int index)
			{
				return gOnlineSetRespawnStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10267C70
			void OnlineSetRespawnStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gOnlineSetRespawnStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x10267C80
			OnlineSetRespawnStateTrack::OnlineSetRespawnStateTrack() : player(0), state(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10267CB0
			float OnlineSetRespawnStateTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10267CC0
			float OnlineSetRespawnStateTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10267CD0
			OnlineSetRespawnStateTrack::~OnlineSetRespawnStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x102684C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OnlineSetRespawnStateTrack::RegisterProperties()
			{
				if (gOnlineSetRespawnStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<OnlineSetRespawnStateTrack>("player", motion::gGrabPlayerTrackGrabbingPlayerTable, motion::gGrabPlayerTrackGrabbingPlayerCount, &OnlineSetRespawnStateTrack::SetPlayer);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<OnlineSetRespawnStateTrack>("state", online::gOnlineTestForRespawnStateConditionStateTable, online::gOnlineTestForRespawnStateConditionStateCount, &OnlineSetRespawnStateTrack::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gOnlineSetRespawnStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10268270
			fight::TrackFactory* CreateOnlineSetRespawnStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnlineSetRespawnStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10268700
			void RegisterOnlineSetRespawnStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnlineSetRespawnStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gOnlineSyncLocalWorldCellStreamingTrackProperties;  // 0x11255E60

			// FUNCTION: ENGINE 0x10267AF0
			bool OnlineSyncLocalWorldCellStreamingTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10267B10
			bool OnlineSyncLocalWorldCellStreamingTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10267CE0
			fight::Property* OnlineSyncLocalWorldCellStreamingTrack::GetProperty(int index)
			{
				return gOnlineSyncLocalWorldCellStreamingTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10267D00
			void OnlineSyncLocalWorldCellStreamingTrack::ClearProperties()
			{
				fight::FreePropertyList(&gOnlineSyncLocalWorldCellStreamingTrackProperties);
			}

			// FUNCTION: ENGINE 0x10267D10
			OnlineSyncLocalWorldCellStreamingTrack::OnlineSyncLocalWorldCellStreamingTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10267D40
			float OnlineSyncLocalWorldCellStreamingTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10267D50
			float OnlineSyncLocalWorldCellStreamingTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10267D60
			OnlineSyncLocalWorldCellStreamingTrack::~OnlineSyncLocalWorldCellStreamingTrack()
			{
			}

			// FUNCTION: ENGINE 0x102685C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OnlineSyncLocalWorldCellStreamingTrack::RegisterProperties()
			{
				if (gOnlineSyncLocalWorldCellStreamingTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<OnlineSyncLocalWorldCellStreamingTrack>("timeBegin", &OnlineSyncLocalWorldCellStreamingTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<OnlineSyncLocalWorldCellStreamingTrack>("timeEnd", &OnlineSyncLocalWorldCellStreamingTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gOnlineSyncLocalWorldCellStreamingTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102682A0
			fight::TrackFactory* CreateOnlineSyncLocalWorldCellStreamingTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnlineSyncLocalWorldCellStreamingTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10268730
			void RegisterOnlineSyncLocalWorldCellStreamingTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnlineSyncLocalWorldCellStreamingTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<OnlineFlagPlayerDeathTrack>;
			template class fight::TrackFactoryTemplate<OnlineFlagPlayerDeathTrack>;
			template class fight::TrackFactoryCasterTemplate<OnlineFlagPlayerDeathTrack>;
			template class fight::PropertyEnumConstList<OnlineSetPairingVolumeStateTrack>;
			template class fight::PropertyBool<OnlineSetPairingVolumeStateTrack>;
			template class fight::TrackFactoryTemplate<OnlineSetPairingVolumeStateTrack>;
			template class fight::TrackFactoryCasterTemplate<OnlineSetPairingVolumeStateTrack>;
			template class fight::PropertyEnumConstList<OnlineSetRespawnStateTrack>;
			template class fight::TrackFactoryTemplate<OnlineSetRespawnStateTrack>;
			template class fight::TrackFactoryCasterTemplate<OnlineSetRespawnStateTrack>;
			template class fight::PropertyFloatConstRange<OnlineSyncLocalWorldCellStreamingTrack>;
			template class fight::TrackFactoryTemplate<OnlineSyncLocalWorldCellStreamingTrack>;
			template class fight::TrackFactoryCasterTemplate<OnlineSyncLocalWorldCellStreamingTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10267D70
// FUNCTION: ENGINE 0x10267DA0
// FUNCTION: ENGINE 0x10267DD0
// FUNCTION: ENGINE 0x10267E00
// FUNCTION: ENGINE 0x10267E30
// FUNCTION: ENGINE 0x10267E40
// FUNCTION: ENGINE 0x10267E70
// FUNCTION: ENGINE 0x10267E80
// FUNCTION: ENGINE 0x10267EB0
// FUNCTION: ENGINE 0x10267EC0
// FUNCTION: ENGINE 0x10267EF0
// FUNCTION: ENGINE 0x10267F00
// FUNCTION: ENGINE 0x10267F30
// FUNCTION: ENGINE 0x10267F70
// FUNCTION: ENGINE 0x10267F80
// FUNCTION: ENGINE 0x10267FB0
// FUNCTION: ENGINE 0x10267FD0
// FUNCTION: ENGINE 0x10267FE0
// FUNCTION: ENGINE 0x10268020
// FUNCTION: ENGINE 0x10268030
// FUNCTION: ENGINE 0x10268060
// FUNCTION: ENGINE 0x10268080
// FUNCTION: ENGINE 0x10268090
// FUNCTION: ENGINE 0x102680C0
// FUNCTION: ENGINE 0x102680E0
// FUNCTION: ENGINE 0x102680F0
// FUNCTION: ENGINE 0x10268130
// FUNCTION: ENGINE 0x10268140
// FUNCTION: ENGINE 0x10268170
// FUNCTION: ENGINE 0x10268190
// FUNCTION: ENGINE 0x102681A0
// FUNCTION: ENGINE 0x102681D0
// FUNCTION: ENGINE 0x10268200
// FUNCTION: ENGINE 0x10268760
// FUNCTION: ENGINE 0x10268790
// FUNCTION: ENGINE 0x102687B0
// FUNCTION: ENGINE 0x102687E0
// FUNCTION: ENGINE 0x10268800
// FUNCTION: ENGINE 0x10268830
// FUNCTION: ENGINE 0x10268850
// FUNCTION: ENGINE 0x10268880
// FUNCTION: ENGINE 0x102688A0
// FUNCTION: ENGINE 0x102688F0
// FUNCTION: ENGINE 0x10268940
// FUNCTION: ENGINE 0x10268990
