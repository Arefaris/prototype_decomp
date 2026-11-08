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

	// FUNCTION: ENGINE 0x106DD8F0
	void JointMask::SetAll()
	{
		unsigned int count = (jointCount + 31) >> 5;
		for (unsigned int i = 0; i < count; i++)
		{
			words[i] = 0xFFFFFFFF;
		}
	}

	// FUNCTION: ENGINE 0x106DD910
	void JointMask::SetWord(unsigned int index, unsigned int value)
	{
		words[index] = value;
	}

	// FUNCTION: ENGINE 0x106DD950
	math::Quaternion* SkeletonData::GetLimbRotation(unsigned int index)
	{
		return mLimbRotations + index;
	}

	// FUNCTION: ENGINE 0x106DD960
	math::Vector4* SkeletonData::GetLimbTranslation(unsigned int index)
	{
		return mLimbTranslations + index;
	}

	// FUNCTION: ENGINE 0x106DD970
	Skeleton::Partition* Skeleton::GetPartition(unsigned int index)
	{
		return partitions + index;
	}

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
		mData.BuildBindPose();
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

	// FUNCTION: ENGINE 0x106DDB60
	void Unknown106DDB60()
	{
		if (gRootPartition.joints)
		{
			delete gRootPartition.joints;
		}
		gRootPartition.joints = 0;
		core::Name<core::CaseSensitiveKey> empty(0, 1);
		gRootPartition.name = empty;
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
	// NONMATCHING: the engine zeroes the empty name before constructing it, keeps the name in ebx and walks the partitions by index (27.7 %)
#ifdef NONMATCHING
	Skeleton::Partition* Skeleton::FindPartition(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned int i = 0;
		core::Name<core::CaseSensitiveKey> empty(0, 1);
		if (name == empty || name == gRootPartition.name)
		{
			return &gRootPartition;
		}
		unsigned int count = partitionCount;
		if (i < count)
		{
			Partition* partition = partitions;
			do
			{
				if (partition->name == name)
				{
					return partition;
				}
				i++;
				partition++;
			}
			while (i < count);
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
