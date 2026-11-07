// engine::AudioCue (RTTI name; base content::LoadObject): the load object the audio library's music cue entities are
// handed out in; it keeps one counted reference to the entity. Unit 0x1087E3C0 - 0x1087EC70 (with the music
// channel; no assert path, the file name is a guess). Names other than the RTTI one are guesses.
#ifndef ENGINE_AUDIO_AUDIOCUE_H
#define ENGINE_AUDIO_AUDIOCUE_H

#include "code/om/atgcontent.h"

namespace engine
{
	class AudioCue : public content::LoadObject
	{
	public:
		// 0x1087EA50: counts the entity
		explicit AudioCue(om::Entity* newEntity);
		// The destructor is the compiler's (0x1087EAB0, the deleting destructor 0x1087EAF0)
		// 0x1087E650
		virtual void Slot3(int unused);
		// 0x1087E6B0
		virtual bool IsReady();
		// 0x1087E540 (the allocation's tag, an empty string)
		OM_ALLOCATION(AudioCue);

		om::EntityReference reference;  // 8
	};
}

#endif
