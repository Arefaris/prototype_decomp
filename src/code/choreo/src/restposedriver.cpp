// choreo::RestPoseDriver (driver type 8; the unit after the drivers' copies, 0x109573C0 - 0x10957690). Names are
// guesses.
#include "code/choreo/drivers.h"
#include "code/choreo/poseblendjob.h"

namespace math
{
	// 0x11283234 (symbols.txt)
	extern const Vector kZeroVector;
}

namespace choreo
{
	// FUNCTION: ENGINE 0x109573C0
	RestPoseDriver::RestPoseDriver(pure3d::Skeleton* skeleton) : PartitionDriver(skeleton, 8)
	{
		Unknown1094A430(true);
	}

	// FUNCTION: ENGINE 0x109573F0
	RestPoseDriver::~RestPoseDriver()
	{
	}

	// FUNCTION: ENGINE 0x10957400
	RestPoseDriver* GetRestPoseDriver(Driver* driver)
	{
		return driver->mType == 8 ? static_cast<RestPoseDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10957420
	RestPoseDriver* Unknown10957420(Driver* driver)
	{
		return driver->mType == 8 ? static_cast<RestPoseDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10957440
	void RestPoseDriver::Update(float dt)
	{
	}

	// FUNCTION: ENGINE 0x10957450
	void RestPoseDriver::FillNode(PoseBlendNode* node, PoseBlendSample* sample)
	{
		unsigned int first = mFirstJoint;
		if (first == 0)
		{
			math::Quaternion rotation;
			rotation.z = 0.0f;
			rotation.y = 0.0f;
			rotation.x = 0.0f;
			rotation.w = 1.0f;
			node->SetRotation(rotation);
			node->SetTranslation(math::kZeroVector);
			first = 1;
		}
		else
		{
			node->SetNoRoot();
		}
		node->SetJoints(first, mLastJoint, const_cast<pure3d::JointMask*>(mJointMask));
		node->SetMode3();
	}
}
