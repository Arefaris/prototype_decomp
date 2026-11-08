// The global at 0x11276374 that the game's sound players reach the audio library's filter through (the class of the
// object is a guess; audio::Filter is an RTTI name, derived from audio::Effect). Only what the game's events use is declared.
#ifndef AUDIO_MASTER_H
#define AUDIO_MASTER_H

namespace audio
{
	class Filter
	{
	public:
		// 0x105BBFF0 (name guess): sets the filter up for a cut-off frequency and a quality (the kind 0 is the low pass)
		void Set(int kind, float cutoff, float quality);
	};

	class Master
	{
	public:
		unsigned char unknown0[0x2420];
		Filter filter;  // +0x2420
	};

	extern Master* gMaster;
}

#endif
