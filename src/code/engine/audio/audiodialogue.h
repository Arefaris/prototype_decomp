// The load objects of the audio dialogue unit (RTTI: engine::AudioDialoguePersonalityLoader,
// engine::AudioDialogueSubtitleLoader; both derive from content::ObjectLoader2): the loaders of the dialogue
// personalities and of the subtitles of the dialogue lines. Their loading functions (vftable slot 5) are not
// reconstructed. Names other than the RTTI ones are guesses.
#ifndef ENGINE_AUDIO_AUDIODIALOGUE_H
#define ENGINE_AUDIO_AUDIODIALOGUE_H

#include "code/core/criticalsection.h"
#include "code/core/name.h"
#include "code/om/allocation.h"
#include "code/om/atgcontent.h"

namespace engine
{
	class AudioDialoguePersonalityLoader : public content::ObjectLoader2
	{
	public:
		// 0x10856470 (the engine keeps this copy); the destructor is 0x108564B0, the deleting destructor 0x108564C0
		AudioDialoguePersonalityLoader()
		{
		}
		// 0x1085B140
		virtual void Load(void* object, void* name, void* source, void* unknown, void* inventory);
		OM_ALLOCATION(AudioDialoguePersonalityLoader);
	};

	// A critical section that is made and deleted with the object that holds it (24 bytes; name guessed)
	struct DialogueLock
	{
		DialogueLock()
		{
			core::CriticalSectionInit(section);
		}
		~DialogueLock()
		{
			core::CriticalSectionDelete(section);
		}

		unsigned char section[0x18];
	};

	class __declspec(align(8)) AudioDialogueSubtitleLoader : public content::ObjectLoader2
	{
	public:
		// 0x10858230; the destructor is 0x10858280, the deleting destructor 0x108582A0
		AudioDialogueSubtitleLoader();
		// 0x108599D0
		virtual void Load(void* object, void* name, void* source, void* unknown, void* inventory);
		OM_ALLOCATION(AudioDialogueSubtitleLoader);

		DialogueLock lock;  // +8
		core::Name<core::CaseSensitiveKey> name;  // +0x20
	};
}

#endif
