// pure3d::FrameController, AnimationFrameController, SimpleFrameController and BlendFrameController (unit around
// 0x10776F80 - 0x10778400; file name guessed from the classes). Names are guesses.
#include <float.h>

#include "code/core/refptr.h"
#include "code/pure3d/framecontroller.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gTwo;
		extern const float gThirty;
	}

	namespace camera
	{
		extern const float gThree;
		extern const float gThousandth;
	}
}

namespace pure3d
{
	// The frame held inside the range
	static __forceinline float ClampFrame(float frame, float start, float end)
	{
		float clamped = start;
		if (frame - start >= 0.0f)
		{
			clamped = frame;
		}
		if (clamped - end >= 0.0f)
		{
			clamped = end;
		}
		return clamped;
	}

	// FUNCTION: ENGINE 0x10776F80
	FrameController::FrameController()
	{
		mUpdateOnAdvance = false;
	}

	// FUNCTION: ENGINE 0x10776FA0
	FrameController::FrameController(const FrameController& other)
	{
		mUpdateOnAdvance = other.mUpdateOnAdvance;
	}

	// FUNCTION: ENGINE 0x10776FC0
	FrameController::~FrameController()
	{
	}

	// FUNCTION: ENGINE 0x10776FD0
	void FrameController::SetUpdateOnAdvance(bool value)
	{
		mUpdateOnAdvance = value;
	}

	// FUNCTION: ENGINE 0x10776FE0
	bool FrameController::GetUpdateOnAdvance()
	{
		return mUpdateOnAdvance;
	}

	// FUNCTION: ENGINE 0x10776FF0
	// EQUIVALENT: the engine loads the speed constant before it stores the vftable, ours after (80.6 %)
	AnimationFrameController::AnimationFrameController()
	{
		float speed = engine::driving::gOne;
		mRelativeSpeed = speed;
	}

	// FUNCTION: ENGINE 0x10777010
	AnimationFrameController::AnimationFrameController(const AnimationFrameController& other) : FrameController(other)
	{
		mRelativeSpeed = other.mRelativeSpeed;
	}

	// FUNCTION: ENGINE 0x10777040
	AnimationFrameController::~AnimationFrameController()
	{
	}

	// FUNCTION: ENGINE 0x10777050
	void AnimationFrameController::SetRelativeSpeed(float speed)
	{
		mRelativeSpeed = speed;
	}

	// FUNCTION: ENGINE 0x10777060
	float AnimationFrameController::GetRelativeSpeed()
	{
		return mRelativeSpeed;
	}

	// FUNCTION: ENGINE 0x10777070
	// EQUIVALENT: the same cases in the same order with the same float operations; the engine places the return of the largest float inside the first case, ours after the switch (42.1 %)
	float AnimationFrameController::GetRemaining()
	{
		float start;
		float end;
		GetFrameRange(&start, &end);
		float length = end - start;
		unsigned int cycles = GetNumCycles();
		float frame = GetFrame();
		switch (GetCycleMode())
		{
		case 4:
			if (cycles == 0)
			{
				break;
			}
			return (float)cycles * length + (float)cycles * length - (frame - start);
		case 5:
			if (cycles == 0)
			{
				break;
			}
			return (float)cycles * length + (float)cycles * length - (end - frame);
		case 2:
			if (cycles == 0)
			{
				break;
			}
			return (float)cycles * length - (frame - start);
		case 3:
			if (cycles == 0)
			{
				break;
			}
			return (float)cycles * length - (end - frame);
		case 0:
		{
			Animation* animation = GetAnimation();
			if (animation == 0)
			{
				return 0.0f;
			}
			if (animation->mFlag0 != 1)
			{
				return length;
			}
			break;
		}
		default:
			return 0.0f;
		}
		return FLT_MAX;
	}

	// FUNCTION: ENGINE 0x107771D0
	void AnimationFrameController::Reset()
	{
		mRelativeSpeed = engine::driving::gOne;
	}

	// FUNCTION: ENGINE 0x107771E0
	SimpleFrameController::SimpleFrameController()
	{
		mRemaining = FLT_MAX;
		mCycleMode = 0;
		mNumCycles = 0;
		mAnimation = 0;
		mStartFrame = 0;
		mEndFrame = 0;
		mFrame = 0;
		mForward = true;
	}

	// FUNCTION: ENGINE 0x10777D20
	SimpleFrameController::SimpleFrameController(const SimpleFrameController& other) : AnimationFrameController(other)
	{
		mCycleMode = other.mCycleMode;
		mNumCycles = other.mNumCycles;
		mRemaining = other.mRemaining;
		mStartFrame = other.mStartFrame;
		mEndFrame = other.mEndFrame;
		mFrame = other.mFrame;
		mForward = other.mForward;
		mAnimation = 0;
		core::RefAssign(mAnimation, other.mAnimation);
	}

	// FUNCTION: ENGINE 0x10777D80
	SimpleFrameController::~SimpleFrameController()
	{
		core::SafeRelease(mAnimation);
	}

	// FUNCTION: ENGINE 0x10777230
	void SimpleFrameController::Advance(float dt, bool update)
	{
		if (mAnimation != 0)
		{
			mFrame = mAnimation->AdvanceFrame(&mRemaining, &mForward, mFrame, mRelativeSpeed * dt, mStartFrame,
				mEndFrame, mNumCycles == 0, mCycleMode);
			if (mUpdateOnAdvance == true || update == true)
			{
				Unknown5();
			}
		}
	}

	// FUNCTION: ENGINE 0x107772A0
	float SimpleFrameController::Unknown8()
	{
		if (mAnimation != 0)
		{
			return mAnimation->mFrameRate;
		}
		return engine::driving::gThirty;
	}

	// FUNCTION: ENGINE 0x107772C0
	float SimpleFrameController::Unknown9()
	{
		if (mAnimation != 0)
		{
			return mAnimation->numFrames;
		}
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x107772D0
	void SimpleFrameController::SetFrame(float frame)
	{
		mFrame = ClampFrame(frame, mStartFrame, mEndFrame);
		mRemaining = GetRemaining();
		mForward = mCycleMode != 3 && mCycleMode != 5;
	}

	// FUNCTION: ENGINE 0x10777340
	float SimpleFrameController::GetFrame()
	{
		return mFrame;
	}

	// FUNCTION: ENGINE 0x10777350
	void SimpleFrameController::SetFrameRange(float start, float end)
	{
		if (start != mStartFrame || end != mEndFrame)
		{
			mStartFrame = start;
			mEndFrame = end;
			float clamped = start;
			if (mFrame - start >= 0.0f)
			{
				clamped = mFrame;
			}
			if (clamped - end >= 0.0f)
			{
				clamped = end;
			}
			mFrame = clamped;
			mRemaining = GetRemaining();
			mForward = mCycleMode != 3 && mCycleMode != 5;
		}
	}

	// FUNCTION: ENGINE 0x107773E0
	void SimpleFrameController::GetFrameRange(float* start, float* end)
	{
		*start = mStartFrame;
		*end = mEndFrame;
	}

	// FUNCTION: ENGINE 0x10777400
	void SimpleFrameController::SetCycleMode(Animation::CycleMode mode)
	{
		if (mode != mCycleMode)
		{
			mCycleMode = mode;
			mRemaining = GetRemaining();
			if (mCycleMode == 0 && mRemaining == FLT_MAX)
			{
				mNumCycles = 0;
			}
			mForward = mCycleMode != 3 && mCycleMode != 5;
		}
	}

	// FUNCTION: ENGINE 0x10777460
	int SimpleFrameController::GetCycleMode()
	{
		return mCycleMode;
	}

	// FUNCTION: ENGINE 0x10777470
	void SimpleFrameController::SetNumCycles(unsigned int count)
	{
		if (mNumCycles != count)
		{
			mNumCycles = count;
			mRemaining = GetRemaining();
			if (mCycleMode == 0 && mRemaining == FLT_MAX)
			{
				mNumCycles = 0;
			}
			mForward = mCycleMode != 3 && mCycleMode != 5;
		}
	}

	// FUNCTION: ENGINE 0x107774D0
	unsigned int SimpleFrameController::GetNumCycles()
	{
		if (mCycleMode == 0 && mAnimation != 0)
		{
			return mAnimation->mFlag0 == 0;
		}
		return mNumCycles;
	}

	// FUNCTION: ENGINE 0x107774F0
	float SimpleFrameController::Unknown19()
	{
		return mRemaining;
	}

	// FUNCTION: ENGINE 0x10777500
	bool SimpleFrameController::Unknown20()
	{
		return mRemaining <= 0.000001f;
	}

	// FUNCTION: ENGINE 0x10777E10
	void SimpleFrameController::Reset()
	{
		mCycleMode = 0;
		mNumCycles = 0;
		mStartFrame = 0;
		float last;
		if (mAnimation == 0 || (last = mAnimation->numFrames - engine::driving::gOne) < 0.0f)
		{
			last = 0.0f;
		}
		mEndFrame = last;
		mFrame = 0;
		mRemaining = FLT_MAX;
		mForward = true;
		AnimationFrameController::Reset();
	}

	// FUNCTION: ENGINE 0x10777DA0
	void SimpleFrameController::SetAnimation(Animation* animation, float a, float b)
	{
		core::RefAssign(mAnimation, animation);
		float length = mAnimation->numFrames - engine::driving::gOne;
		float last = length < 0.0f ? 0.0f : length;
		SetFrameRange(0.0f, last);
		SetFrame(a);
	}

	// FUNCTION: ENGINE 0x10777220
	Animation* SimpleFrameController::GetAnimation()
	{
		return mAnimation;
	}

	// FUNCTION: ENGINE 0x10777520
	BlendEntry::BlendEntry()
	{
		frame = 0;
		startFrame = 0;
		endFrame = 0;
		fadeLeft = 0;
		fadeRate = 0;
		weight = 0;
		remaining = FLT_MAX;
		numCycles = 0;
		cycleMode = 0;
		forward = true;
		animation = 0;
	}

	// FUNCTION: ENGINE 0x10777E60
	BlendEntry::~BlendEntry()
	{
		if (animation != 0)
		{
			animation->Unknown106E7B50();
		}
		core::SafeRelease(animation);
	}

	// FUNCTION: ENGINE 0x10777570
	Animation* BlendEntry::GetAnimation()
	{
		return animation;
	}

	// FUNCTION: ENGINE 0x10777E80
	void BlendEntry::SetAnimation(Animation* newAnimation)
	{
		if (animation != 0)
		{
			animation->Unknown106E7B50();
		}
		core::RefAssign(animation, newAnimation);
		if (animation != 0)
		{
			animation->Unknown106E9310(0);
		}
	}

	// FUNCTION: ENGINE 0x10777EC0
	// EQUIVALENT: the same stores; the engine keeps the constant and the zero in other registers and orders the loads differently (75.6 %)
	void BlendEntry::Reset()
	{
		float one = engine::driving::gOne;
		frame = 0;
		startFrame = 0;
		float last;
		if (animation == 0 || (last = animation->numFrames - one) < 0.0f)
		{
			last = 0.0f;
		}
		fadeLeft = 0;
		fadeRate = 0;
		endFrame = last;
		weight = one;
		remaining = FLT_MAX;
		numCycles = 0;
		cycleMode = 0;
		forward = true;
	}

	// FUNCTION: ENGINE 0x10777F20
	BlendFrameController::BlendFrameController() : mCycleMode(0), mNumCycles(0), mCount(0)
	{
		unknown108 = false;
		for (int i = 0; i < 5; i++)
		{
			mEntries[i].Reset();
		}
	}

	// FUNCTION: ENGINE 0x10777F80
	BlendFrameController::BlendFrameController(const BlendFrameController& other) : AnimationFrameController(other),
		mCycleMode(other.mCycleMode), mNumCycles(other.mNumCycles), mCount(0)
	{
		unknown108 = false;
		mCount = 0;
		while (mCount < other.mCount)
		{
			mEntries[mCount].SetAnimation(other.mEntries[mCount].animation);
			mEntries[mCount].frame = other.mEntries[mCount].frame;
			mEntries[mCount].startFrame = other.mEntries[mCount].startFrame;
			mEntries[mCount].endFrame = other.mEntries[mCount].endFrame;
			mEntries[mCount].fadeLeft = other.mEntries[mCount].fadeLeft;
			mEntries[mCount].fadeRate = other.mEntries[mCount].fadeRate;
			mEntries[mCount].weight = other.mEntries[mCount].weight;
			mEntries[mCount].remaining = other.mEntries[mCount].remaining;
			mEntries[mCount].numCycles = other.mEntries[mCount].numCycles;
			mEntries[mCount].cycleMode = other.mEntries[mCount].cycleMode;
			mCount++;
		}
	}

	// FUNCTION: ENGINE 0x10778090
	BlendFrameController::~BlendFrameController()
	{
		for (unsigned int i = 0; i < mCount; i++)
		{
			mEntries[i].SetAnimation(0);
		}
	}

	// FUNCTION: ENGINE 0x107775C0
	// EQUIVALENT: the same calls, stores and float operations; the engine multiplies the scaled time in place and copies the full weight through a register, ours loads and stores it directly (9.7 %)
	void BlendFrameController::Advance(float dt, bool update)
	{
		dt = mRelativeSpeed * dt;
		float scaled = dt * engine::camera::gThousandth;
		unknown108 = false;
		unsigned int alive = 1;
		unsigned int i = 0;
		if (mCount > 0)
		{
			do
			{
				BlendEntry* entry = &mEntries[i];
				Animation* animation = entry->GetAnimation();
				entry->frame = animation->AdvanceFrame(&entry->remaining, &entry->forward, entry->frame, dt,
					entry->startFrame, entry->endFrame, entry->numCycles == 0, entry->cycleMode);
				float fade = entry->fadeLeft - animation->mFrameRate * scaled;
				entry->fadeLeft = fade;
				if (fade > 0.0f)
				{
					float t = engine::driving::gOne - entry->fadeRate * fade;
					float blend = 0.0f;
					if (!(0.0f >= t))
					{
						if (t >= engine::driving::gOne)
						{
							alive++;
							blend = engine::driving::gOne;
							entry->weight = blend;
							goto next;
						}
						blend = (engine::camera::gThree - t * engine::driving::gTwo) * t * t;
					}
					alive++;
					entry->weight = blend;
				}
				else
				{
					entry->weight = engine::driving::gOne;
				}
			next:
				i++;
			}
			while (i < mCount);
		}
		while (alive < mCount)
		{
			RemoveFirst();
			unknown108 = true;
		}
		if (mCount > 0 && (mUpdateOnAdvance == true || update == true))
		{
			Unknown5();
		}
	}

	// FUNCTION: ENGINE 0x10777AC0
	void BlendFrameController::Unknown5()
	{
		if (mCount == 1)
		{
			Unknown26();
		}
		else
		{
			Unknown27();
		}
	}

	// FUNCTION: ENGINE 0x10777740
	float BlendFrameController::Unknown8()
	{
		float rate;
		if (mCount > 0)
		{
			rate = mEntries[mCount - 1].GetAnimation()->mFrameRate;
		}
		else
		{
			rate = engine::driving::gThirty;
		}
		return rate;
	}

	// FUNCTION: ENGINE 0x10777780
	float BlendFrameController::Unknown9()
	{
		float length;
		if (mCount > 0)
		{
			length = mEntries[mCount - 1].GetAnimation()->numFrames;
		}
		else
		{
			length = 0.0f;
		}
		return length;
	}

	// FUNCTION: ENGINE 0x107777B0
	void BlendFrameController::SetFrame(float frame)
	{
		if (mCount > 0)
		{
			int last = mCount - 1;
			mEntries[last].frame = ClampFrame(frame, mEntries[last].startFrame, mEntries[last].endFrame);
			mEntries[last].remaining = GetRemaining();
			mEntries[last].forward = mEntries[last].cycleMode != 3 && mEntries[last].cycleMode != 5;
		}
	}

	// FUNCTION: ENGINE 0x10777830
	float BlendFrameController::GetFrame()
	{
		float frame;
		if (mCount > 0)
		{
			frame = mEntries[mCount - 1].frame;
		}
		else
		{
			frame = 0.0f;
		}
		return frame;
	}

	// FUNCTION: ENGINE 0x10777860
	void BlendFrameController::SetFrameRange(float start, float end)
	{
		if (mCount > 0)
		{
			int last = mCount - 1;
			if (start != mEntries[last].startFrame || end != mEntries[last].endFrame)
			{
				mEntries[last].startFrame = start;
				mEntries[last].endFrame = end;
				mEntries[last].frame = ClampFrame(mEntries[last].frame, start, end);
				mEntries[last].remaining = GetRemaining();
				mEntries[last].forward = mEntries[last].cycleMode != 3 && mEntries[last].cycleMode != 5;
			}
		}
	}

	// FUNCTION: ENGINE 0x10777900
	void BlendFrameController::GetFrameRange(float* start, float* end)
	{
		if (mCount > 0)
		{
			int last = mCount - 1;
			*start = mEntries[last].startFrame;
			*end = mEntries[last].endFrame;
			return;
		}
		*start = 0;
		*end = 0;
	}

	// FUNCTION: ENGINE 0x10777940
	void BlendFrameController::SetCycleMode(Animation::CycleMode mode)
	{
		if (mCycleMode != mode)
		{
			mCycleMode = mode;
			if (mCount > 0)
			{
				int last = mCount - 1;
				mEntries[last].cycleMode = mode;
				mEntries[last].remaining = GetRemaining();
				if (mEntries[last].cycleMode == 0 && mEntries[last].remaining == FLT_MAX)
				{
					mNumCycles = 0;
				}
				mEntries[last].forward = mEntries[last].cycleMode != 3 && mEntries[last].cycleMode != 5;
			}
		}
	}

	// FUNCTION: ENGINE 0x107779C0
	int BlendFrameController::GetCycleMode()
	{
		return mCycleMode;
	}

	// FUNCTION: ENGINE 0x107779D0
	void BlendFrameController::SetNumCycles(unsigned int count)
	{
		if (mNumCycles != count)
		{
			mNumCycles = count;
			if (mCount > 0)
			{
				int last = mCount - 1;
				mEntries[last].numCycles = count;
				if (mEntries[last].cycleMode == 0 && mEntries[last].remaining == FLT_MAX)
				{
					mNumCycles = 0;
				}
				mEntries[last].remaining = GetRemaining();
				mEntries[last].forward = mEntries[last].cycleMode != 3 && mEntries[last].cycleMode != 5;
			}
		}
	}

	// FUNCTION: ENGINE 0x10777A40
	unsigned int BlendFrameController::GetNumCycles()
	{
		if (mCount > 0)
		{
			int last = mCount - 1;
			if (mEntries[last].cycleMode == 0)
			{
				if (mEntries[last].animation != 0)
				{
					return mEntries[last].animation->mFlag0 == 0;
				}
			}
			else
			{
				return mEntries[last].numCycles;
			}
		}
		return mNumCycles;
	}

	// FUNCTION: ENGINE 0x10777A70
	float BlendFrameController::Unknown19()
	{
		if (mCount > 0)
		{
			return mEntries[mCount - 1].remaining;
		}
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10777A90
	bool BlendFrameController::Unknown20()
	{
		if (mCount == 0)
		{
			return true;
		}
		if (mCount == 1)
		{
			return mEntries[0].remaining <= 0.000001f;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10778280
	void BlendFrameController::Reset()
	{
		while (mCount > 1)
		{
			RemoveFirst();
		}
		if (mCount == 1)
		{
			mEntries[0].Reset();
		}
		mCycleMode = 0;
		mNumCycles = 0;
		AnimationFrameController::Reset();
	}

	// FUNCTION: ENGINE 0x107780E0
	// EQUIVALENT: the same calls, stores and clamps; the constant is loaded one instruction earlier and the entry count is kept in a register across the final test (78.5 %)
	void BlendFrameController::SetAnimation(Animation* animation, float a, float b)
	{
		if (animation != 0)
		{
			float length = animation->numFrames - engine::driving::gOne;
			float last = length < 0.0f ? 0.0f : length;
			if (b <= 0.0f)
			{
				mEntries[0].SetAnimation(animation);
				float clamped = a;
				if (!(clamped >= 0.0f))
				{
					clamped = 0.0f;
				}
				if (clamped - last >= 0.0f)
				{
					clamped = last;
				}
				float one = engine::driving::gOne;
				mEntries[0].frame = clamped;
				mEntries[0].fadeLeft = 0.0f;
				mEntries[0].fadeRate = 0.0f;
				mEntries[0].weight = one;
				mEntries[0].numCycles = mNumCycles;
				mEntries[0].cycleMode = mCycleMode;
				for (unsigned int i = 1; i < mCount; i++)
				{
					mEntries[i].SetAnimation(0);
				}
				mCount = 1;
			}
			else
			{
				if (mCount == 5)
				{
					RemoveFirst();
				}
				mEntries[mCount].SetAnimation(animation);
				float clamped = a;
				if (!(clamped >= 0.0f))
				{
					clamped = 0.0f;
				}
				if (clamped - last >= 0.0f)
				{
					clamped = last;
				}
				float one = engine::driving::gOne;
				mEntries[mCount].frame = clamped;
				mEntries[mCount].fadeLeft = b;
				mEntries[mCount].fadeRate = one / b;
				mEntries[mCount].weight = 0.0f;
				mEntries[mCount].numCycles = mNumCycles;
				mEntries[mCount].cycleMode = mCycleMode;
				if (mCount == 0)
				{
					mEntries[0].weight = one;
				}
				mCount++;
			}
			SetFrameRange(0.0f, last);
		}
	}

	// FUNCTION: ENGINE 0x107775A0
	Animation* BlendFrameController::GetAnimation()
	{
		if (mCount > 0)
		{
			return mEntries[mCount - 1].GetAnimation();
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107782C0
	void BlendFrameController::Stop()
	{
		while (mCount > 1)
		{
			RemoveFirst();
		}
		if (mCount == 1)
		{
			mCount = 0;
			mEntries[0].SetAnimation(0);
			mEntries[0].Reset();
		}
		mCycleMode = 0;
		mNumCycles = 0;
		AnimationFrameController::Reset();
	}

	// FUNCTION: ENGINE 0x10778320
	// EQUIVALENT: the same copies; the engine interleaves the loads and stores in source order and advances the entry pointer in the middle (30.9 %)
	void BlendFrameController::RemoveFirst()
	{
		BlendEntry* entry = mEntries;
		for (unsigned int i = 1; i < mCount; i++)
		{
			core::RefAssign(entry->animation, entry[1].animation);
			entry->frame = entry[1].frame;
			entry->startFrame = entry[1].startFrame;
			entry->endFrame = entry[1].endFrame;
			entry->fadeLeft = entry[1].fadeLeft;
			entry->fadeRate = entry[1].fadeRate;
			entry->weight = entry[1].weight;
			entry->remaining = entry[1].remaining;
			entry->numCycles = entry[1].numCycles;
			entry->cycleMode = entry[1].cycleMode;
			entry->forward = entry[1].forward;
			entry++;
		}
		if (mCount != 0)
		{
			mCount--;
			mEntries[mCount].SetAnimation(0);
		}
	}
}
