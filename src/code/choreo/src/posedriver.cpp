// choreo::PoseDriver (driver type 7; the unit before the joint driver's, 0x10951840 - 0x10951A40). Names are guesses.
#include "code/choreo/drivers.h"
#include "code/choreo/poseblendjob.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x10951840
	PoseDriver* GetPoseDriver(Driver* driver)
	{
		return driver->mType == 7 ? static_cast<PoseDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10951860
	PoseDriver* Unknown10951860(Driver* driver)
	{
		return driver->mType == 7 ? static_cast<PoseDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10951880
	void PoseDriver::Update(float dt)
	{
	}

	// FUNCTION: ENGINE 0x109518B0
	PoseDriver::PoseDriver(const PoseDriver& other) : PartitionDriver(other)
	{
		mChannels = other.mChannels;
		mPose = 0;
		core::RefAssign(mPose, other.mPose);
	}

	// FUNCTION: ENGINE 0x109518F0
	PoseDriver::~PoseDriver()
	{
		core::SafeRelease(mPose);
		gPoseDriverCount--;
	}

	// FUNCTION: ENGINE 0x10951920
	void PoseDriver::SetPose(pure3d::Pose* pose)
	{
		core::RefAssign((pure3d::LockableRefCounted*&)mPose, (pure3d::LockableRefCounted*)pose);
	}

	// FUNCTION: ENGINE 0x10951940
	// EQUIVALENT: the same calls with the same arguments in the same order; the engine sets the this pointer of the node
	// calls once before the branch on the pose, ours in each branch, and loads the three arguments of SetJoints in
	// another order (56.3 %)
	void PoseDriver::FillNode(PoseBlendNode* node, PoseBlendSample* sample)
	{
		unsigned int first = mFirstJoint;
		if (first < 1)
		{
			first = 1;
		}
		node->SetJoints(first, mLastJoint, const_cast<pure3d::JointMask*>(mJointMask));
		if (mPose != 0)
		{
			node->SetPose(&mPose->mData, mChannels);
			node->SetNoRoot();
		}
		else
		{
			node->SetNone(true, true);
		}
	}

	// FUNCTION: ENGINE 0x109519A0
	PoseDriver::PoseDriver(pure3d::Skeleton* skeleton, pure3d::Pose* pose, unsigned int channels) :
		PartitionDriver(skeleton, 7)
	{
		mChannels = channels;
		mPose = 0;
		SetPose(pose);
		Unknown1094A430(true);
		gPoseDriverCount++;
		if (gPoseDriverCount > gPoseDriverPeak)
		{
			gPoseDriverPeak = gPoseDriverCount;
		}
	}

	// FUNCTION: ENGINE 0x10951A20
	void PoseDriver::Bind(const DriverInfo& info)
	{
		PartitionDriver::Bind(info);
		SetPose(reinterpret_cast<pure3d::Pose*>(const_cast<DriverInfo*>(&info)));
	}
}
