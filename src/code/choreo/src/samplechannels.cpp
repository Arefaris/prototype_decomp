// choreo::SampleChannels (unit around 0x10952120 - 0x10955600, which samples animations into poses; file name
// guessed from the class). Names are guesses.
#include "code/choreo/samplechannels.h"
#include "code/choreo/rootdriver.h"
#include "code/choreo/poseblendjob.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x10952150
	pure3d::QuaternionChannel* SampleChannels::GetRotation(int joint)
	{
		return mRotations[joint];
	}

	// FUNCTION: ENGINE 0x10952160
	pure3d::VectorChannel* SampleChannels::GetTranslation(int joint)
	{
		return mTranslations[joint];
	}

	// FUNCTION: ENGINE 0x10952170
	pure3d::VectorChannel* SampleChannels::GetUnknown10(int joint)
	{
		return mUnknown10[joint];
	}

	// FUNCTION: ENGINE 0x10952180
	pure3d::VectorChannel* SampleChannels::GetScale(int joint)
	{
		return mScales[joint];
	}

	// FUNCTION: ENGINE 0x10952190
	pure3d::VectorChannel* SampleChannels::GetUnknown14(int joint)
	{
		return mUnknown14[joint];
	}

	// FUNCTION: ENGINE 0x109521A0
	pure3d::VectorChannel* SampleChannels::GetUnknown1C(int joint)
	{
		return mUnknown1C[joint];
	}

	// FUNCTION: ENGINE 0x10952120
	bool SampleChannels::HasRootChannels(int part) const
	{
		return mRootRotations[part] != 0 && mRootTranslations[part] != 0;
	}

	// FUNCTION: ENGINE 0x109521B0
	pure3d::QuaternionChannel* SampleChannels::GetRootRotation(int part) const
	{
		return mRootRotations[part];
	}

	// FUNCTION: ENGINE 0x109521C0
	pure3d::VectorChannel* SampleChannels::GetRootTranslation(int part) const
	{
		return mRootTranslations[part];
	}

	// FUNCTION: ENGINE 0x109521D0
	pure3d::VectorChannel* SampleChannels::GetUnknown920() const
	{
		return mUnknown920;
	}

	// FUNCTION: ENGINE 0x109521E0
	AnimationClip::AnimationClip()
	{
		mFlag0 = false;
		mFlag1 = false;
		mDuration = 0.0f;
		mFrameRate = 0.0f;
		mUnknownC = 0.0f;
		mAnimation = 0;
		mChannels = (SampleChannels*)core::HeapAllocAligned(core::GetCurrentHeap(), sizeof(SampleChannels), 0x10);
	}

	// FUNCTION: ENGINE 0x10952220
	AnimationClip::AnimationClip(const AnimationClip& other)
	{
		mDuration = other.mDuration;
		mFrameRate = other.mFrameRate;
		mUnknownC = other.mUnknownC;
		mFlag0 = other.mFlag0;
		mFlag1 = other.mFlag1;
		mAnimation = other.mAnimation;
		mChannels = (SampleChannels*)core::HeapAllocAligned(core::GetCurrentHeap(), sizeof(SampleChannels), 0x10);
		*mChannels = *other.mChannels;
	}

	// FUNCTION: ENGINE 0x10952290
	AnimationClip::~AnimationClip()
	{
		core::FreeAligned(mChannels);
	}

	// FUNCTION: ENGINE 0x10952310
	bool AnimationClip::IsSet() const
	{
		return mAnimation != 0;
	}

	// FUNCTION: ENGINE 0x10952320
	float AnimationClip::GetDuration() const
	{
		return mDuration;
	}

	// FUNCTION: ENGINE 0x10952330
	float AnimationClip::GetFrameRate() const
	{
		return mFrameRate;
	}

	// FUNCTION: ENGINE 0x10952340
	void AnimationClip::SetFrameRate(float rate)
	{
		mFrameRate = rate;
	}

	// FUNCTION: ENGINE 0x10952350
	float AnimationClip::Unknown10952350() const
	{
		return mUnknownC;
	}

	// FUNCTION: ENGINE 0x10952360
	void AnimationClip::Unknown10952360(float value)
	{
		mUnknownC = value;
	}

	// FUNCTION: ENGINE 0x10952370
	bool AnimationClip::Unknown10952370() const
	{
		return mFlag0;
	}

	// FUNCTION: ENGINE 0x10952380
	bool AnimationClip::Unknown10952380() const
	{
		return mFlag1;
	}

	// FUNCTION: ENGINE 0x10952480
	void AnimationClip::Unknown10952480(PoseBlendSample* sample) const
	{
		sample->mChannels = mChannels;
	}

	// FUNCTION: ENGINE 0x10952490
	AnimationBinding::AnimationBinding() : mSource(0)
	{
	}

	// FUNCTION: ENGINE 0x10955530
	AnimationBinding::AnimationBinding(const AnimationBinding& other) : mSource(0), mClip(other.mClip)
	{
		core::RefAssign(mSource, other.mSource);
	}

	// FUNCTION: ENGINE 0x10955560
	AnimationBinding::~AnimationBinding()
	{
		core::SafeRelease(mSource);
	}

	// FUNCTION: ENGINE 0x10955260
	int AnimationClip::GetRootRotation(float to, float from, bool forward, math::Quaternion* out)
	{
		return mChannels->GetRootRotation(pure3d::FrameTime(to), pure3d::FrameTime(from), forward, out);
	}

	// FUNCTION: ENGINE 0x109552C0
	bool AnimationClip::GetRootTranslation(float to, float from, bool forward, math::Vector* out)
	{
		return mChannels->GetRootTranslation(pure3d::FrameTime(to), pure3d::FrameTime(from), forward, out);
	}

	// FUNCTION: ENGINE 0x10955320
	bool AnimationClip::GetRootScale(float time, math::Vector* out)
	{
		return mChannels->GetRootScale(pure3d::FrameTime(time), out);
	}

	// FUNCTION: ENGINE 0x10955360
	void AnimationClip::GetTranslationAt(float time, math::Vector* out, int joint)
	{
		mChannels->GetTranslationAt(pure3d::FrameTime(time), out, joint);
	}

	// FUNCTION: ENGINE 0x10953130
	void SampleChannels::GetTranslationAt(pure3d::FrameTime time, math::Vector* out, int joint)
	{
		if (mTranslations[joint] != 0)
		{
			GetTranslation(joint)->mKeys.Evaluate(time, out);
		}
	}

	// FUNCTION: ENGINE 0x109530F0
	bool SampleChannels::GetRootScale(pure3d::FrameTime time, math::Vector* out)
	{
		bool found = false;
		if (mScales[0] != 0)
		{
			found = true;
			GetScale(0)->mKeys.Evaluate(time, out);
		}
		return found;
	}

	// FUNCTION: ENGINE 0x109554C0
	void AnimationClip::BlendValue(float time, float* value, float weight)
	{
		mChannels->BlendValue(pure3d::FrameTime(time), value, weight);
	}
}
