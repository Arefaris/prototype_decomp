// The fight tracks of the audio system (RTTI: engine::DialogueTrack, SoundTrack, SoundBoolValueTrack, MixerTrack,
// MusicTrack, ReverbTrack and SoundZoneTrack, each 16 vftable slots over fight::Track). Their members, constructors and
// slot bodies belong to the audio units (0x1087AA00 - 0x1087D1xx, 0x108A86A0 - 0x108A8E40); the fight track unit that
// registers them only needs the sizes, the constructors and the property list functions, so the layouts stay
// unrecovered here. Class names are the RTTI's; the sizes come from the factories' allocations.
#ifndef ENGINE_AUDIO_AUDIOTRACKS_H
#define ENGINE_AUDIO_AUDIOTRACKS_H

#include "code/engine/fight/dialoguetrack.h"
#include "code/engine/fight/trackfactory.h"

namespace fight
{
	// The tracks a track owns, as the head of a singly linked list (the engine's kept copies of the constructor 0x105A7A60
	// and of the destructor 0x105A7B20, which deletes every track of the list; name guessed)
	class TrackChildren
	{
	public:
		TrackChildren();
		~TrackChildren();

		Track* head;
	};
}

namespace engine
{
	// The slots every audio track overrides: 0 the property list, 7 the destructor, 9 and 10 the times, 15
	class SoundTrack : public fight::Track
	{
	public:
		// 0x1087AE90
		SoundTrack();
		// The destructor is the compiler's (0x1087AF40, the deleting destructor 0x1087B9F0)
		// 0x1087A9F0
		virtual fight::Property* GetProperty(int index);
		// 0x1087AF20
		virtual float GetTimeBegin() const;
		// 0x1087AF30
		virtual float Slot10() const;
		// 0x1087BA20
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The members the properties write (the order of the property list)
		bool SetTimeBegin(float value);
		bool SetPatch(const fight::Name& value);
		bool SetTrigger(const fight::Name& value);
		bool SetVolumeFactor(float value);
		bool SetMinDistance(float value);
		bool SetMaxDistance(float value);
		bool SetMinPitch(float value);
		bool SetMaxPitch(float value);
		bool SetCyclicPhase(float value);
		bool SetInstanceName(const fight::Name& value);
		bool SetFrequency(float value);
		bool SetPolledLifetime(bool value);
		bool SetTriggerType(int value);

		// ClearProperties 0x1087AA00, RegisterProperties 0x1087C6B0
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float unknown14;
		fight::TrackChildren children;  // +0x18
		// The names sit at multiples of 8
		int unknown1C;
		fight::Name patch;  // +0x20
		fight::Name trigger;  // +0x28
		fight::Name unknown30;
		float volumeFactor;  // +0x38
		float minDistance;
		float maxDistance;
		float minPitch;
		float maxPitch;
		float cyclicPhase;
		float frequency;  // +0x50
		int unknown54;
		fight::Name instanceName;  // +0x58
		bool polledLifetime;  // +0x60
		int triggerType;  // +0x64
	};

	extern fight::Property** gSoundTrackProperties;

	class SoundBoolValueTrack : public fight::Track
	{
	public:
		// 0x1087AF60
		SoundBoolValueTrack();
		// The destructor is the compiler's (0x1087AFB0, the deleting destructor 0x1087BC00)
		// 0x1087AA30
		virtual fight::Property* GetProperty(int index);
		// 0x1087AF90
		virtual float GetTimeBegin() const;
		// 0x1087AFA0
		virtual float Slot10() const;
		// 0x1087BC20
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		bool SetPatch(const fight::Name& value);
		bool SetControl(const fight::Name& value);
		bool SetValue(bool value);

		// ClearProperties 0x1087AA40, RegisterProperties 0x1087C990
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name patch;  // +0x10
		fight::Name control;  // +0x18
		bool value;  // +0x20
		float timeBegin;  // +0x24
	};

	extern fight::Property** gSoundBoolValueTrackProperties;

	class MixerTrack : public fight::Track
	{
	public:
		// 0x1087AFD0
		MixerTrack();
		// The destructor is the compiler's (0x1087B030, the deleting destructor 0x1087BCC0)
		// 0x1087AA50
		virtual fight::Property* GetProperty(int index);
		// 0x1087AAF0
		virtual float GetTimeBegin() const;
		// 0x1087AAE0
		virtual float Slot10() const;
		// 0x1087AA70
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		bool SetFadeTime(float value);
		bool SetMixer(const fight::Name& value);
		bool SetCategory(const fight::Name& value);
		bool SetFadeIn(bool value);
		bool SetUninstallOnExit(bool value);

		// ClearProperties 0x1087AA60, RegisterProperties 0x1087CAA0
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float unknown14;
		fight::TrackChildren children;  // +0x18
		int unknown1C;
		fight::Name mixer;  // +0x20
		fight::Name category;  // +0x28
		bool fadeIn;  // +0x30
		float fadeTime;  // +0x34
		bool uninstallOnExit;  // +0x38
		int unknown3C;
	};

	extern fight::Property** gMixerTrackProperties;

	class MusicTrack : public fight::Track
	{
	public:
		// 0x1087B050
		MusicTrack();
		// The destructor is the compiler's (0x1087B130, the deleting destructor 0x1087BCF0)
		// 0x1087AB00
		virtual fight::Property* GetProperty(int index);
		// 0x1087B110
		virtual float GetTimeBegin() const;
		// 0x1087B120
		virtual float Slot10() const;
		// 0x1087AB20
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		bool SetGroup(const fight::Name& value);
		bool SetCue(const fight::Name& value);
		bool SetPart(const fight::Name& value);
		bool SetPriority(int value);
		bool SetResetPriority(bool value);
		bool SetOverrideFadeOut(bool value);
		bool SetFadeoutStartBar(int value);
		bool SetFadeoutStartBeat(int value);
		bool SetFadeoutStartNote(int value);
		bool SetFadeoutLengthBar(int value);
		bool SetFadeoutLengthBeat(int value);
		bool SetFadeoutLengthNote(int value);
		bool SetOverrideFadeIn(bool value);
		bool SetFadeinStartBar(int value);
		bool SetFadeinStartBeat(int value);
		bool SetFadeinStartNote(int value);
		bool SetFadeinLengthBar(int value);
		bool SetFadeinLengthBeat(int value);
		bool SetFadeinLengthNote(int value);

		// ClearProperties 0x1087AB10, RegisterProperties 0x1087CC10
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float unknown14;
		fight::TrackChildren children;  // +0x18
		int unknown1C;
		fight::Name cue;  // +0x20
		fight::Name part;  // +0x28
		fight::Name group;  // +0x30
		int priority;  // +0x38
		// The flags sit at 4-byte slots (three bytes of padding behind each)
		bool resetPriority;  // +0x3C
		unsigned char padding3D[3];
		bool overrideFadeOut;  // +0x40
		unsigned char padding41[3];
		int fadeoutStartNote;  // +0x44
		int fadeoutStartBeat;
		int fadeoutStartBar;
		int unknown50;
		bool unknown54;
		unsigned char padding55[3];
		int fadeoutLengthNote;  // +0x58
		int fadeoutLengthBeat;
		int fadeoutLengthBar;
		int unknown64;
		bool unknown68;
		unsigned char padding69[3];
		bool overrideFadeIn;  // +0x6C
		unsigned char padding6D[3];
		int fadeinStartNote;  // +0x70
		int fadeinStartBeat;
		int fadeinStartBar;
		int unknown7C;
		bool unknown80;
		unsigned char padding81[3];
		int fadeinLengthNote;  // +0x84
		int fadeinLengthBeat;
		int fadeinLengthBar;
		int unknown90;
		bool unknown94;
		unsigned char padding95[3];
	};

	extern fight::Property** gMusicTrackProperties;

	class ReverbTrack : public fight::Track
	{
	public:
		// 0x1087B150
		ReverbTrack();
		// The destructor is the compiler's (0x1087B1C0, the deleting destructor 0x1087BD20)
		// 0x1087AB60
		virtual fight::Property* GetProperty(int index);
		// 0x1087B1A0
		virtual float GetTimeBegin() const;
		// 0x1087B1B0
		virtual float Slot10() const;
		// 0x1087AB80
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetTimeBegin(float value);
		bool SetPreset(const fight::Name& value);
		bool SetGain(float value);

		// ClearProperties 0x1087AB70, RegisterProperties 0x1087D040
		static void RegisterProperties();
		static void ClearProperties();

		float timeBegin;  // +0x10
		float unknown14;
		fight::TrackChildren children;  // +0x18
		int unknown1C;
		fight::Name preset;  // +0x20
		float gain;  // +0x28
		int unknown2C;
	};

	extern fight::Property** gReverbTrackProperties;

	class SoundZoneTrack : public fight::Track
	{
	public:
		// 0x1087B1E0
		SoundZoneTrack();
		// The destructor is the compiler's (0x1087B250, the deleting destructor 0x1087BD50)
		// 0x1087ABC0
		virtual fight::Property* GetProperty(int index);
		// 0x1087B230
		virtual float GetTimeBegin() const;
		// 0x1087B240
		virtual float Slot10() const;
		// 0x1087ABE0
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		bool SetZoneName(const fight::Name& value);
		bool SetReverb(const fight::Name& value);
		bool SetAmbience(const fight::Name& value);
		bool SetMix(const fight::Name& value);
		bool SetBoundaryAction(int value);

		// ClearProperties 0x1087ABD0, RegisterProperties 0x1087D120
		static void RegisterProperties();
		static void ClearProperties();

		// Not set by the constructor (slots 9 and 10 read them)
		float unknown10;
		float unknown14;
		fight::TrackChildren children;  // +0x18
		int unknown1C;
		fight::Name zoneName;  // +0x20
		fight::Name reverb;  // +0x28
		fight::Name ambience;  // +0x30
		fight::Name mix;  // +0x38
		int boundaryAction;  // +0x40
		int unknown44;
	};

	extern fight::Property** gSoundZoneTrackProperties;

	// The 27-byte factory makers and the registration of the audio tracks (0x108082A0 - 0x10808360 and 0x10808380)
	fight::TrackFactory* CreateDialogueTrackFactory(const char* name);
	fight::TrackFactory* CreateSoundTrackFactory(const char* name);
	fight::TrackFactory* CreateSoundBoolValueTrackFactory(const char* name);
	fight::TrackFactory* CreateMixerTrackFactory(const char* name);
	fight::TrackFactory* CreateMusicTrackFactory(const char* name);
	fight::TrackFactory* CreateReverbTrackFactory(const char* name);
	fight::TrackFactory* CreateSoundZoneTrackFactory(const char* name);
	void RegisterAudioTrackFactories(fight::TrackRegistry* registry);
}

#endif
