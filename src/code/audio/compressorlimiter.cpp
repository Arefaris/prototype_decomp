// The compressor and limiter effect of the mixer (0x105C4A70 - 0x105C5120).
#include "code/audio/compressorlimiter.h"
#include "code/audio/dtask.h"
#include <math.h>
#include <memory.h>

namespace audio
{
	// FUNCTION: ENGINE 0x105C4A70
	void CompressorLimiter::SetUnknown44(bool value)
	{
		unknown44 = value;
	}

	// FUNCTION: ENGINE 0x105C4A80
	void CompressorLimiter::SetUnknown40(float value)
	{
		unknown40 = value;
	}

	// FUNCTION: ENGINE 0x105C4A90
	void CompressorLimiter::SetUnknown3C(float value)
	{
		unknown3C = value;
	}

	// FUNCTION: ENGINE 0x105C4AA0
	void CompressorLimiter::SetUnknown8(bool value)
	{
		unknown8 = value;
	}

	// FUNCTION: ENGINE 0x105C4AB0
	void CompressorLimiter::SetUnknown18(bool value)
	{
		unknown18 = value;
	}

	// FUNCTION: ENGINE 0x105C4AC0
	void CompressorLimiter::UpdateUnknown20()
	{
		if (unknown8)
		{
			unknown20 = sqrtf(unknownC / unknown1C);
		}
		else
		{
			unknown20 = 1.0f;
		}
	}

	// FUNCTION: ENGINE 0x105C4B40
	void CompressorLimiter::SetChannelCount(unsigned int count)
	{
		if (count > 8)
		{
			count = 8;
		}
		if (previousPeak == 0)
		{
			previousPeak = static_cast<float*>(om::Allocate("comp_limit_mpPreviousPeak", 0x20, 0x80));
			memset(previousPeak, 0, 0x20);
		}
		if (count != channelCount)
		{
			if (count > channelCount)
			{
				for (unsigned int i = channelCount; i < count; i++)
				{
					void* memory = om::Allocate("comp_limit_mpDelayedBuffer", 0x400, 0x80);
					delayedBuffer[i] = static_cast<float*>(memory);
					memset(memory, 0, 0x400);
				}
			}
			else
			{
				for (unsigned int i = count; i < channelCount; i++)
				{
					om::Release(delayedBuffer[i], 0x400, 0x80);
					delayedBuffer[i] = 0;
				}
			}
			channelCount = count;
		}
	}

	// FUNCTION: ENGINE 0x105C4C20
	void CompressorLimiter::SetUnknown1C(float value)
	{
		unknown1C = Clamp(value, 0.01f, 4.0f);
	}

	// FUNCTION: ENGINE 0x105C4C60
	void CompressorLimiter::SetUnknownC(float value)
	{
		if (unknown18)
		{
			unknownC = Clamp(value, 0.01f, unknown1C);
		}
		else
		{
			unknownC = Clamp(value, 0.01f, 4.0f);
		}
		unknown14 = sqrtf(unknownC);
	}

	// FUNCTION: ENGINE 0x105C4CD0
	void CompressorLimiter::SetUnknown24(float value)
	{
		value = Clamp(value, 0.0001f, 1.0f);
		unknown24 = value;
		unknown30 = 1.0f - expf(-2.2f / (value * 48000.0f));
	}

	// FUNCTION: ENGINE 0x105C4D40
	void CompressorLimiter::SetUnknown28(float value)
	{
		value = Clamp(value, 0.01f, 10.0f);
		unknown28 = value;
		unknown34 = 1.0f - expf(-2.2f / (value * 48000.0f));
	}

	// FUNCTION: ENGINE 0x105C4DB0
	void CompressorLimiter::SetUnknown2C(float value)
	{
		value = Clamp(value, 0.0f, 0.0053333333f);
		unknown2C = value;
		unsigned int samples = static_cast<unsigned int>(value * 48000.0f);
		unknown38 = samples - (samples & 3);
	}

	// FUNCTION: ENGINE 0x105C4E50
	CompressorLimiter::CompressorLimiter() :
		channelCount(0),
		unknown8(false),
		unknownC(0.5f),
		unknown10(0.5f),
		unknown18(true),
		unknown1C(0.95f),
		unknown24(0.0001f),
		unknown28(3.0f),
		unknown2C(0.001f),
		unknown3C(0.85f),
		unknown40(1.0f),
		unknown44(false),
		unknown48(1.0f),
		unknown4C(true),
		previousPeak(0)
	{
		SetUnknown1C(0.95f);
		SetUnknownC(unknownC);
		UpdateUnknown20();
		SetUnknown24(unknown24);
		SetUnknown28(unknown28);
		SetUnknown2C(unknown2C);
		SetChannelCount(8);
	}

	// FUNCTION: ENGINE 0x105C4F60
	CompressorLimiter::~CompressorLimiter()
	{
		SetChannelCount(0);
		if (previousPeak != 0)
		{
			om::Release(previousPeak, 0x20, 0x80);
		}
	}

	// FUNCTION: ENGINE 0x105C4F90
	void CompressorLimiter::Process(const void* input, void* output, int mode)
	{
		UpdateUnknown20();
		const EffectBuffer* sources = static_cast<const EffectBuffer*>(input);
		EffectBuffer* destinations = static_cast<EffectBuffer*>(output);
		float* source[8];
		float* destination[8];
		for (unsigned int i = 0; i < channelCount; i++)
		{
			source[i] = sources[i].aligned;
			destination[i] = destinations[i].aligned;
		}
		if (!unknown18)
		{
			for (unsigned int i = 0; i < channelCount; i++)
			{
				dtask::CopyCommand* command = dtask::AllocateCommand<dtask::CopyCommand>();
				command->type = 10;
				command->size = sizeof(dtask::CopyCommand);
				command->unknown8 = 0;
				command->source = source[i];
				command->destination = destination[i];
				command->bytes = 0x400;
			}
		}
		else
		{
			dtask::CompressorLimiterCommand* command = dtask::AllocateCommand<dtask::CompressorLimiterCommand>();
			command->type = 11;
			command->size = sizeof(dtask::CompressorLimiterCommand);
			command->unknown8 = 0;
			for (unsigned int i = 0; i < channelCount; i++)
			{
				command->source[i] = source[i];
				command->destination[i] = destination[i];
				command->delayed[i] = delayedBuffer[i];
			}
			command->previousPeak = previousPeak;
			command->buffer = buffer.aligned;
			command->unknown74 = unknown8;
			command->unknown78 = unknownC;
			command->unknown7C = unknown14;
			command->unknown80 = unknown18;
			command->unknown84 = unknown1C;
			command->unknown88 = unknown20;
			command->unknown8C = unknown30;
			command->unknown90 = unknown34;
			command->unknown94 = unknown38;
			command->unknown98 = unknown3C;
			command->unknown9C = unknown40;
			command->channelCount = channelCount;
			command->unknownA4 = unknown44;
		}
	}
}

// FUNCTION: ENGINE 0x105C4010
// EQUIVALENT: register allocation (the engine keeps the old end of the queue in a second register; 50.0 %)
template dtask::CopyCommand* dtask::AllocateCommand<dtask::CopyCommand>();

// FUNCTION: ENGINE 0x105C4E20
// EQUIVALENT: register allocation (the engine keeps the old end of the queue in a second register)
template dtask::CompressorLimiterCommand* dtask::AllocateCommand<dtask::CompressorLimiterCommand>();
