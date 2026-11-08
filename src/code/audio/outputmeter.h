// The meter of the audio output (names guessed; the class has no RTTI): the peak of each channel with the last time it was
// beaten, and a ring of the load of the last updates. One instance exists at a time (0x112768E0).
#ifndef AUDIO_OUTPUTMETER_H
#define AUDIO_OUTPUTMETER_H

namespace audio
{
	class OutputMeter
	{
	public:
		// 0x105E47C0
		OutputMeter();
		// 0x105E4880
		~OutputMeter();
		// 0x105E48F0: the instance
		static OutputMeter* Get();
		// 0x105E48A0 / 0x105E48C0 / 0x105E48E0: the lock around the meter's values
		void Lock();
		void Unlock();
		bool IsLocked() const;
		// 0x105E4900: the time the measuring starts from
		void Restart();

		float peak[8];  // 0
		float held[8];  // 0x20
		unsigned int heldTime[8];  // 0x40
		int unknown60;
		// The ring of the load of the last updates; the constructor clears its first word as a whole
		union
		{
			float history[32];  // 0x64
			unsigned int firstWord;
		};
		int historyIndex;  // 0xE4
		bool unknownE8;
		bool unknownE9;
		unsigned int startTime;  // 0xEC
		char section[0x18];  // 0xF0: a critical section
		bool locked;  // 0x108
	};
}

#endif
