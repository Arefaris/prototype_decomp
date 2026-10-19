// The smaller driver classes of the choreo module (RTTI names; all derive from choreo::Driver, the pose, joint and rest
// pose drivers through choreo::PartitionDriver): the IK driver (type 2), the joint driver (3), the joint lock driver (4),
// the pose driver (7), the rest pose driver (8) and the strafe adjust root driver (10). Names and members are guesses.
// The virtuals are in the order of the engine's vftables.
#ifndef CHOREO_DRIVERS_H
#define CHOREO_DRIVERS_H

#include "code/choreo/deltatransform.h"
#include "code/choreo/rootdriver.h"

namespace choreo
{
	class PoseBlendLimbTask;
	class PoseBlendRootTask;

	// How many of each kind exist and the most that ever did (names guessed)
	// 0x1131E6EC / 0x1131E6F0: pose drivers, 0x1131E6F4 / 0x1131E6F8: joint drivers, 0x1131E734 / 0x1131E738: joint
	// lock drivers
	extern int gPoseDriverCount;
	extern int gPoseDriverPeak;
	extern int gJointDriverCount;
	extern int gJointDriverPeak;
	extern int gJointLockDriverCount;
	extern int gJointLockDriverPeak;

	// The driver that bends the limb of three joints towards a target (vftable 0x10E8B8F4, five slots)
	class IKDriver : public Driver
	{
	public:
		// 0x10949680
		IKDriver();
		// 0x10949700 (the destructor the compiler makes)
		// slots 2 and 3 (0x109497B0 / 0x109497C0): the first and the last joint of the limb
		virtual unsigned int GetFirstJoint() const;
		virtual unsigned int GetLastJoint() const;

		// 0x10949750: the three joints of the limb
		void SetJoints(unsigned int first, unsigned int middle, unsigned int last);
		// 0x10949770 / 0x10949790: the point the limb reaches for and the direction it bends in
		void SetTarget(const math::Vector& target);
		void SetAxis(const math::Vector& axis);
		// 0x109497D0: nothing to step
		void Update(float dt);
		// 0x109497E0: the task that applies the driver to the pose
		void FillLimbTask(PoseBlendLimbTask* task);
		// 0x1094A2D0: places the limb of the pose
		void Unknown1094A2D0(Puppet* puppet, pure3d::PoseData* pose, float first, float second);

		unsigned int mFirst;       // 0x20
		unsigned int mMiddle;      // 0x24
		unsigned int mLast;        // 0x28
		math::Vector mTarget;      // 0x2C
		math::Vector mAxis;        // 0x38
	};

	// 0x10949710 / 0x10949730: the driver as an IK driver, when it is one (type 2)
	IKDriver* GetIKDriver(Driver* driver);
	IKDriver* Unknown10949730(Driver* driver);

	// The driver that moves one joint (vftable 0x10E8C774, five slots, driver type 3)
	class JointDriver : public Driver
	{
	public:
		// 0x10951A40 / 0x10951A90
		JointDriver();
		explicit JointDriver(unsigned int joint);
		// 0x10951AE0
		virtual ~JointDriver();
		// slots 2 and 3 (0x10951B40 / 0x10951B50): the joint
		virtual unsigned int GetFirstJoint() const;
		virtual unsigned int GetLastJoint() const;

		// 0x10951B60 / 0x10951B70: the joint and which parts of the root the driver moves
		void SetJoint(unsigned int joint);
		void SetRootParts(unsigned int parts);
		// 0x10951B90: nothing to step
		void Update(float dt);
		// 0x10951BA0: the blend node of the joint
		void FillNode(PoseBlendNode* node, PoseBlendSample* sample);

		unsigned int mJoint;       // 0x20
		unsigned int mRootParts;   // 0x24
		Transform mTransform;      // 0x28
	};

	// 0x10951B00 / 0x10951B20: the driver as a joint driver, when it is one (type 3)
	JointDriver* GetJointDriver(Driver* driver);
	JointDriver* Unknown10951B20(Driver* driver);

	// The driver that holds a joint where it was (vftable 0x10E8CAE4, five slots, driver type 4)
	class JointLockDriver : public Driver
	{
	public:
		// 0x10955DF0
		JointLockDriver();
		// 0x10956AF0 (its matrix is copied row by row by the engine)
		JointLockDriver(const JointLockDriver& other);
		// 0x10955CC0
		virtual ~JointLockDriver();
		// slots 2 and 3 (0x10955D70 / 0x10955D80): the driver drives no joint of the partition
		virtual unsigned int GetFirstJoint() const;
		virtual unsigned int GetLastJoint() const;

		// 0x10955D20: whether the driver takes part in the blend (when the joint and the mode are set)
		void UpdateActive();
		// 0x10955D50 / 0x10955D60
		void SetJoint(unsigned int joint);
		void SetMode(unsigned int mode);
		// 0x10955D90 / 0x10955DC0: takes the world matrix of the joint from a pose
		void GrabMatrix(pure3d::PoseData* pose);
		void GrabMatrix(pure3d::Pose* pose);
		// 0x10955DD0: nothing to step
		void Update(float dt);
		// 0x10955DE0: the task that applies the driver to the pose
		void FillLimbTask(PoseBlendLimbTask* task);
		// 0x10955E70: holds the joint of the pose
		void Unknown10955E70(Puppet* puppet, pure3d::PoseData* pose, float first, float second);

		unsigned int mJoint;       // 0x20
		unsigned int mMode;        // 0x24
		Transform mTransform;      // 0x28
		math::Matrix mMatrix;      // 0x88
		bool mUnknownC8;           // 0xC8
	};

	// 0x10955CE0 / 0x10955D00
	JointLockDriver* GetJointLockDriver(Driver* driver);
	JointLockDriver* Unknown10955D00(Driver* driver);

	// The driver that shows a pose (vftable 0x10E8C654, six slots, driver type 7)
	class PoseDriver : public PartitionDriver
	{
	public:
		// 0x109519A0
		PoseDriver(pure3d::Skeleton* skeleton, pure3d::Pose* pose, unsigned int channels);
		// 0x109518B0
		PoseDriver(const PoseDriver& other);
		// slot 0 (0x10951A20): binds the driver and takes the pose it shows
		virtual void Bind(const DriverInfo& info);
		// 0x109518F0
		virtual ~PoseDriver();

		// 0x10951880: nothing to step
		void Update(float dt);
		// 0x10951920: the pose to show
		void SetPose(pure3d::Pose* pose);
		// 0x10951940: the blend node of the pose
		void FillNode(PoseBlendNode* node, PoseBlendSample* sample);

		unsigned int mChannels;    // 0x38
		pure3d::Pose* mPose;       // 0x3C
	};

	// 0x10951840 / 0x10951860
	PoseDriver* GetPoseDriver(Driver* driver);
	PoseDriver* Unknown10951860(Driver* driver);

	// The driver that holds the pose of the skeleton at rest (vftable 0x10E8CC04, six slots, driver type 8)
	class RestPoseDriver : public PartitionDriver
	{
	public:
		// 0x109573C0
		explicit RestPoseDriver(pure3d::Skeleton* skeleton);
		// 0x109573F0
		virtual ~RestPoseDriver();

		// 0x10957440: nothing to step
		void Update(float dt);
		// 0x10957450: the blend node of the rest pose
		void FillNode(PoseBlendNode* node, PoseBlendSample* sample);
	};

	// The driver that adjusts the root of a strafing character (vftable 0x10E8CC20, five slots, driver type 10)
	class StrafeAdjustRootDriver : public Driver
	{
	public:
		// 0x10956F30
		StrafeAdjustRootDriver();
		// 0x10956F90
		virtual ~StrafeAdjustRootDriver();
		// slots 2 and 3 (0x109567B0 / 0x109567C0): the joint
		virtual unsigned int GetFirstJoint() const;
		virtual unsigned int GetLastJoint() const;

		// 0x10956FE0: whether the driver takes part in the blend (when it has a joint)
		void UpdateActive();
		// 0x10957060: the joint
		void SetJoint(unsigned int joint);
		// 0x10957170: turns the angle on by the speed
		void Update(float dt);
		// 0x109571B0: the task that applies the driver to the root
		void FillRootTask(PoseBlendRootTask* task);
		// 0x109571C0: moves the root of the pose with the puppet's root delta by the two weights
		void Unknown109571C0(Puppet* puppet, pure3d::PoseData* pose, float first, float second);

		unsigned int mJoint;       // 0x20
		math::Vector mVectorA;     // 0x24
		math::Vector mVectorB;     // 0x30
		float unknown3C;           // 0x3C
		float mSpeed;              // 0x40
		float mAngle;              // 0x44
		float unknown48;           // 0x48
	};

	// The driver that walks a character (driver types 5 and 6 are its two kinds; vftable 0x10E8C534, seven slots, the
	// last pure). Only what the driver tables reach is laid out.
	class LocomotionDriver : public PartitionDriver
	{
	public:
		unsigned int mUnknown38;   // 0x38
		unsigned int mUnknown3C;   // 0x3C
		unsigned int mUnknown40;   // 0x40
	};

	// The locomotion that steers (vftable 0x10E8C414, seven slots, driver type 5, 0x2F8 bytes)
	class LocomotionSteerDriver : public LocomotionDriver
	{
	public:
		// 0x10956B50
		LocomotionSteerDriver(const LocomotionSteerDriver& other);
		// 0x10951060: steps the driver
		void Update(float dt);
		// 0x1094FDD0: the blend node of the driver
		void FillNode(PoseBlendNode* node, PoseBlendSample* sample);
		// 0x1094FCB0: whether the clips of all the entries are at rest against the skeleton
		bool AllAtRest() const;

		unsigned char unknown48[0x2AC - 0x48];
		unsigned int mUnknown2AC;  // 0x2AC
		unsigned char unknown2B0[0x2F8 - 0x2B0];
	};

	// The locomotion that strafes (vftable 0x10E8BA44, seven slots, driver type 6, 0x270 bytes)
	class LocomotionStrafeDriver : public LocomotionDriver
	{
	public:
		// 0x10956C80
		LocomotionStrafeDriver(const LocomotionStrafeDriver& other);
		// 0x1094C2F0: steps the driver
		void Update(float dt);
		// 0x1094AD30: the blend node of the driver
		void FillNode(PoseBlendNode* node, PoseBlendSample* sample);
		// 0x1094A800
		unsigned int GetUnknown1C0() const;
		// 0x1094A810: whether the clips of all the entries are at rest against the skeleton
		bool AllAtRest() const;

		unsigned char unknown48[0x270 - 0x48];
	};

}

#endif
