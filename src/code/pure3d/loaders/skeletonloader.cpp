// pure3d::SkeletonLoader: see the header. The file name is a guess.
#include <new>
#include <string.h>

#include "code/pure3d/loaders/skeletonloader.h"

#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/pose.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x106DE090
	// EQUIVALENT: the same calls, arguments, branches and memory accesses in the same order (15 %); the engine keeps
	// the reader in ebp and the skeleton in esi and caches the kind of the joint in a register where this compiler
	// reloads it, saves edi only inside the block, schedules the loads of the reader's stream differently and lays the
	// frame out in 4 bytes more
	void SkeletonLoader::LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
		content::LoadInventory* inventory)
	{
		char skeletonName[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(skeletonName, length, 1, 1);
			skeletonName[length] = 0;
		}
		unsigned int version;
		reader->Read(&version, 1, 4, 1);
		unsigned int jointCount;
		reader->Read(&jointCount, 1, 4, 1);
		unsigned int partitionCount;
		reader->Read(&partitionCount, 1, 4, 1);
		unsigned int limbCount;
		reader->Read(&limbCount, 1, 4, 1);
		unsigned int joints = jointCount;
		SkeletonDebugInfo* debugInfo = 0;
		if (jointCount >= 1)
		{
			Skeleton* skeleton = new Skeleton(joints, partitionCount, limbCount);
			skeleton->AddRef();
			JointMask* mask;
			{
				core::HeapScope scope(1);
				unsigned int wordCount = (joints + 31) >> 5;
				mask = (JointMask*)new unsigned int[wordCount + 1];
				mask->jointCount = joints;
				for (unsigned int i = 0; i < wordCount; i++)
				{
					mask->words[i] = 0;
				}
			}
			if (SkeletonLoader::sKeepNames)
			{
				debugInfo = new SkeletonDebugInfo(skeleton);
				debugInfo->name = core::StrCpy(new char[strlen(skeletonName) + 1], skeletonName);
				debugInfo->jointNames = new char*[joints];
				if (partitionCount > 0)
				{
					debugInfo->partitionCount = partitionCount;
					debugInfo->partitionNames = new char*[partitionCount];
				}
				if (limbCount > 0)
				{
					debugInfo->limbNames = new char*[limbCount];
				}
				skeleton->debugInfo = debugInfo;
			}
			unsigned int jointIndex = 0;
			unsigned int partitionIndex = 0;
			unsigned int limbIndex = 0;
			while (reader->HasChunk())
			{
				reader->BeginChunk();
				if (reader->GetChunkId() == 0x23001)
				{
					char jointName[0x100];
					{
						unsigned char length;
						reader->Read(&length, 1, 1, 1);
						reader->Read(jointName, length, 1, 1);
						jointName[length] = 0;
					}
					skeleton->mData.mNames[jointIndex].SetText(jointName);
					unsigned int parent;
					reader->Read(&parent, 1, 4, 1);
					skeleton->mData.mParents[jointIndex] = (unsigned short)parent;
					reader->Read(skeleton->mData.mFileMatrices + jointIndex, 0x10, 4, 1);
					if (version == 1)
					{
						math::Vector first;
						reader->Read(&first, 3, 4, 1);
						math::Vector second;
						reader->Read(&second, 3, 4, 1);
						math::Vector third;
						reader->Read(&third, 3, 4, 1);
						math::Vector fourth;
						reader->Read(&fourth, 3, 4, 1);
						unsigned short kind;
						reader->Read(&kind, 1, 2, 1);
						int enabled;
						reader->Read(&enabled, 1, 4, 1);
						bool flag;
						if (enabled == 0 || kind != 1)
						{
							flag = false;
						}
						else
						{
							flag = true;
						}
						math::Vector4* destination = skeleton->mData.mUnknown10 + jointIndex;
						destination->x = first.x;
						destination->y = first.y;
						destination->z = first.z;
						destination = skeleton->mData.mScales + jointIndex;
						destination->x = second.x;
						destination->y = second.y;
						destination->z = second.z;
						destination = skeleton->mData.mUnknown18 + jointIndex;
						destination->x = third.x;
						destination->y = third.y;
						destination->z = third.z;
						destination = skeleton->mData.mUnknown1C + jointIndex;
						destination->x = fourth.x;
						destination->y = fourth.y;
						destination->z = fourth.z;
						skeleton->mData.mUnknown3C[jointIndex] = kind;
						skeleton->mData.mUnknown40[jointIndex] = flag;
						skeleton->mData.mUnknown10[jointIndex].w = 0.0f;
						skeleton->mData.mScales[jointIndex].w = 1.0f;
						skeleton->mData.mUnknown18[jointIndex].w = 0.0f;
						skeleton->mData.mUnknown1C[jointIndex].w = 0.0f;
					}
					else
					{
						math::Vector4* destination = skeleton->mData.mUnknown10 + jointIndex;
						destination->z = 0.0f;
						destination->y = 0.0f;
						destination->x = 0.0f;
						destination = skeleton->mData.mScales + jointIndex;
						destination->x = 1.0f;
						destination->y = 1.0f;
						destination->z = 1.0f;
						destination->w = 1.0f;
						destination = skeleton->mData.mUnknown18 + jointIndex;
						destination->z = 0.0f;
						destination->y = 0.0f;
						destination->x = 0.0f;
						destination = skeleton->mData.mUnknown1C + jointIndex;
						destination->z = 0.0f;
						destination->y = 0.0f;
						destination->x = 0.0f;
						skeleton->mData.mUnknown3C[jointIndex] = 0;
						skeleton->mData.mUnknown40[jointIndex] = 0;
					}
					if (debugInfo != 0)
					{
						debugInfo->jointNames[jointIndex] = core::StrCpy(new char[strlen(jointName) + 1], jointName);
					}
					jointIndex++;
				}
				else if (reader->GetChunkId() == 0x23002)
				{
					Skeleton::Partition* partition = skeleton->partitions + partitionIndex;
					char partitionName[0x100];
					{
						unsigned char byte;
						reader->Read(&byte, 1, 1, 1);
						unsigned int length = byte;
						reader->Read(partitionName, length, 1, 1);
						partitionName[length] = 0;
					}
					partition->name.SetText(partitionName);
					unsigned int count;
					reader->Read(&count, 1, 4, 1);
					for (unsigned int i = 0; i < count; i++)
					{
						unsigned int word;
						reader->Read(&word, 1, 4, 1);
						partition->joints->words[i] = word;
					}
					if (debugInfo != 0)
					{
						debugInfo->partitionNames[partitionIndex] = core::StrCpy(
							new char[strlen(partitionName) + 1], partitionName);
					}
					partitionIndex++;
				}
				else if (reader->GetChunkId() == 0x23003)
				{
					SkeletonLimb* limb = skeleton->mData.mLimbs + limbIndex;
					char limbName[0x100];
					reader->ReadString(limbName);
					limb->name.SetText(limbName);
					limb->joints[0] = ReadWord(reader);
					limb->joints[1] = ReadWord(reader);
					limb->joints[2] = ReadWord(reader);
					unsigned int* targets[3];
					unsigned int wordCount = (mask->jointCount + 31) >> 5;
					for (unsigned int i = 0; i < wordCount; i++)
					{
						mask->words[i] = 0;
					}
					unsigned int count;
					reader->Read(&count, 1, 4, 1);
					unsigned int* word = mask->words;
					for (unsigned int remaining = count; remaining > 0; remaining--)
					{
						*word++ = ReadWord(reader);
					}
					targets[0] = &limb->joints[0];
					targets[1] = &limb->joints[1];
					targets[2] = &limb->joints[2];
					unsigned int bitCount = mask->jointCount;
					unsigned int found = 0;
					for (unsigned int bit = 0; bit < bitCount; bit++)
					{
						if (bit >= jointCount || found >= 3)
						{
							break;
						}
						if ((mask->words[bit >> 5] & (1 << (bit & 0x1F))) != 0)
						{
							if (*targets[found] >= jointCount)
							{
								*targets[found] = bit;
							}
							found++;
						}
					}
					if (debugInfo != 0)
					{
						debugInfo->limbNames[limbIndex] = core::StrCpy(new char[strlen(limbName) + 1], limbName);
					}
					limbIndex++;
				}
				reader->EndChunk();
			}
			delete mask;
			skeleton->Finish();
			*object = skeleton;
			*name = content::ObjectName(skeletonName, 1);
		}
	}
}
