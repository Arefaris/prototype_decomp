// pure3d animations (code/pure3d/anim/src/animation.cpp, path from the asserts; the unit starts around 0x106E2A30):
// the key readers of the channels among others. Names are guesses.
#include "code/math/compressedquaternion.h"
#include "code/compress/compress.h"
#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/math/mathutils.h"
#include <math.h>
#include <new>
#include "code/pure3d/animation.h"
#include "code/pure3d/channel.h"
#include "code/pure3d/effects/particlecontroller.h"
#include "code/pure3d/vertexstream.h"

namespace engine
{
	namespace camera
	{
		extern const float gThousandth;
	}

	namespace driving
	{
		extern const float gThirty;
	}
}


namespace math
{
	// The scale factors sit in the data section (initialised there, not constants of the code)
	float CompressedQuaternion6::sScale = 1.0f / 32767.0f;
	float CompressedQuaternion3::sScale = 1.0f / 127.0f;
	float CompressedQuaternion4::sScale = 1.0f / 1023.0f;
	float CompressedQuaternion4::sScaleZ = 1.0f / 511.0f;

	// FUNCTION: ENGINE 0x106E2F50
	inline Quaternion CompressedQuaternion8::ToQuaternion() const
	{
		Quaternion q;
		q.x = x * CompressedQuaternion6::sScale;
		q.y = y * CompressedQuaternion6::sScale;
		q.z = z * CompressedQuaternion6::sScale;
		q.w = w * CompressedQuaternion6::sScale;
		return q;
	}

	// FUNCTION: ENGINE 0x106E3EA0
	inline Quaternion CompressedQuaternion4::ToQuaternion() const
	{
		float qx = (float)(int)(packed & 0x7FF) * sScale - 1.0f;
		float qy = (float)(int)((packed >> 11) & 0x7FF) * sScale - 1.0f;
		float qz = (float)(int)(packed >> 22) * sScaleZ - 1.0f;
		float qw = sqrtf(Max(1.0f - (qz * qz + qy * qy + qx * qx), 0.0f));
		Quaternion q;
		q.x = qx;
		q.y = qy;
		q.z = qz;
		q.w = qw;
		return q;
	}

	// FUNCTION: ENGINE 0x106E3E10
	inline Quaternion CompressedQuaternion6::ToQuaternion() const
	{
		float qx = x * sScale;
		float qy = y * sScale;
		float qz = z * sScale;
		float qw = sqrtf(Max(1.0f - (qz * qz + qy * qy + qx * qx), 0.0f));
		Quaternion q;
		q.x = qx;
		q.y = qy;
		q.z = qz;
		q.w = qw;
		return q;
	}

	// FUNCTION: ENGINE 0x106E3F50
	inline Quaternion CompressedQuaternion3::ToQuaternion() const
	{
		float qx = x * sScale;
		float qy = y * sScale;
		float qz = z * sScale;
		float qw = sqrtf(Max(1.0f - (qz * qz + qy * qy + qx * qx), 0.0f));
		Quaternion q;
		q.x = qx;
		q.y = qy;
		q.z = qz;
		q.w = qw;
		return q;
	}
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x106E2FE0
	FrameTime::FrameTime()
	{
		frame = 0;
		time = 0.0f;
	}

	// FUNCTION: ENGINE 0x106E2FF0
	FrameTime::FrameTime(short newFrame)
	{
		frame = newFrame;
		time = (float)newFrame;
	}

	// FUNCTION: ENGINE 0x106E3010
	FrameTime::FrameTime(float newTime)
	{
		time = newTime;
		frame = (short)(int)newTime;
	}

	// FUNCTION: ENGINE 0x106E3030
	void FrameTime::SetFrame(short newFrame)
	{
		frame = newFrame;
		time = (float)newFrame;
	}

	// FUNCTION: ENGINE 0x106E3070
	void ChannelKeysBase::SetMode(unsigned int newMode)
	{
		mode = newMode;
	}

	// FUNCTION: ENGINE 0x106E3080
	void ChannelKeysBase::Set(unsigned int newMode, unsigned int newCount, const short* newFrames)
	{
		SetMode(newMode);
		count = newCount;
		frames = newFrames;
	}

	// FUNCTION: ENGINE 0x106E3240
	void RotationKeysBase::Set(unsigned int newMode, unsigned int newCount, const short* newFrames)
	{
		ChannelKeysBase::Set(newMode, newCount, newFrames);
	}

	// FUNCTION: ENGINE 0x106E3100
	void VectorKeysBase::Set(unsigned int newMode, unsigned int newCount, const short* newFrames)
	{
		ChannelKeysBase::Set(newMode, newCount, newFrames);
	}

	template<class T> void DOFKeys<T>::Set(unsigned int mode, unsigned int count, const short* frames, int newAxis,
		math::Vector newConstant, const T* newValues)
	{
		VectorKeysBase::Set(mode, count, frames);
		axis = newAxis;
		constant.x = newConstant.x;
		constant.y = newConstant.y;
		constant.z = newConstant.z;
		values = newValues;
	}

	// FUNCTION: ENGINE 0x106E3270
	VectorKeys::VectorKeys()
	{
		type = 5;
	}

	// The keys of a form are copied into the object that follows the tag
	template<class T> static inline void CopyKeys(unsigned char* to, const T& from)
	{
		*(T*)to = from;
	}

	// FUNCTION: ENGINE 0x106E3280
	void VectorKeys::Set(const DOFKeys<float>& newKeys)
	{
		type = 0;
		CopyKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E32A0
	void VectorKeys::Set(const DOFKeys<Float2>& newKeys)
	{
		type = 1;
		CopyKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E32C0
	void VectorKeys::Set(const ChannelKeys<math::Vector>& newKeys)
	{
		type = 2;
		CopyKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E32F0
	void VectorKeys::Set(const DOFKeys<Short2>& newKeys)
	{
		type = 3;
		CopyKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E3310
	void VectorKeys::Set(const ChannelKeys<Short3>& newKeys)
	{
		type = 4;
		CopyKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E3340
	RotationKeys::RotationKeys()
	{
		type = 5;
	}

	// The compressed forms share the layout of the uncompressed one (a tag, the keys, the values)
	template<class T> static inline void CopyRotationKeys(ChannelKeys<math::Quaternion>& to, const ChannelKeys<T>& from)
	{
		to = *(const ChannelKeys<math::Quaternion>*)&from;
	}

	// FUNCTION: ENGINE 0x106E3350
	void RotationKeys::Set(ChannelKeys<math::Quaternion> newKeys)
	{
		type = 0;
		keys = newKeys;
	}

	// FUNCTION: ENGINE 0x106E3380
	void RotationKeys::Set(ChannelKeys<math::CompressedQuaternion8> newKeys)
	{
		type = 1;
		CopyRotationKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E33B0
	void RotationKeys::Set(ChannelKeys<math::CompressedQuaternion6> newKeys)
	{
		type = 2;
		CopyRotationKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E33E0
	void RotationKeys::Set(ChannelKeys<math::CompressedQuaternion4> newKeys)
	{
		type = 3;
		CopyRotationKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E3410
	void RotationKeys::Set(ChannelKeys<math::CompressedQuaternion3> newKeys)
	{
		type = 4;
		CopyRotationKeys(keys, newKeys);
	}

	// FUNCTION: ENGINE 0x106E79D0
	AnimationGroup* Animation::GetGroup(int index)
	{
		return mGroups[index];
	}

	// FUNCTION: ENGINE 0x106E79E0
	// NONMATCHING: register allocation (65 %: the engine keeps the upper bound in edi and the lower in esi; same operations)
#ifdef NONMATCHING
	AnimationGroup* Animation::FindOverallGroup(int id)
	{
		if (mGroupCount > 0)
		{
			if (mSortMode == 1)
			{
				int low = 0;
				int high = mGroupCount - 1;
				int middle = high / 2;
				if (high > 0)
				{
					do
					{
						int key = mGroups[middle]->mId;
						if (key > id)
						{
							high = middle - 1;
						}
						else
						{
							if (key >= id)
							{
								return mGroups[middle];
							}
							low = middle + 1;
						}
						middle = (high - low) / 2 + low;
					}
					while (low < high);
				}
				AnimationGroup* group = mGroups[middle];
				if (group->mId == id)
				{
					return group;
				}
			}
			else
			{
				int i = 0;
				if (mGroupCount > 0)
				{
					AnimationGroup** group = mGroups;
					do
					{
						if ((*group)->mId == id)
						{
							return mGroups[i];
						}
						i++;
						group++;
					}
					while (i < mGroupCount);
					return 0;
				}
			}
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x106E7A90
	// NONMATCHING: register allocation (65 %: the engine keeps the upper bound in edi and the lower in esi; same operations)
#ifdef NONMATCHING
	int Animation::FindOverallGroupIndex(int id)
	{
		if (mGroupCount > 0)
		{
			if (mSortMode == 1)
			{
				int high = mGroupCount - 1;
				int low = 0;
				int middle = high / 2;
				if (high > 0)
				{
					do
					{
						int key = mGroups[middle]->mId;
						if (key > id)
						{
							high = middle - 1;
						}
						else
						{
							if (key >= id)
							{
								return middle;
							}
							low = middle + 1;
						}
						middle = (high - low) / 2 + low;
					}
					while (low < high);
				}
				if (mGroups[middle]->mId == id)
				{
					return middle;
				}
			}
			else
			{
				int i = 0;
				if (mGroupCount > 0)
				{
					AnimationGroup** group = mGroups;
					do
					{
						if ((*group)->mId == id)
						{
							return i;
						}
						i++;
						group++;
					}
					while (i < mGroupCount);
				}
			}
		}
		return -1;
	}
#endif

	// FUNCTION: ENGINE 0x106E8240
	unsigned __int64 AnimationGroup::GetNameHash()
	{
		return mName.GetHash();
	}

	// FUNCTION: ENGINE 0x106E8770
	// NONMATCHING: operand order of the step and the argument register (22 %: the engine multiplies the frame rate by dt
	// before the scale and passes the flag zero-extended)
#ifdef NONMATCHING
	float Animation::AdvanceFrame(float* remaining, bool* forward, float frame, float dt, float start, float end,
		bool unlimited, int mode)
	{
		if (mode == 0)
		{
			unlimited = mFlag0;
		}
		return AdvanceFrameCycle(remaining, forward, frame, mFrameRate * dt * engine::camera::gThousandth, start, end,
			unlimited, mode);
	}
#endif

	// FUNCTION: ENGINE 0x106E8D30
	AnimationGroup* Animation::FindGroup(const char* name)
	{
		return FindGroup(&core::Name<core::CaseSensitiveKey>(name, 1));
	}

	// FUNCTION: ENGINE 0x106E8D60
	int Animation::FindGroupIndex(const char* name)
	{
		return FindGroupIndex(&core::Name<core::CaseSensitiveKey>(name, 1));
	}

	// FUNCTION: ENGINE 0x106E5CC0
	void VectorKeys::Evaluate(FrameTime time, math::Vector* out)
	{
		switch (type)
		{
		case 0:
			((DOFKeys<float>*)keys)->Evaluate(time, out);
			break;
		case 1:
			((DOFKeys<Float2>*)keys)->Evaluate(time, out);
			break;
		case 2:
			((ChannelKeys<math::Vector>*)keys)->Evaluate(time, out);
			break;
		case 3:
			((DOFKeys<Short2>*)keys)->Evaluate(time, out);
			break;
		case 4:
			((ChannelKeys<Short3>*)keys)->Evaluate(time, out);
			break;
		}
	}

	// FUNCTION: ENGINE 0x106E6D70
	void RotationKeys::Evaluate(FrameTime time, math::Quaternion* out)
	{
		switch (type)
		{
		case 0:
			keys.Evaluate(time, out);
			break;
		case 1:
			((ChannelKeys<math::CompressedQuaternion8>*)&keys)->Evaluate(time, out);
			break;
		case 2:
			((ChannelKeys<math::CompressedQuaternion6>*)&keys)->Evaluate(time, out);
			break;
		case 3:
			((ChannelKeys<math::CompressedQuaternion4>*)&keys)->Evaluate(time, out);
			break;
		case 4:
			((ChannelKeys<math::CompressedQuaternion3>*)&keys)->Evaluate(time, out);
			break;
		}
	}

	// FUNCTION: ENGINE 0x106E3980
	VectorKeysBase* VectorKeys::GetBase()
	{
		switch (type)
		{
		case 0:
			return (DOFKeys<float>*)keys;
		case 1:
			return (DOFKeys<Float2>*)keys;
		case 2:
			return (ChannelKeys<math::Vector>*)keys;
		case 3:
			return (DOFKeys<Short2>*)keys;
		case 4:
			return (ChannelKeys<Short3>*)keys;
		}
		return (VectorKeysBase*)keys;
	}

	// FUNCTION: ENGINE 0x106E39B0
	RotationKeysBase* RotationKeys::GetBase()
	{
		switch (type)
		{
		case 0:
			return &keys;
		case 1:
			return (ChannelKeys<math::CompressedQuaternion8>*)&keys;
		case 2:
			return (ChannelKeys<math::CompressedQuaternion6>*)&keys;
		case 3:
			return (ChannelKeys<math::CompressedQuaternion4>*)&keys;
		case 4:
			return (ChannelKeys<math::CompressedQuaternion3>*)&keys;
		}
		return &keys;
	}

	// FUNCTION: ENGINE 0x106E5D70
	// NONMATCHING: the engine schedules the component sums differently (75 %)
#ifdef NONMATCHING
	void VectorKeys::GetDelta(FrameTime from, FrameTime to, math::Vector* out)
	{
		math::Vector v0;
		math::Vector v1;
		Evaluate(from, &v0);
		Evaluate(to, &v1);
		if (to.time >= from.time)
		{
			out->x = v1.x - v0.x;
			out->y = v1.y - v0.y;
			out->z = v1.z - v0.z;
			return;
		}
		math::Vector first;
		math::Vector last;
		Evaluate(FrameTime(0.0f), &first);
		Evaluate(FrameTime((short)GetBase()->GetLastFrame()), &last);
		math::Vector tail;
		tail.Sub(last, v0);
		math::Vector head;
		head.Sub(v1, first);
		out->Add(head, tail);
	}
#endif

	// FUNCTION: ENGINE 0x106E6FC0
	void RotationKeys::GetDelta(FrameTime from, FrameTime to, math::Quaternion* out)
	{
		math::Quaternion q0;
		math::Quaternion q1;
		Evaluate(from, &q0);
		Evaluate(to, &q1);
		if (to.time >= from.time)
		{
			out->MultiplyInverse(q1, q0);
			return;
		}
		math::Quaternion first;
		Evaluate(FrameTime(0.0f), &first);
		int lastFrame = GetBase()->GetLastFrame();
		math::Quaternion last;
		Evaluate(FrameTime((float)lastFrame), &last);
		math::Quaternion wrapped;
		wrapped.MultiplyInverse(q1, first);
		out->MultiplyInverse(last, q0);
		math::Multiply(*out, *out, wrapped);
	}

	// FUNCTION: ENGINE 0x106E7820
	// NONMATCHING: the engine keeps no zero register (16 %)
#ifdef NONMATCHING
	AnimationMemoryBlock::AnimationMemoryBlock(const unsigned int* sizes)
	{
		mSizes[0] = sizes[0];
		mUsed[0] = 0;
		mPools[0] = mSizes[0] > 0 ? new char[mSizes[0]] : 0;
		mSizes[1] = sizes[1];
		mUsed[1] = 0;
		if (mSizes[1] > 0)
		{
			mPools[1] = new char[mSizes[1]];
		}
		else
		{
			mPools[1] = 0;
		}
	}
#endif

	// FUNCTION: ENGINE 0x106E7890
	AnimationMemoryBlock::~AnimationMemoryBlock()
	{
		delete[] mPools[0];
		delete[] mPools[1];
	}

	// FUNCTION: ENGINE 0x106E78C0
	// NONMATCHING: the engine computes the address before it stores the new fill (57 %)
#ifdef NONMATCHING
	void* AnimationMemoryBlock::Allocate(unsigned int size, unsigned int alignmentMask)
	{
		if (size > 0)
		{
			unsigned int pool = alignmentMask != 7;
			unsigned int offset = (mUsed[pool] + alignmentMask) & ~alignmentMask;
			void* result = mPools[pool] + offset;
			mUsed[pool] = offset + size;
			return result;
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x106E7960
	// NONMATCHING: scheduling (64 %: the engine loads the frame rate and zeroes the float registers first and stores the
	// vftable after the member words)
#ifdef NONMATCHING
	Animation::Animation()
	{
		float zero = 0.0f;
		float rate = engine::driving::gThirty;
		mFlag0 = false;
		mType = 0;
		mSortMode = 0;
		mGroupCount = 0;
		mGroups = 0;
		mGroupBlock = 0;
		mEventCount = 0;
		mEvents = 0;
		mBlock = 0;
		numFrames = zero;
		mFrameRate = rate;
		mUnknown20 = zero;
	}
#endif

	// FUNCTION: ENGINE 0x106E91F0
	Animation::~Animation()
	{
		if (mGroupBlock == 0)
		{
			for (int i = 0; i < mGroupCount; i++)
			{
				AnimationGroup* group = mGroups[i];
				if (group)
				{
					delete group;
				}
			}
			delete[] mEvents;
			delete[] mGroups;
		}
		else
		{
			for (int i = 0; i < mGroupCount; i++)
			{
				mGroups[i]->Clear();
			}
			if (mEvents)
			{
				mGroupBlock->Release();
			}
			core::SafeRelease(mGroupBlock);
		}
		if (mBlock)
		{
			AnimationMemoryManager* manager = gAnimationMemoryManager;
			if (manager)
			{
				manager->mFreed += mBlock->mEnd - mBlock->mStart;
			}
			if (mBlock->mData)
			{
				if (manager)
				{
					manager->FreeData(mBlock->mData);
				}
				else
				{
					core::FreeAligned(mBlock->mData);
				}
				mBlock->mData = 0;
			}
			delete[] mBlock->mArray;
			delete mBlock;
		}
	}

	// FUNCTION: ENGINE 0x106E79B0
	bool Animation::Unknown3()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x106E79C0
	Animation* Animation::Unknown4()
	{
		return this;
	}

	// FUNCTION: ENGINE 0x106E8550
	AnimationGroup::AnimationGroup()
	{
		mId = 0;
		mChannelCount = 0;
		mChannels = 0;
		mBlock = 0;
	}

	// FUNCTION: ENGINE 0x106E91E0
	AnimationGroup::~AnimationGroup()
	{
		Clear();
	}

	// FUNCTION: ENGINE 0x106E8C80
	void AnimationGroup::Clear()
	{
		if (mBlock == 0)
		{
			for (unsigned int i = 0; i < mChannelCount; i++)
			{
				Channel* channel = mChannels[i];
				if (channel)
				{
					delete channel;
				}
			}
			delete[] mChannels;
		}
		else
		{
			for (unsigned int i = 0; i < mChannelCount; i++)
			{
				mChannels[i]->Clear();
			}
			core::SafeRelease(mBlock);
		}
	}

	// FUNCTION: ENGINE 0x106E8590
	// NONMATCHING: register allocation (64 %: the engine keeps the group count in ebx and the lower bound in edi; same operations)
#ifdef NONMATCHING
	AnimationGroup* Animation::FindGroup(const core::Name<core::CaseSensitiveKey>* name)
	{
		int count = mGroupCount;
		if (count > 0)
		{
			if (mSortMode == 0)
			{
				count = count - 1;
				int low = 0;
				int middle = count / 2;
				if (count > 0)
				{
					AnimationGroup** groups = mGroups;
					do
					{
						AnimationGroup* group = groups[middle];
						if (group->mName > *name)
						{
							count = middle - 1;
						}
						else
						{
							if (!(group->mName < *name))
							{
								return groups[middle];
							}
							low = middle + 1;
						}
						middle = (count - low) / 2 + low;
					}
					while (low < count);
				}
				AnimationGroup* group = mGroups[middle];
				if (group->mName == *name)
				{
					return group;
				}
			}
			else
			{
				int i = 0;
				if (count > 0)
				{
					AnimationGroup** groups = mGroups;
					AnimationGroup** item = groups;
					do
					{
						if ((*item)->mName == *name)
						{
							return groups[i];
						}
						i++;
						item++;
					}
					while (i < count);
				}
			}
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x106E8690
	// NONMATCHING: register allocation (66 %: the engine keeps the group count in ebx and the lower bound in edi; same operations)
#ifdef NONMATCHING
	int Animation::FindGroupIndex(const core::Name<core::CaseSensitiveKey>* name)
	{
		int count = mGroupCount;
		if (count > 0)
		{
			if (mSortMode == 0)
			{
				count = count - 1;
				int low = 0;
				int middle = count / 2;
				if (count > 0)
				{
					AnimationGroup** groups = mGroups;
					do
					{
						AnimationGroup* group = groups[middle];
						if (group->mName > *name)
						{
							count = middle - 1;
						}
						else
						{
							if (!(group->mName < *name))
							{
								return middle;
							}
							low = middle + 1;
						}
						middle = (count - low) / 2 + low;
					}
					while (low < count);
				}
				if (mGroups[middle]->mName == *name)
				{
					return middle;
				}
			}
			else
			{
				int i = 0;
				if (count > 0)
				{
					AnimationGroup** groups = mGroups;
					AnimationGroup** item = groups;
					do
					{
						if ((*item)->mName == *name)
						{
							return i;
						}
						i++;
						item++;
					}
					while (i < count);
				}
			}
		}
		return -1;
	}
#endif

	// FUNCTION: ENGINE 0x106E76C0
	void AnimationMemoryManager::Touch(void* data)
	{
		AnimationDataHeader* header = (AnimationDataHeader*)data - 1;
		if (header->stream)
		{
			core::CriticalSectionEnter(&unknown10);
			compress::Stream* stream = header->stream;
			if (stream && !stream->IsDone())
			{
				header->stream->Wait();
			}
			core::CriticalSectionLeave(&unknown10);
		}
	}

	// FUNCTION: ENGINE 0x106E9820
	unsigned int SwapColour(unsigned int colour)
	{
		return colour >> 16 & 0xFF | (colour & 0xFF) << 16 | colour & 0xFF00FF00;
	}

	// FUNCTION: ENGINE 0x106E7910
	void* AnimationGroup::FindChannel(unsigned int type, unsigned int format)
	{
		for (unsigned int i = 0; i < mChannelCount; i++)
		{
			if (type == mChannels[i]->unknown8 && format == mChannels[i]->GetType())
			{
				return mChannels[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106E7B50
	void Animation::Unknown106E7B50()
	{
		AnimationMemoryManager* manager = gAnimationMemoryManager;
		if (manager && mBlock)
		{
			manager->Release(mBlock->mData);
		}
	}

	// FUNCTION: ENGINE 0x106E9310
	void Animation::Unknown106E9310(int mode)
	{
		AnimationMemoryManager* manager = gAnimationMemoryManager;
		if (manager && mBlock)
		{
			if (mBlock->mData == 0)
			{
				manager->Load(this);
				manager = gAnimationMemoryManager;
			}
			manager->Use(mBlock->mData, mode);
		}
	}

	// FUNCTION: ENGINE 0x106E3050
	void FrameTime::SetTime(float newTime)
	{
		time = newTime;
		frame = (short)(int)newTime;
	}

	// FUNCTION: ENGINE 0x106E7B20
	void Animation::Touch()
	{
		if (gAnimationMemoryManager && mBlock && mBlock->mData)
		{
			gAnimationMemoryManager->Touch(mBlock->mData);
		}
	}

	template<class T> void ChannelKeys<T>::Set(unsigned int mode, unsigned int count, const short* frames,
		const T* values)
	{
		KeysBase<T>::Type::Set(mode, count, frames);
		this->values = values;
	}

	// FUNCTION: ENGINE 0x106E3440
	// NONMATCHING: the engine's search tests once more whether the key is above the frame before it drops the upper half (a
	// comparison that cannot be true there; 146 bytes against 148)
#ifdef NONMATCHING
	bool ChannelKeysBase::FindKeys(float frame, unsigned int* index0, unsigned int* index1)
	{
		short key = (short)(int)frame;
		const short* keys = this->frames;
		if (key < keys[0])
		{
			*index1 = 0;
			*index0 = 0;
			return false;
		}
		if (key >= keys[count - 1])
		{
			*index1 = *index0 = count - 1;
			return false;
		}
		unsigned int low = 0;
		unsigned int high = count - 1;
		unsigned int sum = high + low;
		for (;;)
		{
			unsigned int middle = sum >> 1;
			short value = keys[middle];
			if (value <= key)
			{
				if (key < keys[middle + 1])
				{
					*index0 = middle;
					*index1 = middle + 1;
					return true;
				}
				if (value < key)
				{
					low = middle + 1;
				}
			}
			else
			{
				high = middle - 1;
			}
			sum = high + low;
		}
	}
#endif

	// FUNCTION: ENGINE 0x106E34E0
	// EQUIVALENT: the engine's search tests once more whether the key is above the time before it drops the upper
	// half (a comparison that cannot be true there; 206 bytes against 204)
	bool ChannelKeysBase::FindKeys(FrameTime time, unsigned int* index0, unsigned int* index1, short* frame0,
		short* frame1)
	{
		const short* keys = frames;
		if (time.frame < keys[0])
		{
			*index0 = *index1 = 0;
			*frame0 = *frame1 = keys[0];
			return false;
		}
		if (time.frame >= keys[count - 1])
		{
			*index0 = *index1 = count - 1;
			*frame0 = *frame1 = keys[count - 1];
			return false;
		}
		unsigned int low = 0;
		unsigned int high = count - 1;
		unsigned int sum = low + high;
		for (;;)
		{
			unsigned int middle = sum >> 1;
			short frame = keys[middle];
			if (frame <= time.frame)
			{
				if (time.frame < keys[middle + 1])
				{
					*index0 = middle;
					*frame0 = keys[middle];
					*index1 = middle + 1;
					*frame1 = keys[middle + 1];
					return true;
				}
				if (frame < time.frame)
				{
					low = middle + 1;
				}
			}
			else
			{
				high = middle - 1;
			}
			sum = high + low;
		}
	}

	// The key readers: one value (or two) of a key array by index
	template<class T> void GetKey(const T* values, int index, T* out)
	{
		*out = values[index];
	}

	template<class T> void GetKeys(const T* values, int index0, int index1, T* out0, T* out1)
	{
		*out0 = values[index0];
		*out1 = values[index1];
	}

	// The pairs and the vectors are copied float by float (defined below)
	template<> void GetKey<Float2>(const Float2* values, int index, Float2* out);
	template<> void GetKeys<Float2>(const Float2* values, int index0, int index1, Float2* out0, Float2* out1);
	template<> void GetKey<math::Vector>(const math::Vector* values, int index, math::Vector* out);
	template<> void GetKeys<math::Vector>(const math::Vector* values, int index0, int index1, math::Vector* out0,
		math::Vector* out1);

	// FUNCTION: ENGINE 0x106E3FE0
	int ChannelKeysBase::GetFirstFrame()
	{
		short frame;
		pure3d::GetKey(frames, 0, &frame);
		return frame;
	}

	// FUNCTION: ENGINE 0x106E4000
	int ChannelKeysBase::GetLastFrame()
	{
		short frame;
		pure3d::GetKey(frames, count - 1, &frame);
		return frame;
	}

	template<class T> void ChannelKeys<T>::GetKeyAt(unsigned int index, float* frame, typename KeyValue<T>::Type* out)
	{
		short key;
		pure3d::GetKey(frames, index, &key);
		*frame = (float)key;
		pure3d::GetKey(values, index, out);
	}

	// FUNCTION: ENGINE 0x106E41C0
	template<> void ChannelKeys<float>::Evaluate(FrameTime time, float* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			float a;
			float b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				*out = a;
				return;
			}
			*out = ((b - a) / (time1.time - time0.time)) * alpha + a;
			return;
		}
		pure3d::GetKey(values, index0, out);
	}

	// FUNCTION: ENGINE 0x106E4060
	template<> void ChannelKeys<int>::Evaluate(FrameTime time, int* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			int a;
			int b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				*out = a;
				return;
			}
			*out = (int)(((float)(b - a) / (time1.time - time0.time)) * alpha) + a;
			return;
		}
		pure3d::GetKey(values, index0, out);
	}

	// FUNCTION: ENGINE 0x106E4320
	// NONMATCHING: stack frame (53 %: the engine's frame is 8 bytes larger, it keeps the interpolation factor in memory)
#ifdef NONMATCHING
	template<> void ChannelKeys<Float2>::Evaluate(FrameTime time, Float2* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			Float2 a;
			Float2 b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				out->x = a.x;
				out->y = a.y;
				return;
			}
			float t = alpha / (time1.time - time0.time);
			out->x = (b.x - a.x) * t + a.x;
			out->y = (b.y - a.y) * t + a.y;
			return;
		}
		pure3d::GetKey(values, index0, out);
	}
#endif

	// FUNCTION: ENGINE 0x106E57C0
	// NONMATCHING: stack frame (49 %: the engine's frame is 8 bytes larger and it computes the time offset before the key call)
#ifdef NONMATCHING
	template<> void ChannelKeys<math::Vector>::Evaluate(FrameTime time, math::Vector* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			math::Vector a;
			math::Vector b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				out->x = a.x;
				out->y = a.y;
				out->z = a.z;
				return;
			}
			float t = alpha / (time1.time - time0.time);
			out->x = (b.x - a.x) * t + a.x;
			out->y = (b.y - a.y) * t + a.y;
			out->z = (b.z - a.z) * t + a.z;
			return;
		}
		pure3d::GetKey(values, index0, out);
	}
#endif

	// FUNCTION: ENGINE 0x106E5B40
	template<> void ChannelKeys<math::Quaternion>::Evaluate(FrameTime time, math::Quaternion* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			math::Quaternion a;
			math::Quaternion b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				*out = a;
				return;
			}
			float t = alpha / (time1.time - time0.time);
			out->Slerp(a, b, t);
			return;
		}
		pure3d::GetKey(values, index0, out);
	}

	// FUNCTION: ENGINE 0x106E6350
	template<> void ChannelKeys<math::CompressedQuaternion6>::Evaluate(FrameTime time, math::Quaternion* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			math::CompressedQuaternion6 a;
			math::CompressedQuaternion6 b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				*out = a.ToQuaternion();
				return;
			}
			float t = alpha / (time1.time - time0.time);
			out->Slerp(a.ToQuaternion(), b.ToQuaternion(), t);
			return;
		}
		math::CompressedQuaternion6 key;
		pure3d::GetKey(values, index0, &key);
		*out = key.ToQuaternion();
	}

	// FUNCTION: ENGINE 0x106E69B0
	template<> void ChannelKeys<math::CompressedQuaternion3>::Evaluate(FrameTime time, math::Quaternion* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			math::CompressedQuaternion3 a;
			math::CompressedQuaternion3 b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				*out = a.ToQuaternion();
				return;
			}
			float t = alpha / (time1.time - time0.time);
			out->Slerp(a.ToQuaternion(), b.ToQuaternion(), t);
			return;
		}
		math::CompressedQuaternion3 key;
		pure3d::GetKey(values, index0, &key);
		*out = key.ToQuaternion();
	}

	// The matrix of a stored rotation (the key or the value at a time)
	template<class T> void ChannelKeys<T>::GetKeyAt(unsigned int index, float* frame, math::Matrix* out)
	{
		math::Quaternion q;
		GetKeyAt(index, frame, &q);
		q.ToMatrix(*out);
	}

	template<class T> void ChannelKeys<T>::Evaluate(float time, typename KeyValue<T>::Type* out)
	{
		Evaluate(FrameTime(time), out);
	}

	template<class T> void ChannelKeys<T>::Evaluate(float time, math::Matrix* out)
	{
		math::Quaternion q;
		Evaluate(FrameTime(time), &q);
		q.ToMatrix(*out);
	}

	// FUNCTION: ENGINE 0x106E5EB0
	template<> void ChannelKeys<math::CompressedQuaternion8>::GetKeyAt(unsigned int index, float* frame,
		math::Quaternion* out)
	{
		short key;
		pure3d::GetKey(frames, index, &key);
		*frame = (float)key;
		math::CompressedQuaternion8 value;
		pure3d::GetKey(values, index, &value);
		*out = value.ToQuaternion();
	}

	// FUNCTION: ENGINE 0x106E6230
	template<> void ChannelKeys<math::CompressedQuaternion6>::GetKeyAt(unsigned int index, float* frame,
		math::Quaternion* out)
	{
		short key;
		pure3d::GetKey(frames, index, &key);
		*frame = (float)key;
		math::CompressedQuaternion6 value;
		pure3d::GetKey(values, index, &value);
		*out = value.ToQuaternion();
	}

	// FUNCTION: ENGINE 0x106E6540
	template<> void ChannelKeys<math::CompressedQuaternion4>::GetKeyAt(unsigned int index, float* frame,
		math::Quaternion* out)
	{
		short key;
		pure3d::GetKey(frames, index, &key);
		*frame = (float)key;
		math::CompressedQuaternion4 value;
		pure3d::GetKey(values, index, &value);
		*out = value.ToQuaternion();
	}

	// FUNCTION: ENGINE 0x106E6890
	template<> void ChannelKeys<math::CompressedQuaternion3>::GetKeyAt(unsigned int index, float* frame,
		math::Quaternion* out)
	{
		short key;
		pure3d::GetKey(frames, index, &key);
		*frame = (float)key;
		math::CompressedQuaternion3 value;
		pure3d::GetKey(values, index, &value);
		*out = value.ToQuaternion();
	}

	// FUNCTION: ENGINE 0x106E5FA0
	template<> void ChannelKeys<math::CompressedQuaternion8>::Evaluate(FrameTime time, math::Quaternion* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			math::CompressedQuaternion8 a;
			math::CompressedQuaternion8 b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				*out = a.ToQuaternion();
				return;
			}
			float t = alpha / (time1.time - time0.time);
			out->Slerp(a.ToQuaternion(), b.ToQuaternion(), t);
			return;
		}
		math::CompressedQuaternion8 key;
		pure3d::GetKey(values, index0, &key);
		*out = key.ToQuaternion();
	}

	// FUNCTION: ENGINE 0x106E6680
	template<> void ChannelKeys<math::CompressedQuaternion4>::Evaluate(FrameTime time, math::Quaternion* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			math::CompressedQuaternion4 a;
			math::CompressedQuaternion4 b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				*out = a.ToQuaternion();
				return;
			}
			float t = alpha / (time1.time - time0.time);
			out->Slerp(a.ToQuaternion(), b.ToQuaternion(), t);
			return;
		}
		math::CompressedQuaternion4 key;
		pure3d::GetKey(values, index0, &key);
		*out = key.ToQuaternion();
	}

	// The two axes a Float2 / Short2 key fills, by the axis the channel leaves to its constant (data section)
	static int sAxisPairs[3][2] = {{1, 2}, {0, 2}, {0, 1}};

	// FUNCTION: ENGINE 0x106E4460
	// NONMATCHING: the engine copies the constant vector with the first component through the x87 unit and the others through SSE (55 %)
#ifdef NONMATCHING
	template<> void DOFKeys<float>::GetKeyAt(unsigned int index, float* frame, math::Vector* out)
	{
		short key;
		pure3d::GetKey(frames, index, &key);
		*frame = (float)key;
		math::Vector copy(constant.x, constant.y, constant.z);
		out->x = copy.x;
		out->y = copy.y;
		out->z = copy.z;
		float value;
		pure3d::GetKey(values, index, &value);
		((float*)out)[axis] = value;
	}
#endif

	// FUNCTION: ENGINE 0x106E4620
	// NONMATCHING: the engine copies the constant vector with the first component through the x87 unit and the others through SSE (48 %)
#ifdef NONMATCHING
	template<> void DOFKeys<Float2>::GetKeyAt(unsigned int index, float* frame, math::Vector* out)
	{
		short key;
		pure3d::GetKey(frames, index, &key);
		*frame = (float)key;
		math::Vector copy(constant.x, constant.y, constant.z);
		out->x = copy.x;
		out->y = copy.y;
		out->z = copy.z;
		Float2 value;
		pure3d::GetKey(values, index, &value);
		((float*)out)[sAxisPairs[axis][0]] = value.x;
		((float*)out)[sAxisPairs[axis][1]] = value.y;
	}
#endif

	// FUNCTION: ENGINE 0x106E44D0
	// NONMATCHING: the engine copies the constant vector with the first component through the x87 unit and the others through SSE (30 %)
#ifdef NONMATCHING
	template<> void DOFKeys<float>::Evaluate(FrameTime time, math::Vector* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		math::Vector copy(constant.x, constant.y, constant.z);
		out->x = copy.x;
		out->y = copy.y;
		out->z = copy.z;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			float a;
			float b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				((float*)out)[axis] = a;
				return;
			}
			((float*)out)[axis] = ((b - a) / (time1.time - time0.time)) * alpha + a;
			return;
		}
		float value;
		pure3d::GetKey(values, index0, &value);
		((float*)out)[axis] = value;
	}
#endif

	// FUNCTION: ENGINE 0x106E49D0
	// NONMATCHING: the engine copies the constant vector with the first component through the x87 unit and the others through SSE (27 %)
#ifdef NONMATCHING
	template<> void DOFKeys<Float2>::Evaluate(FrameTime time, math::Vector* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		math::Vector copy(constant.x, constant.y, constant.z);
		out->x = copy.x;
		out->y = copy.y;
		out->z = copy.z;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			Float2 a;
			Float2 b;
			GetKeys(values, index0, index1, &a, &b);
			if (alpha == 0.0f)
			{
				((float*)out)[sAxisPairs[axis][0]] = a.x;
				((float*)out)[sAxisPairs[axis][1]] = a.y;
				return;
			}
			float t = alpha / (time1.time - time0.time);
			((float*)out)[sAxisPairs[axis][0]] = (b.x - a.x) * t + a.x;
			((float*)out)[sAxisPairs[axis][1]] = (b.y - a.y) * t + a.y;
			return;
		}
		Float2 value;
		pure3d::GetKey(values, index0, &value);
		((float*)out)[sAxisPairs[axis][0]] = value.x;
		((float*)out)[sAxisPairs[axis][1]] = value.y;
	}
#endif

	// FUNCTION: ENGINE 0x106E5740
	template<> void ChannelKeys<Short3>::GetKeyAt(unsigned int index, float* frame, math::Vector* out)
	{
		short key;
		pure3d::GetKey(frames, index, &key);
		*frame = (float)key;
		Short3 value;
		pure3d::GetKey(values, index, &value);
		math::Vector vector = ((Half3&)value).ToVector();
		out->x = vector.x;
		out->y = vector.y;
		out->z = vector.z;
	}

	// FUNCTION: ENGINE 0x106E5930
	// NONMATCHING: the engine places the two vectors of the keys over the keys' own slots (frame 0x38 against 0x54, 51 %)
#ifdef NONMATCHING
	template<> void ChannelKeys<Short3>::Evaluate(FrameTime time, math::Vector* out)
	{
		FrameTime time0;
		FrameTime time1;
		unsigned int index0;
		unsigned int index1;
		int frame0;
		int frame1;
		bool found = FindKeys(time, &index0, &index1, (short*)&frame0, (short*)&frame1);
		time0.SetFrame(frame0);
		time1.SetFrame(frame1);
		if (found && mode != 0)
		{
			float alpha = time.time - time0.time;
			Short3 a;
			Short3 b;
			GetKeys(values, index0, index1, &a, &b);
			math::Vector va = ((Half3&)a).ToVector();
			math::Vector vb = ((Half3&)b).ToVector();
			if (alpha != 0.0f)
			{
				float t = alpha / (time1.time - time0.time);
				out->x = (vb.x - va.x) * t + va.x;
				out->y = (vb.y - va.y) * t + va.y;
				out->z = (vb.z - va.z) * t + va.z;
				return;
			}
			out->x = va.x;
			out->y = va.y;
			out->z = va.z;
			return;
		}
		Short3 value;
		pure3d::GetKey(values, index0, &value);
		math::Vector v = ((Half3&)value).ToVector();
		out->x = v.x;
		out->y = v.y;
		out->z = v.z;
	}
#endif
}

// FUNCTION: ENGINE 0x106E30C0
template void pure3d::ChannelKeys<float>::Set(unsigned int mode, unsigned int count, const short* frames,
	const float* values);

// FUNCTION: ENGINE 0x106E3A40
template void pure3d::GetKey<float>(const float* values, int index, float* out);

// FUNCTION: ENGINE 0x106E3A60
template void pure3d::GetKeys<float>(const float* values, int index0, int index1, float* out0, float* out1);

// FUNCTION: ENGINE 0x106E3CC0
template void pure3d::GetKey<math::CompressedQuaternion6>(const math::CompressedQuaternion6* values, int index,
	math::CompressedQuaternion6* out);

// FUNCTION: ENGINE 0x106E3CE0
template void pure3d::GetKeys<math::CompressedQuaternion6>(const math::CompressedQuaternion6* values, int index0,
	int index1, math::CompressedQuaternion6* out0, math::CompressedQuaternion6* out1);

// FUNCTION: ENGINE 0x106E3D60
template void pure3d::GetKey<math::CompressedQuaternion3>(const math::CompressedQuaternion3* values, int index,
	math::CompressedQuaternion3* out);

// FUNCTION: ENGINE 0x106E3D80
template void pure3d::GetKeys<math::CompressedQuaternion3>(const math::CompressedQuaternion3* values, int index0,
	int index1, math::CompressedQuaternion3* out0, math::CompressedQuaternion3* out1);

// The setters of the typed keys (one COMDAT copy per type)
// FUNCTION: ENGINE 0x106E30A0
template void pure3d::ChannelKeys<int>::Set(unsigned int mode, unsigned int count, const short* frames,
	const int* values);

// FUNCTION: ENGINE 0x106E30E0
template void pure3d::ChannelKeys<pure3d::Float2>::Set(unsigned int mode, unsigned int count, const short* frames,
	const pure3d::Float2* values);

// FUNCTION: ENGINE 0x106E3110
template void pure3d::DOFKeys<float>::Set(unsigned int mode, unsigned int count, const short* frames, int axis,
	math::Vector constant, const float* values);

// FUNCTION: ENGINE 0x106E3160
template void pure3d::DOFKeys<pure3d::Float2>::Set(unsigned int mode, unsigned int count, const short* frames, int axis,
	math::Vector constant, const pure3d::Float2* values);

// FUNCTION: ENGINE 0x106E31B0
template void pure3d::DOFKeys<pure3d::Short2>::Set(unsigned int mode, unsigned int count, const short* frames, int axis,
	math::Vector constant, const pure3d::Short2* values);

// FUNCTION: ENGINE 0x106E3200
template void pure3d::ChannelKeys<math::Vector>::Set(unsigned int mode, unsigned int count, const short* frames,
	const math::Vector* values);

// FUNCTION: ENGINE 0x106E3220
template void pure3d::ChannelKeys<pure3d::Short3>::Set(unsigned int mode, unsigned int count, const short* frames,
	const pure3d::Short3* values);

// FUNCTION: ENGINE 0x106E3250
template void pure3d::ChannelKeys<math::Quaternion>::Set(unsigned int mode, unsigned int count, const short* frames,
	const math::Quaternion* values);

// FUNCTION: ENGINE 0x106E39E0
template void pure3d::GetKey<short>(const short* values, int index, short* out);

// FUNCTION: ENGINE 0x106E3A00
template void pure3d::GetKey<int>(const int* values, int index, int* out);

// FUNCTION: ENGINE 0x106E3A20
template void pure3d::GetKeys<int>(const int* values, int index0, int index1, int* out0, int* out1);

// The floats of a pair are copied one by one
// FUNCTION: ENGINE 0x106E3AD0
template void pure3d::GetKey<pure3d::Short2>(const pure3d::Short2* values, int index, pure3d::Short2* out);

// FUNCTION: ENGINE 0x106E3AF0
template void pure3d::GetKeys<pure3d::Short2>(const pure3d::Short2* values, int index0, int index1,
	pure3d::Short2* out0, pure3d::Short2* out1);

// FUNCTION: ENGINE 0x106E3A80
template<> void pure3d::GetKey<pure3d::Float2>(const pure3d::Float2* values, int index, pure3d::Float2* out)
{
	out->x = values[index].x;
	out->y = values[index].y;
}

// FUNCTION: ENGINE 0x106E3AA0
template<> void pure3d::GetKeys<pure3d::Float2>(const pure3d::Float2* values, int index0, int index1,
	pure3d::Float2* out0, pure3d::Float2* out1)
{
	out0->x = values[index0].x;
	out0->y = values[index0].y;
	out1->x = values[index1].x;
	out1->y = values[index1].y;
}

// FUNCTION: ENGINE 0x106E3B10
template<> void pure3d::GetKey<math::Vector>(const math::Vector* values, int index, math::Vector* out)
{
	out->x = values[index].x;
	out->y = values[index].y;
	out->z = values[index].z;
}

// FUNCTION: ENGINE 0x106E3B40
template void pure3d::GetKey<pure3d::Short3>(const pure3d::Short3* values, int index, pure3d::Short3* out);

// FUNCTION: ENGINE 0x106E3B60
template<> void pure3d::GetKeys<math::Vector>(const math::Vector* values, int index0, int index1, math::Vector* out0,
	math::Vector* out1)
{
	out0->x = values[index0].x;
	out0->y = values[index0].y;
	out0->z = values[index0].z;
	out1->x = values[index1].x;
	out1->y = values[index1].y;
	out1->z = values[index1].z;
}

// FUNCTION: ENGINE 0x106E3BB0
template void pure3d::GetKeys<pure3d::Short3>(const pure3d::Short3* values, int index0, int index1,
	pure3d::Short3* out0, pure3d::Short3* out1);

// FUNCTION: ENGINE 0x106E3BF0
template void pure3d::GetKey<math::Quaternion>(const math::Quaternion* values, int index, math::Quaternion* out);

// FUNCTION: ENGINE 0x106E3C20
template void pure3d::GetKeys<math::Quaternion>(const math::Quaternion* values, int index0, int index1,
	math::Quaternion* out0, math::Quaternion* out1);

// FUNCTION: ENGINE 0x106E3C70
template void pure3d::GetKey<math::CompressedQuaternion8>(const math::CompressedQuaternion8* values, int index,
	math::CompressedQuaternion8* out);

// FUNCTION: ENGINE 0x106E3C90
template void pure3d::GetKeys<math::CompressedQuaternion8>(const math::CompressedQuaternion8* values, int index0,
	int index1, math::CompressedQuaternion8* out0, math::CompressedQuaternion8* out1);

// FUNCTION: ENGINE 0x106E3D20
template void pure3d::GetKey<math::CompressedQuaternion4>(const math::CompressedQuaternion4* values, int index,
	math::CompressedQuaternion4* out);

// FUNCTION: ENGINE 0x106E3D40
template void pure3d::GetKeys<math::CompressedQuaternion4>(const math::CompressedQuaternion4* values, int index0,
	int index1, math::CompressedQuaternion4* out0, math::CompressedQuaternion4* out1);

// FUNCTION: ENGINE 0x106E4020
template void pure3d::ChannelKeys<int>::GetKeyAt(unsigned int index, float* frame, int* out);

// FUNCTION: ENGINE 0x106E4180
template void pure3d::ChannelKeys<float>::GetKeyAt(unsigned int index, float* frame, float* out);

// FUNCTION: ENGINE 0x106E42E0
template void pure3d::ChannelKeys<pure3d::Float2>::GetKeyAt(unsigned int index, float* frame, pure3d::Float2* out);

// FUNCTION: ENGINE 0x106E5700
template void pure3d::ChannelKeys<math::Vector>::GetKeyAt(unsigned int index, float* frame, math::Vector* out);

// FUNCTION: ENGINE 0x106E5AD0
template void pure3d::ChannelKeys<math::Quaternion>::GetKeyAt(unsigned int index, float* frame, math::Quaternion* out);

// FUNCTION: ENGINE 0x106E5B10
template void pure3d::ChannelKeys<math::Quaternion>::GetKeyAt(unsigned int index, float* frame, math::Matrix* out);

// FUNCTION: ENGINE 0x106E5F70
template void pure3d::ChannelKeys<math::CompressedQuaternion8>::GetKeyAt(unsigned int index, float* frame, math::Matrix* out);

// FUNCTION: ENGINE 0x106E6320
template void pure3d::ChannelKeys<math::CompressedQuaternion6>::GetKeyAt(unsigned int index, float* frame, math::Matrix* out);

// FUNCTION: ENGINE 0x106E6650
template void pure3d::ChannelKeys<math::CompressedQuaternion4>::GetKeyAt(unsigned int index, float* frame, math::Matrix* out);

// FUNCTION: ENGINE 0x106E6980
template void pure3d::ChannelKeys<math::CompressedQuaternion3>::GetKeyAt(unsigned int index, float* frame, math::Matrix* out);

// FUNCTION: ENGINE 0x106E6BA0
template void pure3d::ChannelKeys<math::CompressedQuaternion8>::Evaluate(float time, math::Quaternion* out);

// FUNCTION: ENGINE 0x106E6BD0
template void pure3d::ChannelKeys<math::CompressedQuaternion6>::Evaluate(float time, math::Quaternion* out);

// FUNCTION: ENGINE 0x106E6C00
template void pure3d::ChannelKeys<math::CompressedQuaternion4>::Evaluate(float time, math::Quaternion* out);

// FUNCTION: ENGINE 0x106E6C30
template void pure3d::ChannelKeys<math::CompressedQuaternion3>::Evaluate(float time, math::Quaternion* out);

// FUNCTION: ENGINE 0x106E6C60
template void pure3d::ChannelKeys<math::Quaternion>::Evaluate(float time, math::Quaternion* out);

// FUNCTION: ENGINE 0x106E6C90
template void pure3d::ChannelKeys<math::Quaternion>::Evaluate(float time, math::Matrix* out);

// FUNCTION: ENGINE 0x106E6E20
template void pure3d::ChannelKeys<math::CompressedQuaternion8>::Evaluate(float time, math::Matrix* out);

// FUNCTION: ENGINE 0x106E6E60
template void pure3d::ChannelKeys<math::CompressedQuaternion6>::Evaluate(float time, math::Matrix* out);

// FUNCTION: ENGINE 0x106E6EA0
template void pure3d::ChannelKeys<math::CompressedQuaternion4>::Evaluate(float time, math::Matrix* out);

// FUNCTION: ENGINE 0x106E6EE0
template void pure3d::ChannelKeys<math::CompressedQuaternion3>::Evaluate(float time, math::Matrix* out);

// FUNCTION: ENGINE 0x106E8200
template void core::SafeRelease<pure3d::AnimationMemoryBlock>(pure3d::AnimationMemoryBlock*& object);

// FUNCTION: ENGINE 0x106E8220
template void core::SafeRelease<pure3d::ChannelLoader>(pure3d::ChannelLoader*& object);
