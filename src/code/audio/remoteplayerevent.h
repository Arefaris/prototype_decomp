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
	// The output bins of a mix (RTTI: the argument of RemotePlayerEvent_Param2<enum audio::MixBin, float>)
	enum MixBin
	{
		MIXBIN_FIRST = 0
	};

	// The ring buffer the events live in (0x1127636C holds its address; 0x105BA7B0 / 0x105BA730)
	class EventQueue
	{
	public:
		// 0x105BA5B0: a ring of that many bytes (a power of two); the queue becomes the one in force
		explicit EventQueue(unsigned int newCapacity);
		// 0x105BA5F0
		~EventQueue();
		// 0x105BA7B0: room for an event of that size; waits for the audio thread to free some when the ring is full
		void* Allocate(unsigned int size);
		// 0x105BA730: the audio thread gives an event's room back
		void Free(void* block, unsigned int size);
		// 0x105BA680: how much room there is in front of the write position and how much behind the read position
		void GetSpace(unsigned int* space, unsigned int* limit);
		// 0x105BA6D0: the next event the audio thread has not seen, null when there is none
		unsigned char* Peek();
		// 0x105BA710: lets the audio thread see everything written so far
		void Publish();

		unsigned char* buffer;  // 0
		unsigned int capacity;  // 4
		unsigned int write;  // 8: where the next event goes
		unsigned int visible;  // 0xC: how far the audio thread may read
		unsigned int free;  // 0x10: how far the audio thread has read (set with an atomic exchange)
		unsigned int unknown14;
	};
	// 0x105BA610 (om): the value rounded up to a multiple of the alignment
	// 0x105BA640 / 0x105BA660: an atomic read and an atomic exchange (names guessed)
	long AtomicRead(volatile long* value);
	long AtomicExchange(volatile long* value, const long* newValue);
	extern EventQueue* gEventQueue;

	// A remote player of the audio library (the entry's first word, a pointer, is the player). The events keep the
	// method they call as a pointer to a member of it; only the methods the game posts are declared.
	class RemotePlayer
	{
	public:
		// 0x104A5E20 (behind the jump thunk 0x1003CD62) and 0x104A2D90 (behind 0x10023DDF); names guessed
		void Stop(unsigned int value);
		void Play(unsigned int value);

		// The setters of the unit 0x1087F100 - 0x1087F200 (names guessed): the audio thread writes the settings the game
		// sent in events into the player
		void SetUnknown444(float value);
		void SetUnknown528(float value);
		void SetUnknown52C(float value);
		void SetUnknown520(float value);
		void SetUnknown524(float value);
		void SetUnknown544(float value);
		void SetBinVolume(MixBin bin, float value);
		void SetChannelVolume(unsigned int channel, float value);

		unsigned char unknown0[0xb0];
		float channelVolumes[18];  // +0xB0
		float binVolumes[(0x444 - 0xf8) / 4];  // +0xF8
		float unknown444;
		unsigned char unknown448[0x520 - 0x448];
		float unknown520;
		float unknown524;
		float unknown528;
		float unknown52C;
		unsigned char unknown530[0x544 - 0x530];
		float unknown544;
	};
	struct RemotePlayerEntry
	{
		RemotePlayer* player;
		unsigned char unknown4[0x28 - 4];
		bool unknown28;
		unsigned int unknown2C;
		float amplitude;  // +0x30
		int unknown34;
		float unknown38;
	};
	struct RemotePlayerHandle;
	struct RemotePlayerTable
	{
		// 0x105BAF90: lets the player of the handle go
		void Destroy(RemotePlayerHandle handle);

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
		typedef void (RemotePlayer::*Function)(T);

		RemotePlayerEvent_Param1(const RemotePlayerHandle& newPlayer, Function newFunction, T newValue) :
			RemotePlayerEvent(newPlayer),
			function(newFunction),
			value(newValue)
		{
		}
		virtual void Execute()
		{
			(gRemotePlayers->entries[player.index].player->*function)(value);
		}
		AUDIO_EVENT_MEMORY(RemotePlayerEvent_Param1)

		Function function;
		typename StoredType<T>::Type value;
	};

	template<class T1, class T2> class RemotePlayerEvent_Param2 : public RemotePlayerEvent
	{
	public:
		typedef void (RemotePlayer::*Function)(T1, T2);

		RemotePlayerEvent_Param2(RemotePlayerHandle newPlayer, Function newFunction, T1 newValue1, T2 newValue2) :
			RemotePlayerEvent(newPlayer),
			function(newFunction),
			value1(newValue1),
			value2(newValue2)
		{
		}
		virtual void Execute()
		{
			(gRemotePlayers->entries[player.index].player->*function)(value1, value2);
		}
		AUDIO_EVENT_MEMORY(RemotePlayerEvent_Param2)

		Function function;
		T1 value1;
		T2 value2;
	};
}

#endif
