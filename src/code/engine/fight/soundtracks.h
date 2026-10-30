// The fight tracks of the audio: a sound, a mixer setting, a music cue, a reverb preset and a sound zone (unit 0x1087A750 -
// 0x1087D2C0; no assert path, file name guessed). Only the members the actions read are named; the constructors, the
// property lists and the setters are the unit's own and not reconstructed. Member names are the property names.
#ifndef ENGINE_FIGHT_SOUNDTRACKS_H
#define ENGINE_FIGHT_SOUNDTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::SoundTrack (16 vftable slots)
	class SoundTrack : public fight::Track
	{
	public:
		SoundTrack();
		virtual ~SoundTrack();

		// vftable slot 0 (0x1087A9F0), slot 9 (0x1087AF20), slot 10 (0x1087AF30) and slot 15 (0x1087BA20)
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		float timeBegin;  // +0x10
		int unknown14;
		int unknown18;
		int unknown1C;
		fight::Name patch;  // +0x20
		fight::Name trigger;  // +0x28
		fight::Name unknown30;
		float volumeFactor;  // +0x38
		float minDistance;  // +0x3C
		float maxDistance;  // +0x40
		float minPitch;  // +0x44
		float maxPitch;  // +0x48
		float cyclicPhase;  // +0x4C
		float frequency;  // +0x50
		int unknown54;
		fight::Name instanceName;  // +0x58
		bool polledLifetime;  // +0x60
		int triggerType;  // +0x64
	};

	// RTTI: engine::MixerTrack (16 vftable slots)
	class MixerTrack : public fight::Track
	{
	public:
		MixerTrack();
		virtual ~MixerTrack();

		// vftable slot 0 (0x1087AA50), slot 9 (0x1087AAF0), slot 10 (0x1087AAE0) and slot 15 (0x1087AA70)
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		float timeBegin;  // +0x10
		int unknown14;
		int unknown18;
		int unknown1C;
		fight::Name mixer;  // +0x20
		fight::Name category;  // +0x28
		bool fadeIn;  // +0x30
		float fadeTime;  // +0x34
		bool uninstallOnExit;  // +0x38
	};

	// A position in the music: the note, the beat and the bar
	struct MusicTime
	{
		MusicTime()
		{
			note = 0;
			beat = 0;
			bar = 0;
			unknownC = false;
			unknown10 = 0;
		}

		int note;  // +0
		int beat;  // +4
		int bar;  // +8
		bool unknownC;
		int unknown10;
	};

	// What a music fade is told (the track keeps one for the fade out at +0x44 and one for the fade in at +0x70): when it
	// starts and how long it lasts
	struct MusicFade
	{
		MusicTime start;  // +0
		MusicTime length;  // +0x14
	};

	// RTTI: engine::MusicTrack (16 vftable slots)
	class MusicTrack : public fight::Track
	{
	public:
		MusicTrack();
		virtual ~MusicTrack();

		// vftable slot 0 (0x1087AB00), slot 9 (0x1087B110), slot 10 (0x1087B120) and slot 15 (0x1087AB20)
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		float timeBegin;  // +0x10
		int unknown14;
		int unknown18;
		int unknown1C;
		fight::Name cue;  // +0x20
		fight::Name part;  // +0x28
		fight::Name group;  // +0x30
		int unknown38;  // the priority
		bool resetPriority;  // +0x3C
		unsigned char unknown3D[3];
		bool overrideFadeOut;  // +0x40
		unsigned char unknown41[3];
		MusicFade fadeOut;  // +0x44
		bool overrideFadeIn;  // +0x6C
		MusicFade fadeIn;  // +0x70
	};

	// RTTI: engine::ReverbTrack (16 vftable slots)
	class ReverbTrack : public fight::Track
	{
	public:
		ReverbTrack();
		virtual ~ReverbTrack();

		// vftable slot 0 (0x1087AB60), slot 9 (0x1087B1A0), slot 10 (0x1087B1B0) and slot 15 (0x1087AB80)
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		float timeBegin;  // +0x10
		int unknown14;
		int unknown18;
		int unknown1C;
		fight::Name preset;  // +0x20
		float gain;  // +0x28
	};

	// RTTI: engine::SoundZoneTrack (16 vftable slots)
	class SoundZoneTrack : public fight::Track
	{
	public:
		SoundZoneTrack();
		virtual ~SoundZoneTrack();

		// vftable slot 0 (0x1087ABC0), slot 9 (0x1087B230), slot 10 (0x1087B240) and slot 15 (0x1087ABE0)
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		int unknown10;
		int unknown14;
		int unknown18;
		int unknown1C;
		fight::Name zoneName;  // +0x20
		fight::Name reverb;  // +0x28
		fight::Name ambience;  // +0x30
		fight::Name mix;  // +0x38
		int boundaryAction;  // +0x40
	};
}

#endif
