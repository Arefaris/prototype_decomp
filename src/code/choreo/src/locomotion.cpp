// choreo::LocomotionDriver (the base of the two locomotion drivers; the start of the unit 0x109515F0, file name guessed
// from the class). Names are guesses.
#include "code/choreo/drivers.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x109515F0
	LocomotionDriver::LocomotionDriver(pure3d::Skeleton* skeleton, int type) : PartitionDriver(skeleton, type)
	{
		mUnknown38 = 0.0f;
		mUnknown3C = 0.0f;
		mUnknown40 = 0.0f;
		gLocomotionDriverCount++;
		if (gLocomotionDriverCount > gLocomotionDriverPeak)
		{
			gLocomotionDriverPeak = gLocomotionDriverCount;
		}
		Unknown1094A440(true);
		Unknown1094A430(true);
		Unknown1094A460(true);
		Unknown1094A480(true);
	}

	// FUNCTION: ENGINE 0x10951660
	LocomotionDriver::~LocomotionDriver()
	{
		gLocomotionDriverCount--;
	}

	// FUNCTION: ENGINE 0x10951680
	LocomotionDriver* GetLocomotionDriver(Driver* driver)
	{
		if (driver->mType != 5 && driver->mType != 6)
		{
			driver = 0;
		}
		return static_cast<LocomotionDriver*>(driver);
	}

	// FUNCTION: ENGINE 0x109516A0
	LocomotionDriver* Unknown109516A0(Driver* driver)
	{
		if (driver->mType != 5 && driver->mType != 6)
		{
			driver = 0;
		}
		return static_cast<LocomotionDriver*>(driver);
	}
}
