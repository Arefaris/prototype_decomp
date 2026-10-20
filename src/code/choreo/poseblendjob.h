// The pose blend job of the puppets (code/choreo/src/poseblendjob.cpp, path from the asserts): a batch of puppets is
// updated, the blend nodes of all their drivers are laid out in shared buffers and applied. Only what the job's
// control flow touches; names are guesses.
#ifndef CHOREO_POSEBLENDJOB_H
#define CHOREO_POSEBLENDJOB_H

#include "code/math/matrix.h"
#include "code/math/quaternion.h"
#include "code/math/vector.h"
#include "code/pure3d/channel.h"
#include "code/pure3d/posedata.h"

namespace choreo
{
	class Puppet;
	class SampleChannels;
	class PoseBlendNode;
	class StrafeAdjustRootDriver;
	class IKDriver;
	class JointLockDriver;

	// The clip a driver plays, sampled over the frames of one step: the channels of its animation, the two frames
	// and the direction they are read in. Its methods are in the unit of the job.
	class PoseBlendSample
	{
	public:
		// 0x109577A0: the weight curve's scale and bias, the frame and the one before it, and the direction
		void Set(float scale, float bias, float frame, float previousFrame, bool forward);
		// 0x109577F0 / 0x10957820 / 0x10957850: what the channels give for the root over the frames of the sample
		// (the rotation and translation of the step, and the further root value; the last says whether there is one)
		int GetRootRotation(math::Quaternion* out);
		bool GetRootTranslation(math::Vector* out);
		bool GetRootScale(math::Vector* out);
		// 0x109582E0 / 0x10958360 / 0x10958400: lays the channels over a value, the joints of a pose, or the matrices
		// of a pose, each moving towards them by the weight that elapsed time t gives
		void BlendValue(float* value, float t);
		void BlendJoints(pure3d::JointArrays* arrays, unsigned int first, unsigned int last, const pure3d::JointMask* mask,
			const pure3d::SkeletonData* rest, bool full, float t);
		void BlendMatrices(math::Matrix* matrices, const pure3d::JointMask* mask, const pure3d::SkeletonData* skeleton,
			float t);
		// 0x10958770: the root motion of the step, blended into the root matrix (its rotation and translation by
		// weight) and the first scale of the arrays (by scaleWeight)
		void BlendRoot(math::Matrix* root, pure3d::JointArrays* arrays, bool rotation, bool translation, bool scale,
			float weight, float scaleWeight);

		SampleChannels* mChannels;    // 0x00
		float mScale;                 // 0x04
		float mBias;                  // 0x08
		pure3d::FrameTime mFrame;     // 0x0C
		pure3d::FrameTime mPreviousFrame; // 0x14
		bool mForward;                // 0x1C
		unsigned char unknown1D[3];
	};

	// A mask of up to 96 joints (0x10 bytes): the joint count and the bits; no joints at all means every joint
	struct PoseJointMask
	{
		// 0x109585F0: takes the joint count and the bits of a mask
		void Assign(const pure3d::JointMask* mask);

		unsigned int jointCount;
		unsigned int words[3];
	};

	// Where a node reads its values from: the sample and the arrays it is read into (a sampled node), or the layout of
	// a pose (a node that shows a pose)
	union PoseBlendSource
	{
		struct
		{
			PoseBlendSample* sample;
			pure3d::JointArrays* arrays;
		} sampled;
		pure3d::PoseLayout pose;
	};

	// One driver's blend node: what it shows and the root motion it adds to the pose (0x70 bytes)
	class PoseBlendNode
	{
	public:
		// 0x109578B0: the node adds no root motion (bit 1 of the state of the two parts)
		void SetNone(bool rotation, bool translation);
		// 0x109578E0: the node shows the sample, taking the rotation and the translation from the sample or from the
		// identity (the state of each part is cleared, and full says whether the further channels take part)
		void Set(PoseBlendSample* sample, void* arrays, bool rotation, bool translation, bool full);
		// 0x10957870: the weights of the node's four kinds of motion
		void SetWeights(float a, float b, float c, float d);
		// 0x109578A0: which parts of the root the node moves (bit 0 the translation, bit 1 the rotation)
		void SetRootParts(unsigned int parts);
		// 0x10957920: a single joint, taken from a rotation and a translation
		void SetJoint(unsigned int joint, const math::Quaternion& rotation, const math::Vector& translation);
		// 0x10957970: the node shows a pose, restricted to the channels in channels
		void SetPose(pure3d::PoseData* pose, unsigned int channels);
		// 0x10957990
		void SetMode3();
		// 0x109579A0 / 0x109579B0: the root rotation the node adds: none / this one
		void SetNoRotation();
		void SetRotation(const math::Quaternion& rotation);
		// 0x109579E0 / 0x109579F0: the same for the root translation
		void SetNoTranslation();
		void SetTranslation(const math::Vector& translation);
		// 0x10957A10: no root rotation or translation
		void SetNoRoot();
		// 0x10957A20: the node adds nothing
		void SetEmpty();
		// 0x10957A40: moves the root joint of the arrays towards the node's root translation and rotation by the
		// first weight (as far as the root parts say)
		void BlendRootJoint(pure3d::JointArrays* arrays, unsigned int joint);
		// 0x10957B20: moves the joints first to last of the arrays towards the pose the node shows, for every kind
		// of value the channels say, by the first weight
		void BlendJoints(pure3d::JointArrays* arrays);
		// 0x10957E10: moves the rotations and translations of the joints first to last towards another pose's
		void BlendPose(pure3d::JointArrays* arrays, pure3d::PoseData* pose);
		// 0x10958A80: which joints of the pose the node is blended into
		void SetJoints(unsigned int first, unsigned int last, void* mask);

		PoseBlendSource mSource;       // 0x00
		unsigned int mChannels;        // 0x10
		int mMode;                     // 0x14
		unsigned int mFirstJoint;      // 0x18
		unsigned int mLastJoint;       // 0x1C
		unsigned int mRootParts;       // 0x20
		PoseJointMask mMask;           // 0x24
		math::Quaternion mRotation;    // 0x34
		math::Vector mTranslation;     // 0x44
		int mRotationState;            // 0x50
		int mTranslationState;         // 0x54
		bool mFull;                    // 0x58
		unsigned char unknown59[3];
		float mWeights[4];             // 0x5C
		unsigned char unknown6C[4];
	};

	// How many blend nodes of each kind a puppet has (4 words per puppet)
	struct PuppetCounts
	{
		// 0x10946CB0 - 0x10946CF0: the first count, whether the first / the third / the fourth is not zero, the next
		// puppet's counts
		unsigned int GetFirst() const;
		int HasFirst() const;
		int HasThird() const;
		int HasFourth() const;
		PuppetCounts* GetNext();

		unsigned int count[4];
	};

	// Where the next puppet's nodes of each kind go in the buffers
	struct PoseBlendCursors
	{
		// 0x109580C0
		PoseBlendCursors();

		unsigned char* cursor[7];
	};

	// A blend node of a puppet's root (0x30 bytes)
	struct __declspec(align(16)) BlendRootNode
	{
		// 0x10958CD0
		void Apply();

		PoseBlendNode* mBegin;             // 0x00
		PoseBlendNode* mEnd;               // 0x04
		pure3d::PoseLayout mLayout;        // 0x08
		pure3d::SkeletonLimbInfo mLimbInfo;// 0x18
		Puppet* mPuppet;                   // 0x20
		unsigned char unknown24[0xC];
	};

	// The drivers' own part of the blend that is not a node: they are applied to the pose by tasks. Both kinds of task
	// are 0x10 bytes; the tasks of a puppet are listed in a range, which carries the pose and the puppet to apply
	// them with
	// (the drivers' classes are in choreo/drivers.h)

	// A root adjustment to apply
	class PoseBlendRootTask
	{
	public:
		// 0x10957F80: the driver to apply
		void SetDriver(StrafeAdjustRootDriver* driver);
		// 0x10957F60: the two weights
		void SetWeights(float first, float second);
		// 0x10957F90
		void Apply(Puppet* puppet, pure3d::PoseData* pose);

		int mKind;                         // 0x00
		StrafeAdjustRootDriver* mDriver;   // 0x04
		float mFirst;                      // 0x08
		float mSecond;                     // 0x0C
	};

	// A limb task to apply: the driver is an IKDriver or a JointLockDriver, as the kind says
	class PoseBlendLimbTask
	{
	public:
		// 0x10958010 / 0x10958020: the driver to apply
		void SetIK(IKDriver* driver);
		void SetJointLock(JointLockDriver* driver);
		// 0x10957FF0: the two weights
		void SetWeights(float first, float second);
		// 0x10958030
		void Apply(Puppet* puppet, pure3d::PoseData* pose);

		int mKind;                         // 0x00
		void* mDriver;                     // 0x04
		float mFirst;                      // 0x08
		float mSecond;                     // 0x0C
	};

	// The root tasks of one puppet
	struct PoseBlendRootRange
	{
		// 0x10957FC0
		void Apply();

		PoseBlendRootTask* mBegin;
		PoseBlendRootTask* mEnd;
		pure3d::PoseData* mPose;
		Puppet* mPuppet;
	};

	// The limb tasks of one puppet
	struct PoseBlendLimbRange
	{
		// 0x10958090
		void Apply();

		PoseBlendLimbTask* mBegin;
		PoseBlendLimbTask* mEnd;
		pure3d::PoseData* mPose;
		Puppet* mPuppet;
	};

	// The buffers of the blend nodes of a batch of puppets: one block carved up by kind, each kind with its total
	class PoseBlendBuffers
	{
	public:
		// 0x109580E0: no blocks and no counts yet (the count table is not touched)
		PoseBlendBuffers();
		// 0x10958490: counts the nodes of the puppets and carves the blocks
		void Count(Puppet** begin, Puppet** end);
		// 0x10958120: lets every puppet write its nodes into the buffers
		void Fill(Puppet** begin, Puppet** end);
		// 0x10958D50: applies the root nodes
		void ApplyRootNodes();
		// 0x10958220 / 0x10958250: apply the root tasks / the limb tasks of every puppet
		void Apply10958220();
		void Apply10958250();
		// 0x109581F0 / 0x10958200 / 0x10958210: whether there are root nodes, root task ranges, limb task ranges
		bool HasRootNodes();
		bool HasRootTasks();
		bool HasLastNodes();

		PuppetCounts* mCounts;
		BlendRootNode* mRootNodes;
		unsigned char* mBlock[6];
		unsigned int mPuppetCount;
		unsigned int mRootNodeCount;
		unsigned int mNodeCount;
		unsigned int mSampleCount;
		unsigned int mRootRangeCount;
		unsigned int mRootTaskCount;
		unsigned int mLimbRangeCount;
		unsigned int mLimbTaskCount;
	};

	// What the job task is given: the puppets of the batch, the step, and the two locks around the shared parts
	struct PoseBlendJob
	{
		unsigned int unknown0;
		Puppet** mBegin;
		Puppet** mEnd;
		float mDt;
		void* mBufferLock;
		void* mResultLock;
	};

	// 0x10959150: Puppet::Update of each puppet of the batch
	void UpdatePuppets(float dt, Puppet** begin, Puppet** end);
	// 0x109591E0: Update, Evaluate, UpdatePose and ReleaseRemoved of each puppet of the batch in turn
	void UpdatePuppetsSerial(float dt, Puppet** begin, Puppet** end);
	// 0x10959180 / 0x109591B0
	void Unknown10959180(Puppet** begin, Puppet** end);
	void Unknown109591B0(Puppet** begin, Puppet** end);
	// 0x10958DA0: the task body
	void RunPoseBlendJob(PoseBlendJob* job);
}

#endif
