// The pose blend job (code/choreo/src/poseblendjob.cpp, path from the asserts; the unit runs from about 0x10957600 to
// 0x10959200). Names are guesses.
#include "code/choreo/poseblendjob.h"
#include "code/choreo/puppet.h"
#include "code/core/criticalsection.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x109580C0
	PoseBlendCursors::PoseBlendCursors()
	{
		cursor[0] = 0;
		cursor[1] = 0;
		cursor[2] = 0;
		cursor[3] = 0;
		cursor[4] = 0;
		cursor[5] = 0;
		cursor[6] = 0;
	}

	// FUNCTION: ENGINE 0x109580E0
	PoseBlendBuffers::PoseBlendBuffers()
	{
		mRootNodes = 0;
		mBlock[0] = 0;
		mBlock[1] = 0;
		mBlock[2] = 0;
		mBlock[3] = 0;
		mBlock[4] = 0;
		mBlock[5] = 0;
		mPuppetCount = 0;
		mRootNodeCount = 0;
		mUnknown28 = 0;
		mUnknown2C = 0;
		mUnknown30 = 0;
		mUnknown34 = 0;
		mLastNodeCount = 0;
		mUnknown3C = 0;
	}

	// FUNCTION: ENGINE 0x10958210
	bool PoseBlendBuffers::HasLastNodes()
	{
		return 0 < mLastNodeCount;
	}

	// FUNCTION: ENGINE 0x10958120
	// EQUIVALENT: the same cursors and steps in the same order; the engine keeps the buffers in edx and the counts in
	// esi (ours the reverse) and loads the blocks in another order
	void PoseBlendBuffers::Fill(Puppet** begin, Puppet** end)
	{
		PoseBlendCursors cursors;
		cursors.cursor[0] = (unsigned char*)mRootNodes;
		cursors.cursor[3] = mBlock[0];
		cursors.cursor[4] = mBlock[1];
		cursors.cursor[1] = mBlock[2];
		cursors.cursor[5] = mBlock[3];
		cursors.cursor[2] = mBlock[4];
		cursors.cursor[6] = mBlock[5];
		PuppetCounts* counts = mCounts;
		for (; begin < end; begin++, counts++)
		{
			(*begin)->BuildNodes(counts, &cursors);
			cursors.cursor[0] += (0 < counts->count[0]) * 0x30;
			cursors.cursor[1] += (0 < counts->count[2]) * 0x10;
			cursors.cursor[2] += (0 < counts->count[3]) * 0x10;
			cursors.cursor[3] += counts->count[0] * 0x70;
			cursors.cursor[4] += counts->count[1] * 0x20;
			cursors.cursor[5] += counts->count[2] * 0x10;
			cursors.cursor[6] += counts->count[3] * 0x10;
		}
	}

	// FUNCTION: ENGINE 0x10958D50
	void PoseBlendBuffers::ApplyRootNodes()
	{
		BlendRootNode* node = mRootNodes;
		for (unsigned int i = 0; i < mRootNodeCount; i++)
		{
			node->Apply();
			node++;
		}
	}

	// FUNCTION: ENGINE 0x10959150
	void UpdatePuppets(float dt, Puppet** begin, Puppet** end)
	{
		for (; begin < end; begin++)
		{
			(*begin)->Update(dt);
		}
	}

	// FUNCTION: ENGINE 0x10958DA0
	void RunPoseBlendJob(PoseBlendJob* job)
	{
		Puppet** begin = job->mBegin;
		Puppet** end = job->mEnd;
		UpdatePuppets(job->mDt, begin, end);
		PoseBlendBuffers buffers;
		core::CriticalSectionEnter(job->mBufferLock);
		buffers.Count(begin, end);
		core::CriticalSectionLeave(job->mBufferLock);
		buffers.Fill(begin, end);
		buffers.ApplyRootNodes();
		buffers.Apply10958220();
		if (buffers.HasLastNodes())
		{
			Unknown10959180(begin, end);
			buffers.Apply10958250();
		}
		for (Puppet** it = begin; it < end; it++)
		{
			Puppet* puppet = *it;
			puppet->BuildRootDelta();
			puppet->UpdatePose();
		}
		core::CriticalSectionEnter(job->mResultLock);
		Unknown109591B0(begin, end);
		core::CriticalSectionLeave(job->mResultLock);
	}
}
