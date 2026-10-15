// choreo::RootDriver and choreo::AnimationDriver (rootdriver.cpp, the unit after deltatransform.cpp). Names are
// guesses; the driver type 9 is the root driver's (from its constructor) and its delta transform sits at +0x24.
#include "code/choreo/rootdriver.h"

namespace choreo
{
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
	int RootDriver::Unknown1094EFE0()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x1094EFF0
	int RootDriver::Unknown1094EFF0()
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

	// FUNCTION: ENGINE 0x1094F230
	Driver* Unknown1094F230(Driver* driver)
	{
		return driver->mType ? 0 : driver;
	}

	// FUNCTION: ENGINE 0x1094F300
	// NONMATCHING: the engine encodes the two float comparisons with the operands the other way round (comiss of the
	// constant and then of the frame against the limit, against ours of the frame first); 90 %
#ifdef NONMATCHING
	void AnimationDriver::SetStartFrame(float frame)
	{
		float limit = mClip.GetDuration() - 1.0f;
		float value = 0.0f;
		if (value <= frame)
		{
			value = limit;
			if (frame <= limit)
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
		float limit = mClip.GetDuration() - 1.0f;
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

	// FUNCTION: ENGINE 0x1094F5C0
	float AnimationDriver::ClampFrame(float frame) const
	{
		return choreo::ClampFrame(frame, mStartFrame, mEndFrame, mUnknown54);
	}

	// FUNCTION: ENGINE 0x1094F5F0
	float AnimationDriver::GetFrameAdvance(float dt) const
	{
		return mClip.GetFrameRate() * mUnknown58 * dt;
	}

	// FUNCTION: ENGINE 0x1094F610
	void AnimationDriver::SetUnknownE4(float frame)
	{
		mUnknownE4 = ClampFrame(frame);
	}
}
