// choreo::Driver (the base of the drivers; the unit after the IK driver's, 0x1094A3F0 - 0x1094A610). Names are guesses.
#include "code/choreo/puppet.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x1094A3F0
	void Driver::AddRef()
	{
		mRefCount++;
	}

	// FUNCTION: ENGINE 0x1094A400
	void Driver::Release()
	{
		mRefCount--;
		if (mRefCount <= 0)
		{
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x1094A420
	core::Name<core::CaseSensitiveKey>& Driver::GetName()
	{
		return mName;
	}

	// FUNCTION: ENGINE 0x1094A430
	void Driver::Unknown1094A430(bool enabled)
	{
		mFlag0 = enabled;
	}

	// FUNCTION: ENGINE 0x1094A440
	void Driver::Unknown1094A440(bool enabled)
	{
		mFlag1 = enabled;
	}

	// FUNCTION: ENGINE 0x1094A460
	void Driver::Unknown1094A460(bool enabled)
	{
		mFlag2 = enabled;
	}

	// FUNCTION: ENGINE 0x1094A480
	void Driver::Unknown1094A480(bool enabled)
	{
		mFlag3 = enabled;
	}

	// FUNCTION: ENGINE 0x1094A4A0
	void Driver::Unknown1094A4A0(bool enabled)
	{
		mFlag4 = enabled;
	}

	// FUNCTION: ENGINE 0x1094A4C0
	void Driver::Unknown1094A4C0(bool enabled)
	{
		mFlag5 = enabled;
	}

	// FUNCTION: ENGINE 0x1094A4E0
	Driver::Driver(int type)
	{
		mFlag0 = false;
		mFlag1 = false;
		mFlag2 = false;
		mFlag3 = false;
		mFlag4 = false;
		mFlag5 = false;
		mType = type;
		mRefCount = 0;
		gDriverCount++;
		if (gDriverCount > gDriverPeak)
		{
			gDriverPeak = gDriverCount;
		}
	}

	// FUNCTION: ENGINE 0x1094A530
	Driver::Driver(const Driver& other) : mName(other.mName)
	{
		mRefCount = 0;
		mType = other.mType;
		mFlag0 = other.mFlag0;
		mFlag1 = other.mFlag1;
		mFlag2 = other.mFlag2;
		mFlag3 = other.mFlag3;
		mFlag4 = other.mFlag4;
		mFlag5 = other.mFlag5;
	}

	// FUNCTION: ENGINE 0x1094A5B0
	Driver::~Driver()
	{
		gDriverCount--;
	}

	// FUNCTION: ENGINE 0x1094A5C0
	const char* Driver::GetNameText() const
	{
		return mName.GetText();
	}

	// FUNCTION: ENGINE 0x1094A5D0
	void Driver::SetName(const core::Name<core::CaseSensitiveKey>& name)
	{
		mName = name;
	}

	// FUNCTION: ENGINE 0x1094A5E0
	unsigned __int64 Driver::GetNameHash() const
	{
		return mName.GetHash();
	}
}
