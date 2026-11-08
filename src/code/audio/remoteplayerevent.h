// audio::Event and the events the game posts to the audio library's remote players (RTTI: audio::Event,
// audio::RemotePlayerEvent and the templates audio::RemotePlayerEvent_Param1<T> / _Param2<T1, T2>). An event is built
// in the audio thread's ring buffer (class operator new / delete) and runs later in the audio thread: it calls a
// method of the remote player the handle names with the arguments it kept. Names other than the RTTI ones are guesses.
#ifndef AUDIO_REMOTEPLAYEREVENT_H
#define AUDIO_REMOTEPLAYEREVENT_H

#include <string.h>
#include <typeinfo.h>
#include "code/om/dynamicarray.h"
#include "code/om/name.h"
#include "code/om/string.h"
#include "code/om/vector.h"

namespace dsp
{
	// The volumes of a voice for every channel and bin (RTTI: dsp::MixVoiceChannelBinVolumes, 0x240 bytes)
	struct MixVoiceChannelBinVolumes
	{
		float volumes[144];
	};
}

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
		// 0x104A5E20 (behind the jump thunk 0x1003CD62): stops the player; 0x104A2D90 (behind 0x10023DDF): plays it from
		// a position (rounded down to a multiple of 16). Names guessed
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

		// The setters the game's sound players post (their unit's copies; names guessed)
		// 0x104A2DB0
		void SetLoop(bool value);
		// 0x104A2DC0: the volumes of the voice
		void SetVolumes(const dsp::MixVoiceChannelBinVolumes& newVolumes);
		// 0x104A2DE0: one of the five numbers at 0x3E8
		void SetUnknown3E8(unsigned int index, float value);
		// 0x104A5460: the mix busses the player sends to
		void SetMixBuses(const om::DynamicArray<om::ClassName, unsigned short>& newBuses);
		// 0x104A5E30 / 0x104A5E60: two vectors
		void SetPosition(const om::Vector& newPosition);
		void SetVelocity(const om::Vector& newVelocity);
		// 0x104A5E90 - 0x104A5F50: numbers by their place in the player (the pitch and the filters are among them)
		void SetUnknown474(float value);
		void SetUnknown478(float value);
		void SetUnknown498(float value);
		void SetUnknown49C(float value);
		void SetUnknown51C(float value);
		void SetUnknown530(float value);
		void SetUnknown484(float value);
		// 0x105BE360: the name of the file the player plays (not reconstructed)
		void SetFilename(const om::String& newFilename);
		// 0x105BE320: a list of names (not reconstructed)
		void SetNames(const om::DynamicArray<om::String, unsigned short>& newNames);

		unsigned char unknown0[0xb0];
		float channelVolumes[18];  // +0xB0
		float binVolumes[8];  // +0xF8
		dsp::MixVoiceChannelBinVolumes volumes;  // +0x118: for every channel and bin
		unsigned char unknown358[0x3e8 - 0x358];
		float unknown3E8[5];  // +0x3E8
		om::Vector position;  // +0x3FC
		om::Vector velocity;  // +0x408
		unsigned char unknown414[0x444 - 0x414];
		float unknown444;
		unsigned char unknown448[0x474 - 0x448];
		float unknown474;
		float unknown478;
		unsigned char unknown47C[0x484 - 0x47c];
		float unknown484;
		unsigned char unknown488[0x498 - 0x488];
		float unknown498;
		float unknown49C;
		unsigned char unknown4A0[0x4f8 - 0x4a0];
		unsigned int startPosition;  // +0x4F8
		unsigned char unknown4FC[0x510 - 0x4fc];
		bool loop;  // +0x510
		unsigned char unknown511[0x51c - 0x511];
		float unknown51C;
		float unknown520;
		float unknown524;
		float unknown528;
		float unknown52C;
		float unknown530;
		om::DynamicArray<om::ClassName, unsigned short> mixBuses;  // +0x534
		unsigned char unknown53C[0x544 - 0x53c];
		float unknown544;
		unsigned int stopped;  // +0x548
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
	// Names a remote player (0x11276370 holds the table): the index in the low half
	struct RemotePlayerHandle
	{
		RemotePlayerHandle()
		{
		}
		// The table hands the handle out as one word
		RemotePlayerHandle(unsigned int packed) :
			word(packed)
		{
		}

		union
		{
			unsigned int word;
			struct
			{
				unsigned short index;
				unsigned short serial;
			};
		};
	};

	// What a new remote player is made from (the first word is the kind of player, the rest is zero for the game's players)
	struct RemotePlayerParams
	{
		explicit RemotePlayerParams(int newKind) :
			kind(newKind)
		{
			memset(unknown4, 0, sizeof(unknown4));
		}

		int kind;
		unsigned char unknown4[0x44];
	};

	struct RemotePlayerTable
	{
		// 0x105BAE40: makes a remote player (the audio thread is told to make it) and answers its handle (name guessed;
		// the arguments after the parameters are not recovered, the type is the class of the game's player that asks)
		unsigned int Create(const RemotePlayerParams& params, int unknown1, int unknown2, int unknown3, const type_info* owner, int unknown4);
		// 0x105BAF90: lets the player of the handle go
		void Destroy(RemotePlayerHandle handle);

		// The posting members (names after the members of the player they run): each posts an event that calls the
		// member on the player the handle names
		void Play(const RemotePlayerHandle& player);  // 0x104A3C40, position 0
		void SetLoop(const RemotePlayerHandle& player, bool value);  // 0x104A3C90
		void SetFilename(const RemotePlayerHandle& player, const om::String& value);  // 0x104A3CE0
		void SetVolumes(const RemotePlayerHandle& player, const dsp::MixVoiceChannelBinVolumes& value);  // 0x104A3D30
		void SetUnknown3E8(const RemotePlayerHandle& player, unsigned int index, float value);  // 0x104A3D90
		void Stop(const RemotePlayerHandle& player);  // 0x104A6370
		void SetPosition(const RemotePlayerHandle& player, const om::Vector& value);  // 0x104A63C0
		void SetVelocity(const RemotePlayerHandle& player, const om::Vector& value);  // 0x104A6420
		void SetUnknown474(const RemotePlayerHandle& player, float value);  // 0x104A6480
		void SetUnknown478(const RemotePlayerHandle& player, float value);  // 0x104A64D0
		void SetUnknown498(const RemotePlayerHandle& player, float value);  // 0x104A6520
		void SetUnknown49C(const RemotePlayerHandle& player, float value);  // 0x104A6570
		void SetUnknown51C(const RemotePlayerHandle& player, float value);  // 0x104A65C0
		void SetUnknown530(const RemotePlayerHandle& player, float value);  // 0x104A6610
		void SetUnknown484(const RemotePlayerHandle& player, float value);  // 0x104A6660
		void SetNames(const RemotePlayerHandle& player, const om::DynamicArray<om::String, unsigned short>& value);  // 0x104A7470
		// 0x104A58D0: the names of the busses as 64-bit keys
		void SetMixBuses(const RemotePlayerHandle& player, const om::DynamicArray<om::String, unsigned short>& names);

		RemotePlayerEntry* entries;
	};
	extern RemotePlayerTable* gRemotePlayers;

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

	inline void RemotePlayerTable::Play(const RemotePlayerHandle& player)
	{
		new RemotePlayerEvent_Param1<unsigned int>(player, &RemotePlayer::Play, 0);
	}

	inline void RemotePlayerTable::SetLoop(const RemotePlayerHandle& player, bool value)
	{
		new RemotePlayerEvent_Param1<bool>(player, &RemotePlayer::SetLoop, value);
	}

	inline void RemotePlayerTable::SetFilename(const RemotePlayerHandle& player, const om::String& value)
	{
		new RemotePlayerEvent_Param1<const om::String&>(player, &RemotePlayer::SetFilename, value);
	}

	inline void RemotePlayerTable::SetVolumes(const RemotePlayerHandle& player, const dsp::MixVoiceChannelBinVolumes& value)
	{
		new RemotePlayerEvent_Param1<const dsp::MixVoiceChannelBinVolumes&>(player, &RemotePlayer::SetVolumes, value);
	}

	inline void RemotePlayerTable::SetUnknown3E8(const RemotePlayerHandle& player, unsigned int index, float value)
	{
		new RemotePlayerEvent_Param2<unsigned int, float>(player, &RemotePlayer::SetUnknown3E8, index, value);
	}

	inline void RemotePlayerTable::Stop(const RemotePlayerHandle& player)
	{
		new RemotePlayerEvent_Param1<unsigned int>(player, &RemotePlayer::Stop, 0);
	}

	inline void RemotePlayerTable::SetPosition(const RemotePlayerHandle& player, const om::Vector& value)
	{
		new RemotePlayerEvent_Param1<const om::Vector&>(player, &RemotePlayer::SetPosition, value);
	}

	inline void RemotePlayerTable::SetVelocity(const RemotePlayerHandle& player, const om::Vector& value)
	{
		new RemotePlayerEvent_Param1<const om::Vector&>(player, &RemotePlayer::SetVelocity, value);
	}

	inline void RemotePlayerTable::SetUnknown474(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown474, value);
	}

	inline void RemotePlayerTable::SetUnknown478(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown478, value);
	}

	inline void RemotePlayerTable::SetUnknown498(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown498, value);
	}

	inline void RemotePlayerTable::SetUnknown49C(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown49C, value);
	}

	inline void RemotePlayerTable::SetUnknown51C(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown51C, value);
	}

	inline void RemotePlayerTable::SetUnknown530(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown530, value);
	}

	inline void RemotePlayerTable::SetUnknown484(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown484, value);
	}

	inline void RemotePlayerTable::SetNames(const RemotePlayerHandle& player, const om::DynamicArray<om::String, unsigned short>& value)
	{
		new RemotePlayerEvent_Param1<const om::DynamicArray<om::String, unsigned short>&>(player, &RemotePlayer::SetNames, value);
	}
}

#endif
