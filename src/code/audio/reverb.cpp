// The reverberation effect of the mixer (0x105C3940 - 0x105C4A30).
#include "code/audio/reverb.h"
#include "code/audio/dtask.h"
#include <math.h>
#include <memory.h>

namespace audio
{
	// The delays in samples of the early and the late reflections of the four lines (0x10E2F008 and 0x10E2F048)
	extern const unsigned int gReverbEarlyDelays[4][4];
	extern const unsigned int gReverbLateDelays[4][4];

	// FUNCTION: ENGINE 0x105C3940
	void Reverb::SetUnknown2C(float value)
	{
		unknown2C = value;
	}

	// FUNCTION: ENGINE 0x105C3950
	void Reverb::SetUnknown30(float value)
	{
		unknown30 = value;
	}

	// FUNCTION: ENGINE 0x105C3960
	void Reverb::SetUnknown34(float value)
	{
		unknown34 = value;
	}

	// FUNCTION: ENGINE 0x105C3970
	void Reverb::SetUnknown38(float value)
	{
		unknown38 = value;
	}

	// FUNCTION: ENGINE 0x105C39C0
	void Reverb::SetUnknown44(float value)
	{
		unknown44 = value;
	}

	// FUNCTION: ENGINE 0x105C39D0
	void Reverb::SetDelayLength(unsigned int length)
	{
		if (length != delayLength)
		{
			if (delayLength > 0)
			{
				for (int i = 0; i < 4; i++)
				{
					om::Release(delayLine[i], delayLength * 4, 0x80);
				}
			}
			delayLength = length;
			if (length > 0)
			{
				delayLength = (length - (length & 3)) + 4;
				for (int i = 0; i < 4; i++)
				{
					void* line = om::Allocate("radverb_fdn_mpDelayLine", delayLength * 4, 0x80);
					delayLine[i] = static_cast<float*>(line);
					size_t size = delayLength * 4;
					if (size != 0)
					{
						memset(line, 0, size);
					}
				}
			}
			writePosition = 0;
		}
	}

	// FUNCTION: ENGINE 0x105C3A80
	void Reverb::SetUnknown48(float value)
	{
		unknown48 = value;
	}

	// FUNCTION: ENGINE 0x105C3A90
	void Reverb::SetUnknown4C(float value)
	{
		unknown4C = value;
	}

	// FUNCTION: ENGINE 0x105C3AA0
	void Reverb::SetUnknown50(float value)
	{
		unknown50 = value;
	}

	// FUNCTION: ENGINE 0x105C3AB0
	void Reverb::SetUnknown54(float value)
	{
		unknown54 = value;
	}

	// FUNCTION: ENGINE 0x105C3AC0
	void Reverb::SetUnknown58(float value)
	{
		unknown58 = value;
	}

	// FUNCTION: ENGINE 0x105C3AD0
	void Reverb::SetUnknown5C(float value)
	{
		unknown5C = value;
	}

	// FUNCTION: ENGINE 0x105C3AE0
	void Reverb::SetUnknown60(float value)
	{
		unknown60 = value;
	}

	// FUNCTION: ENGINE 0x105C3AF0
	void Reverb::SetUnknown14(float value)
	{
		unknown14 = value;
	}

	// FUNCTION: ENGINE 0x105C3B00
	Reverb::~Reverb()
	{
		SetDelayLength(0);
		for (int i = 0; i < 4; i++)
		{
			om::Release(earlyRefDelaysInit[i], 0x10, 0x80);
			om::Release(lateRefDelaysInit[i], 0x10, 0x80);
			om::Release(earlyRefCoeffs[i], 0x10, 0x80);
			om::Release(earlyRefDelays[i], 0x10, 0x80);
			om::Release(lateRefCoeffs[i], 0x10, 0x80);
			om::Release(lateRefDelays[i], 0x10, 0x80);
		}
		om::Release(inputLpfStore, 0x10, 0x80);
		om::Release(earlyOutLpfStore, 0x10, 0x80);
		om::Release(lateOutLpfStore, 0x10, 0x80);
		om::Release(dampingLpfStore, 0x10, 0x80);
	}

	// FUNCTION: ENGINE 0x105C3C10
	// EQUIVALENT: the last two coefficient stores of the engine come in the other order and the x87 values are kept in other registers (97.3 %)
	void Reverb::SetLateReflectionMix(float mix)
	{
		mix = Clamp(mix, 0.0f, 1.0f);
		float* first = lateRefCoeffs[0];
		float cosine = cosf(mix * 1.5707964f);
		float sine = sinf(mix * 1.5707964f);
		float negative = cosine * -1.0f;
		first[0] = cosine;
		first[1] = sine;
		float* second = lateRefCoeffs[1];
		second[0] = sine;
		second[1] = negative;
		float* fourth = lateRefCoeffs[3];
		float* third = lateRefCoeffs[2];
		fourth[3] = cosine;
		third[3] = sine;
		fourth[2] = sine;
		third[2] = negative;
	}

	// FUNCTION: ENGINE 0x105C3CB0
	// EQUIVALENT: the engine builds the result of the tolerance test as a byte and tests it again, and keeps one shared exit (27.3 %)
	void Reverb::SetUnknown8(float value)
	{
		bool unchanged = Absolute(value - unknown8) <= 0.00001f;
		if (!unchanged)
		{
			value = Clamp(value, 0.1f, 10.0f);
			unsigned int longest = 0;
			unknown8 = Clamp(value, 0.1f, 10.0f);
			for (int channel = 0; channel < 4; channel++)
			{
				for (unsigned int i = 0; i < 4; i++)
				{
					unsigned int early = static_cast<unsigned int>(static_cast<float>(*(earlyRefDelaysInit[channel] + i)) * unknown8);
					if (early > longest)
					{
						longest = early;
					}
					earlyRefDelays[channel][i] = early;
					unsigned int late = static_cast<unsigned int>(static_cast<float>(lateRefDelaysInit[channel][i]) * unknown8);
					if (late > longest)
					{
						longest = late;
					}
					lateRefDelays[channel][i] = late;
				}
			}
			SetDelayLength(longest);
		}
	}

	// FUNCTION: ENGINE 0x105C3E20
	void Reverb::SetUnknown3C(float value)
	{
		unknown3C = Clamp(value, 0.1f, 1.0f);
		for (int channel = 0; channel < 4; channel++)
		{
			for (unsigned int i = 0; i < 4; i++)
			{
				earlyRefDelays[channel][i] = static_cast<unsigned int>(static_cast<float>(earlyRefDelaysInit[channel][i]) * unknown3C * unknown8);
			}
		}
	}

	// FUNCTION: ENGINE 0x105C3ED0
	// NONMATCHING: ours folds value * 0.7071f + 0.7071f into (value + 1) * 0.7071f, which the engine does not (best 23.6 %)
#ifdef NONMATCHING
	void Reverb::SetUnknown40(float value)
	{
		value = Clamp(value, 0.0f, 1.0f);
		unknown40 = value;
		value = value - 1.0f;
		float first = value * 0.0f + 0.7071f;
		first = first >= 0.0f ? first : 0.0f;
		float fourth = value * 0.35355f + 0.7071f;
		fourth = fourth >= 0.0f ? fourth : 0.0f;
		float third = value * 0.7071f + 0.7071f;
		third = third >= 0.0f ? third : 0.0f;
		float second = value * 1.06065f + 0.7071f;
		second = second >= 0.0f ? second : 0.0f;
		earlyRefCoeffs[0][0] = first;
		earlyRefCoeffs[0][1] = second;
		earlyRefCoeffs[0][2] = third;
		earlyRefCoeffs[0][3] = fourth;
		earlyRefCoeffs[1][0] = second;
		earlyRefCoeffs[1][1] = first;
		earlyRefCoeffs[1][2] = fourth;
		earlyRefCoeffs[1][3] = third;
		earlyRefCoeffs[2][0] = third;
		earlyRefCoeffs[2][1] = fourth;
		earlyRefCoeffs[2][2] = first;
		earlyRefCoeffs[2][3] = second;
		earlyRefCoeffs[3][0] = fourth;
		earlyRefCoeffs[3][1] = third;
		earlyRefCoeffs[3][2] = second;
		earlyRefCoeffs[3][3] = first;
	}
#endif

	// FUNCTION: ENGINE 0x105C4100
	void Reverb::SetParameters(const ReverbParameters& parameters)
	{
		unknown2C = parameters.unknown0;
		unknown34 = parameters.unknown4;
		unknown30 = parameters.unknown8;
		unknown38 = parameters.unknownC;
		SetUnknown44(parameters.unknown40);
		SetUnknown5C(parameters.unknown14);
		SetUnknown8(parameters.unknown18);
		SetUnknown54(parameters.unknown24);
		SetUnknown4C(parameters.unknown28);
		SetUnknown48(parameters.unknown2C);
		SetUnknown60(parameters.unknown30);
		SetLateReflectionMix(parameters.unknown34);
		SetUnknown58(parameters.unknown38);
		SetUnknown50(parameters.unknown3C);
		unknown64 = parameters.unknown1C;
		unknown68 = parameters.unknown20;
	}

	// FUNCTION: ENGINE 0x105C41B0
	void Reverb::ResetReflections()
	{
		unsigned int* early0 = earlyRefDelaysInit[0];
		early0[0] = gReverbEarlyDelays[0][0];
		early0[1] = gReverbEarlyDelays[0][1];
		early0[2] = gReverbEarlyDelays[0][2];
		early0[3] = gReverbEarlyDelays[0][3];
		unsigned int* early1 = earlyRefDelaysInit[1];
		early1[0] = gReverbEarlyDelays[1][0];
		early1[1] = gReverbEarlyDelays[1][1];
		early1[2] = gReverbEarlyDelays[1][2];
		early1[3] = gReverbEarlyDelays[1][3];
		unsigned int* early2 = earlyRefDelaysInit[2];
		early2[0] = gReverbEarlyDelays[2][0];
		early2[1] = gReverbEarlyDelays[2][1];
		early2[2] = gReverbEarlyDelays[2][2];
		early2[3] = gReverbEarlyDelays[2][3];
		unsigned int* early3 = earlyRefDelaysInit[3];
		early3[0] = gReverbEarlyDelays[3][0];
		early3[1] = gReverbEarlyDelays[3][1];
		early3[2] = gReverbEarlyDelays[3][2];
		early3[3] = gReverbEarlyDelays[3][3];
		SetUnknown40(unknown40);
		unsigned int* late0 = lateRefDelaysInit[0];
		late0[0] = gReverbLateDelays[0][0];
		late0[1] = gReverbLateDelays[0][1];
		late0[2] = gReverbLateDelays[0][2];
		late0[3] = gReverbLateDelays[0][3];
		unsigned int* late1 = lateRefDelaysInit[1];
		late1[0] = gReverbLateDelays[1][0];
		late1[1] = gReverbLateDelays[1][1];
		late1[2] = gReverbLateDelays[1][2];
		late1[3] = gReverbLateDelays[1][3];
		unsigned int* late2 = lateRefDelaysInit[2];
		late2[0] = gReverbLateDelays[2][0];
		late2[1] = gReverbLateDelays[2][1];
		late2[2] = gReverbLateDelays[2][2];
		late2[3] = gReverbLateDelays[2][3];
		unsigned int* late3 = lateRefDelaysInit[3];
		late3[0] = gReverbLateDelays[3][0];
		late3[1] = gReverbLateDelays[3][1];
		late3[2] = gReverbLateDelays[3][2];
		late3[3] = gReverbLateDelays[3][3];
		SetLateReflectionMix(unknown28);
		SetUnknown8(1.0f);
	}

	// FUNCTION: ENGINE 0x105C46E0
	// EQUIVALENT: register allocation of the pointer and the zero that clears the allocated arrays (96.1 %)
	void Reverb::InitBuffers()
	{
		for (int i = 0; i < 4; i++)
		{
			earlyRefDelaysInit[i] = static_cast<unsigned int*>(om::Allocate("radverb_fdn_mpuiEarlyRefDelays_INIT", 0x10, 0x80));
			lateRefDelaysInit[i] = static_cast<unsigned int*>(om::Allocate("radverb_fdn_mpuiLateRefDelays_INIT", 0x10, 0x80));
			memset(earlyRefDelaysInit[i], 0, 0x10);
			memset(lateRefDelaysInit[i], 0, 0x10);
		}
		for (int i = 0; i < 4; i++)
		{
			void* earlyCoeffs = om::Allocate("radverb_fdn_mpfEarlyRefCoeffs", 0x10, 0x80);
			earlyRefCoeffs[i] = static_cast<float*>(earlyCoeffs);
			memset(earlyCoeffs, 0, 0x10);
			void* earlyDelays = om::Allocate("radverb_fdn_mpuiEarlyRefDelays", 0x10, 0x80);
			earlyRefDelays[i] = static_cast<unsigned int*>(earlyDelays);
			memset(earlyDelays, 0, 0x10);
			void* lateCoeffs = om::Allocate("radverb_fdn_mpfLateRefCoeffs", 0x10, 0x80);
			lateRefCoeffs[i] = static_cast<float*>(lateCoeffs);
			memset(lateCoeffs, 0, 0x10);
			void* lateDelays = om::Allocate("radverb_fdn_mpuiLateRefDelays", 0x10, 0x80);
			lateRefDelays[i] = static_cast<unsigned int*>(lateDelays);
			memset(lateDelays, 0, 0x10);
		}
		void* store = om::Allocate("radverb_fdn_mpfInputLPFStore", 0x10, 0x80);
		inputLpfStore = static_cast<float*>(store);
		memset(store, 0, 0x10);
		store = om::Allocate("radverb_fdn_mpfEarlyOutLPFStore", 0x10, 0x80);
		earlyOutLpfStore = static_cast<float*>(store);
		memset(store, 0, 0x10);
		store = om::Allocate("radverb_fdn_mpfLateOutLPFStore", 0x10, 0x80);
		lateOutLpfStore = static_cast<float*>(store);
		memset(store, 0, 0x10);
		store = om::Allocate("radverb_fdn_mpfDampingLPFStore", 0x10, 0x80);
		dampingLpfStore = static_cast<float*>(store);
		memset(store, 0, 0x10);
		ResetReflections();
	}

	// FUNCTION: ENGINE 0x105C4330
	// NONMATCHING: the engine steps the input and the buffer pointers separately where ours derives one from the other, scatters its loads differently while smoothing and lays out its loops differently (best 41.3 %)
#ifdef NONMATCHING
	void Reverb::Process(const void* input, void* output, int mode)
	{
		float smoothing = unknown44;
		float rest = 1.0f - smoothing;
		unknown4 = unknown48 * rest + smoothing * unknown4;
		unknownC = unknown4C * rest + smoothing * unknownC;
		unknown10 = unknown50 * rest + unknown10 * smoothing;
		unknown18 = unknown54 * rest + smoothing * unknown18;
		unknown1C = unknown58 * rest + smoothing * unknown1C;
		unknown20 = unknown5C * rest + smoothing * unknown20;
		unknown24 = unknown60 * rest + unknown24 * smoothing;
		SetUnknown3C(unknown64 * rest + unknown3C * smoothing);
		SetUnknown40((1.0f - unknown44) * unknown68 + unknown40 * unknown44);
		const ChannelBuffer* inputs = static_cast<const ChannelBuffer*>(input);
		ChannelBuffer* outputs = static_cast<ChannelBuffer*>(output);
		EffectBuffer* buffers = &buffer0;
		float* wet[8];
		float* scratch[8];
		float* dry[8];
		for (unsigned int i = 0; i < 8; i++)
		{
			dry[i] = inputs[i].aligned;
			wet[i] = buffers[i].aligned;
			dtask::CopyCommand* copy = dtask::AllocateCommand<dtask::CopyCommand>();
			copy->type = 10;
			copy->size = sizeof(dtask::CopyCommand);
			copy->unknown8 = 0;
			copy->source = dry[i];
			copy->destination = wet[i];
			copy->bytes = 0x400;
			scratch[i] = buffers[8 + i].aligned;
			dtask::ClearCommand* clear = dtask::AllocateCommand<dtask::ClearCommand>();
			clear->type = 2;
			clear->size = sizeof(dtask::ClearCommand);
			clear->unknown8 = 0;
			clear->buffer = scratch[i];
			clear->count = 0x100;
			clear->unknown14 = 0.0f;
		}
		dtask::ReverbCommand* command = dtask::AllocateCommand<dtask::ReverbCommand>();
		command->unknown18 = wet[0];
		command->unknown10 = wet[1];
		command->unknownC = wet[4];
		command->unknown14 = wet[5];
		command->unknown1C = wet[6];
		command->unknown20 = wet[7];
		command->unknown24 = wet[2];
		command->unknown34 = scratch[0];
		command->unknown2C = scratch[1];
		command->unknown28 = scratch[4];
		command->unknown30 = scratch[5];
		command->unknown38 = scratch[6];
		command->unknown3C = scratch[7];
		command->unknown40 = scratch[2];
		command->type = 12;
		command->size = sizeof(dtask::ReverbCommand);
		command->unknown8 = 0;
		for (int i = 0; i < 4; i++)
		{
			command->delayLine[i] = delayLine[i];
			command->earlyRefCoeffs[i] = earlyRefCoeffs[i];
			command->earlyRefDelays[i] = earlyRefDelays[i];
			command->lateRefCoeffs[i] = lateRefCoeffs[i];
			command->lateRefDelays[i] = lateRefDelays[i];
		}
		command->inputLpfStore = inputLpfStore;
		command->earlyOutLpfStore = earlyOutLpfStore;
		command->lateOutLpfStore = lateOutLpfStore;
		command->dampingLpfStore = dampingLpfStore;
		command->unknownA4 = unknown20;
		command->unknownA8 = unknown18;
		command->unknownAC = unknown1C;
		command->unknownB0 = unknown4;
		command->unknownB4 = unknown24;
		command->unknownD4 = unknownC;
		command->unknownD8 = unknown10;
		command->unknownDC = unknown14;
		command->delayLength = delayLength;
		command->writePosition = writePosition;
		command->unknownC0 = unknown28;
		command->unknownC4 = unknown2C;
		command->unknownC8 = unknown30;
		command->unknownCC = unknown34;
		command->unknownD0 = unknown38;
		writePosition += 0x100;
		if (writePosition >= delayLength)
		{
			writePosition = writePosition % delayLength;
		}
		for (int i = 0; i < 8; i++)
		{
			dtask::AddCommand* add = dtask::AllocateCommand<dtask::AddCommand>();
			add->type = 5;
			add->size = sizeof(dtask::AddCommand);
			add->unknown8 = 0;
			add->source = buffers[8 + i].aligned;
			add->destination = outputs[i].aligned;
			add->count = 0x100;
		}
	}
#endif

	// FUNCTION: ENGINE 0x105C4880
	// EQUIVALENT: scheduling of the sixteen pointer initialisations (89.2 %)
	Reverb::Reverb() :
		unknown4(0.0f),
		unknown8(0.0f),
		unknownC(0.0f),
		unknown10(0.0f),
		unknown14(0.0f),
		unknown18(0.0f),
		unknown1C(0.0f),
		unknown20(0.0f),
		unknown24(0.0f),
		unknown28(0.5f),
		unknown2C(0.0f),
		unknown30(0.0f),
		unknown34(0.0f),
		unknown38(0.0f),
		unknown3C(1.0f),
		unknown40(0.5f),
		unknown44(0.0f),
		unknown48(0.0f),
		unknown4C(0.0f),
		unknown50(0.0f),
		unknown54(0.0f),
		unknown58(0.0f),
		unknown5C(0.0f),
		unknown60(0.0f),
		unknown64(0.0f),
		unknown68(0.0f),
		delayLength(0),
		writePosition(0)
	{
		InitBuffers();
	}
}

// FUNCTION: ENGINE 0x105C4040
// EQUIVALENT: register allocation (the engine keeps the old end of the queue in a second register)
template dtask::ClearCommand* dtask::AllocateCommand<dtask::ClearCommand>();

// FUNCTION: ENGINE 0x105C4070
// EQUIVALENT: register allocation (the engine keeps the old end of the queue in a second register)
template dtask::ReverbCommand* dtask::AllocateCommand<dtask::ReverbCommand>();

// FUNCTION: ENGINE 0x105C40A0
// EQUIVALENT: register allocation (the engine keeps the old end of the queue in a second register)
template dtask::AddCommand* dtask::AllocateCommand<dtask::AddCommand>();
