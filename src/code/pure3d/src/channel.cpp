// pure3d animation channels (unit around 0x10734F00 - 0x10738E00 with the channel loader; file name guessed from the
// classes). Names are guesses.
#include <new>
#include <string.h>

#include "code/core/refptr.h"
#include "code/pure3d/channel.h"

// This unit's copies of the reference helper for the entities of an entity channel and the handlers of the loader
// FUNCTION: ENGINE 0x107360D0
template void core::SafeRelease<pure3d::Entity>(pure3d::Entity*& object);

// FUNCTION: ENGINE 0x107360F0
template void core::SafeRelease<pure3d::ChannelHandler>(pure3d::ChannelHandler*& object);

namespace pure3d
{
	// The element copies of the channels' copy constructors (inline in the engine, x87 component moves)
	inline void CopyVector(math::Vector* to, const math::Vector* from)
	{
		to->x = from->x;
		to->y = from->y;
		to->z = from->z;
	}

	inline void CopyFloat2(Float2* to, const Float2* from)
	{
		to->x = from->x;
		to->y = from->y;
	}

	// The reads of the loaders below (inline in the engine: each one has a temporary of its own)
	inline unsigned int ReadWord(content::ChunkReader* reader)
	{
		unsigned int value;
		reader->Read(&value, 1, 4, 1);
		return value;
	}

	inline unsigned short ReadShort(content::ChunkReader* reader)
	{
		unsigned short value;
		reader->Read(&value, 1, 2, 1);
		return value;
	}

	inline unsigned char ReadByte(content::ChunkReader* reader)
	{
		unsigned char value;
		reader->Read(&value, 1, 1, 1);
		return value;
	}

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

	// FUNCTION: ENGINE 0x10736010
	template<> void ChannelKeys<math::CompressedQuaternion8>::Set(unsigned int newMode, unsigned int newCount,
		const short* newFrames, const math::CompressedQuaternion8* newValues)
	{
		RotationKeysBase::Set(newMode, newCount, newFrames);
		values = newValues;
	}

	// FUNCTION: ENGINE 0x10736040
	template<> void ChannelKeys<math::CompressedQuaternion6>::Set(unsigned int newMode, unsigned int newCount,
		const short* newFrames, const math::CompressedQuaternion6* newValues)
	{
		RotationKeysBase::Set(newMode, newCount, newFrames);
		values = newValues;
	}

	// FUNCTION: ENGINE 0x10736070
	template<> void ChannelKeys<math::CompressedQuaternion4>::Set(unsigned int newMode, unsigned int newCount,
		const short* newFrames, const math::CompressedQuaternion4* newValues)
	{
		RotationKeysBase::Set(newMode, newCount, newFrames);
		values = newValues;
	}

	// FUNCTION: ENGINE 0x107360A0
	template<> void ChannelKeys<math::CompressedQuaternion3>::Set(unsigned int newMode, unsigned int newCount,
		const short* newFrames, const math::CompressedQuaternion3* newValues)
	{
		RotationKeysBase::Set(newMode, newCount, newFrames);
		values = newValues;
	}

	template<class T> CompressedQuaternionChannel<T>::CompressedQuaternionChannel(unsigned int newCount,
		AnimationMemoryBlock* newBlock) : RotationChannel(newCount, newBlock)
	{
		values = 0;
		if (count > 0)
		{
			if (block == 0)
			{
				values = new T[count];
			}
			else
			{
				values = (T*)block->Allocate(count * sizeof(T), 3);
			}
			T* newValues = values;
			ChannelKeys<T> keys;
			keys.RotationKeysBase::Set(mode, count, frames);
			keys.values = newValues;
			mKeys.Set(keys);
		}
	}

	template<class T> CompressedQuaternionChannel<T>::~CompressedQuaternionChannel()
	{
		CompressedQuaternionChannel<T>::Clear();
	}

	template<class T> void CompressedQuaternionChannel<T>::Clear()
	{
		if (block == 0)
		{
			delete[] values;
		}
		values = 0;
		SimpleChannel::Clear();
	}

	template<class T> void CompressedQuaternionChannel<T>::Relocate(int base)
	{
		if (offset != -1)
		{
			SimpleChannel::Relocate(base);
			T* newValues = (T*)((base + count * 2 + 3 + offset) & ~3);
			values = newValues;
			ChannelKeys<T> keys;
			keys.RotationKeysBase::Set(mode, count, frames);
			keys.values = newValues;
			mKeys.Set(keys);
		}
	}

	// FUNCTION: ENGINE 0x10737D60
	template CompressedQuaternionChannel<math::CompressedQuaternion8>::CompressedQuaternionChannel(unsigned int,
		AnimationMemoryBlock*);
	// FUNCTION: ENGINE 0x10737EB0
	template CompressedQuaternionChannel<math::CompressedQuaternion8>::~CompressedQuaternionChannel();
	// FUNCTION: ENGINE 0x10737E80
	template void CompressedQuaternionChannel<math::CompressedQuaternion8>::Clear();
	// FUNCTION: ENGINE 0x10737E10
	template void CompressedQuaternionChannel<math::CompressedQuaternion8>::Relocate(int);

	// FUNCTION: ENGINE 0x10737ED0
	template CompressedQuaternionChannel<math::CompressedQuaternion6>::CompressedQuaternionChannel(unsigned int,
		AnimationMemoryBlock*);
	// FUNCTION: ENGINE 0x10738020
	template CompressedQuaternionChannel<math::CompressedQuaternion6>::~CompressedQuaternionChannel();
	// FUNCTION: ENGINE 0x10737FF0
	template void CompressedQuaternionChannel<math::CompressedQuaternion6>::Clear();
	// FUNCTION: ENGINE 0x10737F80
	template void CompressedQuaternionChannel<math::CompressedQuaternion6>::Relocate(int);

	// FUNCTION: ENGINE 0x10738040
	template CompressedQuaternionChannel<math::CompressedQuaternion4>::CompressedQuaternionChannel(unsigned int,
		AnimationMemoryBlock*);
	// FUNCTION: ENGINE 0x10738190
	template CompressedQuaternionChannel<math::CompressedQuaternion4>::~CompressedQuaternionChannel();
	// FUNCTION: ENGINE 0x10738160
	template void CompressedQuaternionChannel<math::CompressedQuaternion4>::Clear();
	// FUNCTION: ENGINE 0x107380F0
	template void CompressedQuaternionChannel<math::CompressedQuaternion4>::Relocate(int);

	// FUNCTION: ENGINE 0x107381B0
	template CompressedQuaternionChannel<math::CompressedQuaternion3>::CompressedQuaternionChannel(unsigned int,
		AnimationMemoryBlock*);
	// FUNCTION: ENGINE 0x10738300
	template CompressedQuaternionChannel<math::CompressedQuaternion3>::~CompressedQuaternionChannel();
	// FUNCTION: ENGINE 0x107382D0
	template void CompressedQuaternionChannel<math::CompressedQuaternion3>::Clear();
	// FUNCTION: ENGINE 0x10738260
	template void CompressedQuaternionChannel<math::CompressedQuaternion3>::Relocate(int);

	// FUNCTION: ENGINE 0x10738500
	Float1Channel::Float1Channel(const Float1Channel& other)
	{
		mode = other.mode;
		unknown8 = other.unknown8;
		name = other.name;
		block = 0;
		count = other.count;
		frames = new short[count];
		values = new float[count];
		for (unsigned int i = 0; i < count; i++)
		{
			frames[i] = other.frames[i];
			values[i] = other.values[i];
		}
	}

	// FUNCTION: ENGINE 0x10738CE0
	BoolChannel::BoolChannel(const BoolChannel& other)
	{
		mode = other.mode;
		unknown8 = other.unknown8;
		name = other.name;
		block = 0;
		count = other.count;
		frames = new short[count];
		values = new unsigned int[count];
		for (unsigned int i = 0; i < count; i++)
		{
			frames[i] = other.frames[i];
			values[i] = other.values[i];
		}
	}

	// FUNCTION: ENGINE 0x107385F0
	Vector1DOFChannel::Vector1DOFChannel(const Vector1DOFChannel& other)
	{
		mode = other.mode;
		unknown8 = other.unknown8;
		name = other.name;
		constant.x = other.constant.x;
		constant.y = other.constant.y;
		constant.z = other.constant.z;
		axis = other.axis;
		block = 0;
		count = other.count;
		frames = new short[count];
		values = new float[count];
		for (unsigned int i = 0; i < count; i++)
		{
			frames[i] = other.frames[i];
			values[i] = other.values[i];
		}
		DOFKeys<float> keys;
		keys.Set(mode, count, frames, axis, constant, values);
		mKeys.Set(keys);
	}

	// FUNCTION: ENGINE 0x10738720
	Vector2DOFChannel::Vector2DOFChannel(const Vector2DOFChannel& other)
	{
		mode = other.mode;
		unknown8 = other.unknown8;
		name = other.name;
		constant.x = other.constant.x;
		constant.y = other.constant.y;
		constant.z = other.constant.z;
		axis = other.axis;
		block = 0;
		count = other.count;
		frames = new short[count];
		values = new Float2[count];
		for (unsigned int i = 0; i < count; i++)
		{
			frames[i] = other.frames[i];
			CopyFloat2(&values[i], &other.values[i]);
		}
		DOFKeys<Float2> keys;
		keys.Set(mode, count, frames, axis, constant, values);
		mKeys.Set(keys);
	}

	// FUNCTION: ENGINE 0x10738870
	CompressedVector2DOFChannel::CompressedVector2DOFChannel(const CompressedVector2DOFChannel& other)
	{
		mode = other.mode;
		unknown8 = other.unknown8;
		name = other.name;
		constant.x = other.constant.x;
		constant.y = other.constant.y;
		constant.z = other.constant.z;
		axis = other.axis;
		block = 0;
		count = other.count;
		frames = new short[count];
		values = new Short2[count];
		for (unsigned int i = 0; i < count; i++)
		{
			frames[i] = other.frames[i];
			values[i] = other.values[i];
		}
	}

	// FUNCTION: ENGINE 0x10738960
	Vector3DOFChannel::Vector3DOFChannel(const Vector3DOFChannel& other)
	{
		mode = other.mode;
		unknown8 = other.unknown8;
		name = other.name;
		block = 0;
		count = other.count;
		frames = new short[count];
		values = new math::Vector[count];
		for (unsigned int i = 0; i < count; i++)
		{
			frames[i] = other.frames[i];
			CopyVector(&values[i], &other.values[i]);
		}
		ChannelKeys<math::Vector> keys;
		keys.Set(mode, count, frames, values);
		mKeys.Set(keys);
	}

	// FUNCTION: ENGINE 0x10738A80
	CompressedVector3DOFChannel::CompressedVector3DOFChannel(const CompressedVector3DOFChannel& other)
	{
		mode = other.mode;
		unknown8 = other.unknown8;
		name = other.name;
		block = 0;
		count = other.count;
		frames = new short[count];
		values = new Short3[count];
		for (unsigned int i = 0; i < count; i++)
		{
			frames[i] = other.frames[i];
			values[i] = other.values[i];
		}
	}

	// FUNCTION: ENGINE 0x10738B60
	QuaternionChannel::QuaternionChannel(const QuaternionChannel& other)
	{
		mode = other.mode;
		unknown8 = other.unknown8;
		name = other.name;
		block = 0;
		count = other.count;
		frames = new short[count];
		values = new math::Quaternion[count];
		for (unsigned int i = 0; i < count; i++)
		{
			frames[i] = other.frames[i];
			values[i] = other.values[i];
		}
		ChannelKeys<math::Quaternion> keys;
		keys.Set(mode, count, frames, values);
		mKeys.Set(keys);
	}

	// FUNCTION: ENGINE 0x10734E40
	void RotationKeys::GetDelta(float previousTime, float time, math::Quaternion* out)
	{
		GetDelta(FrameTime(previousTime), FrameTime(time), out);
	}

	// FUNCTION: ENGINE 0x10735790
	// NONMATCHING: the engine converts each lerped byte with the inline fnstcw / fistp sequence on x87 values and inserts
	// it into the word with xor / and; any cast spelling here gives the call to _ftol2 or other code (best 13 %)
#ifdef NONMATCHING
	void BlendColour(Colour* out, const Colour* from, const Colour* to, float t)
	{
		out->r = (unsigned int)(((float)to->r - (float)from->r) * t + (float)from->r);
		out->g = (unsigned int)(((float)to->g - (float)from->g) * t + (float)from->g);
		out->b = (unsigned int)(((float)to->b - (float)from->b) * t + (float)from->b);
		out->a = (unsigned int)(((float)to->a - (float)from->a) * t + (float)from->a);
	}
#endif

	// FUNCTION: ENGINE 0x107358F0
	void ColourChannel::GetValue(float time, unsigned int* out)
	{
		unsigned int index0;
		unsigned int index1;
		if (FindKeys(time, &index0, &index1) && mode != 0)
		{
			float offset = time - (float)frames[index0];
			if (offset == 0.0f)
			{
				*out = values[index0];
				return;
			}
			BlendColour((Colour*)out, (Colour*)&values[index0], (Colour*)&values[index1],
				offset / (float)(frames[index1] - frames[index0]));
			return;
		}
		*out = values[index0];
	}

	// FUNCTION: ENGINE 0x10735CD0
	int BlendInt(IntChannel* from, IntChannel* to, float t, float time)
	{
		int a;
		int b;
		from->GetValue(time, &a);
		to->GetValue(time, &b);
		return (int)((float)(b - a) * t) + a;
	}

	// FUNCTION: ENGINE 0x10735D20
	float BlendFloat(Float1Channel* from, Float1Channel* to, float t, float time)
	{
		float a;
		float b;
		from->GetValue(time, &a);
		to->GetValue(time, &b);
		return (b - a) * t + a;
	}

	// FUNCTION: ENGINE 0x10735D70
	float BlendFloatDelta(Float1Channel* from, Float1Channel* to, float t, float previousTime, float time)
	{
		float a;
		float b;
		from->GetDelta(previousTime, time, &a, -1.0f, false);
		to->GetDelta(previousTime, time, &b, -1.0f, false);
		return (b - a) * t + a;
	}

	// FUNCTION: ENGINE 0x10735E60
	math::Vector* BlendVector(math::Vector* out, VectorChannel* from, VectorChannel* to, float t, float time)
	{
		math::Vector b;
		from->mKeys.Evaluate(FrameTime(time), out);
		to->mKeys.Evaluate(FrameTime(time), &b);
		out->x = (b.x - out->x) * t + out->x;
		out->y = (b.y - out->y) * t + out->y;
		out->z = (b.z - out->z) * t + out->z;
		return out;
	}

	// FUNCTION: ENGINE 0x10735F20
	math::Quaternion* BlendQuaternion(math::Quaternion* out, RotationChannel* from, RotationChannel* to, float t,
		float time)
	{
		math::Quaternion b;
		from->mKeys.Evaluate(FrameTime(time), out);
		to->mKeys.Evaluate(FrameTime(time), &b);
		out->Slerp(*out, b, t);
		return out;
	}

	// FUNCTION: ENGINE 0x10735FA0
	unsigned int* BlendColourValue(unsigned int* out, ColourChannel* from, ColourChannel* to, float t, float time)
	{
		unsigned int a = 0;
		unsigned int b = 0;
		*out = 0;
		from->GetValue(time, &a);
		to->GetValue(time, &b);
		BlendColour((Colour*)out, (Colour*)&a, (Colour*)&b, t);
		return out;
	}

	// FUNCTION: ENGINE 0x10736430
	void DefaultChannelHandler::ReadChunks(SimpleChannel* channel, content::ChunkReader* reader)
	{
		while (reader->HasChunk())
		{
			switch (reader->BeginChunk())
			{
			case 0x121110:
				ReadWord(reader);
				channel->mode = ReadWord(reader);
				break;
			case 0x121116:
			{
				char text[256];
				ReadWord(reader);
				unsigned int length = ReadByte(reader);
				reader->Read(text, length, 1, 1);
				text[length] = 0;
				core::Name<core::CaseInsensitiveKey32> newName(text, 1);
				channel->name = newName;
				break;
			}
			case 0x121120:
				ReadWord(reader);
				channel->count = ReadWord(reader);
				channel->offset = ReadWord(reader);
				break;
			}
			reader->EndChunk();
		}
	}

	// FUNCTION: ENGINE 0x10737030
	IntChannel* DefaultChannelHandler::LoadInt(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		ReadWord(reader);
		int version = ReadWord(reader);
		unsigned int count = ReadWord(reader);
		IntChannel* channel;
		if (block == 0)
		{
			channel = new IntChannel(count, 0);
		}
		else
		{
			channel = new (block->Allocate(0x24, 7)) IntChannel(count, block);
		}
		channel->unknown8 = version;
		if (count > 0)
		{
			reader->Read(channel->frames, count, 2, 1);
			reader->Read(channel->values, count, 4, 1);
		}
		ReadChunks(channel, reader);
		return channel;
	}

	// FUNCTION: ENGINE 0x10737110
	Float1Channel* DefaultChannelHandler::LoadFloat1(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		ReadWord(reader);
		int version = ReadWord(reader);
		unsigned int count = ReadWord(reader);
		Float1Channel* channel;
		if (block == 0)
		{
			channel = new Float1Channel(count, 0);
		}
		else
		{
			channel = new (block->Allocate(0x24, 7)) Float1Channel(count, block);
		}
		channel->unknown8 = version;
		if (count > 0)
		{
			reader->Read(channel->frames, count, 2, 1);
			reader->Read(channel->values, count, 4, 1);
		}
		ReadChunks(channel, reader);
		return channel;
	}

	// FUNCTION: ENGINE 0x107371F0
	Float2Channel* DefaultChannelHandler::LoadFloat2(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		ReadWord(reader);
		int version = ReadWord(reader);
		unsigned int count = ReadWord(reader);
		Float2Channel* channel;
		if (block == 0)
		{
			channel = new Float2Channel(count, 0);
		}
		else
		{
			channel = new (block->Allocate(0x24, 7)) Float2Channel(count, block);
		}
		channel->unknown8 = version;
		if (count > 0)
		{
			reader->Read(channel->frames, count, 2, 1);
			reader->Read(channel->values, count * 2, 4, 1);
		}
		ReadChunks(channel, reader);
		return channel;
	}

	// FUNCTION: ENGINE 0x10737C10
	ColourChannel* DefaultChannelHandler::LoadColour(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		ReadWord(reader);
		int version = ReadWord(reader);
		unsigned int count = ReadWord(reader);
		ColourChannel* channel;
		if (block == 0)
		{
			channel = new ColourChannel(count, 0);
		}
		else
		{
			channel = new (block->Allocate(0x24, 7)) ColourChannel(count, block);
		}
		channel->unknown8 = version;
		if (count > 0)
		{
			reader->Read(channel->frames, count, 2, 1);
			reader->Read(channel->values, count, 4, 1);
		}
		ReadChunks(channel, reader);
		return channel;
	}

	// FUNCTION: ENGINE 0x10737AE0
	// EQUIVALENT: the engine copies the key count into the loop counter after clearing the word index; ours before (98.6 %)
	BoolChannel* DefaultChannelHandler::LoadBool(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		ReadWord(reader);
		int version = ReadWord(reader);
		bool value = (short)ReadShort(reader) == 1;
		unsigned int count = ReadWord(reader);
		BoolChannel* channel;
		if (block == 0)
		{
			channel = new BoolChannel(count + 1, 0);
		}
		else
		{
			channel = new (block->Allocate(0x24, 7)) BoolChannel(count + 1, block);
		}
		channel->unknown8 = version;
		reader->Read(channel->frames + 1, count, 2, 1);
		unsigned int keys = count + 1;
		channel->frames[0] = -1;
		unsigned int bit = 0;
		if (keys > 0)
		{
			unsigned int left = keys;
			unsigned int word = 0;
			do
			{
				if (value == true)
				{
					channel->values[word] |= 1 << bit;
				}
				bit++;
				if (bit == 32)
				{
					bit = 0;
					word++;
				}
				value = !value;
				left--;
			}
			while (left != 0);
		}
		return channel;
	}

	// FUNCTION: ENGINE 0x107379B0
	// EQUIVALENT: the engine stores the name's terminator after setting up the call's arguments; ours before them (94.8 %)
	StringChannel* DefaultChannelHandler::LoadString(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		char text[256];
		ReadWord(reader);
		int version = ReadWord(reader);
		unsigned int count = ReadWord(reader);
		StringChannel* channel;
		if (block == 0)
		{
			channel = new StringChannel(count, 0);
		}
		else
		{
			channel = new (block->Allocate(0x24, 7)) StringChannel(count, block);
		}
		channel->unknown8 = version;
		reader->Read(channel->frames, count, 2, 1);
		for (unsigned int i = 0; i < count; i++)
		{
			unsigned int length = ReadByte(reader);
			reader->Read(text, length, 1, 1);
			text[length] = 0;
			channel->values[i].SetText(text);
		}
		return channel;
	}

	// FUNCTION: ENGINE 0x107395B0
	EntityChannel* DefaultChannelHandler::LoadEntity(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		char text[256];
		ReadWord(reader);
		int version = ReadWord(reader);
		unsigned int count = ReadWord(reader);
		EntityChannel* channel;
		if (block == 0)
		{
			channel = new EntityChannel(count, 0);
		}
		else
		{
			channel = new (block->Allocate(0x24, 7)) EntityChannel(count, block);
		}
		channel->unknown8 = version;
		reader->Read(channel->frames, count, 2, 1);
		for (unsigned int i = 0; i < count; i++)
		{
			unsigned int length = ReadByte(reader);
			reader->Read(text, length, 1, 1);
			text[length] = 0;
			channel->values[i] = inventory->Find<Entity>(text);
			if (channel->values[i] != 0)
			{
				channel->values[i]->AddRef();
			}
		}
		ReadChunks(channel, reader);
		return channel;
	}

	// FUNCTION: ENGINE 0x10739730
	// EQUIVALENT: the engine hoists the memset size push above the reference count stores of the base (84.6 %)
	ChannelLoader::ChannelLoader()
	{
		count = 0;
		memset(handlers, 0, sizeof(handlers));
		AddHandler(new DefaultChannelHandler);
	}

	// FUNCTION: ENGINE 0x107365D0
	ChannelLoader::~ChannelLoader()
	{
		for (int i = 0; i < count; i++)
		{
			core::SafeRelease(handlers[i]);
		}
	}

	// FUNCTION: ENGINE 0x10735BB0
	void ChannelLoader::AddHandler(ChannelHandler* handler)
	{
		if (handler != 0)
		{
			memmove(&handlers[1], &handlers[0], count * 4);
			handlers[0] = handler;
			handler->AddRef();
			count++;
		}
	}

	// FUNCTION: ENGINE 0x10735BF0
	ChannelHandler* ChannelLoader::FindHandler(unsigned int chunkId)
	{
		for (int i = 0; i < count; i++)
		{
			if (handlers[i]->IsSupported(chunkId) == true)
			{
				return handlers[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10735C40
	bool ChannelLoader::HasHandler(unsigned int chunkId)
	{
		for (int i = 0; i < count; i++)
		{
			if (handlers[i]->IsSupported(chunkId) == true)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10735C80
	Channel* ChannelLoader::Load(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		for (int i = 0; i < count; i++)
		{
			if (handlers[i]->IsSupported(reader->GetChunkId()) == true)
			{
				return handlers[i]->Load(reader, inventory, block);
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107359B0
	bool DefaultChannelHandler::IsSupported(unsigned int chunkId)
	{
		switch (chunkId)
		{
		case 0x121100:
		case 0x121101:
		case 0x121102:
		case 0x121103:
		case 0x121104:
		case 0x121105:
		case 0x121106:
		case 0x121107:
		case 0x121108:
		case 0x121109:
		case 0x12110E:
		case 0x121111:
		case 0x121112:
		case 0x121113:
		case 0x121114:
		case 0x121118:
		case 0x121119:
			return true;
		default:
			return false;
		}
	}

	// FUNCTION: ENGINE 0x107397A0
	// EQUIVALENT: the engine keeps the reader in ebx, the handler in edi and the result in esi; ours edi, esi, ebx (38 %)
	Channel* DefaultChannelHandler::Load(content::ChunkReader* reader, content::LoadInventory* inventory,
		AnimationMemoryBlock* block)
	{
		Channel* channel = 0;
		switch (reader->GetChunkId())
		{
		case 0x121100:
			channel = LoadFloat1(reader, inventory, block);
			return channel;
		case 0x121101:
			channel = LoadFloat2(reader, inventory, block);
			return channel;
		case 0x121102:
		case 0x121103:
		case 0x121104:
		case 0x121118:
		case 0x121119:
			channel = LoadVector(reader, inventory, block);
			return channel;
		case 0x121105:
		case 0x121111:
		case 0x121112:
		case 0x121113:
		case 0x121114:
			channel = LoadRotation(reader, inventory, block);
			return channel;
		case 0x121106:
			channel = LoadString(reader, inventory, block);
			return channel;
		case 0x121107:
			channel = LoadEntity(reader, inventory, block);
			return channel;
		case 0x121108:
			channel = LoadBool(reader, inventory, block);
			return channel;
		case 0x121109:
			channel = LoadColour(reader, inventory, block);
			break;
		case 0x12110E:
			channel = LoadInt(reader, inventory, block);
			return channel;
		}
		return channel;
	}

	// FUNCTION: ENGINE 0x10735A00
	// NONMATCHING: the engine's switch is a plain jump table with tail-merged case bodies; ours gets a byte index table and
	// other bodies (best 25 %)
#ifdef NONMATCHING
	void DefaultChannelHandler::GetSize(unsigned int* objectSize, unsigned int* dataSize, unsigned int chunkId,
		unsigned short count)
	{
		unsigned int frames = 0;
		unsigned int values = 0;
		*objectSize = 0;
		switch (chunkId)
		{
		case 0x121100:
		case 0x121107:
		case 0x121109:
		case 0x12110E:
			*objectSize = 0x24;
			frames = count * 2;
			values = count * 4;
			break;
		case 0x121101:
		case 0x121106:
			*objectSize = 0x24;
			frames = count * 2;
			values = count * 8;
			break;
		case 0x121102:
		case 0x121118:
			*objectSize = 0x58;
			frames = count * 2;
			values = count * 4;
			break;
		case 0x121103:
			*objectSize = 0x58;
			frames = count * 2;
			values = count * 8;
			break;
		case 0x121104:
			*objectSize = 0x48;
			frames = count * 2;
			values = count * 12;
			break;
		case 0x121105:
			*objectSize = 0x38;
			frames = count * 2;
			values = count * 16;
			break;
		case 0x121108:
			*objectSize = 0x24;
			frames = count * 2;
			values = (((int)count - 1) >> 5) * 4 + 4;
			break;
		case 0x121111:
			*objectSize = 0x38;
			frames = count * 2;
			values = count * 8;
			break;
		case 0x121112:
			*objectSize = 0x38;
			frames = count * 2;
			values = count * 6;
			break;
		case 0x121113:
			*objectSize = 0x38;
			frames = count * 2;
			values = count * 4;
			break;
		case 0x121114:
			*objectSize = 0x38;
			frames = count * 2;
			values = count * 3;
			break;
		case 0x121119:
			*objectSize = 0x48;
			frames = count * 2;
			values = count * 6;
			break;
		}
		*objectSize = (*objectSize + 7) & ~7;
		*dataSize = ((values + 3) & ~3) + ((frames + 3) & ~3);
	}
#endif
}

// The lookup of an entity by name (the filter the entity channel loader hands the inventory)
// FUNCTION: ENGINE 0x10736610
// FUNCTION: ENGINE 0x10736620
template class content::LoadInventory::DynamicCaster<pure3d::Entity>;
