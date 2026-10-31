// engine::ThreadEntryCallback (RTTI name; the callback the audio engine's threads are created with): puts the thread on
// the audio heap. Unit 0x10844C20 - 0x10845800 (the audio manager's; file name guessed).
#ifndef ENGINE_AUDIO_AUDIOTHREADCALLBACK_H
#define ENGINE_AUDIO_AUDIOTHREADCALLBACK_H

#include "code/om/thread.h"

namespace engine
{
	class ThreadEntryCallback : public om::ThreadEntryCallback
	{
	public:
		// vftable slot 0 (0x10844F50): the thread allocates from heap 11
		virtual void OnThreadEntry(om::Thread* thread);
	};
}

#endif
