// The reverberation effect of the mixer (RTTI: audio::Reverb; its allocation tags and buffers are named "radverb_fdn_*").
// Four feedback delay lines with early and late reflections for 16 channel buffers.
#ifndef AUDIO_REVERB_H
#define AUDIO_REVERB_H

#include "code/audio/effect.h"
#include "code/om/allocation.h"

namespace audio
{
	// The description of a reverb as the mixer stores it (a bank of floats; names guessed from their offsets)
	struct ReverbParameters
	{
		float unknown0;
		float unknown4;
		float unknown8;
		float unknownC;
		float unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
		float unknown20;
		float unknown24;
		float unknown28;
		float unknown2C;
		float unknown30;
		float unknown34;
		float unknown38;
		float unknown3C;
		float unknown40;
	};

	class Reverb : public Effect
	{
	public:
		// 0x105C4880
		Reverb();
		// 0x105C3B00
		virtual ~Reverb();
		// 0x105C4330
		virtual void Process(const void* input, void* output, int mode);
		OM_ALLOCATION(Reverb);

		// The values the mixer sets, one setter each (names guessed from their offsets)
		void SetUnknown2C(float value);
		void SetUnknown30(float value);
		void SetUnknown34(float value);
		void SetUnknown38(float value);
		void SetUnknown44(float value);
		void SetUnknown48(float value);
		void SetUnknown4C(float value);
		void SetUnknown50(float value);
		void SetUnknown54(float value);
		void SetUnknown58(float value);
		void SetUnknown5C(float value);
		void SetUnknown60(float value);
		void SetUnknown14(float value);
		// 0x105C4100: takes over the parameters of the mixer's description of the reverb
		void SetParameters(const ReverbParameters& parameters);
		void SetUnknown3C(float value);
		void SetUnknown40(float value);
		// 0x105C3C10: the coefficients of the late reflections for a mix of 0 to 1 (sine and cosine of a quarter turn)
		void SetLateReflectionMix(float mix);
		// 0x105C3CB0: scales the delays of the reflections and the length of the delay lines
		void SetUnknown8(float value);
		// 0x105C39D0: the length of the four feedback delay lines in samples (rounded up to a multiple of four)
		void SetDelayLength(unsigned int length);

		float unknown4;
		float unknown8;
		float unknownC;
		float unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
		float unknown20;
		float unknown24;
		float unknown28;
		float unknown2C;
		float unknown30;
		float unknown34;
		float unknown38;
		float unknown3C;
		float unknown40;
		float unknown44;
		float unknown48;
		float unknown4C;
		float unknown50;
		float unknown54;
		float unknown58;
		float unknown5C;
		float unknown60;
		float unknown64;
		float unknown68;
		unsigned int delayLength;  // 0x6C
		unsigned int writePosition;  // 0x70
		float* delayLine[4];  // 0x74
		float* earlyRefCoeffs[4];  // 0x84
		unsigned int* earlyRefDelays[4];  // 0x94
		float* lateRefCoeffs[4];  // 0xA4
		unsigned int* lateRefDelays[4];  // 0xB4
		unsigned int* earlyRefDelaysInit[4];  // 0xC4
		unsigned int* lateRefDelaysInit[4];  // 0xD4
		float* inputLpfStore;  // 0xE4
		float* earlyOutLpfStore;  // 0xE8
		float* lateOutLpfStore;  // 0xEC
		float* dampingLpfStore;  // 0xF0
		EffectBuffer buffer0;
		EffectBuffer buffer1;
		EffectBuffer buffer2;
		EffectBuffer buffer3;
		EffectBuffer buffer4;
		EffectBuffer buffer5;
		EffectBuffer buffer6;
		EffectBuffer buffer7;
		EffectBuffer buffer8;
		EffectBuffer buffer9;
		EffectBuffer buffer10;
		EffectBuffer buffer11;
		EffectBuffer buffer12;
		EffectBuffer buffer13;
		EffectBuffer buffer14;
		EffectBuffer buffer15;

	private:
		// 0x105C46E0: allocates the arrays and the stores and loads the defaults
		void InitBuffers();
		// 0x105C41B0: the default delays and reflection coefficients
		void ResetReflections();
	};
}

#endif
