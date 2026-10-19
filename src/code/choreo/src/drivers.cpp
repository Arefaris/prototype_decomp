// choreo drivers (the driver type tables around 0x10955FF0 - 0x10957690; file name guessed). Names are guesses.
#include "code/choreo/puppet.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x10956050
	int GetSampleCount(Driver* driver)
	{
		int type = driver->mType;
		return gDriverSampleCount[type](driver);
	}

	// FUNCTION: ENGINE 0x10956070
	int GetNodeKind(int type)
	{
		int kinds[11] = { 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 1 };
		return kinds[type];
	}

	// FUNCTION: ENGINE 0x109560C0
	void UpdateDriver(Driver* driver, float dt)
	{
		gDriverUpdate[driver->mType](driver, dt);
	}

	// FUNCTION: ENGINE 0x109560E0
	void FillNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		gDriverNode[driver->mType](driver, node, sample);
	}

	// FUNCTION: ENGINE 0x10956100
	void FillRootTask(Driver* driver, PoseBlendRootTask* task)
	{
		gDriverRootTask[driver->mType](driver, task);
	}

	// FUNCTION: ENGINE 0x10956120
	void FillLimbTask(Driver* driver, PoseBlendLimbTask* task)
	{
		gDriverLimbTask[driver->mType](driver, task);
	}

	// FUNCTION: ENGINE 0x10956140
	Driver* CloneDriver(Driver* driver)
	{
		int type = driver->mType;
		return gDriverClone[type](driver);
	}
}
