// The pose blend job of the puppets (code/choreo/src/poseblendjob.cpp, path from the asserts): a batch of puppets is
// updated, the blend nodes of all their drivers are laid out in shared buffers and applied. Only what the job's
// control flow touches; names are guesses.
#ifndef CHOREO_POSEBLENDJOB_H
#define CHOREO_POSEBLENDJOB_H

namespace choreo
{
	class Puppet;

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
