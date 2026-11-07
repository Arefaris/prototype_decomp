// engine::AudioPlayerSimple and engine::AudioPlayerPhysics (RTTI names; bases engine::AudioPlayer and, for the physics
// player, AudioPlayerSimple): the audio players that drive one remote player of the audio library (the handle at +0xC
// names it; the events they post run in the audio thread). Unit 0x1087F2B0 - 0x10880650 (no assert path; the file name
// is a guess). Only the slots reconstructed are declared with their bodies; names other than the RTTI ones are guesses.
#ifndef ENGINE_AUDIO_AUDIOPLAYERSIMPLE_H
#define ENGINE_AUDIO_AUDIOPLAYERSIMPLE_H

#include "code/audio/remoteplayerevent.h"
#include "code/engine/audio/audioplayer.h"

namespace engine
{
	class AudioPlayerSimple : public AudioPlayer
	{
	public:
		// vftable slot 1 (0x1087F680): "play" and "stop" are the events it answers
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name);
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
		virtual void Slot9(void* unknown);
		// 0x1087F700: posts the play event
		virtual void Slot10();

		int unknown4;
		int unknown8;
		audio::RemotePlayerHandle player;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};
}

#endif
