// choreo::JointDriver (the unit after the pose driver's, 0x10951A40 - 0x10951C20). Names are guesses.
#include "code/choreo/drivers.h"
#include "code/choreo/poseblendjob.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x10951A40
	JointDriver::JointDriver() : Driver(3), mJoint(0), mRootParts(3), mTransform()
	{
		gJointDriverCount++;
		if (gJointDriverCount > gJointDriverPeak)
		{
			gJointDriverPeak = gJointDriverCount;
		}
		Unknown1094A430(true);
	}

	// FUNCTION: ENGINE 0x10951A90
	JointDriver::JointDriver(unsigned int joint) : Driver(3), mJoint(joint), mRootParts(3), mTransform()
	{
		gJointDriverCount++;
		if (gJointDriverCount > gJointDriverPeak)
		{
			gJointDriverPeak = gJointDriverCount;
		}
	}

	// FUNCTION: ENGINE 0x10951AE0
	JointDriver::~JointDriver()
	{
		gJointDriverCount--;
	}

	// FUNCTION: ENGINE 0x10951B00
	JointDriver* GetJointDriver(Driver* driver)
	{
		return driver->mType == 3 ? static_cast<JointDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10951B20
	JointDriver* Unknown10951B20(Driver* driver)
	{
		return driver->mType == 3 ? static_cast<JointDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10951B40
	unsigned int JointDriver::GetFirstJoint() const
	{
		return mJoint;
	}

	// FUNCTION: ENGINE 0x10951B50
	unsigned int JointDriver::GetLastJoint() const
	{
		return mJoint;
	}

	// FUNCTION: ENGINE 0x10951B60
	void JointDriver::SetJoint(unsigned int joint)
	{
		mJoint = joint;
	}

	// FUNCTION: ENGINE 0x10951B70
	void JointDriver::SetRootParts(unsigned int parts)
	{
		mRootParts = parts;
		Unknown1094A430(parts != 0);
	}

	// FUNCTION: ENGINE 0x10951B90
	void JointDriver::Update(float dt)
	{
	}

	// FUNCTION: ENGINE 0x10951BA0
	void JointDriver::FillNode(PoseBlendNode* node, PoseBlendSample* sample)
	{
		node->SetRootParts(mRootParts);
		Transform& transform = mTransform;
		math::Vector translation(transform.mMatrix.m[3][0], transform.mMatrix.m[3][1], transform.mMatrix.m[3][2]);
		node->SetJoint(mJoint, transform.GetQuaternion(), translation);
		node->SetNoRoot();
	}
}
