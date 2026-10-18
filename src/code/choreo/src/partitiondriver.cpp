// choreo::PartitionDriver and choreo::AnimationBlendDriver (the unit before deltatransform.cpp; file name guessed).
// The unit builds the drivers that partition the pose of a puppet and drive the clips of one animation: the blend
// driver keeps a table of fifteen clips (0x2C bytes each, from +0x3C) and the partition driver knows the range of
// joints of the pose its clip is blended into. Names are guesses.
#include "code/choreo/blenddriver.h"
#include "code/choreo/poseblendjob.h"
#include "code/core/refptr.h"
#include <math.h>

namespace choreo
{
	// The smallest length and rate the blend still divides by (the constant at 0x10E8BA6C)
	static const float BLENDDRIVER_EPSILON = 1e-5f;

	// FUNCTION: ENGINE 0x1094C790
	bool AnimationBlendDriver::IsLooping() const
	{
		return mLooping;
	}

	// FUNCTION: ENGINE 0x1094C7A0
	bool AnimationBlendDriver::GetUnknown2D1() const
	{
		return mUnknown2D1;
	}

	// FUNCTION: ENGINE 0x1094C7B0
	float AnimationBlendDriver::GetScale() const
	{
		return mScale;
	}

	// FUNCTION: ENGINE 0x1094C7C0
	float AnimationBlendDriver::GetPhase() const
	{
		return mPhase;
	}

	// FUNCTION: ENGINE 0x1094C7D0
	BlendEntry::BlendEntry() : mStartFrame(0.0f), mEndFrame(-1.0f), mRate(1.0f), mWeight(1.0f)
	{
	}

	// FUNCTION: ENGINE 0x1094C820
	bool BlendEntry::IsIdle() const
	{
		return !(mBinding.mClip.IsSet() && mWeight >= BLENDDRIVER_EPSILON);
	}

	// FUNCTION: ENGINE 0x1094C850
	float BlendEntry::GetLength() const
	{
		if (!mBinding.mClip.IsSet())
		{
			return 0.0f;
		}
		float last = mBinding.mClip.GetDuration() - 1.0f;
		float start = mStartFrame >= 0.0f ? mStartFrame : 0.0f;
		if (start - last >= 0.0f)
		{
			start = last;
		}
		float wrapped = mEndFrame < 0.0f ? mEndFrame + last + 1.0f : mEndFrame;
		float end = wrapped >= 0.0f ? wrapped : 0.0f;
		if (end - last >= 0.0f)
		{
			end = last;
		}
		return end - start;
	}

	// FUNCTION: ENGINE 0x1094C8F0
	float BlendEntry::GetFrame(float phase, bool wrap) const
	{
		if (!mBinding.mClip.IsSet())
		{
			return 0.0f;
		}
		float last = mBinding.mClip.GetDuration() - 1.0f;
		float start = mStartFrame >= 0.0f ? mStartFrame : 0.0f;
		if (start - last >= 0.0f)
		{
			start = last;
		}
		float wrapped = mEndFrame < 0.0f ? mEndFrame + last + 1.0f : mEndFrame;
		float end = wrapped >= 0.0f ? wrapped : 0.0f;
		if (end - last >= 0.0f)
		{
			end = last;
		}
		float current = WrapFrame(start, end, mBinding.mClip.Unknown10952350());
		float range = end - start;
		float result;
		if (wrap)
		{
			result = WrapFrame(start, end, range * phase + current);
		}
		else if (phase <= 0.0f)
		{
			result = start;
		}
		else if (phase >= 1.0f)
		{
			result = end;
		}
		else
		{
			float frame = range * phase + current;
			if (!(frame - start >= 0.0f))
			{
				frame = start;
			}
			if (frame - end >= 0.0f)
			{
				frame = end;
			}
			result = frame;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1094CA80
	float BlendEntry::GetFrameStep(float phaseStep) const
	{
		return GetLength() * phaseStep;
	}

	// FUNCTION: ENGINE 0x1094CA90
	float BlendEntry::GetPhaseStep(float frames) const
	{
		float length = GetLength();
		return !(BLENDDRIVER_EPSILON >= fabsf(length)) ? frames / length : 0.0f;
	}

	// FUNCTION: ENGINE 0x1094CAE0
	AnimationBlendDriver* GetAnimationBlendDriver(Driver* driver)
	{
		return driver->mType == 1 ? static_cast<AnimationBlendDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x1094CB00
	AnimationBlendDriver* Unknown1094CB00(Driver* driver)
	{
		return driver->mType == 1 ? static_cast<AnimationBlendDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x1094CB20
	void AnimationBlendDriver::Unbind()
	{
		for (int i = 0; i < MAX_ENTRIES; i++)
		{
			if (mEntries[i].mBinding.mSource != 0)
			{
				mEntries[i].mBinding.mSource->Unknown106E7B50();
			}
		}
	}

	// FUNCTION: ENGINE 0x1094CB50
	void AnimationBlendDriver::Bind(const DriverInfo& info)
	{
		PartitionDriver::Bind(info);
		bool movesRoot = false;
		for (int i = 0; i < MAX_ENTRIES; i++)
		{
			AnimationBinding& binding = mEntries[i].mBinding;
			if (binding.mClip.IsSet())
			{
				binding.mClip.Set(binding.mSource, mSkeleton, false);
				if (movesRoot || binding.mClip.Unknown10952380())
				{
					movesRoot = true;
				}
			}
		}
		Unknown1094A4A0(movesRoot);
	}

	// FUNCTION: ENGINE 0x1094CBC0
	int AnimationBlendDriver::GetActiveCount() const
	{
		return mActiveCount;
	}

	// FUNCTION: ENGINE 0x1094CBD0
	pure3d::Animation* AnimationBlendDriver::GetAnimation(int index) const
	{
		return mEntries[index].mBinding.mSource;
	}

	// FUNCTION: ENGINE 0x1094CBE0
	bool AnimationBlendDriver::AllAtRest() const
	{
		bool atRest = true;
		for (int i = 0; i < MAX_ENTRIES; i++)
		{
			if (mEntries[i].mBinding.mClip.IsSet())
			{
				if (Unknown1094D4C0(mEntries[i].mBinding) && atRest)
				{
					atRest = true;
				}
				else
				{
					atRest = false;
				}
			}
		}
		return atRest;
	}

	// FUNCTION: ENGINE 0x1094CC30
	float AnimationBlendDriver::GetEntryUnknownC(int index) const
	{
		return mEntries[index].mBinding.mClip.Unknown10952350();
	}

	// FUNCTION: ENGINE 0x1094CC50
	void AnimationBlendDriver::SetEntryUnknownC(int index, float value)
	{
		mEntries[index].mBinding.mClip.Unknown10952360(value);
	}

	// FUNCTION: ENGINE 0x1094CC70
	float AnimationBlendDriver::GetStartFrame(int index) const
	{
		return mEntries[index].mStartFrame;
	}

	// FUNCTION: ENGINE 0x1094CC80
	void AnimationBlendDriver::SetStartFrame(int index, float frame)
	{
		mEntries[index].mStartFrame = frame;
	}

	// FUNCTION: ENGINE 0x1094CCA0
	float AnimationBlendDriver::GetEndFrame(int index) const
	{
		return mEntries[index].mEndFrame;
	}

	// FUNCTION: ENGINE 0x1094CCB0
	void AnimationBlendDriver::SetEndFrame(int index, float frame)
	{
		mEntries[index].mEndFrame = frame;
	}

	// FUNCTION: ENGINE 0x1094CCD0
	float AnimationBlendDriver::GetRate(int index) const
	{
		return mEntries[index].mRate;
	}

	// FUNCTION: ENGINE 0x1094CCE0
	void AnimationBlendDriver::SetRate(int index, float rate)
	{
		mEntries[index].mRate = rate;
	}

	// FUNCTION: ENGINE 0x1094CD00
	float AnimationBlendDriver::GetWeight(int index) const
	{
		return mEntries[index].mWeight;
	}

	// FUNCTION: ENGINE 0x1094CD10
	void AnimationBlendDriver::SetWeight(int index, float weight)
	{
		bool wasIdle = mEntries[index].IsIdle();
		mEntries[index].mWeight = weight;
		bool idle = mEntries[index].IsIdle();
		if (idle != wasIdle)
		{
			if (idle)
			{
				mActiveCount--;
			}
			if (wasIdle)
			{
				mActiveCount++;
			}
		}
	}

	// FUNCTION: ENGINE 0x1094CD60
	float AnimationBlendDriver::GetNaturalDuration() const
	{
		float duration = 0.0f;
		float totalWeight = 0.0f;
		for (int i = 0; i < MAX_ENTRIES; i++)
		{
			const BlendEntry& entry = mEntries[i];
			if (entry.mBinding.mClip.IsSet())
			{
				totalWeight = entry.mWeight + totalWeight;
				float share = totalWeight > 0.0f ? entry.mWeight / totalWeight : 0.0f;
				float frameRate = entry.mBinding.mClip.GetFrameRate();
				float perFrame;
				if (BLENDDRIVER_EPSILON >= fabsf(frameRate))
				{
					perFrame = 0.0f;
				}
				else
				{
					perFrame = 1.0f / frameRate;
				}
				float rate = entry.mRate;
				float perRate;
				if (BLENDDRIVER_EPSILON >= fabsf(rate))
				{
					perRate = 0.0f;
				}
				else
				{
					perRate = 1.0f / rate;
				}
				duration = (entry.GetLength() * perRate * perFrame - duration) * share + duration;
			}
		}
		float factor;
		if (BLENDDRIVER_EPSILON >= fabsf(mScale))
		{
			factor = 0.0f;
		}
		else
		{
			factor = 1.0f / mScale;
		}
		return factor * duration;
	}

	// FUNCTION: ENGINE 0x1094CEA0
	void AnimationBlendDriver::SetDuration(float duration)
	{
		mScale = 1.0f;
		float natural = GetNaturalDuration();
		if (!(BLENDDRIVER_EPSILON >= fabsf(duration)))
		{
			mScale = natural / duration;
		}
	}

	// FUNCTION: ENGINE 0x1094CEF0
	float AnimationBlendDriver::GetPhaseStep(float dt) const
	{
		float step = 0.0f;
		float totalWeight = 0.0f;
		for (int i = 0; i < MAX_ENTRIES; i++)
		{
			const BlendEntry& entry = mEntries[i];
			if (entry.mBinding.mClip.IsSet())
			{
				totalWeight = entry.mWeight + totalWeight;
				float share = totalWeight > 0.0f ? entry.mWeight / totalWeight : 0.0f;
				float entryStep = entry.GetPhaseStep(entry.mBinding.mClip.GetFrameRate() * entry.mRate * dt);
				step = (entryStep - step) * share + step;
			}
		}
		return mScale * step;
	}

	// FUNCTION: ENGINE 0x1094CF90
	void AnimationBlendDriver::SetPhase(float phase)
	{
		if (mLooping)
		{
			mPhase = WrapPhase(phase);
			return;
		}
		if (!(phase >= 0.0f))
		{
			phase = 0.0f;
		}
		if (phase - 1.0f >= 0.0f)
		{
			phase = 1.0f;
		}
		mPhase = phase;
	}

	// FUNCTION: ENGINE 0x1094CFF0
	void AnimationBlendDriver::Advance()
	{
		mPreviousPhase = mPhase;
		SetPhase(mPhaseStep + mPhase);
	}

	// FUNCTION: ENGINE 0x1094D020
	void AnimationBlendDriver::FillNode(PoseBlendNode* node, PoseBlendSample* samples)
	{
		unsigned int first = mFirstJoint;
		bool rotation = false;
		bool translation = false;
		bool full = false;
		if (first == 0)
		{
			rotation = true;
			translation = true;
			full = true;
			first = 1;
		}
		node->SetJoints(first, mLastJoint, (void*)mJointMask);
		node->Set(samples, samples + mActiveCount, rotation, translation, full);
		float weightSum = 0.0f;
		for (int i = 0; i < MAX_ENTRIES; i++)
		{
			BlendEntry& entry = mEntries[i];
			if (!entry.IsIdle())
			{
				weightSum = entry.mWeight + weightSum;
				entry.mBinding.mClip.Unknown10952480(samples);
				samples->Set(entry.mWeight, weightSum, entry.GetFrame(mPhase, mLooping),
					entry.GetFrame(mPreviousPhase, mLooping), entry.GetFrameStep(mPhaseStep) >= 0.0f);
				samples++;
				entry.mBinding.mSource->Touch();
			}
		}
	}

	// FUNCTION: ENGINE 0x1094D160
	void AnimationBlendDriver::UpdateFinished()
	{
		bool finished = false;
		if (!mLooping && !mUnknown2D1)
		{
			if (mScale >= 0.0f)
			{
				finished = mPhase >= 1.0f;
			}
			else
			{
				finished = 0.0f >= mPhase;
			}
		}
		Unknown1094A4C0(finished);
	}

	// FUNCTION: ENGINE 0x1094D1F0
	AnimationBlendDriver::AnimationBlendDriver(pure3d::Skeleton* skeleton) : PartitionDriver(skeleton, 1), mActiveCount(0)
	{
		mScale = 1.0f;
		mLooping = false;
		mUnknown2D1 = false;
		mPreviousPhase = 0.0f;
		mPhase = 0.0f;
		mPhaseStep = 0.0f;
		Unknown1094A430(true);
		Unknown1094A440(true);
		Unknown1094A460(true);
	}

	// FUNCTION: ENGINE 0x1094D290
	AnimationBlendDriver::~AnimationBlendDriver()
	{
	}

	// FUNCTION: ENGINE 0x1094D2C0
	void AnimationBlendDriver::SetAnimation(int index, pure3d::Animation* animation)
	{
		bool wasIdle = mEntries[index].IsIdle();
		if (mEntries[index].mBinding.mSource != 0)
		{
			mEntries[index].mBinding.mSource->Unknown106E7B50();
		}
		core::RefAssign(mEntries[index].mBinding.mSource, animation);
		if (animation != 0)
		{
			animation->Unknown106E9310(1);
			mEntries[index].mBinding.mClip.Set(animation, mSkeleton, true);
		}
		bool idle = mEntries[index].IsIdle();
		if (idle != wasIdle)
		{
			if (idle)
			{
				mActiveCount--;
			}
			if (wasIdle)
			{
				mActiveCount++;
			}
		}
		bool movesRoot = false;
		for (int i = 0; i < MAX_ENTRIES; i++)
		{
			if (mEntries[i].mBinding.mClip.IsSet())
			{
				movesRoot = movesRoot || mEntries[i].mBinding.mClip.Unknown10952380();
			}
		}
		Unknown1094A4A0(movesRoot);
	}

	// FUNCTION: ENGINE 0x1094D390
	void AnimationBlendDriver::Step(float dt)
	{
		mPhaseStep = GetPhaseStep(dt);
		Advance();
		UpdateFinished();
	}

	// FUNCTION: ENGINE 0x1094D3E0
	PartitionDriver::PartitionDriver(const PartitionDriver& other) : Driver(other)
	{
		mFirstJoint = other.mFirstJoint;
		mLastJoint = other.mLastJoint;
		mSkeleton = other.mSkeleton;
		mPartition = other.mPartition;
		mJointMask = other.mJointMask;
		mSkeleton->AddRef();
	}

	// FUNCTION: ENGINE 0x1094D430
	PartitionDriver::~PartitionDriver()
	{
		mSkeleton->Release();
	}

	// FUNCTION: ENGINE 0x1094D450
	void PartitionDriver::SetFirstJoint(unsigned int joint)
	{
		mFirstJoint = joint;
		Unknown1094A440(CoversRoot());
	}

	// FUNCTION: ENGINE 0x1094D470
	void PartitionDriver::SetLastJoint(unsigned int joint)
	{
		mLastJoint = joint;
		Unknown1094A440(CoversRoot());
	}

	// FUNCTION: ENGINE 0x1094D490
	void PartitionDriver::ResetRange()
	{
		mPartition = 0;
		mJointMask = 0;
		mFirstJoint = 0;
		mLastJoint = mSkeleton->mData.mJointCount - 1;
	}

	// FUNCTION: ENGINE 0x1094D4B0
	bool PartitionDriver::CoversRoot() const
	{
		return mFirstJoint == 0;
	}

	// FUNCTION: ENGINE 0x1094D4C0
	bool PartitionDriver::Unknown1094D4C0(const AnimationBinding& binding) const
	{
		if (binding.mSource != 0 && mSkeleton != 0)
		{
			if (!binding.mClip.Unknown10952390(mJointMask))
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1094D520
	PartitionDriver::PartitionDriver(pure3d::Skeleton* skeleton, int type) : Driver(type)
	{
		mSkeleton = skeleton;
		mSkeleton->AddRef();
		ResetRange();
	}

	// FUNCTION: ENGINE 0x1094D570
	void PartitionDriver::SetPartition(pure3d::SkeletonPartition* partition)
	{
		if (partition == 0)
		{
			ResetRange();
			return;
		}
		mPartition = partition;
		const pure3d::JointMask* mask = partition->mMask;
		mJointMask = mask;
		unsigned int count = mask->mJointCount;
		for (unsigned int joint = 0; joint < count; joint++)
		{
			if (mask->words[joint >> 5] & (1 << (joint & 0x1F)))
			{
				mFirstJoint = joint;
				break;
			}
		}
		unsigned int last = count - 1;
		while (last >= mFirstJoint)
		{
			if (mask->words[last >> 5] & (1 << (last & 0x1F)))
			{
				mLastJoint = last;
				break;
			}
			last--;
		}
		CoversRoot();
	}

	// FUNCTION: ENGINE 0x1094D610
	void PartitionDriver::SetPartitionIndex(int index)
	{
		SetPartition(&mSkeleton->mPartitions[index]);
	}

	// FUNCTION: ENGINE 0x1094D630
	void PartitionDriver::SetPartitionByName(const core::Name<core::CaseSensitiveKey>& name)
	{
		core::Name<core::CaseSensitiveKey> empty(0, 1);
		if (name == empty)
		{
			SetPartition(0);
			return;
		}
		SetPartition(mSkeleton->FindPartition(name));
	}

	// FUNCTION: ENGINE 0x1094D690
	void PartitionDriver::Bind(const DriverInfo& info)
	{
		core::Name<core::CaseSensitiveKey> name = mPartition != 0 ? mPartition->mName : core::Name<core::CaseSensitiveKey>(0, 1);
		core::RefAssign(mSkeleton, info.mSkeleton);
		SetPartitionByName(name);
	}
}
