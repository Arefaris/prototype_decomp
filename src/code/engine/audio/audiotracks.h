// The fight tracks of the audio system (RTTI: engine::DialogueTrack, SoundTrack, SoundBoolValueTrack, MixerTrack,
// MusicTrack, ReverbTrack and SoundZoneTrack, each 16 vftable slots over fight::Track). Their members, constructors and
// slot bodies belong to the audio units (0x1087AA00 - 0x1087D1xx, 0x108A86A0 - 0x108A8E40); the fight track unit that
// registers them only needs the sizes, the constructors and the property list functions, so the layouts stay
// unrecovered here. Class names are the RTTI's; the sizes come from the factories' allocations.
#ifndef ENGINE_AUDIO_AUDIOTRACKS_H
#define ENGINE_AUDIO_AUDIOTRACKS_H

#include "code/engine/fight/dialoguetrack.h"
#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// The slots every audio track overrides: 0 the property list, 7 the destructor, 9 and 10 the times, 15
	class SoundTrack : public fight::Track
	{
	public:
		// 0x1087AE90
		SoundTrack();
		virtual ~SoundTrack();
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// ClearProperties 0x1087AA00, RegisterProperties 0x1087C6B0
		static void RegisterProperties();
		static void ClearProperties();

		int unknown10[22];
	};

	class SoundBoolValueTrack : public fight::Track
	{
	public:
		// 0x1087AF60
		SoundBoolValueTrack();
		virtual ~SoundBoolValueTrack();
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// ClearProperties 0x1087AA40, RegisterProperties 0x1087C990
		static void RegisterProperties();
		static void ClearProperties();

		int unknown10[6];
	};

	class MixerTrack : public fight::Track
	{
	public:
		// 0x1087AFD0
		MixerTrack();
		virtual ~MixerTrack();
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// ClearProperties 0x1087AA60, RegisterProperties 0x1087CAA0
		static void RegisterProperties();
		static void ClearProperties();

		int unknown10[12];
	};

	class MusicTrack : public fight::Track
	{
	public:
		// 0x1087B050
		MusicTrack();
		virtual ~MusicTrack();
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// ClearProperties 0x1087AB10, RegisterProperties 0x1087CC10
		static void RegisterProperties();
		static void ClearProperties();

		int unknown10[34];
	};

	class ReverbTrack : public fight::Track
	{
	public:
		// 0x1087B150
		ReverbTrack();
		virtual ~ReverbTrack();
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// ClearProperties 0x1087AB70, RegisterProperties 0x1087D040
		static void RegisterProperties();
		static void ClearProperties();

		int unknown10[8];
	};

	class SoundZoneTrack : public fight::Track
	{
	public:
		// 0x1087B1E0
		SoundZoneTrack();
		virtual ~SoundZoneTrack();
		virtual fight::Property* GetProperty(int index);
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// ClearProperties 0x1087ABD0, RegisterProperties 0x1087D120
		static void RegisterProperties();
		static void ClearProperties();

		int unknown10[14];
	};

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
