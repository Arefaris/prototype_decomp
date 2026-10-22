// The compressor and limiter effect of the mixer (RTTI: audio::CompressorLimiter; its allocation tags are named
// "comp_limit_*"). It delays the signal of up to eight channels by a look-ahead and follows the peaks of the channels to
// reduce the gain.
#ifndef AUDIO_COMPRESSORLIMITER_H
#define AUDIO_COMPRESSORLIMITER_H

#include "code/audio/effect.h"
#include "code/om/allocation.h"

namespace audio
{
	class CompressorLimiter : public Effect
	{
	public:
		// 0x105C4E50
		CompressorLimiter();
		// 0x105C4F60
		virtual ~CompressorLimiter();
		// 0x105C4F90
		virtual void Process(const void* input, void* output, int mode);
		OM_ALLOCATION(CompressorLimiter);

		// 0x105C4B40: the number of channels (at most eight) and with it their delay buffers of 256 samples
		void SetChannelCount(unsigned int count);
		void SetUnknown8(bool value);
		// 0x105C4C60: the threshold (clamped to the range of the limit when the limiter is on)
		void SetUnknownC(float value);
		void SetUnknown18(bool value);
		// 0x105C4C20
		void SetUnknown1C(float value);
		// 0x105C4AC0: the gain of the limiter derived from the threshold and the limit
		void UpdateUnknown20();
		void SetUnknown24(float value);
		void SetUnknown28(float value);
		void SetUnknown2C(float value);
		void SetUnknown3C(float value);
		void SetUnknown40(float value);
		void SetUnknown44(bool value);

		unsigned int channelCount;  // 4
		bool unknown8;
		float unknownC;
		float unknown10;
		float unknown14;
		bool unknown18;
		float unknown1C;
		float unknown20;
		float unknown24;
		float unknown28;
		float unknown2C;
		float unknown30;
		float unknown34;
		unsigned int unknown38;
		float unknown3C;
		float unknown40;
		bool unknown44;
		float unknown48;
		bool unknown4C;
		float* previousPeak;  // 0x50
		float* delayedBuffer[8];  // 0x54
		EffectBuffer buffer;  // 0x74
	};
}

#endif
