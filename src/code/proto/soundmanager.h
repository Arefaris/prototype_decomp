// proto::SoundManager (RTTI name of the script wrappers): the manager of the game's sound that registers its natives with
// the script context. Unit 0x1049B130 - 0x104A0000 (no assert path; the file names are guesses). Only the signatures of
// the natives are known so far.
#ifndef PROTO_SOUNDMANAGER_H
#define PROTO_SOUNDMANAGER_H

namespace proto
{
	class SoundManager
	{
	public:
		void Native();
		void NativeWithText(const char* text);
		void NativeWithFlag(bool flag);
	};
}

#endif
