// engine::AudioManager (class name guessed from the system name "AudioManager" its constructor registers; no RTTI):
// the singleton that runs the audio subsystems once a frame. Unit around 0x10844C00 - 0x10845800 (no assert path;
// directory and file name are guesses). The subsystems live in other units and are only declared here; all their
// names are guesses.
#ifndef ENGINE_AUDIO_AUDIOMANAGER_H
#define ENGINE_AUDIO_AUDIOMANAGER_H

#include "code/core/name.h"
#include "code/om/string.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace engine
{
	// The audio system (another unit)
	class AudioSystem
	{
	public:
		static AudioSystem* Get();
		// 0x108712D0
		void Update(UpdateContext context);
		int GetUnknown28() const
		{
			return unknown28;
		}
		// 0x10871140: makes the sound group (its limits)
		void AddSoundGroup(const om::String& name, unsigned int maxSounds, unsigned int maxSoundsPerInstance);
		// 0x10871240: lets the group interrupt another
		void AddInterrupt(const om::String& group, const om::String& other);
		// 0x108712B0
		void SetGroupEnabled(const om::String& group, bool enabled);
		// 0x1086FC30
		void DisableAllGroups();

		int unknown0[0x28 / 4];
		int unknown28;
	};

	// An audio subsystem with a frame update (another unit, singleton at 0x11315408)
	class AudioMixer
	{
	public:
		// 0x10855460
		static AudioMixer* Get();
		// 0x108583F0: stops the dialogue line of that number (name guess)
		void StopDialogue(int id);
		// 0x1085AB40
		void Update(UpdateContext context);
		// 0x10859460: starts a dialogue line (names guessed): the two zeros, then three names, the object it comes
		// from, the shortest and the longest wait in milliseconds, two numbers, a name and a subtitle text
		void PlayDialogue(int unknown1, int unknown2, const core::Name<core::CaseSensitiveKey>& first,
			const core::Name<core::CaseSensitiveKey>& second, const core::Name<core::CaseSensitiveKey>& third,
			GameObjectHandle object, int minimum, int maximum, float fourth, float fifth,
			const core::Name<core::CaseSensitiveKey>& sixth, const om::String& text);
	};

	// The audio clock (another unit, singleton at 0x113275F0): advances by the milliseconds since its last update
	class AudioClock
	{
	public:
		// 0x10AA9B40
		static AudioClock* Get();
		// 0x10AA9B50
		void Update();
	};

	struct MusicFade;

	// The music channel of a name (another unit; names guessed)
	class MusicChannel
	{
	public:
		// 0x1087E450: the music system the fight tracks start their cues on (the global at 0x11316C70; the engine's
		// callers push the cue's arguments before they call it)
		static MusicChannel* GetInstance();
		// 0x1087EF30: starts the cue of a group (names guessed): the group, the cue, the part, the fades out and in
		// (null for none), the priority and whether it resets the priority
		void PlayCue(const core::Name<core::CaseSensitiveKey>& group, const core::Name<core::CaseSensitiveKey>& cue,
			const core::Name<core::CaseSensitiveKey>& part, const MusicFade* fadeOut, const MusicFade* fadeIn, int priority,
			unsigned int resetPriority);
		// 0x1087E450
		static MusicChannel* __stdcall Get(const core::Name<core::CaseSensitiveKey>& channel);
		// 0x1087EFF0: plays the music of the group
		void Play(const core::Name<core::CaseSensitiveKey>& music, const core::Name<core::CaseSensitiveKey>& group,
			int priority, bool loop);
		// 0x1087EC50
		void Stop();
	};

	// The sound zones (another unit; the global at 0x11316AC0, names guessed): a zone is made of the name of its
	// reverb, its ambience and its mix; the names are passed by value
	class SoundZoneManager
	{
	public:
		// 0x1087A4A0
		void AddZone(core::Name<core::CaseSensitiveKey> zone, core::Name<core::CaseSensitiveKey> reverb,
			core::Name<core::CaseSensitiveKey> ambience, core::Name<core::CaseSensitiveKey> mix, int boundaryAction);
		// 0x1087A630
		void RemoveZone(core::Name<core::CaseSensitiveKey> zone);
	};
	extern SoundZoneManager* gSoundZoneManager;

	// The audio emitters' system (another unit; the global at 0x11316A90)
	class AudioEmitterSystem
	{
	public:
		// 0x10877B00: a mix event (names guessed): the two names, the flag, the numbers
		void MixEvent(const core::Name<core::CaseSensitiveKey>& first, const core::Name<core::CaseSensitiveKey>& second,
			bool flag, int unknown1, float value, float unknown2);
		// 0x10878010
		void Update(UpdateContext context);
		// 0x10877E60 / 0x10877850: the volume a setting has (the first by two names, the second by one; 1 when
		// it has none)
		float Unknown10877E60(const core::Name<core::CaseSensitiveKey>* first,
			const core::Name<core::CaseSensitiveKey>* second);
		float Unknown10877850(const core::Name<core::CaseSensitiveKey>* name);
		// 0x10877E30: sets the volume of the second name's setting (the first is the mix's)
		void Unknown10877E30(const core::Name<core::CaseSensitiveKey>* first,
			const core::Name<core::CaseSensitiveKey>* second, float volume);
	};
	extern AudioEmitterSystem* gAudioEmitterSystem;

	class AudioUpdatable;

	// The list node of an AudioUpdatable
	struct AudioUpdatableLink
	{
		AudioUpdatableLink* next;
		AudioUpdatableLink* previous;
	};

	// What the manager's list holds: objects told the time step every frame (slot 8), linked through a node at +0x50
	class AudioUpdatable
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Update(float dt);

		int unknown4[0x13];
		AudioUpdatableLink link;

		// The object a node is in (null for no node)
		static AudioUpdatable* FromLink(AudioUpdatableLink* link)
		{
			return link != 0 ? (AudioUpdatable*)((char*)link - 0x50) : 0;
		}
	};

	class AudioManager
	{
	public:
		static AudioManager* Get();
		// 0x108459A0: plays the patch in the group (the two numbers are 0 for the scripts' calls; meaning unknown)
		void PlayPatch(const core::Name<core::CaseSensitiveKey>& patch, const core::Name<core::CaseSensitiveKey>& group,
			int unknown1, int unknown2);
		// Runs the audio subsystems for a frame, and the registered objects when time passes
		void Update(UpdateContext context);
		// 0x10844D40: the simulation step's audio part (the audio system, the listener and the sound zones)
		void Unknown10844D40(UpdateContext context);

		static AudioUpdatableLink* sFirst;
		static AudioUpdatableLink* sLast;
	};
}

#endif
