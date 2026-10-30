// The actions of the audio tracks (unit 0x108E3310 - 0x108E3E00, no assert path; file name guessed).
#include "code/engine/fight/soundactions.h"
#include "code/engine/audio/audiomanager.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108E3900
	MixerAction::MixerAction(MixerTrack* newTrack, int newUnknown28)
		: fight::Action(newTrack->uninstallOnExit ? 0x600 : 0x200), link(newTrack), unknown28(newUnknown28)
	{
	}

	// FUNCTION: ENGINE 0x108E3710
	MixerAction::~MixerAction()
	{
	}

	// FUNCTION: ENGINE 0x108E3980
	bool MixerAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		gAudioEmitterSystem->MixEvent(link.object->mixer, link.object->category, link.object->fadeIn, 1,
			link.object->fadeTime, -1.0f);
		return link.object->uninstallOnExit;
	}

	// FUNCTION: ENGINE 0x108E39D0
	void MixerAction::Slot6()
	{
		gAudioEmitterSystem->MixEvent(link.object->mixer, link.object->category, false, 1, -1.0f, -1.0f);
	}

	// FUNCTION: ENGINE 0x108E3A00
	MusicAction::MusicAction(MusicTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108E3AB0
	// NONMATCHING: the engine keeps the reset flag in a stack word (byte store, then a dword load) behind the two fade structs (7 %)
#ifdef NONMATCHING
	bool MusicAction::Slot5(int arg, float value)
	{
		MusicTrack* track = link.object;
		if (track != 0)
		{
			MusicFade fadeOut;
			MusicFade fadeIn;
			const MusicFade* fadeOutArgument = 0;
			const MusicFade* fadeInArgument = 0;
			if (track->overrideFadeOut)
			{
				fadeOut.start = track->fadeOut.start;
				fadeOut.length = track->fadeOut.length;
				fadeOutArgument = &fadeOut;
			}
			if (track->overrideFadeIn)
			{
				fadeIn.start = track->fadeIn.start;
				fadeIn.length = track->fadeIn.length;
				fadeInArgument = &fadeIn;
			}
			track = link.object;
			MusicChannel::GetInstance()->PlayCue(track->group, track->cue, track->part, fadeOutArgument, fadeInArgument,
				track->unknown38, track->resetPriority);
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x108E3C00
	ReverbAction::ReverbAction(ReverbTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108E3CB0
	bool ReverbAction::Slot5(int arg, float value)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x108E3CC0
	SoundZoneAction::SoundZoneAction(SoundZoneTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108E3D70
	// NONMATCHING: the engine loads the zone manager into edi before the names are copied and keeps the track in eax (33 %)
#ifdef NONMATCHING
	bool SoundZoneAction::Slot5(int arg, float value)
	{
		SoundZoneTrack* track = link.object;
		if (track != 0)
		{
			int action = track->boundaryAction;
			if (action == 0)
			{
				SoundZoneManager* manager = gSoundZoneManager;
				manager->AddZone(track->zoneName, track->reverb, track->ambience, track->mix, action);
			}
			else if (action == 1)
			{
				SoundZoneManager* manager = gSoundZoneManager;
				manager->RemoveZone(track->zoneName);
			}
		}
		return false;
	}
#endif
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E3960
// FUNCTION: ENGINE 0x108E3A70
// FUNCTION: ENGINE 0x108E3C70
// FUNCTION: ENGINE 0x108E3D30
