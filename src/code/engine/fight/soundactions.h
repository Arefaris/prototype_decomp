// The actions of the audio tracks (unit 0x108E3310 - 0x108E3E00, no assert path; file name guessed): they start a mix, a
// music cue, a reverb preset or a sound zone with the settings of their track. The tracks are in soundtracks.h.
#ifndef ENGINE_FIGHT_SOUNDACTIONS_H
#define ENGINE_FIGHT_SOUNDACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/soundtracks.h"

namespace engine
{
	// RTTI: engine::MixerAction (9 vftable slots, size 0x2C): applies the mix of its track while it runs
	class MixerAction : public fight::Action
	{
	public:
		// 0x108E3900
		MixerAction(MixerTrack* newTrack, int newUnknown28);
		// 0x108E3710 (deleting destructor 0x108E3730)
		virtual ~MixerAction();

		// vftable slot 5 (0x108E3980) and slot 6 (0x108E39D0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<MixerTrack> link;  // +0x1C
		int unknown28;
	};

	// RTTI: engine::MusicAction (9 vftable slots, size 0x28): starts the cue of its track
	class MusicAction : public fight::Action
	{
	public:
		// 0x108E3A00
		MusicAction(MusicTrack* newTrack, core::IRefCount* owner);

		// vftable slot 5 (0x108E3AB0)
		virtual bool Slot5(int arg, float value);

		core::Link<MusicTrack> link;  // +0x1C
	};

	// RTTI: engine::ReverbAction (9 vftable slots, size 0x28)
	class ReverbAction : public fight::Action
	{
	public:
		// 0x108E3C00
		ReverbAction(ReverbTrack* newTrack, core::IRefCount* owner);

		// vftable slot 5 (0x108E3CB0): does nothing
		virtual bool Slot5(int arg, float value);

		core::Link<ReverbTrack> link;  // +0x1C
	};

	// RTTI: engine::SoundZoneAction (9 vftable slots, size 0x28): makes or removes the sound zone of its track
	class SoundZoneAction : public fight::Action
	{
	public:
		// 0x108E3CC0
		SoundZoneAction(SoundZoneTrack* newTrack, core::IRefCount* owner);

		// vftable slot 5 (0x108E3D70)
		virtual bool Slot5(int arg, float value);

		core::Link<SoundZoneTrack> link;  // +0x1C
	};
}

#endif
