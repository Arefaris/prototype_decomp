// The remote players of the audio library (0x105BA920 - 0x105BB0F0): the table that names them and the events that free
// them.
#include "code/audio/remoteplayerevent.h"

namespace audio
{
	// FUNCTION: ENGINE 0x105BA960
	RemotePlayerEvent_FreePlayer::RemotePlayerEvent_FreePlayer(const RemotePlayerHandle& newPlayer) :
		RemotePlayerEvent(newPlayer)
	{
	}

	// FUNCTION: ENGINE 0x105BB0A0
	void RemotePlayerEvent_FreePlayer::Execute()
	{
		RemotePlayer* remote = gRemotePlayers->entries[player.index].player;
		if (remote != 0)
		{
			delete remote;
		}
		gRemotePlayers->entries[player.index].player = 0;
	}

	// FUNCTION: ENGINE 0x105BAF90
	// NONMATCHING: the engine builds the event inline (its constructor is inline in the original), ours calls the constructor (43.3 %)
#ifdef NONMATCHING
	void RemotePlayerTable::Destroy(RemotePlayerHandle handle)
	{
		unsigned int value = reinterpret_cast<unsigned int&>(handle);
		if (value != 0xFFFFFFFF)
		{
			entries[handle.index].nextFree = firstFree;
			firstFree = value;
			new RemotePlayerEvent_FreePlayer(handle);
		}
	}
#endif
}
