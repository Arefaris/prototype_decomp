// audio::Event and the events the game posts to the audio library's remote players (RTTI: audio::Event,
// audio::RemotePlayerEvent and the templates audio::RemotePlayerEvent_Param1<T> / _Param2<T1, T2>). An event is built
// in the audio thread's ring buffer (class operator new / delete) and runs later in the audio thread: it calls a
// method of the remote player the handle names with the arguments it kept. Names other than the RTTI ones are guesses.
#ifndef AUDIO_REMOTEPLAYEREVENT_H
#define AUDIO_REMOTEPLAYEREVENT_H

#include "code/om/dynamicarray.h"
#include "code/om/string.h"

namespace audio
{
	// The ring buffer the events live in (0x1127636C holds its address; 0x105BA7B0 / 0x105BA730)
	class EventQueue
	{
	public:
		void* Allocate(unsigned int size);
		void Free(void* block, unsigned int size);
	};
	extern EventQueue* gEventQueue;

	// A remote player of the audio library (the entry's first word, a pointer, is the player)
	class RemotePlayer;
	struct RemotePlayerEntry
	{
		RemotePlayer* player;
		unsigned char unknown4[0x3c - 4];
	};
	struct RemotePlayerTable
	{
		RemotePlayerEntry* entries;
	};
	extern RemotePlayerTable* gRemotePlayers;

	// Names a remote player (0x11276370 holds the table): the index in the low half
	struct RemotePlayerHandle
	{
		unsigned short index;
		unsigned short serial;
	};

	class Event
	{
	public:
		Event()
		{
		}
		virtual ~Event()
		{
		}
		virtual void Execute() = 0;
	};

	class RemotePlayerEvent : public Event
	{
	public:
		explicit RemotePlayerEvent(const RemotePlayerHandle& newPlayer)
		{
			player = newPlayer;
		}

		RemotePlayerHandle player;
	};

	// The part every event of a template instance shares: the queue's memory and the player the handle names
#define AUDIO_EVENT_MEMORY(Class) \
	static void* operator new(unsigned int size) \
	{ \
		return gEventQueue->Allocate(size); \
	} \
	static void operator delete(void* block) \
	{ \
		gEventQueue->Free(block, sizeof(Class)); \
	}

	// What an event keeps of an argument: a reference argument is kept by value
	template<class T> struct StoredType
	{
		typedef T Type;
	};
	template<class T> struct StoredType<const T&>
	{
		typedef T Type;
	};

	// Calls function(player, value) in the audio thread
	template<class T> class RemotePlayerEvent_Param1 : public RemotePlayerEvent
	{
	public:
		typedef void (__thiscall *Function)(RemotePlayer*, T);

		RemotePlayerEvent_Param1(const RemotePlayerHandle& newPlayer, Function newFunction, T newValue) :
			RemotePlayerEvent(newPlayer),
			function(newFunction),
			value(newValue)
		{
		}
		virtual void Execute()
		{
			function(gRemotePlayers->entries[player.index].player, value);
		}
		AUDIO_EVENT_MEMORY(RemotePlayerEvent_Param1)

		Function function;
		typename StoredType<T>::Type value;
	};

	template<class T1, class T2> class RemotePlayerEvent_Param2 : public RemotePlayerEvent
	{
	public:
		typedef void (__thiscall *Function)(RemotePlayer*, T1, T2);

		RemotePlayerEvent_Param2(RemotePlayerHandle newPlayer, Function newFunction, T1 newValue1, T2 newValue2) :
			RemotePlayerEvent(newPlayer),
			function(newFunction),
			value1(newValue1),
			value2(newValue2)
		{
		}
		virtual void Execute()
		{
			function(gRemotePlayers->entries[player.index].player, value1, value2);
		}
		AUDIO_EVENT_MEMORY(RemotePlayerEvent_Param2)

		Function function;
		T1 value1;
		T2 value2;
	};
}

#endif
