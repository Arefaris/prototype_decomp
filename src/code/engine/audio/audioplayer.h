// engine::AudioPlayer (RTTI name): what the audio system keeps for a sound source of the game (an ambience, a
// helicopter, a vehicle): the game's players derive from it (proto::SoundPlayerAmbience, SoundPlayerHelicopter and
// SoundPlayerVehicle) and answer the five calls every player gets; the base class has the defaults of the three
// optional ones. Of the classes only what is reconstructed is declared. Names other than the RTTI ones are guesses.
#ifndef ENGINE_AUDIO_AUDIOPLAYER_H
#define ENGINE_AUDIO_AUDIOPLAYER_H

#include "code/core/name.h"

namespace engine
{
	class AudioPlayerMessage;
	// What the audio system hands the players every frame: a list of items they walk (the first five slots are unknown)
	class AudioPlayerUpdate
	{
	public:
		virtual void Slot0() = 0;
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		virtual void* First() = 0;
		virtual void* Next(void* item) = 0;
	};

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
		virtual void Slot2(AudioPlayerUpdate* update) = 0;
		virtual bool Slot3() = 0;
		virtual void Slot4() = 0;
		virtual bool Slot5() = 0;
		// vftable slots 6 - 8 (0x104A2E50, 0x104A2E60, 0x104A2E70): the defaults
		virtual float Slot6(int* unknown);
		virtual void Slot7(int a);
		virtual bool Slot8(const core::Name<core::CaseSensitiveKey>& name, float* value);
	};
}

namespace proto
{
	// The sound players of the game (RTTI: proto::SoundPlayerAmbience, SoundPlayerHelicopter, SoundPlayerVehicle)
	class SoundPlayerAmbience : public engine::AudioPlayer
	{
	public:
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name);
		virtual void Slot2(engine::AudioPlayerUpdate* update);
		virtual bool Slot3();
		virtual void Slot4();
		virtual bool Slot5();
		virtual void Slot7(int a);
	};

	class SoundPlayerHelicopter : public engine::AudioPlayer
	{
	public:
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name);
		virtual void Slot2(engine::AudioPlayerUpdate* update);
		virtual bool Slot3();
		virtual void Slot4();
		virtual bool Slot5();
		virtual void Slot7(int a);
	};

	class SoundPlayerVehicle : public engine::AudioPlayer
	{
	public:
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name);
		virtual void Slot2(engine::AudioPlayerUpdate* update);
		virtual bool Slot3();
		virtual void Slot4();
		virtual bool Slot5();
		virtual void Slot7(int a);
	};
}

#endif
