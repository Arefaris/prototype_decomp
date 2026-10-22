// The signal processing effects of the audio mixer (RTTI: audio::Effect and its derived classes audio::Filter,
// audio::Reverb and audio::CompressorLimiter). An effect is processed once per mixing step on the channel buffers of
// its voice.
#ifndef AUDIO_EFFECT_H
#define AUDIO_EFFECT_H

namespace audio
{
	// The value between lo and hi that is nearest to the value (0x105C4B10 is the instance for unsigned int)
	template<class T> inline T Clamp(const T& value, const T& lo, const T& hi)
	{
		if (value >= lo && value <= hi)
		{
			return value;
		}
		if (value <= hi)
		{
			return lo;
		}
		return hi;
	}

	// The floats are clamped by one comparison more at the end (they are kept inline in the effects)
	template<> inline float Clamp<float>(const float& value, const float& lo, const float& hi)
	{
		if (value >= lo && value <= hi)
		{
			return value;
		}
		return value > hi ? hi : lo;
	}

	// 0.0f as a variable of the engine (0x10D94F78, shared with the other units' copies of the same constant)
	extern const float gZero;

	inline float Absolute(float value)
	{
		return value >= gZero ? value : -0.0f - value;
	}

	// A channel buffer of the mixer, as the effects receive it (the same shape as the effects' own buffers)
	struct ChannelBuffer
	{
		char slack[0x80];
		float samples[0x100];
		float* aligned;
	};

	// Trigonometric, exponential and root helpers of the effects (names guessed)
	float Cosine(float angle);
	float Sine(float angle);
	float Select(float test, float whenPositive, float whenNegative);
	float Exponential(float exponent);
	float SquareRoot(float value);
	float SquareRootOfPower(float value);

	class Effect
	{
	public:
		virtual ~Effect()
		{
		}
		// 0x105BB740: adds the input channels to the output channels (the derived effects replace it)
		virtual void Process(const void* input, void* output, int mode);
	};

	// A buffer of a channel: 256 samples that start at the pointer rounded down to 128 bytes, so the room before them
	// (shared with the end of the previous channel) must be 128 bytes
	struct EffectBuffer
	{
		// 0x105C4B00
		float* GetAligned();
		EffectBuffer() :
			aligned(reinterpret_cast<float*>(reinterpret_cast<unsigned int>(samples) & 0xFFFFFF80))
		{
		}
		char slack[0x80];
		float samples[0x100];
		float* aligned;
	};
}

#endif
