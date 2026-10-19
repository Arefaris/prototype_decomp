// choreo::IKDriver and the empty virtuals of choreo::Driver (the unit before the driver base's, 0x10949680 -
// 0x1094A400; the solver of 0x10949930 is not reconstructed). Names are guesses.
#include "code/choreo/drivers.h"
#include "code/choreo/poseblendjob.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x10949680
	IKDriver::IKDriver() : Driver(2)
	{
		mFirst = 0xFFFF;
		mMiddle = 0xFFFF;
		mLast = 0xFFFF;
		mTarget.Set(0.0f, 0.0f, 0.0f);
		mAxis.Set(1.0f, 0.0f, 0.0f);
		Unknown1094A430(true);
	}

	// FUNCTION: ENGINE 0x109496E0
	void Driver::Bind(const DriverInfo& info)
	{
	}

	// FUNCTION: ENGINE 0x109496F0
	void Driver::Unbind()
	{
	}

	// FUNCTION: ENGINE 0x10949710
	IKDriver* GetIKDriver(Driver* driver)
	{
		return driver->mType == 2 ? static_cast<IKDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10949730
	IKDriver* Unknown10949730(Driver* driver)
	{
		return driver->mType == 2 ? static_cast<IKDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10949750
	void IKDriver::SetJoints(unsigned int first, unsigned int middle, unsigned int last)
	{
		mFirst = first;
		mMiddle = middle;
		mLast = last;
	}

	// FUNCTION: ENGINE 0x10949770
	void IKDriver::SetTarget(const math::Vector& target)
	{
		mTarget.x = target.x;
		mTarget.y = target.y;
		mTarget.z = target.z;
	}

	// FUNCTION: ENGINE 0x10949790
	void IKDriver::SetAxis(const math::Vector& axis)
	{
		mAxis.x = axis.x;
		mAxis.y = axis.y;
		mAxis.z = axis.z;
	}

	// FUNCTION: ENGINE 0x109497B0
	unsigned int IKDriver::GetFirstJoint() const
	{
		return mFirst;
	}

	// FUNCTION: ENGINE 0x109497C0
	unsigned int IKDriver::GetLastJoint() const
	{
		return mLast;
	}

	// FUNCTION: ENGINE 0x109497D0
	void IKDriver::Update(float dt)
	{
	}

	// FUNCTION: ENGINE 0x109497E0
	void IKDriver::FillLimbTask(PoseBlendLimbTask* task)
	{
		task->SetIK(this);
	}
}
