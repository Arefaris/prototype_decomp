// The pose blend job of the puppets (code/choreo/src/poseblendjob.cpp, path from the asserts): a batch of puppets is
// updated, the blend nodes of all their drivers are laid out in shared buffers and applied. Only what the job's
// control flow touches; names are guesses.
#ifndef CHOREO_POSEBLENDJOB_H
#define CHOREO_POSEBLENDJOB_H

#include "code/pure3d/channel.h"

namespace choreo
{
	class Puppet;

	// The clip a driver plays, sampled over the frames of one step: the animation its channels come from, the two
	// frames and the joint arrays they are read into. Its methods are in the unit of the job and only declared here.
	class PoseBlendSample
	{
	public:
		// 0x109577A0: the frames to sample, how fast and in which direction
		void Set(float first, float rate, float from, float to, bool forward);

		void* mAnimation;             // 0x00
		float mFirst;                 // 0x04
		float mRate;                  // 0x08
		pure3d::FrameTime mFrom;      // 0x0C
		pure3d::FrameTime mTo;        // 0x14
		bool mForward;                // 0x1C
		unsigned char unknown1D[3];
		void* mArrays;                // 0x20
	};

	// One driver's blend node: the sample it shows and the root motion it adds to the pose (0x70 bytes)
	class PoseBlendNode
	{
	public:
		// 0x109578B0: the node adds no root motion (bit 1 of the state of the two parts)
		void SetNone(bool rotation, bool translation);
		// 0x109578E0: the node shows the sample, taking the rotation and the translation from the sample or from the
		// identity (the state of each part is cleared, and full says whether the further channels take part)
		void Set(PoseBlendSample* sample, void* arrays, bool rotation, bool translation, bool full);
		// 0x109579B0 / 0x109579F0: the root rotation / translation the node adds
		void SetRotation(const math::Quaternion& rotation);
		void SetTranslation(const math::Vector& translation);
		// 0x10958A80: which joints of the pose the node is blended into
		void SetJoints(unsigned int first, unsigned int last, void* mask);

		unsigned char unknown0[0x70];
	};

	// How many blend nodes of each kind a puppet has (4 words per puppet)
	struct PuppetCounts
	{
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
	struct BlendRootNode
	{
		// 0x10958CD0
		void Apply();

		unsigned char unknown0[0x30];
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
		// 0x10958220 / 0x10958250
		void Apply10958220();
		void Apply10958250();
		// 0x10958210: whether there are nodes of the last kind
		bool HasLastNodes();

		PuppetCounts* mCounts;
		BlendRootNode* mRootNodes;
		unsigned char* mBlock[6];
		unsigned int mPuppetCount;
		unsigned int mRootNodeCount;
		unsigned int mUnknown28;
		unsigned int mUnknown2C;
		unsigned int mUnknown30;
		unsigned int mUnknown34;
		unsigned int mLastNodeCount;
		unsigned int mUnknown3C;
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
	// 0x10959180 / 0x109591B0
	void Unknown10959180(Puppet** begin, Puppet** end);
	void Unknown109591B0(Puppet** begin, Puppet** end);
	// 0x10958DA0: the task body
	void RunPoseBlendJob(PoseBlendJob* job);
}

#endif
