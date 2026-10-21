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
		// 0x10957070 / 0x109570F0: the two directions (normalised before they are kept; a direction without length is ignored)
		void SetDirection(const math::Vector& direction);
		void SetOriginalDirection(const math::Vector& direction);
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
	// last pure). It counts the instances (0x1131E6E4 / 0x1131E6E8).
	class LocomotionDriver : public PartitionDriver
	{
	public:
		// 0x109515F0
		LocomotionDriver(pure3d::Skeleton* skeleton, int type);
		// 0x10951660
		virtual ~LocomotionDriver();
		// slot 6: sets the rate of every clip from a table of speeds (pure here)
		virtual void SetClipRates(const void* speeds) = 0;

		float mUnknown38;          // 0x38
		float mUnknown3C;          // 0x3C
		float mUnknown40;          // 0x40
	};

	// 0x1131E6E4 / 0x1131E6E8
	extern int gLocomotionDriverCount;
	extern int gLocomotionDriverPeak;

	// 0x10951680 / 0x109516A0: the driver as a locomotion driver, when it is one (types 5 and 6)
	LocomotionDriver* GetLocomotionDriver(Driver* driver);
	LocomotionDriver* Unknown109516A0(Driver* driver);

	// What the strafe driver keeps of a clip of its grid: the binding it uses and the speed of the clip (8 bytes)
	struct StrafeCell
	{
		unsigned int mBinding;
		float mSpeed;
	};

	// One clip taking part in the current blend (12 bytes)
	struct StrafeSample
	{
		// The heavier clips first
		bool operator<(const StrafeSample& other) const
		{
			return mWeight > other.mWeight;
		}

		unsigned int mCell;
		float mWeight;
		float mValue;
	};

	// One clip taking part in the current blend of the steer driver (12 bytes)
	struct SteerSample
	{
		// The heavier clips first
		bool operator<(const SteerSample& other) const
		{
			return mWeight > other.mWeight;
		}

		unsigned int mBinding;
		float mWeight;
		float mValue;
	};

	// The locomotion that strafes (vftable 0x10E8BA44, seven slots, driver type 6, 0x270 bytes): a grid of clips by
	// heading and speed
	class LocomotionStrafeDriver : public LocomotionDriver
	{
	public:
		static const unsigned int MAX_BINDINGS = 9;
		static const unsigned int MAX_SAMPLES = 4;

		// 0x1094B780
		LocomotionStrafeDriver(pure3d::Skeleton* skeleton, unsigned int columns, unsigned int rows, void* animations,
			void* rates, void* speeds);
		// slot 0 (0x1094A790) / slot 1 (0x1094A720) / slot 4 (0x1094B0D0) / slot 6 (0x1094A750)
		virtual void Bind(const DriverInfo& info);
		virtual void Unbind();
		virtual ~LocomotionStrafeDriver();
		virtual void SetClipRates(const void* speeds);

		// 0x1094A690 / 0x1094A6A0: the skeleton and the joint mask
		pure3d::Skeleton* GetSkeletonCopy() const;
		const pure3d::JointMask* GetJointMaskCopy() const;
		// 0x1094A6B0: the number of cells of the grid
		unsigned int GetCellCount() const;
		// 0x1094A8A0 / 0x1094A930: the heading of the direction, kept as the first / the second heading
		void SetFirstHeading(const math::Vector& direction);
		void SetHeading(const math::Vector& direction);
		// 0x1094A8E0 / 0x1094A950: the direction of the heading / the velocity of the heading at the speed
		math::Vector* GetDirection(math::Vector* out) const;
		math::Vector* GetVelocity(math::Vector* out) const;
		// 0x1094A9D0 / 0x1094AAC0 / 0x1094AB60: the speed of the grid cell of a row, the row a speed lies in and
		// the speed at a position in the rows
		float GetRowSpeed(unsigned int row, float heading) const;
		float FindRow(float speed, float heading) const;
		float GetSpeedAt(float position, float heading) const;
		// 0x1094B020 / 0x1094B060: the speed of a row / of the last row at the difference of two headings
		float GetRowSpeedAt(unsigned int row, float from, float to) const;
		float GetLastRowSpeedAt(float from, float to) const;
		// 0x1094B0A0: the speed at a position in the rows at the difference of two headings
		float GetSpeedAtDifference(float position, float from, float to) const;
		// 0x1094B3A0: takes the heading and the speed from a velocity (its horizontal part)
		void SetVelocity(const math::Vector* velocity);
		// 0x1094B400 / 0x1094B440: a value divided by the speed of the last row at two headings / at one heading
		float DivideByLastRowSpeedAt(float value, float from, float to) const;
		float DivideByLastRowSpeed(float value, float heading) const;
		// 0x1094B460 / 0x1094B4A0: the same, multiplied
		float MultiplyByLastRowSpeedAt(float value, float from, float to) const;
		float MultiplyByLastRowSpeed(float value, float heading) const;
		// 0x1094B710 / 0x1094B8D0: the value times the speed of the last row at the character's headings, returned /
		// kept as the speed
		float ScaleByHeadingSpeed(float value) const;
		void SetSpeedByHeading(float value);
		// 0x1094B740 / 0x1094B900: the speed at a position in the rows at the character's headings, returned / kept
		float GetSpeedAtHeading(float position) const;
		void SetSpeedAtHeading(float position);
		// 0x1094AC60: puts a clip of the grid into the blend with a weight
		void AddSample(unsigned int cell, float weight, float value);
		// 0x1094B120: sets up the row of the grid
		void SetRow(unsigned int row, void* const* animations, void* rates, float* speeds);
		// 0x1094C2F0: steps the driver
		void Update(float dt);
		// 0x1094AD30: the blend node of the driver
		void FillNode(PoseBlendNode* node, PoseBlendSample* sample);
		// 0x1094A800
		unsigned int GetUnknown1C0() const;
		// 0x1094A810: whether the clips of all the entries are at rest against the skeleton
		bool AllAtRest() const;

		unsigned int mColumns;                // 0x48
		unsigned int mRows;                   // 0x4C
		unsigned int mBindingCount;           // 0x50
		AnimationBinding mBindings[MAX_BINDINGS]; // 0x54
		StrafeCell mCells[12];                // 0x150
		bool mUnknown1B0;                     // 0x1B0
		bool mUnknown1B1;                     // 0x1B1
		float mFirstHeading;                  // 0x1B4
		float mHeading;                       // 0x1B8
		float mSpeed;                         // 0x1BC
		unsigned int mSampleCount;            // 0x1C0
		StrafeSample mSamples[MAX_SAMPLES];   // 0x1C4
		DeltaTransform mDelta;                // 0x1F4
	};

	// 0x1094A6E0 / 0x1094A700: the driver as a strafe driver, when it is one (type 6)
	LocomotionStrafeDriver* GetStrafeDriver(Driver* driver);
	LocomotionStrafeDriver* Unknown1094A700(Driver* driver);

	// The locomotion that steers (vftable 0x10E8C414, seven slots, driver type 5, 0x2F8 bytes)
	class LocomotionSteerDriver : public LocomotionDriver
	{
	public:
		static const unsigned int MAX_BINDINGS = 12;
		static const unsigned int MAX_SAMPLES = 6;

		// slot 0 (0x1094FC20) / slot 1 (0x1094FBB0) / slot 4 (0x10950690) / slot 6 (0x1094FBE0)
		virtual void Bind(const DriverInfo& info);
		virtual void Unbind();
		virtual ~LocomotionSteerDriver();
		virtual void SetClipRates(const void* speeds);

		// 0x1094FB20 / 0x1094FB30: the word at +0x48, and one more
		unsigned int GetUnknown48() const;
		unsigned int GetUnknown48Plus1() const;
		// 0x1094FB40: how many clips take part in the blend
		unsigned int GetSampleCount() const;
		// 0x1094FCF0: a value of the table at +0x1A4
		float GetUnknown1A4(int index) const;
		// 0x1094FD00: puts a clip into the blend with a weight
		void AddSample(unsigned int binding, float weight, float value);
		// 0x10951060: steps the driver
		void Update(float dt);
		// 0x1094FDD0: the blend node of the driver
		void FillNode(PoseBlendNode* node, PoseBlendSample* sample);
		// 0x1094FCB0: whether the clips of all the entries are at rest against the skeleton
		bool AllAtRest() const;

		unsigned int mUnknown48;     // 0x48
		unsigned int mUnknown4C;     // 0x4C
		unsigned int mBindingCount;  // 0x50
		AnimationBinding mBindings[MAX_BINDINGS]; // 0x54
		float mUnknown1A4[4];        // 0x1A4
		float mUnknown1B4[28];       // 0x1B4
		float mUnknown224;           // 0x224
		float mUnknown228;           // 0x228
		float mUnknown22C;           // 0x22C
		DeltaTransform mDelta;       // 0x230
		unsigned int mSampleCount;   // 0x2AC
		SteerSample mSamples[MAX_SAMPLES]; // 0x2B0
	};

	// 0x1094FB70 / 0x1094FB90: the driver as a steer driver, when it is one (type 5)
	LocomotionSteerDriver* GetSteerDriver(Driver* driver);
	LocomotionSteerDriver* Unknown1094FB90(Driver* driver);

}

#endif
