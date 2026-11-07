// engine::AudioPlayerSimple and engine::AudioPlayerPhysics (RTTI names; bases engine::AudioPlayer and, for the physics
// player, AudioPlayerSimple): the audio players that drive one remote player of the audio library (the handle at +0xC
// names it; the events they post run in the audio thread). Unit 0x1087F2B0 - 0x10880650 (no assert path; the file name
// is a guess). Only the slots reconstructed are declared with their bodies; names other than the RTTI ones are guesses.
#ifndef ENGINE_AUDIO_AUDIOPLAYERSIMPLE_H
#define ENGINE_AUDIO_AUDIOPLAYERSIMPLE_H

#include "code/audio/remoteplayerevent.h"
#include "code/engine/audio/audioplayer.h"
#include "code/om/allocation.h"

namespace engine
{
	// What a player is made from (the game's sound player factory fills it; the members are unknown but for the name
	// and the three flags the remote player is created with)
	struct AudioPlayerDescription
	{
		const char* name;
		int unknown4;
		int unknown8;
		int unknownC;
		unsigned char unknown10[0x58 - 0x10];
		unsigned char unknown58[4];
	};

	class AudioPlayerSimple : public AudioPlayer
	{
	public:
		// 0x1087F5E0: creates the remote player of the description
		explicit AudioPlayerSimple(const AudioPlayerDescription* description);
		// 0x1087F660 is the body (the audio library's player of the handle goes away); the deleting destructor is
		// 0x1087F8F0 and the class's operator delete 0x1087F640
		virtual ~AudioPlayerSimple();
		static void operator delete(void* memory)
		{
			om::Release(memory, 0x18, 8);
		}
		// vftable slot 1 (0x1087F680): "play" and "stop" are the events it answers
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name);
		// 0x1087F230: hands every item of the update to slot 9
		virtual void Slot2(AudioPlayerUpdate* update);
		// 0x1087FF80
		virtual bool Slot3();
		// 0x1087F740: posts the stop event
		virtual void Slot4();
		// 0x1087FFA0
		virtual bool Slot5();
		// 0x1087F980
		virtual float Slot6(int* unknown);
		// 0x1087F920: only "amplitude" is known
		virtual bool Slot8(const core::Name<core::CaseSensitiveKey>& name, float* value);
		// 0x1087F9C0 (not reconstructed)
		virtual void Slot9(void* item);
		// 0x1087F700: posts the play event
		virtual void Slot10();

		int unknown4;
		int unknown8;
		union
		{
			unsigned int playerId;
			audio::RemotePlayerHandle player;  // +0xC
		};
		__declspec(align(8)) core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// The player of a physics object (a vehicle's engine, say): the simple player and six members
	class AudioPlayerPhysics : public AudioPlayerSimple
	{
	public:
		// 0x1087F7D0
		explicit AudioPlayerPhysics(const AudioPlayerDescription* description);
		// The deleting destructor is 0x1087FFE0 and the class's operator delete 0x1087F810
		static void operator delete(void* memory)
		{
			om::Release(memory, 0x30, 8);
		}

		int unknown18;
		int unknown1C;
		int unknown20;
		float unknown24;
		float unknown28;
		float unknown2C;
	};
}

#endif
