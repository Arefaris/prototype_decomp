// choreo::Puppet (unit around 0x10946C00 - 0x10949300; file name guessed from the class). Names are guesses.
#include "code/choreo/puppet.h"
#include <string.h>

namespace choreo
{
	// FUNCTION: ENGINE 0x10949080
	// EQUIVALENT: the same operations in the same order; the engine loads the step into the x87 stack at the top of
	// the loop body (ours loads it where it is passed on) and keeps the address of the entry after the current one in
	// a stack slot of its own
	void Puppet::Update(float dt)
	{
		mRootDelta.Identity();
		dt = mTimeScale * dt;
		if (mPose->mArrays.mJointCount > 0)
		{
			math::Quaternion identity;
			identity.x = 0.0f;
			identity.y = 0.0f;
			identity.z = 0.0f;
			identity.w = 1.0f;
			*mPose->mArrays.mRotations = identity;
			mPose->mArrays.mTranslations->Set(0.0f, 0.0f, 0.0f);
			mPose->mArrays.mUnknown10->Set(0.0f, 0.0f, 0.0f);
			mPose->mArrays.mScales->Set(1.0f, 1.0f, 1.0f);
			mPose->mArrays.mUnknown14->Set(0.0f, 0.0f, 0.0f);
			mPose->mArrays.mUnknown1C->Set(0.0f, 0.0f, 0.0f);
		}
		unsigned int index = 0;
		for (DriverEntry* entry = mEntries; index < mDriverCount; )
		{
			Driver* driver = entry->mDriver;
			if ((entry->mLifetime < 0.0f && !entry->mEndless) || (driver->mFlags & 0x20))
			{
				// Ending: fade out, and drop the driver once it is gone
				if (0.0f >= entry->mBlendOut)
				{
					entry->mFade = 0.0f;
				}
				else
				{
					entry->mFade = entry->mFade - dt / entry->mBlendOut;
				}
				if (0.0f >= entry->mFade)
				{
					mDriverCount--;
					memmove(entry, &mEntries[index + 1], (mDriverCount - index) * sizeof(DriverEntry));
					mEntries[mDriverCount].mDriver = driver;
					mRemovedCount++;
					continue;
				}
			}
			else
			{
				if (!entry->mEndless)
				{
					entry->mLifetime = entry->mLifetime - dt;
				}
				if (0.0f >= entry->mBlendIn)
				{
					entry->mFade = 1.0f;
				}
				else
				{
					entry->mFade = dt / entry->mBlendIn + entry->mFade;
					if (entry->mFade > 1.0f)
					{
						entry->mFade = 1.0f;
					}
				}
			}
			UpdateDriver(driver, dt);
			index++;
			entry++;
		}
		if (mDriverCount > 0)
		{
			SortDrivers();
		}
	}
}
