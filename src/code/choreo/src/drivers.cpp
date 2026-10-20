// choreo drivers (the driver tables, the functions that forward to the driver classes' own, the clones of the drivers
// and the strafe adjust root driver; 0x10956050 - 0x109573C0, file name guessed). Names are guesses.
#include "code/choreo/drivers.h"
#include "code/choreo/blenddriver.h"
#include "code/choreo/poseblendjob.h"

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

	// FUNCTION: ENGINE 0x10956360
	bool GetAnimationSampleCount(Driver* driver)
	{
		return static_cast<AnimationDriver*>(driver)->IsSet();
	}

	// FUNCTION: ENGINE 0x10956370
	int GetBlendSampleCount(Driver* driver)
	{
		return static_cast<AnimationBlendDriver*>(driver)->GetActiveCount();
	}

	// FUNCTION: ENGINE 0x10956380
	int GetSteerSampleCount(Driver* driver)
	{
		return static_cast<LocomotionSteerDriver*>(driver)->mSampleCount;
	}

	// FUNCTION: ENGINE 0x10956390
	int GetStrafeSampleCount(Driver* driver)
	{
		return static_cast<LocomotionStrafeDriver*>(driver)->GetUnknown1C0();
	}

	// FUNCTION: ENGINE 0x109563A0
	void UpdateAnimationDriver(Driver* driver, float dt)
	{
		static_cast<AnimationDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x109563C0
	void UpdateBlendDriver(Driver* driver, float dt)
	{
		static_cast<AnimationBlendDriver*>(driver)->Step(dt);
	}

	// FUNCTION: ENGINE 0x109563E0
	void UpdateIKDriver(Driver* driver, float dt)
	{
		static_cast<IKDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x10956400
	void UpdateJointDriver(Driver* driver, float dt)
	{
		static_cast<JointDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x10956420
	void UpdateJointLockDriver(Driver* driver, float dt)
	{
		static_cast<JointLockDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x10956440
	void UpdateSteerDriver(Driver* driver, float dt)
	{
		static_cast<LocomotionSteerDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x10956460
	void UpdateStrafeDriver(Driver* driver, float dt)
	{
		static_cast<LocomotionStrafeDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x10956480
	void UpdatePoseDriver(Driver* driver, float dt)
	{
		static_cast<PoseDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x109564A0
	void UpdateRestPoseDriver(Driver* driver, float dt)
	{
		static_cast<RestPoseDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x109564C0
	void UpdateRootDriver(Driver* driver, float dt)
	{
		static_cast<RootDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x109564E0
	void UpdateStrafeAdjustRootDriver(Driver* driver, float dt)
	{
		static_cast<StrafeAdjustRootDriver*>(driver)->Update(dt);
	}

	// FUNCTION: ENGINE 0x10956500
	void FillAnimationNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		static_cast<AnimationDriver*>(driver)->Unknown1094F6D0(node, sample);
	}

	// FUNCTION: ENGINE 0x10956520
	void FillBlendNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		static_cast<AnimationBlendDriver*>(driver)->FillNode(node, sample);
	}

	// FUNCTION: ENGINE 0x10956540
	void FillJointNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		static_cast<JointDriver*>(driver)->FillNode(node, sample);
	}

	// FUNCTION: ENGINE 0x10956560
	void FillSteerNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		static_cast<LocomotionSteerDriver*>(driver)->FillNode(node, sample);
	}

	// FUNCTION: ENGINE 0x10956580
	void FillStrafeNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		static_cast<LocomotionStrafeDriver*>(driver)->FillNode(node, sample);
	}

	// FUNCTION: ENGINE 0x109565A0
	void FillPoseNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		static_cast<PoseDriver*>(driver)->FillNode(node, sample);
	}

	// FUNCTION: ENGINE 0x109565C0
	void FillRestPoseNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		static_cast<RestPoseDriver*>(driver)->FillNode(node, sample);
	}

	// FUNCTION: ENGINE 0x109565E0
	void FillRootNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample)
	{
		static_cast<RootDriver*>(driver)->FillPose(node, sample);
	}

	// FUNCTION: ENGINE 0x10956600
	void FillStrafeAdjustRootTask(Driver* driver, PoseBlendRootTask* task)
	{
		static_cast<StrafeAdjustRootDriver*>(driver)->FillRootTask(task);
	}

	// FUNCTION: ENGINE 0x10956610
	void FillIKLimbTask(Driver* driver, PoseBlendLimbTask* task)
	{
		static_cast<IKDriver*>(driver)->FillLimbTask(task);
	}

	// FUNCTION: ENGINE 0x10956620
	void FillJointLockLimbTask(Driver* driver, PoseBlendLimbTask* task)
	{
		static_cast<JointLockDriver*>(driver)->FillLimbTask(task);
	}

	// FUNCTION: ENGINE 0x10956630
	Driver* ClonePoseDriver(Driver* driver)
	{
		return new PoseDriver(*static_cast<PoseDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956650
	bool AcceptAnimation(Driver* driver)
	{
		return static_cast<AnimationDriver*>(driver)->UpdateRest();
	}

	// FUNCTION: ENGINE 0x10956660
	bool AcceptBlend(Driver* driver)
	{
		return static_cast<AnimationBlendDriver*>(driver)->AllAtRest();
	}

	// FUNCTION: ENGINE 0x10956670
	bool AcceptSteer(Driver* driver)
	{
		return static_cast<LocomotionSteerDriver*>(driver)->AllAtRest();
	}

	// FUNCTION: ENGINE 0x10956680
	bool AcceptStrafe(Driver* driver)
	{
		return static_cast<LocomotionStrafeDriver*>(driver)->AllAtRest();
	}

	// FUNCTION: ENGINE 0x109567B0
	unsigned int StrafeAdjustRootDriver::GetFirstJoint() const
	{
		return mJoint;
	}

	// FUNCTION: ENGINE 0x109567C0
	unsigned int StrafeAdjustRootDriver::GetLastJoint() const
	{
		return mJoint;
	}

	// FUNCTION: ENGINE 0x109568C0
	Driver* CloneIKDriver(Driver* driver)
	{
		return new IKDriver(*static_cast<IKDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x109568E0
	Driver* CloneJointDriver(Driver* driver)
	{
		return new JointDriver(*static_cast<JointDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956930
	Driver* CloneRestPoseDriver(Driver* driver)
	{
		return new RestPoseDriver(*static_cast<RestPoseDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956960
	Driver* CloneStrafeAdjustRootDriver(Driver* driver)
	{
		return new StrafeAdjustRootDriver(*static_cast<StrafeAdjustRootDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956E10
	Driver* CloneAnimationDriver(Driver* driver)
	{
		return new AnimationDriver(*static_cast<AnimationDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956E40
	Driver* CloneBlendDriver(Driver* driver)
	{
		return new AnimationBlendDriver(*static_cast<AnimationBlendDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956E70
	Driver* CloneJointLockDriver(Driver* driver)
	{
		return new JointLockDriver(*static_cast<JointLockDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956EA0
	Driver* CloneSteerDriver(Driver* driver)
	{
		return new LocomotionSteerDriver(*static_cast<LocomotionSteerDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956ED0
	Driver* CloneStrafeDriver(Driver* driver)
	{
		return new LocomotionStrafeDriver(*static_cast<LocomotionStrafeDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956F00
	Driver* CloneRootDriver(Driver* driver)
	{
		return new RootDriver(*static_cast<RootDriver*>(driver));
	}

	// FUNCTION: ENGINE 0x10956F30
	StrafeAdjustRootDriver::StrafeAdjustRootDriver() : Driver(10)
	{
		mJoint = 0xFFFF;
		mVectorA.Set(0.0f, 0.0f, -1.0f);
		mVectorB.Set(0.0f, 0.0f, -1.0f);
		unknown3C = 0.0f;
		mSpeed = 3.14159274f;
		mAngle = 0.0f;
		unknown48 = 0.0f;
	}

	// FUNCTION: ENGINE 0x10956F90
	StrafeAdjustRootDriver::~StrafeAdjustRootDriver()
	{
	}

	// FUNCTION: ENGINE 0x10956FA0
	StrafeAdjustRootDriver* GetStrafeAdjustRootDriver(Driver* driver)
	{
		return driver->mType == 10 ? static_cast<StrafeAdjustRootDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10956FC0
	StrafeAdjustRootDriver* Unknown10956FC0(Driver* driver)
	{
		return driver->mType == 10 ? static_cast<StrafeAdjustRootDriver*>(driver) : 0;
	}

	// FUNCTION: ENGINE 0x10956FE0
	void StrafeAdjustRootDriver::UpdateActive()
	{
		bool active = mJoint != 0xFFFF;
		Unknown1094A440(active);
		Unknown1094A430(active);
	}

	// FUNCTION: ENGINE 0x10957060
	void StrafeAdjustRootDriver::SetJoint(unsigned int joint)
	{
		mJoint = joint;
		UpdateActive();
	}

	// FUNCTION: ENGINE 0x10957170
	void StrafeAdjustRootDriver::Update(float dt)
	{
		if (mFlag0)
		{
			mAngle = WrapFrame(0.0f, 6.28318548f, mSpeed * dt + mAngle);
		}
	}

	// FUNCTION: ENGINE 0x109571B0
	void StrafeAdjustRootDriver::FillRootTask(PoseBlendRootTask* task)
	{
		task->SetDriver(this);
	}
}
