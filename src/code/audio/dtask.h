// The command queue of the mixer's dsp thread (the allocation tag "dtask::TaskQueue"): the effects write small command
// structures one behind the other into a buffer that the dsp thread executes. Every command starts with its type, its
// size and a word that is zero when it is written.
#ifndef AUDIO_DTASK_H
#define AUDIO_DTASK_H

namespace om
{
	// 0x105BA610: the value rounded up to a multiple of the alignment (name guessed)
	unsigned int AlignUp(unsigned int value, unsigned int alignment);
}

namespace dtask
{
	struct Command
	{
		unsigned int type;
		unsigned int size;
		unsigned int unknown8;
	};

	// The buffer of the queue: its size, its start and the end of what has been written (0x11276820 / 24 / 28)
	extern unsigned int gQueueSize;
	extern char* gQueueBase;
	extern char* gQueueCursor;

	// A command of the type T at the end of the queue; every command takes a multiple of 16 bytes
	template<class T> T* AllocateCommand()
	{
		char* command = gQueueCursor;
		gQueueCursor = command + om::AlignUp(sizeof(T), 0x10);
		return reinterpret_cast<T*>(command);
	}

	// Copies bytes from one channel buffer to another (type 10)
	struct CopyCommand : public Command
	{
		float* destination;
		float* source;
		unsigned int bytes;
	};

	// Sets a channel buffer to zero (type 2)
	struct ClearCommand : public Command
	{
		float* buffer;
		unsigned int count;
		float unknown14;
	};

	// Adds one channel buffer to another (type 5)
	struct AddCommand : public Command
	{
		float* source;
		float* destination;
		unsigned int count;
	};

	// The reverb on 8 channels with its delay lines, coefficients and filter states (type 12)
	struct ReverbCommand : public Command
	{
		float* unknownC;
		float* unknown10;
		float* unknown14;
		float* unknown18;
		float* unknown1C;
		float* unknown20;
		float* unknown24;
		float* unknown28;
		float* unknown2C;
		float* unknown30;
		float* unknown34;
		float* unknown38;
		float* unknown3C;
		float* unknown40;
		float* delayLine[4];  // 0x44
		float* earlyRefCoeffs[4];  // 0x54
		unsigned int* earlyRefDelays[4];  // 0x64
		float* lateRefCoeffs[4];  // 0x74
		unsigned int* lateRefDelays[4];  // 0x84
		float* inputLpfStore;  // 0x94
		float* earlyOutLpfStore;
		float* lateOutLpfStore;
		float* dampingLpfStore;
		float unknownA4;
		float unknownA8;
		float unknownAC;
		float unknownB0;
		float unknownB4;
		unsigned int delayLength;  // 0xB8
		unsigned int writePosition;
		float unknownC0;
		float unknownC4;
		float unknownC8;
		float unknownCC;
		float unknownD0;
		float unknownD4;
		float unknownD8;
		float unknownDC;
	};

	// The compressor and limiter on up to eight channels (type 11)
	struct CompressorLimiterCommand : public Command
	{
		float* source[8];  // 0xC
		float* destination[8];  // 0x2C
		float* delayed[8];  // 0x4C
		float* previousPeak;  // 0x6C
		float* buffer;  // 0x70
		bool unknown74;
		float unknown78;
		float unknown7C;
		bool unknown80;
		float unknown84;
		float unknown88;
		float unknown8C;
		float unknown90;
		unsigned int unknown94;
		float unknown98;
		float unknown9C;
		unsigned int channelCount;  // 0xA0
		bool unknownA4;
	};
}

#endif
