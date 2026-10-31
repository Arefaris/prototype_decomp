// audio::DecoderSystemStreamServer (RTTI name; the audio library's interface to the files its decoder reads) and
// engine::StreamServer (RTTI name; the engine's implementation: the audio files are in the packages
// "audio\english\audiofile\"). The unit is the audio manager's (0x10844C20 - 0x10845800; file name guessed); names
// other than the RTTI ones are guesses.
#ifndef ENGINE_AUDIO_STREAMSERVER_H
#define ENGINE_AUDIO_STREAMSERVER_H

#include "code/om/string.h"

namespace audio
{
	class DecoderSystemStreamServer
	{
	public:
		// (0x10844CE0 is the engine's out-of-line copy)
		DecoderSystemStreamServer()
		{
		}
		// vftable slot 0: the path of the file of a name
		virtual om::String GetPath(const om::String& name) = 0;
		// vftable slot 1 (0x10844CF0): does nothing
		virtual void Slot1(void* argument)
		{
		}
	};
}

namespace engine
{
	class StreamServer : public audio::DecoderSystemStreamServer
	{
	public:
		// 0x10844EB0
		StreamServer();
		// vftable slot 0 (0x10844EC0): the directory of the audio files, then the name with the extension ".p3d"
		virtual om::String GetPath(const om::String& name);
		// vftable slot 1 (0x10844F30): does nothing
		virtual void Slot1(void* argument);
	};
}

#endif
