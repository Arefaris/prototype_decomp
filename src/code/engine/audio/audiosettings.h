// engine::AudioSettings and engine::AudioSettingsDatabaseObserver (the observer's RTTI name; the settings class has no
// RTTI and its name is a guess from the name its constructor gives the list): the player's audio options. The
// settings are kept as database subjects (SettingAudioMusicVolume, SettingAudioSFXVolume, SettingAudioDialogVolume
// and SettingAudioLatency); the observer tells the settings when one of them changes and they put the value into
// effect (the volumes of the mix, the latency of the renderer's driver). Unit 0x108CE7E0 - 0x108CEDB0 (no assert
// path; the file name is a guess).
#ifndef ENGINE_AUDIOSETTINGS_H
#define ENGINE_AUDIOSETTINGS_H

#include "code/core/name.h"
#include "code/engine/audio/audiomessage.h"
#include "code/engine/dbobserver.h"
#include "code/om/allocation.h"

namespace audio
{
	class DirectSoundRendererDriver;
}

namespace engine
{
	typedef core::Name<core::CaseSensitiveKey> SettingName;

	// The options; the list of sounds it is made on is not used (0x28 bytes)
	class AudioSettings : public AudioSoundList
	{
	public:
		// 0x108CE990
		AudioSettings();
		// 0x108CE830 (the deleting destructor 0x108CE960)
		~AudioSettings();
		OM_ALLOCATION(AudioSettings);

		// 0x108CE840: the step of the latencies that holds the latency (the last step's value when none does)
		unsigned int GetLatencyIndex(unsigned int latency);
		// 0x108CE860
		unsigned int GetLatency(unsigned int index);
		// 0x108CE870: the DirectSound driver of the renderer, null when it uses another
		static audio::DirectSoundRendererDriver* GetDirectSoundDriver();
		// 0x108CE8A0 / 0x108CE8B0: the volume of the database (tenths) as the mix's number and back
		float GetVolume(int tenths);
		int GetTenths(float volume);
		// 0x108CE9C0: puts the value of the setting into effect
		void Apply(const SettingName& setting, int value);
		// 0x108CEAC0: the value the setting has now
		int GetValue(const SettingName& setting);
	};

	// 0x108CE820
	AudioSettings* GetAudioSettings();
	// 0x108CEC70 / 0x108CEC90: make the one instance and take it down
	void CreateAudioSettings();
	void DestroyAudioSettings();

	// Tells the settings of the changes of the four subjects (4 bytes)
	class AudioSettingsDatabaseObserver : public DBObserver
	{
	public:
		// 0x108CECF0: adds the subjects
		AudioSettingsDatabaseObserver();
		// 0x108CEBB0: takes them out
		~AudioSettingsDatabaseObserver();
		OM_ALLOCATION(AudioSettingsDatabaseObserver);

		// vftable slot 0 (0x108CEC50): a change of a subject
		virtual void OnDBSlot0(int a, int b);

		// 0x108CEC00: a subject of the setting's current value, observed
		void AddSetting(const SettingName& setting);
		// 0x108CE8D0
		void RemoveSetting(const SettingName& setting);
	};

	// 0x108CED40 / 0x108CED60
	void CreateAudioSettingsObserver();
	void DestroyAudioSettingsObserver();

	// The names of the settings (initialised by another unit)
	extern SettingName gMusicVolumeSetting;
	extern SettingName gSfxVolumeSetting;
	extern SettingName gDialogVolumeSetting;
	extern SettingName gLatencySetting;
	// The names of the emitter groups the volumes belong to (another unit)
	extern SettingName gMusicName;
	extern SettingName gSfxName;
	extern SettingName gDuckName;
	extern SettingName gDialogName;
	extern SettingName gUserMixName;
}

#endif
