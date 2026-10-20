// pure3d animation channels (unit around 0x10734F00 - 0x10738E00 with the channel loader; file name guessed from the
// classes). Names are guesses.
#include <new>
#include <string.h>

#include "code/core/refptr.h"
#include "code/pure3d/channel.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10736110
	Channel::Channel() : mode(-1), unknown8(0), name(0, 1)
	{
	}

	// FUNCTION: ENGINE 0x10736640
	Channel::~Channel()
	{
		Clear();
	}

	// FUNCTION: ENGINE 0x10736150
	void Channel::Clear()
	{
		name.SetText(0);
	}

	// FUNCTION: ENGINE 0x10736140
	void Channel::Relocate(int base)
	{
	}

	// FUNCTION: ENGINE 0x10736650
	SimpleChannel::SimpleChannel(unsigned int newCount, AnimationMemoryBlock* newBlock)
	{
		block = newBlock;
		count = newCount;
		frames = 0;
		offset = -1;
		if (count > 0)
		{
			if (block == 0)
			{
				frames = new short[count];
			}
			else
			{
				frames = (short*)block->Allocate(count * 2, 3);
				block->AddRef();
			}
			memset(frames, 0, count * 2);
		}
	}

	// FUNCTION: ENGINE 0x107366D0
	SimpleChannel::~SimpleChannel()
	{
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10736160
	void SimpleChannel::Clear()
	{
		Channel::Clear();
		if (block == 0)
		{
			delete[] frames;
			frames = 0;
			return;
		}
		if (offset == -1)
		{
			core::SafeRelease(block);
		}
		frames = 0;
	}

	// FUNCTION: ENGINE 0x10734F00
	void SimpleChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			frames = (short*)(offset + base);
		}
	}

	// FUNCTION: ENGINE 0x107366F0
	IntChannel::IntChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) : SimpleChannel(newCount, newBlock)
	{
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new int[count];
			}
			else
			{
				values = (int*)block->Allocate(count * 4, 3);
			}
		}
	}

	// FUNCTION: ENGINE 0x10736760
	IntChannel::~IntChannel()
	{
		IntChannel::Clear();
	}

	// FUNCTION: ENGINE 0x107361A0
	void IntChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10734F60
	void IntChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (int*)((base + count * 2 + 3 + offset) & ~3);
		}
	}

	// FUNCTION: ENGINE 0x10734F90
	unsigned int IntChannel::GetType()
	{
		return 'TNI';
	}

	// FUNCTION: ENGINE 0x10734FA0
	void IntChannel::GetValue(FrameTime time, int* out)
	{
		ChannelKeys<int> keys;
		keys.Set(mode, count, frames, values);
		keys.EvaluateFrame(time, out);
	}

	// FUNCTION: ENGINE 0x10734FE0
	void IntChannel::GetValue(float time, int* out)
	{
		ChannelKeys<int> keys;
		keys.Set(mode, count, frames, values);
		keys.Evaluate(FrameTime(time), out);
	}

	// FUNCTION: ENGINE 0x10736780
	Float1Channel::Float1Channel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		SimpleChannel(newCount, newBlock)
	{
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new float[count];
			}
			else
			{
				values = (float*)block->Allocate(count * 4, 3);
			}
		}
	}

	// FUNCTION: ENGINE 0x107367F0
	Float1Channel::~Float1Channel()
	{
		Float1Channel::Clear();
	}

	// FUNCTION: ENGINE 0x107361D0
	void Float1Channel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735030
	void Float1Channel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (float*)((base + count * 2 + 3 + offset) & ~3);
		}
	}

	// FUNCTION: ENGINE 0x10735060
	unsigned int Float1Channel::GetType()
	{
		return '1TLF';
	}

	// FUNCTION: ENGINE 0x10735070
	void Float1Channel::GetValue(FrameTime time, float* out)
	{
		ChannelKeys<float> keys;
		keys.Set(mode, count, frames, values);
		keys.EvaluateFrame(time, out);
	}

	// FUNCTION: ENGINE 0x107350B0
	void Float1Channel::GetValue(float time, float* out)
	{
		ChannelKeys<float> keys;
		keys.Set(mode, count, frames, values);
		keys.Evaluate(FrameTime(time), out);
	}

	// FUNCTION: ENGINE 0x10735100
	void Float1Channel::GetDelta(float previousTime, float time, float* out, float length, bool cycle)
	{
		ChannelKeys<float> keys;
		keys.Set(mode, count, frames, values);
		keys.GetDelta(previousTime, time, out, length, cycle);
	}

	// FUNCTION: ENGINE 0x10736810
	Float2Channel::Float2Channel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		SimpleChannel(newCount, newBlock)
	{
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new Float2[count];
			}
			else
			{
				values = (Float2*)block->Allocate(count * 8, 3);
			}
		}
	}

	// FUNCTION: ENGINE 0x10736880
	Float2Channel::~Float2Channel()
	{
		Float2Channel::Clear();
	}

	// FUNCTION: ENGINE 0x10736200
	void Float2Channel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735150
	void Float2Channel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (Float2*)((base + count * 2 + 3 + offset) & ~3);
		}
	}

	// FUNCTION: ENGINE 0x10735180
	unsigned int Float2Channel::GetType()
	{
		return '2TLF';
	}

	// FUNCTION: ENGINE 0x10735190
	void Float2Channel::GetValue(FrameTime time, Float2* out)
	{
		ChannelKeys<Float2> keys;
		keys.Set(mode, count, frames, values);
		keys.EvaluateFrame(time, out);
	}

	// FUNCTION: ENGINE 0x107351D0
	void Float2Channel::GetValue(float time, Float2* out)
	{
		ChannelKeys<Float2> keys;
		keys.Set(mode, count, frames, values);
		keys.Evaluate(FrameTime(time), out);
	}

	// FUNCTION: ENGINE 0x10734F20
	bool SimpleChannel::FindKeys(float frame, unsigned int* index0, unsigned int* index1)
	{
		ChannelKeysBase keys;
		keys.Set(mode, count, frames);
		return keys.FindKeys(frame, index0, index1);
	}

	// FUNCTION: ENGINE 0x10736F00
	BoolChannel::BoolChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) : SimpleChannel(newCount, newBlock)
	{
		unsigned int words = ((count - 1) >> 5) + 1;
		values = 0;
		if (block == 0)
		{
			values = new unsigned int[words];
		}
		else
		{
			values = (unsigned int*)block->Allocate(words * 4, 3);
		}
		memset(values, 0, words * 4);
	}

	// FUNCTION: ENGINE 0x10736F80
	BoolChannel::~BoolChannel()
	{
		BoolChannel::Clear();
	}

	// FUNCTION: ENGINE 0x107363D0
	void BoolChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735670
	unsigned int BoolChannel::GetType()
	{
		return 'LOOB';
	}

	// FUNCTION: ENGINE 0x10735680
	void BoolChannel::GetKey(unsigned int index, float* frame, bool* out)
	{
		unsigned int word = index >> 2;
		*out = (values[word] & (1 << (index - word * 4))) > 0;
		*frame = (float)frames[index];
	}

	// FUNCTION: ENGINE 0x107356D0
	void BoolChannel::GetValue(float time, bool* out)
	{
		unsigned int index0;
		unsigned int index1;
		FindKeys(time, &index0, &index1);
		unsigned int offset = (index0 >> 5) * 4;
		*out = (*(unsigned int*)((char*)values + offset) & (1 << (index0 - offset * 8))) > 0;
	}

	// FUNCTION: ENGINE 0x10736FA0
	ColourChannel::ColourChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		SimpleChannel(newCount, newBlock)
	{
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new unsigned int[count];
			}
			else
			{
				values = (unsigned int*)block->Allocate(count * 4, 3);
			}
		}
	}

	// FUNCTION: ENGINE 0x10737010
	ColourChannel::~ColourChannel()
	{
		ColourChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10736400
	void ColourChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735720
	void ColourChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (unsigned int*)((base + count * 2 + 3 + offset) & ~3);
		}
	}

	// FUNCTION: ENGINE 0x10735750
	unsigned int ColourChannel::GetType()
	{
		return 'RLC';
	}

	// FUNCTION: ENGINE 0x10735760
	void ColourChannel::GetKey(int index, float* frame, unsigned int* out)
	{
		*frame = (float)frames[index];
		*out = values[index];
	}

	// FUNCTION: ENGINE 0x10736E70
	EntityChannel::EntityChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		SimpleChannel(newCount, newBlock)
	{
		values = 0;
		if (block == 0)
		{
			values = new Entity*[count];
		}
		else
		{
			values = (Entity**)block->Allocate(count * 4, 3);
		}
		memset(values, 0, count * 4);
	}

	// FUNCTION: ENGINE 0x10736EE0
	EntityChannel::~EntityChannel()
	{
		EntityChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10736380
	void EntityChannel::Clear()
	{
		for (unsigned int i = 0; i < count; i++)
		{
			core::SafeRelease(values[i]);
		}
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x107355F0
	unsigned int EntityChannel::GetType()
	{
		return 'TNE';
	}

	// FUNCTION: ENGINE 0x10735600
	void EntityChannel::GetKey(int index, float* frame, Entity** out)
	{
		*frame = (float)frames[index];
		*out = values[index];
	}

	// FUNCTION: ENGINE 0x10735630
	void EntityChannel::GetValue(float time, Entity** out)
	{
		unsigned int index0;
		unsigned int index1;
		FindKeys(time, &index0, &index1);
		*out = values[index0];
	}

	// FUNCTION: ENGINE 0x10736DA0
	StringChannel::StringChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		SimpleChannel(newCount, newBlock)
	{
		values = 0;
		if (block == 0)
		{
			values = new core::Name<core::CaseSensitiveKey>[count];
		}
		else
		{
			values = (core::Name<core::CaseSensitiveKey>*)block->Allocate(count * 8, 3);
			for (unsigned int i = 0; i < count; i++)
			{
				new (&values[i]) core::Name<core::CaseSensitiveKey>();
			}
		}
	}

	// FUNCTION: ENGINE 0x10736E50
	StringChannel::~StringChannel()
	{
		StringChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10736350
	void StringChannel::Clear()
	{
		if (block == 0 && values != 0)
		{
			operator delete[]((char*)values - 4);
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735570
	unsigned int StringChannel::GetType()
	{
		return 'RTS';
	}

	// FUNCTION: ENGINE 0x10735580
	void StringChannel::GetKey(int index, float* frame, core::Name<core::CaseSensitiveKey>** out)
	{
		*frame = (float)frames[index];
		*out = &values[index];
	}

	// FUNCTION: ENGINE 0x107355B0
	void StringChannel::GetValue(float time, core::Name<core::CaseSensitiveKey>** out)
	{
		unsigned int index0;
		unsigned int index1;
		FindKeys(time, &index0, &index1);
		*out = &values[index0];
	}

	// FUNCTION: ENGINE 0x10738420
	VectorChannel::VectorChannel()
	{
	}

	// FUNCTION: ENGINE 0x107368A0
	VectorChannel::VectorChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		SimpleChannel(newCount, newBlock)
	{
	}

	// FUNCTION: ENGINE 0x107368D0
	VectorChannel::~VectorChannel()
	{
		Clear();
	}

	// FUNCTION: ENGINE 0x10735220
	unsigned int VectorChannel::GetType()
	{
		return 'TCEV';
	}

	// FUNCTION: ENGINE 0x10735230
	void VectorChannel::GetDelta(float previousTime, float time, math::Vector* out)
	{
		VectorKeys keys = mKeys;
		keys.GetDelta(FrameTime(previousTime), FrameTime(time), out);
	}

	// FUNCTION: ENGINE 0x107368F0
	Vector1DOFChannel::Vector1DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		VectorChannel(newCount, newBlock)
	{
		axis = 0;
		constant.Set(0.0f, 0.0f, 0.0f);
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new float[count];
			}
			else
			{
				values = (float*)block->Allocate(count * 4, 3);
			}
			DOFKeys<float> keys;
			keys.Set(mode, count, frames, axis, constant, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x107369B0
	Vector1DOFChannel::~Vector1DOFChannel()
	{
		Vector1DOFChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10736230
	void Vector1DOFChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735290
	void Vector1DOFChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (float*)((base + count * 2 + 3 + offset) & ~3);
			DOFKeys<float> keys;
			keys.Set(mode, count, frames, axis, constant, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x107369D0
	Vector2DOFChannel::Vector2DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		VectorChannel(newCount, newBlock)
	{
		axis = 0;
		constant.Set(0.0f, 0.0f, 0.0f);
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new Float2[count];
			}
			else
			{
				values = (Float2*)block->Allocate(count * 8, 3);
			}
			DOFKeys<Float2> keys;
			keys.Set(mode, count, frames, axis, constant, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x10736A90
	Vector2DOFChannel::~Vector2DOFChannel()
	{
		Vector2DOFChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10736260
	void Vector2DOFChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735300
	void Vector2DOFChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (Float2*)((base + count * 2 + 3 + offset) & ~3);
			DOFKeys<Float2> keys;
			keys.Set(mode, count, frames, axis, constant, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x10736AB0
	CompressedVector2DOFChannel::CompressedVector2DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		VectorChannel(newCount, newBlock)
	{
		axis = 0;
		constant.Set(0.0f, 0.0f, 0.0f);
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new Short2[count];
			}
			else
			{
				values = (Short2*)block->Allocate(count * 4, 3);
			}
		}
	}

	// FUNCTION: ENGINE 0x10736B30
	CompressedVector2DOFChannel::~CompressedVector2DOFChannel()
	{
		CompressedVector2DOFChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10736290
	void CompressedVector2DOFChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735370
	void CompressedVector2DOFChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (Short2*)((base + count * 2 + 3 + offset) & ~3);
			DOFKeys<Short2> keys;
			keys.Set(mode, count, frames, axis, constant, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x10736B50
	Vector3DOFChannel::Vector3DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		VectorChannel(newCount, newBlock)
	{
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new math::Vector[count];
			}
			else
			{
				values = (math::Vector*)block->Allocate(count * 12, 3);
			}
			ChannelKeys<math::Vector> keys;
			keys.Set(mode, count, frames, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x10736BE0
	Vector3DOFChannel::~Vector3DOFChannel()
	{
		Vector3DOFChannel::Clear();
	}

	// FUNCTION: ENGINE 0x107362C0
	void Vector3DOFChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x107353E0
	void Vector3DOFChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (math::Vector*)((base + count * 2 + 3 + offset) & ~3);
			ChannelKeys<math::Vector> keys;
			keys.Set(mode, count, frames, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x10736C00
	CompressedVector3DOFChannel::CompressedVector3DOFChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		VectorChannel(newCount, newBlock)
	{
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new Short3[count];
			}
			else
			{
				values = (Short3*)block->Allocate(count * 6, 3);
			}
		}
	}

	// FUNCTION: ENGINE 0x10736C70
	CompressedVector3DOFChannel::~CompressedVector3DOFChannel()
	{
		CompressedVector3DOFChannel::Clear();
	}

	// FUNCTION: ENGINE 0x107362F0
	void CompressedVector3DOFChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735440
	void CompressedVector3DOFChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (Short3*)((base + count * 2 + 3 + offset) & ~3);
			ChannelKeys<Short3> keys;
			keys.Set(mode, count, frames, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x10738460
	RotationChannel::RotationChannel()
	{
	}

	// FUNCTION: ENGINE 0x10736C90
	RotationChannel::RotationChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		SimpleChannel(newCount, newBlock)
	{
	}

	// FUNCTION: ENGINE 0x10736CC0
	RotationChannel::~RotationChannel()
	{
		Clear();
	}

	// FUNCTION: ENGINE 0x107354A0
	unsigned int RotationChannel::GetType()
	{
		return 'TOR';
	}

	// FUNCTION: ENGINE 0x10736CE0
	QuaternionChannel::QuaternionChannel(unsigned int newCount, AnimationMemoryBlock* newBlock) :
		RotationChannel(newCount, newBlock)
	{
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new math::Quaternion[count];
			}
			else
			{
				values = (math::Quaternion*)block->Allocate(count * 16, 3);
			}
			ChannelKeys<math::Quaternion> keys;
			keys.Set(mode, count, frames, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x10736D80
	QuaternionChannel::~QuaternionChannel()
	{
		QuaternionChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10736320
	void QuaternionChannel::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	// FUNCTION: ENGINE 0x10735500
	void QuaternionChannel::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			values = (math::Quaternion*)((base + count * 2 + 3 + offset) & ~3);
			ChannelKeys<math::Quaternion> keys;
			keys.Set(mode, count, frames, values);
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x107354B0
	void QuaternionChannel::GetDelta(float previousTime, float time, math::Quaternion* out)
	{
		mKeys.GetDelta(FrameTime(previousTime), FrameTime(time), out);
	}
}
