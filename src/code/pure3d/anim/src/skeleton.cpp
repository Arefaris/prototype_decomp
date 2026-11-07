// pure3d::Skeleton and its partitions (unit around 0x106DDA60 - 0x106DE090, the loader's neighbour; file name guessed
// from the class). Names are guesses.
#include <new>

#include "code/math/worldbounds.h"
#include "code/pure3d/pose.h"

namespace pure3d
{
	// 0x110C6C70: the partition the empty name and the name "root" stand for (a static of the engine; it has no members
	// of its own this unit sets up besides the name and the joint mask below)
	extern Skeleton::Partition gRootPartition;

	// FUNCTION: ENGINE 0x106DD9A0
	SkeletonDebugInfo::~SkeletonDebugInfo()
	{
		if (skeleton)
		{
			for (unsigned int i = 0; i < skeleton->mData.mJointCount; i++)
			{
				delete[] jointNames[i];
			}
			for (unsigned int i = 0; i < partitionCount; i++)
			{
				delete[] partitionNames[i];
			}
			for (unsigned int i = 0; i < skeleton->mData.mLimbCount; i++)
			{
				delete[] limbNames[i];
			}
			delete[] name;
			delete[] jointNames;
			delete[] partitionNames;
			delete[] limbNames;
		}
	}

	// FUNCTION: ENGINE 0x106DDA60
	int Skeleton::FindJoint(const core::Name<core::CaseSensitiveKey>& name) const
	{
		return const_cast<SkeletonData&>(mData).FindJoint(name);
	}

	// FUNCTION: ENGINE 0x106DDA70
	Pose* Skeleton::CreatePose(int kind)
	{
		return new Pose(this, kind);
	}

	// FUNCTION: ENGINE 0x106DDAA0
	void Skeleton::Finish()
	{
		mData.Finish();
	}

	// FUNCTION: ENGINE 0x106DDAB0
	void Skeleton::GetRestMatrix(unsigned int joint, math::Matrix* out)
	{
		out->Identity();
		out->FromQuaternion(mData.mLimbRotations[joint]);
		out->SetTranslation(static_cast<const math::Vector&>(mData.mLimbTranslations[joint]));
	}

	// FUNCTION: ENGINE 0x106DDB20
	Skeleton::Partition::Partition()
	{
		joints = 0;
	}

	// FUNCTION: ENGINE 0x106DDB40
	Skeleton::Partition::~Partition()
	{
		if (joints)
		{
			delete joints;
		}
	}

	// FUNCTION: ENGINE 0x106DDC20
	Skeleton::~Skeleton()
	{
		if (partitions)
		{
			delete[] partitions;
			partitions = 0;
		}
		if (debugInfo)
		{
			delete debugInfo;
		}
		mData.Free();
	}

	// FUNCTION: ENGINE 0x106DDC80
	// NONMATCHING: the engine zeroes the empty name before constructing it and keeps the name in ebx (20.1 %)
#ifdef NONMATCHING
	Skeleton::Partition* Skeleton::FindPartition(const core::Name<core::CaseSensitiveKey>& name)
	{
		core::Name<core::CaseSensitiveKey> empty(0, 1);
		if (name == empty || name == gRootPartition.name)
		{
			return &gRootPartition;
		}
		for (unsigned int i = 0; i < partitionCount; i++)
		{
			if (partitions[i].name == name)
			{
				return partitions + i;
			}
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x106DDF20
	// NONMATCHING: register allocation: the engine moves this to ebx and keeps the partition count in esi (15.3 %)
#ifdef NONMATCHING
	Skeleton::Skeleton(unsigned int jointCount, unsigned int newPartitionCount, unsigned int limbCount)
		: mData(jointCount, limbCount)
	{
		partitionCount = newPartitionCount;
		debugInfo = 0;
		if (newPartitionCount != 0)
		{
			partitions = new Partition[newPartitionCount];
			unsigned int words = (jointCount + 31) >> 5;
			for (unsigned int i = 0; i < newPartitionCount; i++)
			{
				unsigned int* mask = new unsigned int[words + 1];
				mask[0] = jointCount;
				for (unsigned int word = 0; word < words; word++)
				{
					mask[1 + word] = 0;
				}
				partitions[i].joints = (JointMask*)mask;
			}
		}
		else
		{
			partitions = 0;
		}
	}
#endif
}
