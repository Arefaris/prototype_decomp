// engine::AudioPlayer (RTTI name): what the audio system keeps for a sound source of the game (an ambience, a
// helicopter, a vehicle): the game's players derive from it (proto::SoundPlayerAmbience, SoundPlayerHelicopter and
// SoundPlayerVehicle, each with a header of its own) and answer the five calls every player gets; the base class has the defaults of the three
// optional ones. Of the classes only what is reconstructed is declared. Names other than the RTTI ones are guesses.
#ifndef ENGINE_AUDIO_AUDIOPLAYER_H
#define ENGINE_AUDIO_AUDIOPLAYER_H

#include "code/core/name.h"

namespace om
{
	class DynamicObject;
}

namespace engine
{
	class AudioPlayerMessage;

	class AudioPlayer
	{
	public:
		// 0x104A3440 (the constructor) / 0x104A2E40 (the destructor body); the deleting destructor is 0x104A2E80
		AudioPlayer();
		virtual ~AudioPlayer()
		{
		}
		// vftable slots 1 - 5
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name) = 0;
		// The settings of the player, a dynamic object whose properties the player takes over one by one
		virtual void Slot2(om::DynamicObject* properties) = 0;
		virtual bool Slot3() = 0;
		virtual void Slot4() = 0;
		virtual bool Slot5() = 0;
		// vftable slots 6 - 8 (0x104A2E50, 0x104A2E60, 0x104A2E70): the defaults
		virtual float Slot6(int* unknown);
		virtual void Slot7(int a);
		virtual bool Slot8(const core::Name<core::CaseSensitiveKey>& name, float* value);
	};
}

#endif
