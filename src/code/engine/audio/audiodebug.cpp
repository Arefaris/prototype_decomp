// The debug hooks of the audio system that do nothing in this build (code/engine/audio/audiodebug.cpp; the file name is a guess, the unit
// starts at 0x10895650). Names are guesses.
#include "code/om/string.h"

namespace engine
{
	class AudioDebug
	{
	public:
		// 0x10895650
		void SetVolume(float volume);

		int spewMode;
	};

	// FUNCTION: ENGINE 0x10895650
	void AudioDebug::SetVolume(float volume)
	{
	}

	// FUNCTION: ENGINE 0x10895720
	void SetAudioDebugOutput(bool enable)
	{
	}

	// FUNCTION: ENGINE 0x10895730
	void SetAudioDebugRendering(bool enable)
	{
	}

	// FUNCTION: ENGINE 0x10895740
	void SetAudioGroupVisible(const om::String& group, bool visible)
	{
	}
}
