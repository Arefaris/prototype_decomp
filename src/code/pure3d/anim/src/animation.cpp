// pure3d animations (code/pure3d/anim/src/animation.cpp, path from the asserts; the unit starts around 0x106E2A30):
// the key readers of the channels among others. Names are guesses.
#include "code/math/compressedquaternion.h"
#include "code/math/mathutils.h"
#include <math.h>
#include "code/pure3d/animation.h"
#include "code/pure3d/channel.h"
#include "code/pure3d/effects/particlecontroller.h"

namespace engine
{
	namespace camera
	{
		extern const float gThousandth;
	}
}


namespace math
{
	// The scale factors sit in the data section (initialised there, not constants of the code)
	float CompressedQuaternion6::sScale = 1.0f / 32767.0f;
	float CompressedQuaternion3::sScale = 1.0f / 127.0f;

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

	template<class T> void ChannelKeys<T>::GetKey(unsigned int index, float* frame, typename KeyValue<T>::Type* out)
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
template void pure3d::ChannelKeys<int>::GetKey(unsigned int index, float* frame, int* out);

// FUNCTION: ENGINE 0x106E4180
template void pure3d::ChannelKeys<float>::GetKey(unsigned int index, float* frame, float* out);

// FUNCTION: ENGINE 0x106E42E0
template void pure3d::ChannelKeys<pure3d::Float2>::GetKey(unsigned int index, float* frame, pure3d::Float2* out);

// FUNCTION: ENGINE 0x106E5700
template void pure3d::ChannelKeys<math::Vector>::GetKey(unsigned int index, float* frame, math::Vector* out);

// FUNCTION: ENGINE 0x106E5AD0
template void pure3d::ChannelKeys<math::Quaternion>::GetKey(unsigned int index, float* frame, math::Quaternion* out);
