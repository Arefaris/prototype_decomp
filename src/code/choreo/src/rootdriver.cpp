// choreo::RootDriver and choreo::AnimationDriver (rootdriver.cpp, the unit after deltatransform.cpp). Names are
// guesses; the driver type 9 is the root driver's (from its constructor) and its delta transform sits at +0x24.
#include "code/choreo/rootdriver.h"
#include "code/choreo/poseblendjob.h"
#include <math.h>

namespace choreo
{
	// The smallest frame rate and rate the driver still plays at (the constant at 0x10E8C1FC)
	static const float ANIMATIONDRIVER_EPSILON = 1e-5f;

	// 0x10D94F78 (symbols.txt): zero in the data
	extern const float gZero;

	// FUNCTION: ENGINE 0x1094EF30
	RootDriver::RootDriver() : Driver(9), mMask(3)
	{
		gRootDriverCount++;
		if (gRootDriverCount > gRootDriverPeak)
		{
			gRootDriverPeak = gRootDriverCount;
		}
		Unknown1094A440(true);
	}

	// FUNCTION: ENGINE 0x1094EF80
	RootDriver::~RootDriver()
	{
		gRootDriverCount--;
	}

	// FUNCTION: ENGINE 0x1094EFA0
	RootDriver* GetRootDriver(Driver* driver)
	{
		return driver->mType == 9 ? static_cast<RootDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x1094EFC0
	RootDriver* Unknown1094EFC0(Driver* driver)
	{
		return driver->mType == 9 ? static_cast<RootDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x1094EFE0
	unsigned int RootDriver::GetFirstJoint() const
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1094EFF0
	unsigned int RootDriver::GetLastJoint() const
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1094F000
	void RootDriver::SetMask(unsigned int mask)
	{
		mMask = mask;
		Unknown1094A440(mask != 0);
	}

	// FUNCTION: ENGINE 0x1094F020
	void RootDriver::Update(float dt)
	{
		mDelta.Update(dt);
	}

	// FUNCTION: ENGINE 0x1094F040
	void RootDriver::FillPose(PoseBlendNode* node, PoseBlendSample* sample)
	{
		node->SetNone(true, true);
		if (mMask & 1)
		{
			node->SetTranslation(mDelta.GetPosition());
		}
		if (mMask & 2)
		{
			node->SetRotation(mDelta.GetQuaternion());
		}
		mDelta.Transform::Reset();
	}

	// FUNCTION: ENGINE 0x1094F0A0
	// NONMATCHING: the engine keeps the copy of the matrix translation below the position the delta transform returns
	// (ours the other way round, which the rest of the function follows); 36 %
#ifdef NONMATCHING
	void RootDriver::BlendIntoMatrix(math::Matrix& matrix, const void* a, const void* b, float weight)
	{
		if (mMask & 1)
		{
			math::Vector current(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
			math::Vector position = mDelta.GetPosition();
			position.x = (position.x - current.x) * weight + current.x;
			position.y = (position.y - current.y) * weight + current.y;
			position.z = (position.z - current.z) * weight + current.z;
			matrix.SetTranslation(position);
		}
		if (mMask & 2)
		{
			math::Quaternion rotation;
			rotation.FromMatrix(matrix);
			const math::Quaternion& delta = mDelta.GetQuaternion();
			rotation.Slerp(rotation, delta, weight);
			matrix.FromQuaternion(rotation);
		}
		mDelta.Transform::Reset();
	}
#endif

	// FUNCTION: ENGINE 0x1094F1C0
	bool AnimationDriver::GetUnknown54() const
	{
		return mUnknown54;
	}

	// FUNCTION: ENGINE 0x1094F1D0
	bool AnimationDriver::GetUnknown55() const
	{
		return mUnknown55;
	}

	// FUNCTION: ENGINE 0x1094F1E0
	bool AnimationDriver::GetUnknown66() const
	{
		return mUnknown66;
	}

	// FUNCTION: ENGINE 0x1094F1F0
	bool AnimationDriver::GetUnknown67() const
	{
		return mUnknown67;
	}

	// FUNCTION: ENGINE 0x1094F200
	AnimationDriver::~AnimationDriver()
	{
		gAnimationDriverCount--;
	}

	// FUNCTION: ENGINE 0x1094F230
	Driver* Unknown1094F230(Driver* driver)
	{
		return driver->mType ? 0 : driver;
	}

	// FUNCTION: ENGINE 0x1094F240
	void AnimationDriver::SetAnimation(pure3d::Animation* animation)
	{
		mBinding.mSource = animation;
		mBinding.mSource->AddRef();
		mBinding.mSource->Unknown106E9310(1);
		mBinding.mClip.Set(mBinding.mSource, mSkeleton, true);
		Unknown1094A4A0(mBinding.mClip.Unknown10952380());
	}

	// FUNCTION: ENGINE 0x1094F290
	void AnimationDriver::Bind(const DriverInfo& info)
	{
		PartitionDriver::Bind(info);
		if (mBinding.mSource != 0)
		{
			mBinding.mClip.Set(mBinding.mSource, mSkeleton, false);
			Unknown1094A4A0(mBinding.mClip.Unknown10952380());
		}
	}

	// FUNCTION: ENGINE 0x1094F2D0
	void AnimationDriver::Unbind()
	{
		if (mBinding.mSource != 0)
		{
			mBinding.mSource->Unknown106E7B50();
		}
	}

	// FUNCTION: ENGINE 0x1094F2E0
	bool AnimationDriver::IsSet() const
	{
		return mBinding.mClip.IsSet() != 0;
	}

	// FUNCTION: ENGINE 0x1094F2F0
	bool AnimationDriver::UpdateRest()
	{
		return Unknown1094D4C0(mBinding);
	}

	// FUNCTION: ENGINE 0x1094F300
	// NONMATCHING: the engine lays the two stores out the other way round (a branch on frame <= limit to the store of
	// the frame, the store of the limit or the lower bound after it); the comparisons are the same, 94 %
#ifdef NONMATCHING
	void AnimationDriver::SetStartFrame(float frame)
	{
		float limit = mBinding.mClip.GetDuration() - 1.0f;
		float value = 0.0f;
		if (!(0.0f > frame))
		{
			value = limit;
			if (!(frame > limit))
			{
				value = frame;
			}
		}
		mStartFrame = value;
	}
#endif

	// FUNCTION: ENGINE 0x1094F350
	// NONMATCHING: as SetStartFrame; 90 %
#ifdef NONMATCHING
	void AnimationDriver::SetEndFrame(float frame)
	{
		float limit = mBinding.mClip.GetDuration() - 1.0f;
		float value = 0.0f;
		if (value <= frame)
		{
			value = limit;
			if (frame <= limit)
			{
				value = frame;
			}
		}
		mEndFrame = value;
	}
#endif

	// FUNCTION: ENGINE 0x1094F3A0
	float AnimationDriver::GetRangeTime() const
	{
		if (fabsf(mUnknown58) <= ANIMATIONDRIVER_EPSILON)
		{
			return -1.0f;
		}
		if (fabsf(mBinding.mClip.GetFrameRate()) <= ANIMATIONDRIVER_EPSILON)
		{
			return -1.0f;
		}
		float to = mEndFrame;
		float from = mStartFrame;
		float rate = mBinding.mClip.GetFrameRate();
		return fabsf((to - from) / (rate * mUnknown58));
	}

	// FUNCTION: ENGINE 0x1094F420
	float AnimationDriver::Unknown1094F420() const
	{
		if (mUnknown54)
		{
			return -1.0f;
		}
		if (mUnknown55)
		{
			return -1.0f;
		}
		return GetRangeTime();
	}

	// FUNCTION: ENGINE 0x1094F440
	float AnimationDriver::GetTimeLeft() const
	{
		float rate = mUnknown58;
		if (fabsf(rate) <= ANIMATIONDRIVER_EPSILON)
		{
			return 0.0f;
		}
		if (fabsf(mBinding.mClip.GetFrameRate()) <= ANIMATIONDRIVER_EPSILON)
		{
			return 0.0f;
		}
		if (rate >= 0.0f)
		{
			float to = mEndFrame;
			float from = mUnknownE4;
			float clipRate = mBinding.mClip.GetFrameRate();
			return (to - from) / (clipRate * mUnknown58);
		}
		float to = mStartFrame;
		float from = mUnknownE4;
		float clipRate = mBinding.mClip.GetFrameRate();
		return (to - from) / (clipRate * mUnknown58);
	}

	// FUNCTION: ENGINE 0x1094F4F0
	void AnimationDriver::SetUnknown64(bool value)
	{
		mUnknown64 = value;
		Unknown1094A440(CoversRoot());
	}

	// FUNCTION: ENGINE 0x1094F510
	void AnimationDriver::SetUnknown65(bool value)
	{
		mUnknown65 = value;
		Unknown1094A440(CoversRoot());
	}

	// FUNCTION: ENGINE 0x1094F530
	bool AnimationDriver::CoversRoot() const
	{
		return (mUnknown64 || mUnknown65) && PartitionDriver::CoversRoot();
	}

	// FUNCTION: ENGINE 0x1094F550
	// NONMATCHING: the engine keeps the two comparisons of the frame's ends the way they are written (the minimum
	// first) where ours are canonicalised into the other order; 74 %
#ifdef NONMATCHING
	float ClampFrame(float frame, float minimum, float maximum, bool wrap)
	{
		if (wrap)
		{
			return WrapFrame(minimum, maximum, frame);
		}
		if (maximum > minimum)
		{
			if (minimum <= frame)
			{
				if (frame <= maximum)
				{
					return frame;
				}
				return maximum;
			}
			return minimum;
		}
		if (frame > minimum)
		{
			return minimum;
		}
		if (maximum <= frame)
		{
			return frame;
		}
		return maximum;
	}
#endif

	// FUNCTION: ENGINE 0x1094F5C0
	float AnimationDriver::ClampFrame(float frame) const
	{
		return choreo::ClampFrame(frame, mStartFrame, mEndFrame, mUnknown54);
	}

	// FUNCTION: ENGINE 0x1094F5F0
	float AnimationDriver::GetFrameAdvance(float dt) const
	{
		return mBinding.mClip.GetFrameRate() * mUnknown58 * dt;
	}

	// FUNCTION: ENGINE 0x1094F610
	void AnimationDriver::SetUnknownE4(float frame)
	{
		mUnknownE4 = ClampFrame(frame);
	}

	// FUNCTION: ENGINE 0x1094F630
	void AnimationDriver::Unknown1094F630(float a, float b, float frame, int mode)
	{
		mBinding.mClip.Unknown10955260(a, b, frame >= 0.0f, mode);
	}

	// FUNCTION: ENGINE 0x1094F670
	void AnimationDriver::Unknown1094F670(float a, float b, float frame, int mode)
	{
		mBinding.mClip.Unknown109552C0(a, b, frame >= 0.0f, mode);
	}

	// FUNCTION: ENGINE 0x1094F6B0
	// NONMATCHING: the engine loads both frames before the call and pushes their slots one at a time, ours the second
	// frame first into an argument area of its own; 35 %
#ifdef NONMATCHING
	void AnimationDriver::Unknown1094F6B0(float a, float b, void* c)
	{
		mBinding.mClip.Unknown10955360(a, b, c);
	}
#endif

	// FUNCTION: ENGINE 0x1094F6D0
	void AnimationDriver::Unknown1094F6D0(PoseBlendNode* node, PoseBlendSample* sample)
	{
		PoseBlendNode* blendNode = node;
		PoseBlendSample* blendSample = sample;
		unsigned int first = mFirstJoint;
		bool rotation = false;
		bool translation = false;
		bool full = false;
		if (first == 0)
		{
			if (mUnknown65)
			{
				if (mUnknown67)
				{
					blendNode->SetRotation(mDelta.GetQuaternion());
				}
				else
				{
					rotation = true;
				}
			}
			if (mUnknown64)
			{
				if (mUnknown66)
				{
					blendNode->SetTranslation(mDelta.GetPosition());
				}
				else
				{
					translation = true;
				}
			}
			full = true;
			first = 1;
		}
		mDelta.Transform::Reset();
		if (mBinding.mClip.IsSet())
		{
			blendNode->SetJoints(first, mLastJoint, (void*)mJointMask);
			blendNode->Set(blendSample, blendSample + 1, rotation, translation, full);
			mBinding.mClip.Unknown10952480(blendSample);
			blendSample->Set(1.0f, 1.0f, mUnknownE4, mUnknownEC, mUnknownE8 >= 0.0f);
			mBinding.mSource->Touch();
		}
		else
		{
			blendNode->SetNone(rotation, translation);
		}
	}

	// FUNCTION: ENGINE 0x1094F810
	// NONMATCHING: the engine keeps the flag in memory and tests the comparison flags of both ranges in one tail (61.6 %)
#ifdef NONMATCHING
	void AnimationDriver::UpdateFinished()
	{
		bool finished = false;
		if (!mUnknown54 && !mUnknown55)
		{
			bool playing;
			if (!(mUnknown58 >= gZero))
			{
				playing = mStartFrame < mUnknownE4;
			}
			else
			{
				playing = mUnknownE4 < mEndFrame;
			}
			finished = true;
			if (playing)
			{
				finished = false;
			}
		}
		Unknown1094A4C0(finished);
	}
#endif

	// FUNCTION: ENGINE 0x1094F860
	AnimationDriver::AnimationDriver(pure3d::Skeleton* skeleton, pure3d::Animation* animation)
		: PartitionDriver(skeleton, 0), mUnknown54(false), mUnknown55(false), mUnknown58(1.0f), mStartFrame(0.0f),
		mUnknown64(true), mUnknown65(true), mUnknown66(false), mUnknown67(false)
	{
		mUnknownE4 = 0.0f;
		mUnknownE8 = 0.0f;
		mUnknownEC = -1.0f;
		mUnknownF0 = false;
		mUnknownF4 = -1.0f;
		SetAnimation(animation);
		Unknown1094A430(true);
		Unknown1094A440(true);
		Unknown1094A460(true);
		Unknown1094A480(true);
		mEndFrame = mBinding.mClip.GetDuration() - 1.0f;
		gAnimationDriverCount++;
		if (gAnimationDriverCount > gAnimationDriverPeak)
		{
			gAnimationDriverPeak = gAnimationDriverCount;
		}
	}

	// FUNCTION: ENGINE 0x1094F970
	void AnimationDriver::SetRange(float duration, float rate, float start, float end)
	{
		SetStartFrame(start);
		if (end < 0.0f)
		{
			SetEndFrame(mBinding.mClip.GetDuration() + end);
		}
		else
		{
			SetEndFrame(end);
		}
		if (duration > ANIMATIONDRIVER_EPSILON && !mUnknown54)
		{
			mUnknown58 = 1.0f;
			float direction;
			if (rate < 0.0f)
			{
				direction = -1.0f;
			}
			else if (rate > 0.0f)
			{
				direction = 1.0f;
			}
			else
			{
				direction = 0.0f;
			}
			mUnknown58 = direction / duration * GetRangeTime();
		}
		else
		{
			mUnknown58 = rate;
		}
	}

	// FUNCTION: ENGINE 0x1094FA70
	void AnimationDriver::Update(float dt)
	{
		if (mUnknownF0)
		{
			if (!(mUnknownF4 >= 0.0f))
			{
				return;
			}
			mUnknownF4 = mUnknownF4 - dt;
			if (!(mUnknownF4 <= 0.0f))
			{
				return;
			}
			mUnknownF0 = false;
			mUnknownF4 = -1.0f;
		}
		mUnknownE8 = GetFrameAdvance(dt);
		mDelta.Update(dt);
		mUnknownEC = mUnknownE4;
		mUnknownE4 = ClampFrame(mUnknownE8 + mUnknownE4);
		UpdateFinished();
	}
}
