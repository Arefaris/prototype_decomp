// choreo::SampleChannels (unit around 0x10952120 - 0x10955600, which samples animations into poses; file name
// guessed from the class). Names are guesses.
#include "code/choreo/samplechannels.h"
#include "code/choreo/rootdriver.h"
#include "code/choreo/poseblendjob.h"
#include "code/core/heap.h"

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
}
