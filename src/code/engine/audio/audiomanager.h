// engine::AudioManager (class name guessed from the system name "AudioManager" its constructor registers; no RTTI):
// the singleton that runs the audio subsystems once a frame. Unit around 0x10844C00 - 0x10845800 (no assert path;
// directory and file name are guesses). The subsystems live in other units and are only declared here; all their
// names are guesses.
#ifndef ENGINE_AUDIO_AUDIOMANAGER_H
#define ENGINE_AUDIO_AUDIOMANAGER_H

#include "code/core/name.h"
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

	// The audio emitters' system (another unit; the global at 0x11316A90)
	class AudioEmitterSystem
	{
	public:
		// 0x10878010
		void Update(UpdateContext context);
		// 0x10877E60 / 0x10877850: the volume a setting has (the first by two names, the second by one; 1 when
		// it has none)
		float Unknown10877E60(const core::Name<core::CaseSensitiveKey>* first,
			const core::Name<core::CaseSensitiveKey>* second);
		float Unknown10877850(const core::Name<core::CaseSensitiveKey>* name);
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
		// Runs the audio subsystems for a frame, and the registered objects when time passes
		void Update(UpdateContext context);

		static AudioUpdatableLink* sFirst;
		static AudioUpdatableLink* sLast;
	};
}

#endif
