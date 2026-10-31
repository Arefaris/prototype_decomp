// engine::AudioMixer (class name guessed; no RTTI): the audio subsystem that plays dialogue and runs a frame update, a
// singleton at 0x11315408. Unit 0x108550E0 - 0x1085AB40 (no assert path; directory and file name are guesses). Of the
// unit only the singleton's getter is reconstructed.
#include "code/engine/audio/audiomanager.h"

namespace engine
{
	// The singleton (0x11315408; created by the engine's start-up)
	extern AudioMixer* gAudioMixer;

	// FUNCTION: ENGINE 0x10855460
	AudioMixer* AudioMixer::Get()
	{
		return gAudioMixer;
	}
}
