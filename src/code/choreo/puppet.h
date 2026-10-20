// choreo::Puppet (the animation state of a character: the drivers that play clips and move the root, layered by
// priority and fade, and the pose they are mixed into) and choreo::Driver (RTTI name; the drivers of the engine
// derive from it: AnimationDriver, LocomotionDriver, RootDriver, ...). Only what the puppet update reads; layouts are
// partial and names are guesses.
#ifndef CHOREO_PUPPET_H
#define CHOREO_PUPPET_H

#include "code/core/name.h"
#include "code/core/refptr.h"
#include "code/math/matrix.h"
#include "code/choreo/poseblendjob.h"
#include "code/pure3d/pose.h"
#include "code/pure3d/posedata.h"

namespace choreo
{
	struct PuppetCounts;
	struct PoseBlendCursors;
	struct BlendRootNode;
	class PoseBlendSample;
	struct PoseBlendRootRange;
	struct PoseBlendLimbRange;

	// What a driver is told about what it drives (the pose its channels belong to)
	struct DriverInfo
	{
		unsigned char unknown0[0xC];
		pure3d::Skeleton* mSkeleton; // 0x0C
	};

	// The drivers are not updated through their vftable but through a table indexed by the driver's type.
	// The virtuals are in the order of the engine's vftables: the binding of slot 0, the release of slot 1, the two
	// ranges of the pose a driver partitions (slots 2 and 3, which every driver class overrides) and the destructor.
	class Driver
	{
	public:
		// 0x1094A4E0: a driver of the given type, not yet taking part in the blend
		Driver(int type);
		// 0x1094A530
		Driver(const Driver& other);
		// slot 0: binds the driver to the pose it drives (nothing in the base, 0x109496E0)
		virtual void Bind(const DriverInfo& info);
		// slot 1: releases what the driver was bound to (nothing in the base, 0x109496F0)
		virtual void Unbind();
		// The first and the last joint of the pose the driver drives
		virtual unsigned int GetFirstJoint() const = 0;
		virtual unsigned int GetLastJoint() const = 0;
		// 0x1094A5B0
		virtual ~Driver();

		// 0x1094A3F0 / 0x1094A400: one more / one less owner; the driver deletes itself when none is left
		void AddRef();
		void Release();
		// 0x1094A420 / 0x1094A5C0 / 0x1094A5D0 / 0x1094A5E0: the driver's name
		core::Name<core::CaseSensitiveKey>& GetName();
		const char* GetNameText() const;
		void SetName(const core::Name<core::CaseSensitiveKey>& name);
		unsigned __int64 GetNameHash() const;
		// 0x1094A430 / 0x1094A460 / 0x1094A480 / 0x1094A4C0: bit 0, bit 2, bit 3 and bit 5 of the flags (names guessed)
		void Unknown1094A430(bool enabled);
		void Unknown1094A460(bool enabled);
		void Unknown1094A480(bool enabled);
		void Unknown1094A4C0(bool enabled);
		// 0x1094A440 / 0x1094A4A0: whether the driver takes part in the blend / moves the root (names guessed)
		void Unknown1094A440(bool enabled);
		void Unknown1094A4A0(bool enabled);
		// 0x10946C50 - 0x10946CA0: the six flags
		bool GetFlag0() const;
		bool GetFlag1() const;
		bool GetFlag2() const;
		bool GetFlag3() const;
		bool GetFlag4() const;
		bool GetFlag5() const;

		// The name is 8-byte aligned in the engine (the class sizes are multiples of 8)
		__declspec(align(8)) core::Name<core::CaseSensitiveKey> mName;  // 0x08
		int mRefCount;                             // 0x10
		int mType;                                 // 0x14
		// Flag 1: the driver takes part in the blend, flag 4: it moves the root, flag 5: the owner stopped it
		bool mFlag0 : 1;                           // 0x18
		bool mFlag1 : 1;
		bool mFlag2 : 1;
		bool mFlag3 : 1;
		bool mFlag4 : 1;
		bool mFlag5 : 1;
		unsigned char unknown18Bit6 : 2;
		unsigned char unknown19[3];
	};

	// How many drivers exist and the most that ever did (0x1131E6CC / 0x1131E6D0)
	extern int gDriverCount;
	extern int gDriverPeak;

	// 0x1094A610: a phase wrapped around into [0, 1) (name guess)
	float WrapPhase(float phase);

	// The update function of each driver type
	typedef void (*DriverUpdateFunction)(Driver* driver, float dt);
	// 0x111EC7C8
	extern DriverUpdateFunction gDriverUpdate[];
	// 0x109560C0: the update function of the driver's type
	void UpdateDriver(Driver* driver, float dt);

	class Puppet;

	// 0x10956140: a copy of the driver, made by the function of the driver's type
	Driver* CloneDriver(Driver* driver);

	class PoseBlendNode;
	class PoseBlendSample;
	class PoseBlendRootTask;
	class PoseBlendLimbTask;

	// The functions of each driver type that the puppet reaches through tables indexed by the type: the sample count
	// (0x111EC820), the node (0x111EC79C), the root task (0x111EC878), the limb task (0x111EC770), the copy of the driver
	// (0x111EC7F4) and whether the type can be added (0x111EC84C)
	typedef int (*DriverSampleCountFunction)(Driver* driver);
	typedef void (*DriverNodeFunction)(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample);
	typedef void (*DriverRootTaskFunction)(Driver* driver, PoseBlendRootTask* task);
	typedef void (*DriverLimbTaskFunction)(Driver* driver, PoseBlendLimbTask* task);
	typedef Driver* (*DriverCloneFunction)(Driver* driver);
	typedef bool (*DriverAcceptFunction)(Driver* driver);
	extern DriverSampleCountFunction gDriverSampleCount[];
	extern DriverNodeFunction gDriverNode[];
	extern DriverRootTaskFunction gDriverRootTask[];
	extern DriverLimbTaskFunction gDriverLimbTask[];
	extern DriverCloneFunction gDriverClone[];
	extern DriverAcceptFunction gDriverAccept[];
	// 0x109560E0 / 0x10956100 / 0x10956120: the node, the root task and the limb task of the driver's type
	void FillNode(Driver* driver, PoseBlendNode* node, PoseBlendSample* sample);
	void FillRootTask(Driver* driver, PoseBlendRootTask* task);
	void FillLimbTask(Driver* driver, PoseBlendLimbTask* task);

	// 0x10956070: which kind of blend nodes a driver type makes: 0 a sampled node, 1 a root task, 2 a limb task
	int GetNodeKind(int type);
	// 0x10956050: the number of samples the driver needs
	int GetSampleCount(Driver* driver);

	// 0x10956250: whether the puppet can take the driver (not when it would have too many drivers or blend nodes);
	// force skips the check on the number of drivers of the kind
	bool AcceptDriver(Driver* driver, Puppet* puppet, bool force);

	// One driver of a puppet with its lifetime and fade (0x2C bytes)
	struct DriverEntry
	{
		// 0x10946E20: the order of the drivers: the higher priority first, then the lower first joint, then the higher
		// last joint
		bool operator<(const DriverEntry& other) const;

		Driver* mDriver;
		// The driver's type
		int mType;
		// Seconds left (counted down while the driver is not endless)
		float mLifetime;
		bool mEndless;
		unsigned char unknownD[3];
		unsigned int mFirstJoint;
		unsigned int mLastJoint;
		int mPriority;
		float mWeight;
		float mBlendIn;
		float mBlendOut;
		// 0 to 1: how far the driver is blended in
		float mFade;
	};

	// How the weight of the drivers is shared among those that take part in one kind of blending: a driver takes
	// part when the flag says so, and the drivers that do share the weight in proportion to their own (16 bytes)
	struct DriverWeightShare
	{
		typedef bool (Driver::*FlagFunction)() const;

		// 0x10947810: the share of the first driver
		DriverWeightShare(FlagFunction flag, const DriverEntry& entry, float scale)
		{
			mFlag = flag;
			mWeight = 0.0f;
			mTotal = 0.0f;
			mScale = 0.0f;
			float weight = entry.mFade * entry.mWeight;
			bool takesPart = (entry.mDriver->*flag)();
			mTotal = takesPart ? weight : 0.0f;
			mWeight = takesPart ? scale : 0.0f;
			mScale = scale;
		}
		// The same for a driver and the weight of its entry already worked out
		DriverWeightShare(FlagFunction flag, Driver* driver, float weight, float scale)
		{
			mFlag = flag;
			mWeight = 0.0f;
			mTotal = 0.0f;
			mScale = 0.0f;
			bool takesPart = (driver->*flag)();
			mTotal = takesPart ? weight : 0.0f;
			mWeight = takesPart ? scale : 0.0f;
			mScale = scale;
		}
		void Add(Driver* driver, float weight)
		{
			bool takesPart = (driver->*mFlag)();
			float shared = takesPart ? weight : 0.0f;
			float total = shared + mTotal;
			mTotal = total;
			mWeight = (takesPart && total > 0.0f) ? mScale / total * weight : 0.0f;
		}
		// 0x10947890: takes the next driver into account
		void Add(const DriverEntry& entry)
		{
			float weight = entry.mFade * entry.mWeight;
			bool takesPart = (entry.mDriver->*mFlag)();
			float shared = takesPart ? weight : 0.0f;
			float total = shared + mTotal;
			mTotal = total;
			mWeight = (takesPart && total > 0.0f) ? mScale / total * weight : 0.0f;
		}
		// 0x10947900
		float GetWeight() const
		{
			return mWeight;
		}

		FlagFunction mFlag;        // 0x00
		float mWeight;             // 0x04
		float mTotal;              // 0x08
		float mScale;              // 0x0C
	};

	// Where a puppet writes its blend nodes and tasks in the shared buffers (16 bytes)
	struct PoseBlendWriter
	{
		// 0x10947700
		__forceinline explicit PoseBlendWriter(const PoseBlendCursors* cursors)
		{
			mRoot = (BlendRootNode*)cursors->cursor[0];
			mSamples = (PoseBlendSample*)cursors->cursor[4];
			mRootRange = (PoseBlendRootRange*)cursors->cursor[1];
			mLimbRange = (PoseBlendLimbRange*)cursors->cursor[2];
		}
		// 0x10947720 / 0x10947790 / 0x109477D0: a node, a root task or a limb task for a driver
		void WriteNode(Driver* driver, float first, float second, float third, float fourth);
		void WriteRootTask(Driver* driver, float first, float second);
		void WriteLimbTask(Driver* driver, float first, float second);
		// 0x10947DF0: whichever the driver's type makes
		void Write(Driver* driver, float first, float second, float third, float fourth);

		BlendRootNode* mRoot;              // 0x00
		PoseBlendSample* mSamples;         // 0x04
		PoseBlendRootRange* mRootRange;    // 0x08
		PoseBlendLimbRange* mLimbRange;    // 0x0C
	};

	// The matrices of the limbs of a skeleton that a puppet blends (0x118 bytes): up to four, each with a weight
	class LimbPoses
	{
	public:
		// 0x10949440: no skeleton and no limbs
		LimbPoses();
		// 0x10949460
		LimbPoses(const LimbPoses& other);
		// 0x10949530
		~LimbPoses();
		// 0x10949540
		LimbPoses& operator=(const LimbPoses& other);
		// 0x10949610: the identity pose of each limb of the skeleton, no weights
		void Reset(pure3d::Skeleton* skeleton);
		// 0x109492A0 / 0x109492B0: the skeleton and the number of limbs
		pure3d::Skeleton* GetSkeleton() const;
		unsigned int GetCount() const;
		// 0x109492C0 / 0x109492F0 / 0x10949300: the matrix and the weight of a limb (the weight kept in [0, 1])
		math::Matrix* GetMatrix(int index);
		// 0x109492D0
		void SetMatrix(int index, const math::Matrix& matrix);
		float GetWeight(int index) const;
		void SetWeight(int index, float weight);
		// 0x10949350: moves each limb's matrix towards the other's by t
		void Blend(const LimbPoses& other, float t);

		pure3d::Skeleton* mSkeleton;               // 0x00
		math::Matrix mMatrices[4];                 // 0x04
		float mWeights[4];                         // 0x104
		unsigned int mCount;                       // 0x114
	};

	// The part of a puppet that is copied from one to another (0x168 bytes): the root delta of the update and the limb
	// poses
	class PuppetState
	{
	public:
		// 0x10947C00
		PuppetState();
		// 0x10946D50
		PuppetState& operator=(const PuppetState& other);
		~PuppetState()
		{
		}

		// The root motion of this update as a matrix
		math::Matrix mRootDelta;                   // 0x00
		bool mUnknown40;                           // 0x40
		unsigned char unknown41[3];
		LimbPoses mLimbs;                          // 0x44
		bool mUnknown15C;                          // 0x15C
		unsigned char unknown15D[3];
		float mUnknown160;                         // 0x160
		float mUnknown164;                         // 0x164
	};

	class Puppet : public PuppetState
	{
	public:
		static const unsigned int MAX_DRIVERS = 16;

		// 0x10947980 - 0x10947A20: the puppet is allocated aligned to 16 bytes
		static void* operator new(unsigned int size);
		static void* operator new(unsigned int size, void* where);
		static void* operator new[](unsigned int size);
		static void* operator new(unsigned int size, int heap);
		static void* operator new[](unsigned int size, int heap);
		static void operator delete(void* block);
		static void operator delete[](void* block);

		// 0x10948400: a puppet of the pose
		Puppet(pure3d::Pose* pose);
		// 0x10947C40
		~Puppet();
		// 0x10947D20: takes over another puppet's pose, root state and limb poses
		void CopyPoseFrom(Puppet* other);
		// 0x10947D80: the pose the puppet works on (all the drivers are bound to it)
		void SetPose(pure3d::Pose* pose);
		// 0x10946DA0: the skeleton of the pose
		pure3d::Skeleton* GetSkeleton();
		// 0x10947A50: whether the puppet can take the driver at all
		bool CanHold(Driver* driver);
		// 0x10947A30 / 0x10947A40: the word the owner keeps
		int GetUserData() const;
		void SetUserData(int data);
		// 0x10947CB0 / 0x10947CC0 / 0x10947CF0: the name of the puppet
		const char* GetNameText() const;
		void SetName(const char* text);
		void SetName(const core::Name<core::CaseSensitiveKey>& name);
		// 0x10946D40 / 0x10948470: one more / one less owner; the puppet destroys itself when none is left
		void AddRef();
		void Release();
		// 0x10946C30: whether there is nothing to blend (no drivers or no pose)
		int IsEmpty() const;
		// 0x10946DC0 / 0x10946DF0: the entry of a driver (null when the puppet does not have it)
		DriverEntry* FindEntry(Driver* driver);
		const DriverEntry* FindEntry(Driver* driver) const;
		// 0x10946E60: puts a driver in the puppet
		bool AddDriver(Driver* driver, float lifetime, int priority, float weight, float blendIn, float blendOut);
		// 0x10946F30: the same for a driver that may be there already (then its entry is changed)
		bool SetDriver(Driver* driver, float lifetime, int priority, float weight, float blendIn, float blendOut,
			float fade);
		// 0x10947010: takes a driver out now, or only makes it end
		bool RemoveDriver(Driver* driver, bool immediately);
		// 0x109470B0: takes all the drivers out now, or makes them end
		void RemoveAll(bool immediately);
		// 0x10947150 - 0x109473E0: the values of a driver's entry
		bool IsEnding(Driver* driver) const;
		bool GetEndless(Driver* driver) const;
		bool GetLifetime(Driver* driver, bool* endless, float* lifetime) const;
		bool SetLifetime(Driver* driver, float lifetime);
		bool SetEndless(Driver* driver, bool endless);
		bool SetEndlessLifetime(Driver* driver, bool endless, float lifetime);
		int GetPriority(Driver* driver) const;
		bool SetPriority(Driver* driver, int priority);
		float GetWeight(Driver* driver) const;
		bool SetWeight(Driver* driver, float weight);
		float GetBlendIn(Driver* driver) const;
		bool SetBlendIn(Driver* driver, float blendIn);
		float GetBlendOut(Driver* driver) const;
		bool SetBlendOut(Driver* driver, float blendOut);
		float GetFade(Driver* driver) const;
		bool SetFade(Driver* driver, float fade);
		// 0x10947420 / 0x10947470: whether a driver is active, and how many are
		bool HasActiveDriver() const;
		int CountActiveDrivers() const;
		// 0x10947560 / 0x109475C0 / 0x109475E0: the n-th active driver / the n-th driver / its type
		Driver* GetActiveDriver(int index) const;
		Driver* GetDriver(unsigned int index) const;
		int GetDriverType(unsigned int index) const;
		// 0x10947600: puts a copy of a driver of another puppet in this one, with the driver's entry
		Driver* CopyDriverFrom(Driver* driver, Puppet* source);

		// 0x10949080: resets the root, fades the drivers in and out (dropping the finished ones) and lets each of
		// them step
		void Update(float dt);
		// 0x10949040: puts the drivers in priority order when they changed
		void SortDrivers();
		// 0x10947660: counts the blend nodes, samples and tasks the puppet's drivers need
		void CountNodes(PuppetCounts* counts);
		// 0x10947E80: writes the drivers first to last of a priority group, sharing the weight
		void WriteGroup(unsigned int first, unsigned int last, float weight, PoseBlendWriter* writer);
		// 0x109484A0: writes all the drivers, group by group of equal priority
		void WriteAll(PoseBlendWriter* writer);
		// 0x10948CB0: blends the drivers into the pose now, on the scratch stack, and turns the root motion into the
		// delta matrix
		void Evaluate();
		// 0x10948770: writes the pose blend nodes of the puppet where the cursors stand
		void BuildNodes(PuppetCounts* counts, PoseBlendCursors* cursors);
		// 0x10946D00: turns the root translation and rotation of the update into the root delta matrix
		void BuildRootDelta();
		// 0x10947910: updates the pose's matrices
		void UpdatePose();
		// 0x10947920: releases the drivers that were dropped
		void ReleaseRemoved();

		unsigned char unknown168[8];
		int mRefCount;                             // 0x170
		unsigned char unknown174[4];
		core::Name<core::CaseSensitiveKey> mName;  // 0x178
		int mUserData;                             // 0x180
		pure3d::Pose* mPoseObject;                // 0x184
		pure3d::PoseData* mPose;                   // 0x188
		float mTimeScale;                          // 0x18C
		unsigned int mDriverCount;                 // 0x190
		DriverEntry mEntries[MAX_DRIVERS];         // 0x194
		bool mSortNeeded;                          // 0x454
		unsigned char unknown455[3];
		// Counts the drivers that were dropped
		unsigned int mRemovedCount;                // 0x458
	};
}

#endif
