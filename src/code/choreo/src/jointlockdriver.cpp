// choreo::JointLockDriver (driver type 4; the unit before the drivers' tables, 0x10955CC0 - 0x10956000). Names are
// guesses.
#include "code/choreo/drivers.h"
#include "code/choreo/poseblendjob.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x10955CC0
	JointLockDriver::~JointLockDriver()
	{
		gJointLockDriverCount--;
	}

	// FUNCTION: ENGINE 0x10955CE0
	JointLockDriver* GetJointLockDriver(Driver* driver)
	{
		return driver->mType == 4 ? static_cast<JointLockDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10955D00
	JointLockDriver* Unknown10955D00(Driver* driver)
	{
		return driver->mType == 4 ? static_cast<JointLockDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10955D20
	void JointLockDriver::UpdateActive()
	{
		bool active;
		if (mJoint != 0xFFFF)
		{
			active = true;
			if (mMode == 0)
			{
				active = false;
			}
		}
		else
		{
			active = false;
		}
		Unknown1094A440(active);
	}

	// FUNCTION: ENGINE 0x10955D50
	void JointLockDriver::SetJoint(unsigned int joint)
	{
		mJoint = joint;
		UpdateActive();
	}

	// FUNCTION: ENGINE 0x10955D60
	void JointLockDriver::SetMode(unsigned int mode)
	{
		mMode = mode;
		UpdateActive();
	}

	// FUNCTION: ENGINE 0x10955D70
	unsigned int JointLockDriver::GetFirstJoint() const
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10955D80
	unsigned int JointLockDriver::GetLastJoint() const
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10955D90
	void JointLockDriver::GrabMatrix(pure3d::PoseData* pose)
	{
		if (mJoint < pose->mArrays.mJointCount)
		{
			mMatrix = pose->mWorldMatrices[mJoint];
		}
	}

	// FUNCTION: ENGINE 0x10955DC0
	void JointLockDriver::GrabMatrix(pure3d::Pose* pose)
	{
		GrabMatrix(&pose->mData);
	}

	// FUNCTION: ENGINE 0x10955DD0
	void JointLockDriver::Update(float dt)
	{
	}

	// FUNCTION: ENGINE 0x10955DE0
	void JointLockDriver::FillLimbTask(PoseBlendLimbTask* task)
	{
		task->SetJointLock(this);
	}

	// FUNCTION: ENGINE 0x10955DF0
	JointLockDriver::JointLockDriver() : Driver(4), mJoint(0xFFFF), mMode(3), mTransform()
	{
		mUnknownC8 = false;
		gJointLockDriverCount++;
		if (gJointLockDriverCount > gJointLockDriverPeak)
		{
			gJointLockDriverPeak = gJointLockDriverCount;
		}
		mMatrix.Identity();
	}
}
