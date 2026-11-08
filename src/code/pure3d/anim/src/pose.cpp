// pure3d::Pose (unit around 0x106DD620 - 0x106DD880; file name guessed from the class). Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/pose.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x106DD620
	// NONMATCHING: the engine keeps the base's vftable and zero stores in front of the skeleton store and loads both arguments first; ours schedules the stores late (77.3 %)
#ifdef NONMATCHING
	Pose::Pose(Skeleton* skeleton, int spaces) : mSkeleton(skeleton), mData(&skeleton->mData, spaces)
	{
		mUpdateCount = 0;
		mSkeleton->AddRef();
	}
#endif

	// FUNCTION: ENGINE 0x106DD6E0
	void Pose::Update()
	{
		mData.Update();
		mUpdateCount++;
	}

	// FUNCTION: ENGINE 0x106DD700
	void Pose::UpdateLocal()
	{
		mData.UpdateLocal();
	}

	// FUNCTION: ENGINE 0x106DD720
	void Pose::UpdateWorldRange(unsigned int first, unsigned int last)
	{
		mData.UpdateWorldRange(first, last);
	}

	// FUNCTION: ENGINE 0x106DD730
	void Pose::Unknown106DD730()
	{
		mData.UpdateSkin();
	}

	// FUNCTION: ENGINE 0x106DD740
	void Pose::GetJointMatrix(int joint, math::Matrix* matrix)
	{
		mData.GetJointMatrix(joint, matrix);
	}

	// FUNCTION: ENGINE 0x106DD750
	void Pose::GetJointPosition(int joint, math::Vector* position)
	{
		mData.GetJointPosition(joint, position);
	}

	// FUNCTION: ENGINE 0x106DD760
	void Pose::Unknown106DD760()
	{
		mData.SetRestPose();
		mUpdateCount++;
	}

	// FUNCTION: ENGINE 0x106DD780
	void Pose::CopyFrom(Pose* other)
	{
		mData.CopyFrom(&other->mData);
	}

	// FUNCTION: ENGINE 0x106DD7A0
	void Pose::CopyMatchingFrom(Pose* other)
	{
		mData.CopyMatchingFrom(&other->mData);
	}

	// FUNCTION: ENGINE 0x106DD7C0
	void Pose::CopyStateFrom(Pose* other)
	{
		mData.CopyMatricesFrom(&other->mData);
	}

	// FUNCTION: ENGINE 0x106DD7E0
	void Pose::Blend(Pose* other, float t, bool root)
	{
		mData.Blend(&other->mData, t, root);
	}

	// FUNCTION: ENGINE 0x106DD800
	Pose::~Pose()
	{
		core::SafeRelease(mSkeleton);
		mData.FreeMemory();
	}

	// FUNCTION: ENGINE 0x106DD830
	Pose* Pose::CreateInstance(int kind)
	{
		Pose* pose = mSkeleton->CreatePose(kind);
		pose->CopyFrom(this);
		return pose;
	}
}
