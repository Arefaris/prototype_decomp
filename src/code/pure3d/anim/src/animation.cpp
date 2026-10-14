// pure3d animations (code/pure3d/anim/src/animation.cpp, path from the asserts; the unit starts around 0x106E2A30):
// the key readers of the channels among others. Names are guesses.
#include "code/math/compressedquaternion.h"
#include "code/math/mathutils.h"
#include <math.h>
#include "code/pure3d/animation.h"
#include "code/pure3d/channel.h"


namespace math
{
	// The scale factors sit in the data section (initialised there, not constants of the code)
	float CompressedQuaternion6::sScale = 1.0f / 32767.0f;
	float CompressedQuaternion8::sScale = 1.0f / 127.0f;

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
	inline Quaternion CompressedQuaternion8::ToQuaternion() const
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
		ChannelKeysBase::Set(mode, count, frames);
		this->values = values;
	}

	// FUNCTION: ENGINE 0x106E34E0
	// EQUIVALENT: same search and branches; the engine keeps the time in esi, the bounds in ebx / edi and starts the
	// loop without the alignment jump (register allocation of the loop variables)
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
		unsigned int middle = high;
		do
		{
			middle = middle >> 1;
			short frame = keys[middle];
			if (frame > time.frame)
			{
				high = middle - 1;
			}
			else
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
					middle = high + low;
					continue;
				}
				if (frame > time.frame)
				{
					high = middle - 1;
				}
			}
			middle = high + low;
		}
		while (true);
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
		GetKey(values, index0, out);
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
		GetKey(values, index0, &key);
		*out = key.ToQuaternion();
	}

	// FUNCTION: ENGINE 0x106E69B0
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
		GetKey(values, index0, &key);
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
template void pure3d::GetKey<math::CompressedQuaternion8>(const math::CompressedQuaternion8* values, int index,
	math::CompressedQuaternion8* out);

// FUNCTION: ENGINE 0x106E3D80
template void pure3d::GetKeys<math::CompressedQuaternion8>(const math::CompressedQuaternion8* values, int index0,
	int index1, math::CompressedQuaternion8* out0, math::CompressedQuaternion8* out1);
