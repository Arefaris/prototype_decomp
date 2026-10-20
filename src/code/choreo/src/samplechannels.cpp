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
		mSkeletonData = 0;
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
		mSkeletonData = other.mSkeletonData;
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
		return mSkeletonData != 0;
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

	// FUNCTION: ENGINE 0x109522A0
	void AnimationClip::Set(pure3d::Animation* animation, pure3d::Skeleton* skeleton, bool reset)
	{
		bool hasChannels = false;
		mChannels->Bind(animation, skeleton, &hasChannels);
		mFlag1 = hasChannels;
		if (reset)
		{
			mDuration = animation->numFrames;
			mFrameRate = animation->mFrameRate;
			mUnknownC = animation->mUnknown20;
			mFlag0 = animation->mFlag0;
		}
		mSkeletonData = &skeleton->mData;
	}

	// FUNCTION: ENGINE 0x10952390
	bool AnimationClip::HasChannelsFor(const pure3d::JointMask* mask) const
	{
		bool result = true;
		unsigned int limbCount = mSkeletonData->mLimbCount;
		if (mask == 0)
		{
			for (unsigned int i = 0; i < limbCount; i++)
			{
				if (result && mChannels->HasRootChannels(i))
				{
					result = true;
				}
				else
				{
					result = false;
				}
			}
			return result;
		}
		for (unsigned int i = 0; i < limbCount; i++)
		{
			const pure3d::SkeletonLimb& limb = mSkeletonData->mLimbs[i];
			bool used = (mask->words[limb.joints[0] >> 5] & (1 << (limb.joints[0] & 31))) != 0 ||
				(mask->words[limb.joints[1] >> 5] & (1 << (limb.joints[1] & 31))) != 0 ||
				(mask->words[limb.joints[2] >> 5] & (1 << (limb.joints[2] & 31))) != 0;
			if (!result || (used && !mChannels->HasRootChannels(i)))
			{
				result = false;
			}
			else
			{
				result = true;
			}
		}
		return result;
	}

	// The four letters of the kinds of channel and of values (as the animation file spells them)
	static const unsigned int CHANNEL_ROT = 0x544F52;
	static const unsigned int CHANNEL_TRAN = 0x4E415254;
	static const unsigned int CHANNEL_VECT = 0x54434556;
	static const unsigned int CHANNEL_SCLP = 0x504C4353;
	static const unsigned int CHANNEL_SCL = 0x4C4353;
	static const unsigned int CHANNEL_SHER = 0x52454853;
	static const unsigned int CHANNEL_SCLT = 0x544C4353;
	static const unsigned int CHANNEL_LCPH = 0x4850434C;
	static const unsigned int CHANNEL_FLT2 = 0x32544C46;

	// FUNCTION: ENGINE 0x10951F30
	// NONMATCHING: the engine steps one pointer over the arrays from the third one and keeps the flag, the joint and the
	// animation in other registers (21.6 %)
#ifdef NONMATCHING
	void SampleChannels::Bind(pure3d::Animation* animation, pure3d::Skeleton* skeleton, bool* hasChannels)
	{
		unsigned int jointCount = skeleton->mData.mJointCount;
		*hasChannels = false;
		for (unsigned int i = 0; i < jointCount; i++)
		{
			pure3d::AnimationGroup* group = animation->FindGroup(&skeleton->mData.mNames[i]);
			if (group == 0)
			{
				mRotations[i] = 0;
				mTranslations[i] = 0;
				mUnknown10[i] = 0;
				mScales[i] = 0;
				mUnknown14[i] = 0;
				mUnknown1C[i] = 0;
			}
			else
			{
				mRotations[i] = (pure3d::QuaternionChannel*)group->FindChannel(CHANNEL_ROT, CHANNEL_ROT);
				mTranslations[i] = (pure3d::VectorChannel*)group->FindChannel(CHANNEL_TRAN, CHANNEL_VECT);
				mUnknown10[i] = (pure3d::VectorChannel*)group->FindChannel(CHANNEL_SCLP, CHANNEL_VECT);
				mScales[i] = (pure3d::VectorChannel*)group->FindChannel(CHANNEL_SCL, CHANNEL_VECT);
				mUnknown14[i] = (pure3d::VectorChannel*)group->FindChannel(CHANNEL_SHER, CHANNEL_VECT);
				mUnknown1C[i] = (pure3d::VectorChannel*)group->FindChannel(CHANNEL_SCLT, CHANNEL_VECT);
				if (*hasChannels == false && mUnknown10[i] == 0 && mScales[i] == 0 && mUnknown14[i] == 0 && mUnknown1C[i] == 0)
				{
					*hasChannels = false;
				}
				else
				{
					*hasChannels = true;
				}
			}
		}
		unsigned int limbCount = skeleton->mData.mLimbCount;
		for (unsigned int part = 0; part < limbCount; part++)
		{
			pure3d::AnimationGroup* group = animation->FindGroup(&skeleton->mData.mLimbs[part].name);
			if (group == 0)
			{
				mRootRotations[part] = 0;
				mRootTranslations[part] = 0;
			}
			else
			{
				mRootRotations[part] = (pure3d::QuaternionChannel*)group->FindChannel(CHANNEL_ROT, CHANNEL_ROT);
				mRootTranslations[part] = (pure3d::VectorChannel*)group->FindChannel(CHANNEL_TRAN, CHANNEL_VECT);
			}
		}
		pure3d::AnimationGroup* overall = animation->FindOverallGroup(0);
		if (overall == 0)
		{
			mUnknown920 = 0;
		}
		else
		{
			mUnknown920 = (pure3d::VectorChannel*)overall->FindChannel(CHANNEL_LCPH, CHANNEL_FLT2);
		}
	}
#endif
}
