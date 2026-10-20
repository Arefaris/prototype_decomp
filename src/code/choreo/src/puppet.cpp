// choreo::Puppet (unit around 0x10946C00 - 0x10949300; file name guessed from the class). Names are guesses.
#include "code/choreo/puppet.h"
#include "code/choreo/poseblendjob.h"
#include "code/core/heap.h"
#include "code/pure3d/posedata.h"
#include "code/ravenphysics/common/stackallocator.h"
#include <algorithm>
#include <string.h>

// The sort of the drivers is the toolchain's <algorithm> for DriverEntry*; the unit keeps every instance of it as a COMDAT
// function of its own, and the compiler reproduces each one
// FUNCTION: ENGINE 0x10947AA0
template choreo::DriverEntry* std::_Checked_base<choreo::DriverEntry*>(choreo::DriverEntry*&, std::_Unchanged_checked_iterator_base_type_tag);

// FUNCTION: ENGINE 0x10947AB0
template std::pair<choreo::DriverEntry*, choreo::DriverEntry*>::pair(choreo::DriverEntry* const&, choreo::DriverEntry* const&);

// FUNCTION: ENGINE 0x10947AD0
template int* std::_Dist_type<choreo::DriverEntry*>(choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10947AE0
template choreo::DriverEntry* std::_Val_type<choreo::DriverEntry*>(choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10947AF0
template void std::swap<choreo::DriverEntry>(choreo::DriverEntry&, choreo::DriverEntry&);

// FUNCTION: ENGINE 0x10947B30
template void std::_Push_heap<choreo::DriverEntry*, int, choreo::DriverEntry>(choreo::DriverEntry*, int, int, choreo::DriverEntry);

// FUNCTION: ENGINE 0x10947BA0
template std::random_access_iterator_tag std::_Iter_random<choreo::DriverEntry*, choreo::DriverEntry*>(choreo::DriverEntry* const&, choreo::DriverEntry* const&);

// FUNCTION: ENGINE 0x10947BB0
template std::_Nonscalar_ptr_iterator_tag std::_Ptr_cat<choreo::DriverEntry*, choreo::DriverEntry*>(choreo::DriverEntry*&, choreo::DriverEntry*&);

// FUNCTION: ENGINE 0x10947BC0
template choreo::DriverEntry* std::_Copy_backward_opt<choreo::DriverEntry*, choreo::DriverEntry*, std::forward_iterator_tag>(choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry*, std::forward_iterator_tag, std::_Nonscalar_ptr_iterator_tag, std::_Range_checked_iterator_tag);

// FUNCTION: ENGINE 0x109481A0
template choreo::DriverEntry* std::_Checked_base<choreo::DriverEntry*>(choreo::DriverEntry*&);

// FUNCTION: ENGINE 0x109481B0
template void std::iter_swap<choreo::DriverEntry*, choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x109481F0
template void std::_Med3<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x109482A0
template void std::_Adjust_heap<choreo::DriverEntry*, int, choreo::DriverEntry>(choreo::DriverEntry*, int, int, choreo::DriverEntry);

// FUNCTION: ENGINE 0x10948360
template choreo::DriverEntry* std::_Copy_backward_opt<choreo::DriverEntry*, choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry*, std::random_access_iterator_tag, std::_Nonscalar_ptr_iterator_tag, std::_Range_checked_iterator_tag);

// FUNCTION: ENGINE 0x109483B0
template void std::_Pop_heap<choreo::DriverEntry*, int, choreo::DriverEntry>(choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry, int*);

// FUNCTION: ENGINE 0x109485C0
template void std::_Median<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948660
template void std::_Make_heap<choreo::DriverEntry*, int, choreo::DriverEntry>(choreo::DriverEntry*, choreo::DriverEntry*, int*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x109486D0
template choreo::DriverEntry* stdext::unchecked_copy_backward<choreo::DriverEntry*, choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948700
template void std::_Pop_heap_0<choreo::DriverEntry*, choreo::DriverEntry>(choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948870
template std::pair<choreo::DriverEntry*, choreo::DriverEntry*> std::_Unguarded_partition<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948B40
template void std::make_heap<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948B80
template void std::_Insertion_sort1<choreo::DriverEntry*, choreo::DriverEntry>(choreo::DriverEntry*, choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948C70
template void std::pop_heap<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948DE0
template void std::_Insertion_sort<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948E00
template void std::_Sort_heap<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948EA0
template void std::sort_heap<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*);

// FUNCTION: ENGINE 0x10948EB0
template void std::_Sort<choreo::DriverEntry*, int>(choreo::DriverEntry*, choreo::DriverEntry*, int);

// FUNCTION: ENGINE 0x10949010
template void std::sort<choreo::DriverEntry*>(choreo::DriverEntry*, choreo::DriverEntry*);

// The pose is assigned as its reference counted base
// FUNCTION: ENGINE 0x10947A70 ; core::RefAssign<classpure3d::LockableRefCounted>
template void core::RefAssign<pure3d::LockableRefCounted>(pure3d::LockableRefCounted*&, pure3d::LockableRefCounted*);

namespace choreo
{
	// FUNCTION: ENGINE 0x10946D30 ; choreo::PuppetState::~PuppetState
#pragma inline_depth(0)
	void KeepPuppetStateDestructor(PuppetState* state)
	{
		state->~PuppetState();
	}
#pragma inline_depth()

	// FUNCTION: ENGINE 0x10946C30
	int Puppet::IsEmpty() const
	{
		if (mDriverCount != 0 && mPose != 0)
		{
			return 0;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10946C50
	bool Driver::GetFlag0() const
	{
		return mFlag0;
	}

	// FUNCTION: ENGINE 0x10946C60
	bool Driver::GetFlag1() const
	{
		return mFlag1;
	}

	// FUNCTION: ENGINE 0x10946C70
	bool Driver::GetFlag2() const
	{
		return mFlag2;
	}

	// FUNCTION: ENGINE 0x10946C80
	bool Driver::GetFlag3() const
	{
		return mFlag3;
	}

	// FUNCTION: ENGINE 0x10946C90
	bool Driver::GetFlag4() const
	{
		return mFlag4;
	}

	// FUNCTION: ENGINE 0x10946CA0
	bool Driver::GetFlag5() const
	{
		return mFlag5;
	}

	// FUNCTION: ENGINE 0x10946CB0
	unsigned int PuppetCounts::GetFirst() const
	{
		return count[0];
	}

	// FUNCTION: ENGINE 0x10946CC0
	int PuppetCounts::HasFirst() const
	{
		return count[0] > 0;
	}

	// FUNCTION: ENGINE 0x10946CD0
	int PuppetCounts::HasThird() const
	{
		return count[2] > 0;
	}

	// FUNCTION: ENGINE 0x10946CE0
	int PuppetCounts::HasFourth() const
	{
		return count[3] > 0;
	}

	// FUNCTION: ENGINE 0x10946CF0
	PuppetCounts* PuppetCounts::GetNext()
	{
		return this + 1;
	}

	// FUNCTION: ENGINE 0x10946D00
	void Puppet::BuildRootDelta()
	{
		math::Quaternion rotation;
		rotation.FromMatrix(mRootDelta);
		rotation.NormalizeFast();
		mRootDelta.FromQuaternion(rotation);
	}

	// FUNCTION: ENGINE 0x10946D40
	void Puppet::AddRef()
	{
		mRefCount++;
	}

	// FUNCTION: ENGINE 0x10946D50
	PuppetState& PuppetState::operator=(const PuppetState& other)
	{
		mRootDelta = other.mRootDelta;
		mUnknown40 = other.mUnknown40;
		mLimbs = other.mLimbs;
		mUnknown15C = other.mUnknown15C;
		mUnknown160 = other.mUnknown160;
		mUnknown164 = other.mUnknown164;
		return *this;
	}

	// FUNCTION: ENGINE 0x10946DA0
	pure3d::Skeleton* Puppet::GetSkeleton()
	{
		return mPoseObject->mSkeleton;
	}

	// FUNCTION: ENGINE 0x10946DB0
	pure3d::Skeleton* Puppet::GetSkeleton() const
	{
		return mPoseObject->mSkeleton;
	}

	// FUNCTION: ENGINE 0x10946DC0
	DriverEntry* Puppet::FindEntry(Driver* driver)
	{
		for (unsigned int i = 0; i < mDriverCount; i++)
		{
			DriverEntry* entry = &mEntries[i];
			if (entry->mDriver == driver)
			{
				return entry;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10946DF0
	const DriverEntry* Puppet::FindEntry(Driver* driver) const
	{
		for (unsigned int i = 0; i < mDriverCount; i++)
		{
			const DriverEntry* entry = &mEntries[i];
			if (entry->mDriver == driver)
			{
				return entry;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10946E20
	bool DriverEntry::operator<(const DriverEntry& other) const
	{
		if (mPriority > other.mPriority)
		{
			return true;
		}
		if (mPriority < other.mPriority)
		{
			return false;
		}
		if (mFirstJoint < other.mFirstJoint)
		{
			return true;
		}
		if (mFirstJoint > other.mFirstJoint)
		{
			return false;
		}
		if (mLastJoint > other.mLastJoint)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10946E60
	bool Puppet::AddDriver(Driver* driver, float lifetime, int priority, float weight, float blendIn, float blendOut)
	{
		if (!AcceptDriver(driver, this, false))
		{
			driver->Unbind();
			return false;
		}
		DriverEntry* entry = &mEntries[mDriverCount];
		entry->mDriver = driver;
		driver->AddRef();
		entry->mType = driver->mType;
		entry->mLifetime = lifetime;
		entry->mEndless = lifetime < 0.0f;
		entry->mFirstJoint = driver->GetFirstJoint();
		entry->mLastJoint = driver->GetLastJoint();
		entry->mPriority = priority;
		if (weight < 0.0f)
		{
			entry->mWeight = 0.0f;
		}
		else
		{
			entry->mWeight = weight;
		}
		entry->mBlendIn = blendIn;
		entry->mBlendOut = blendOut;
		entry->mFade = 0.0f;
		mDriverCount++;
		mSortNeeded = true;
		return true;
	}

	// FUNCTION: ENGINE 0x10946F30
	bool Puppet::SetDriver(Driver* driver, float lifetime, int priority, float weight, float blendIn, float blendOut,
		float fade)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry != 0)
		{
			entry->mLifetime = lifetime;
			entry->mEndless = lifetime < 0.0f;
			entry->mFirstJoint = driver->GetFirstJoint();
			entry->mLastJoint = driver->GetLastJoint();
			entry->mPriority = priority;
			if (weight < 0.0f)
			{
				entry->mWeight = 0.0f;
			}
			else
			{
				entry->mWeight = weight;
			}
			entry->mBlendIn = blendIn;
			entry->mBlendOut = blendOut;
			if (0.0f <= fade)
			{
				entry->mFade = fade;
			}
			mSortNeeded = true;
			return true;
		}
		return AddDriver(driver, lifetime, priority, weight, blendIn, blendOut);
	}

	// FUNCTION: ENGINE 0x10947010
	bool Puppet::RemoveDriver(Driver* driver, bool immediately)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		if (immediately)
		{
			driver->Unbind();
			driver->Release();
			mDriverCount--;
			int index = entry - mEntries;
			memmove(&mEntries[index], &mEntries[index + 1], (mDriverCount - index) * sizeof(DriverEntry));
			return true;
		}
		entry->mLifetime = -1.0f;
		entry->mEndless = false;
		return true;
	}

	// FUNCTION: ENGINE 0x109470B0
	void Puppet::RemoveAll(bool immediately)
	{
		if (immediately)
		{
			for (int i = mDriverCount - 1; i >= 0; i--)
			{
				mEntries[i].mDriver->Unbind();
				mEntries[i].mDriver->Release();
			}
			mDriverCount = 0;
		}
		else
		{
			for (int i = mDriverCount - 1; i >= 0; i--)
			{
				mEntries[i].mLifetime = -1.0f;
				mEntries[i].mEndless = false;
			}
		}
		mUnknown160 = 0.0f;
		mUnknown164 = 0.0f;
	}

	// FUNCTION: ENGINE 0x10947150
	bool Puppet::IsEnding(Driver* driver) const
	{
		const DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return true;
		}
		if (entry->mLifetime < 0.0f && !entry->mEndless)
		{
			return true;
		}
		return driver->mFlag5;
	}

	// FUNCTION: ENGINE 0x109471A0
	bool Puppet::GetEndless(Driver* driver) const
	{
		const DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		return entry->mEndless;
	}

	// FUNCTION: ENGINE 0x109471C0
	bool Puppet::GetLifetime(Driver* driver, bool* endless, float* lifetime) const
	{
		const DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		*endless = entry->mEndless;
		*lifetime = entry->mLifetime;
		return true;
	}

	// FUNCTION: ENGINE 0x109471F0
	bool Puppet::SetLifetime(Driver* driver, float lifetime)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		entry->mLifetime = lifetime;
		return true;
	}

	// FUNCTION: ENGINE 0x10947220
	bool Puppet::SetEndless(Driver* driver, bool endless)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		entry->mEndless = endless;
		return true;
	}

	// FUNCTION: ENGINE 0x10947240
	bool Puppet::SetEndlessLifetime(Driver* driver, bool endless, float lifetime)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		entry->mEndless = endless;
		entry->mLifetime = lifetime;
		return true;
	}

	// FUNCTION: ENGINE 0x10947270
	int Puppet::GetPriority(Driver* driver) const
	{
		const DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return 0;
		}
		return entry->mPriority;
	}

	// FUNCTION: ENGINE 0x10947290
	bool Puppet::SetPriority(Driver* driver, int priority)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		entry->mPriority = priority;
		mSortNeeded = true;
		return true;
	}

	// FUNCTION: ENGINE 0x109472C0
	float Puppet::GetWeight(Driver* driver) const
	{
		const DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return 0.0f;
		}
		return entry->mWeight;
	}

	// FUNCTION: ENGINE 0x109472E0
	bool Puppet::SetWeight(Driver* driver, float weight)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		if (weight < 0.0f)
		{
			entry->mWeight = 0.0f;
			return true;
		}
		entry->mWeight = weight;
		return true;
	}

	// FUNCTION: ENGINE 0x10947320
	float Puppet::GetBlendIn(Driver* driver) const
	{
		const DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return 0.0f;
		}
		return entry->mBlendIn;
	}

	// FUNCTION: ENGINE 0x10947340
	bool Puppet::SetBlendIn(Driver* driver, float blendIn)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		entry->mBlendIn = blendIn;
		return true;
	}

	// FUNCTION: ENGINE 0x10947370
	float Puppet::GetBlendOut(Driver* driver) const
	{
		const DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return 0.0f;
		}
		return entry->mBlendOut;
	}

	// FUNCTION: ENGINE 0x10947390
	bool Puppet::SetBlendOut(Driver* driver, float blendOut)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		entry->mBlendOut = blendOut;
		return true;
	}

	// FUNCTION: ENGINE 0x109473C0
	float Puppet::GetFade(Driver* driver) const
	{
		const DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return 0.0f;
		}
		return entry->mFade;
	}

	// FUNCTION: ENGINE 0x109473E0
	bool Puppet::SetFade(Driver* driver, float fade)
	{
		DriverEntry* entry = FindEntry(driver);
		if (entry == 0)
		{
			return false;
		}
		if (fade < 0.0f)
		{
			entry->mFade = 0.0f;
			return true;
		}
		entry->mFade = fade;
		return true;
	}

	// FUNCTION: ENGINE 0x10947420
	bool Puppet::HasActiveDriver() const
	{
		for (unsigned int i = 0; i < mDriverCount; i++)
		{
			const DriverEntry* entry = &mEntries[i];
			if (!entry->mDriver->mFlag5 && (0.0f <= entry->mLifetime || entry->mEndless))
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10947470
	// EQUIVALENT: the same unrolled loop with the same operations in the same order; the engine counts in eax and
	// indexes with ebp where ours counts in ebp and indexes with ebx (the whole diff is that register assignment)
	int Puppet::CountActiveDrivers() const
	{
		int count = 0;
		for (unsigned int i = 0; i < mDriverCount; i++)
		{
			const DriverEntry* entry = &mEntries[i];
			if (!entry->mDriver->mFlag5 && (0.0f <= entry->mLifetime || entry->mEndless))
			{
				count++;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10947560
	// EQUIVALENT: the same operations in the same order; the engine keeps the number of drivers in edi and the count of
	// the active ones in esi, ours the other way round (the whole diff is that swap)
	Driver* Puppet::GetActiveDriver(int index) const
	{
		int active = 0;
		for (unsigned int i = 0; i < mDriverCount; i++)
		{
			const DriverEntry* entry = &mEntries[i];
			if (!entry->mDriver->mFlag5 && (0.0f <= entry->mLifetime || entry->mEndless))
			{
				if (index == active)
				{
					return entry->mDriver;
				}
				active++;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x109475C0
	Driver* Puppet::GetDriver(unsigned int index) const
	{
		if (index < mDriverCount)
		{
			return mEntries[index].mDriver;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x109475E0
	int Puppet::GetDriverType(unsigned int index) const
	{
		if (index < mDriverCount)
		{
			return mEntries[index].mType;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10947600
	Driver* Puppet::CopyDriverFrom(Driver* driver, Puppet* source)
	{
		DriverEntry* entry = source->FindEntry(driver);
		Driver* clone = CloneDriver(driver);
		DriverEntry* target = &mEntries[mDriverCount];
		*target = *entry;
		target->mDriver = clone;
		clone->AddRef();
		mDriverCount++;
		mSortNeeded = true;
		return clone;
	}

	// FUNCTION: ENGINE 0x10947660
	void Puppet::CountNodes(PuppetCounts* counts)
	{
		unsigned int nodes = 0;
		unsigned int samples = 0;
		unsigned int roots = 0;
		unsigned int limbs = 0;
		for (unsigned int i = 0; i < mDriverCount; i++)
		{
			switch (GetNodeKind(mEntries[i].mType))
			{
			case 0:
				nodes++;
				samples += GetSampleCount(mEntries[i].mDriver);
				break;
			case 1:
				roots++;
				break;
			case 2:
				limbs++;
				break;
			}
		}
		counts->count[0] = nodes;
		counts->count[1] = samples;
		counts->count[2] = roots;
		counts->count[3] = limbs;
	}

	// The constructor of the writer, which the engine also has on its own
	// FUNCTION: ENGINE 0x10947700 ; choreo::PoseBlendWriter::PoseBlendWriter
#pragma inline_depth(0)
	PoseBlendWriter* KeepWriterConstructor(const PoseBlendCursors* cursors)
	{
		return new PoseBlendWriter(cursors);
	}
#pragma inline_depth()

	// FUNCTION: ENGINE 0x10947720
	void PoseBlendWriter::WriteNode(Driver* driver, float first, float second, float third, float fourth)
	{
		mRoot->mEnd->SetEmpty();
		mRoot->mEnd->SetWeights(first, second, third, fourth);
		FillNode(driver, mRoot->mEnd, mSamples);
		mSamples += GetSampleCount(driver);
		mRoot->mEnd += 1;
	}

	// FUNCTION: ENGINE 0x10947790
	void PoseBlendWriter::WriteRootTask(Driver* driver, float first, float second)
	{
		mRootRange->mEnd->SetWeights(first, second);
		FillRootTask(driver, mRootRange->mEnd);
		mRootRange->mEnd += 1;
	}

	// FUNCTION: ENGINE 0x109477D0
	void PoseBlendWriter::WriteLimbTask(Driver* driver, float first, float second)
	{
		mLimbRange->mEnd->SetWeights(first, second);
		FillLimbTask(driver, mLimbRange->mEnd);
		mLimbRange->mEnd += 1;
	}

	// The functions of DriverWeightShare, which the engine also has on their own
	// FUNCTION: ENGINE 0x10947890 ; choreo::DriverWeightShare::Add
	// FUNCTION: ENGINE 0x10947900 ; choreo::DriverWeightShare::GetWeight
	void (DriverWeightShare::*gKeepWeightShare[])(const DriverEntry&) = {&DriverWeightShare::Add};
	float (DriverWeightShare::*gKeepWeightShare2[])() const = {&DriverWeightShare::GetWeight};

	// FUNCTION: ENGINE 0x10947810 ; choreo::DriverWeightShare::DriverWeightShare
#pragma inline_depth(0)
	float KeepWeightShareConstructor(const DriverEntry& entry)
	{
		DriverWeightShare share(&Driver::GetFlag0, entry, 1.0f);
		return share.mWeight;
	}
#pragma inline_depth()

	// FUNCTION: ENGINE 0x10947DF0
	void PoseBlendWriter::Write(Driver* driver, float first, float second, float third, float fourth)
	{
		switch (GetNodeKind(driver->mType))
		{
		case 0:
			WriteNode(driver, first, second, third, fourth);
			break;
		case 1:
			WriteRootTask(driver, first, second);
			break;
		case 2:
			WriteLimbTask(driver, first, second);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10947E80
	// NONMATCHING: the engine's inlined shares keep their fields in other stack slots and share the entry's weight (12.3 %)
#ifdef NONMATCHING
	void Puppet::WriteGroup(unsigned int first, unsigned int last, float weight, PoseBlendWriter* writer)
	{
		const DriverEntry* entry = &mEntries[first];
		float entryWeight = entry->mFade * entry->mWeight;
		Driver* driver = entry->mDriver;
		DriverWeightShare translation(&Driver::GetFlag0, driver, entryWeight, weight);
		DriverWeightShare rotation(&Driver::GetFlag1, driver, entryWeight, weight);
		DriverWeightShare scale(&Driver::GetFlag3, driver, entryWeight, weight);
		DriverWeightShare other(&Driver::GetFlag2, driver, entryWeight, weight);
		writer->Write(driver, translation.mWeight, rotation.mWeight, scale.mWeight, other.mWeight);
		for (unsigned int i = first + 1; i < last; i++)
		{
			entry++;
			driver = entry->mDriver;
			entryWeight = entry->mFade * entry->mWeight;
			translation.Add(driver, entryWeight);
			rotation.Add(driver, entryWeight);
			scale.Add(driver, entryWeight);
			other.Add(driver, entryWeight);
			writer->Write(driver, translation.mWeight, rotation.mWeight, scale.mWeight, other.mWeight);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10947910
	void Puppet::UpdatePose()
	{
		mPose->Update();
	}

	// FUNCTION: ENGINE 0x10947920
	void Puppet::ReleaseRemoved()
	{
		DriverEntry* entry = &mEntries[mDriverCount];
		for (unsigned int i = 0; i < mRemovedCount; i++)
		{
			entry->mDriver->Unbind();
			entry->mDriver->Release();
			entry++;
		}
		mRemovedCount = 0;
	}

	// FUNCTION: ENGINE 0x10947980
	void* Puppet::operator new(unsigned int size)
	{
		return core::HeapAllocAligned(core::GetCurrentHeap(), size, 16);
	}

	// FUNCTION: ENGINE 0x109479A0
	void* Puppet::operator new(unsigned int size, void* where)
	{
		return where;
	}

	// FUNCTION: ENGINE 0x109479B0
	void* Puppet::operator new[](unsigned int size)
	{
		return core::HeapAllocAligned(core::GetCurrentHeap(), size, 16);
	}

	// FUNCTION: ENGINE 0x109479D0
	void* Puppet::operator new(unsigned int size, int heap)
	{
		return core::HeapAllocAligned(heap, size, 16);
	}

	// FUNCTION: ENGINE 0x109479F0
	void* Puppet::operator new[](unsigned int size, int heap)
	{
		return core::HeapAllocAligned(heap, size, 16);
	}

	// FUNCTION: ENGINE 0x10947A10
	void Puppet::operator delete(void* block)
	{
		core::FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x10947A20
	void Puppet::operator delete[](void* block)
	{
		core::FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x10947A30
	int Puppet::GetUserData() const
	{
		return mUserData;
	}

	// FUNCTION: ENGINE 0x10947A40
	void Puppet::SetUserData(int data)
	{
		mUserData = data;
	}

	// FUNCTION: ENGINE 0x10947A50
	bool Puppet::CanHold(Driver* driver)
	{
		return AcceptDriver(driver, this, true);
	}

	// FUNCTION: ENGINE 0x10947BF0
	void Puppet::Unknown10947BF0()
	{
		BuildRootDelta();
	}

	// FUNCTION: ENGINE 0x10947C00
	// EQUIVALENT: the same operations in the same order; the engine loads the this pointer into ecx for the final call after the byte store, ours before (84.6 %)
	PuppetState::PuppetState() : mUnknown40(false), mLimbs()
	{
		mUnknown15C = false;
		mUnknown160 = 0.0f;
		mUnknown164 = 0.0f;
		mRootDelta.Identity();
	}

	// FUNCTION: ENGINE 0x10947C40
	Puppet::~Puppet()
	{
		for (int i = mRemovedCount + mDriverCount - 1; i >= 0; i--)
		{
			mEntries[i].mDriver->Unbind();
			mEntries[i].mDriver->Release();
		}
		if (mPoseObject != 0)
		{
			mPoseObject->Release();
			mPose = 0;
		}
	}

	// FUNCTION: ENGINE 0x10947CB0
	const char* Puppet::GetNameText() const
	{
		return mName.GetText();
	}

	// FUNCTION: ENGINE 0x10947CC0
	void Puppet::SetName(const char* text)
	{
		mName = core::Name<core::CaseSensitiveKey>(text, 1);
	}

	// FUNCTION: ENGINE 0x10947CF0
	void Puppet::SetName(const core::Name<core::CaseSensitiveKey>& name)
	{
		mName = name;
	}

	// FUNCTION: ENGINE 0x10947D20
	void Puppet::CopyPoseFrom(Puppet* other)
	{
		mPoseObject->CopyFrom(other->mPoseObject);
		mRootDelta = other->mRootDelta;
		mUnknown40 = other->mUnknown40;
		mLimbs = other->mLimbs;
		mUnknown15C = other->mUnknown15C;
		mUnknown160 = other->mUnknown160;
		mUnknown164 = other->mUnknown164;
	}

	// FUNCTION: ENGINE 0x10947D80
	void Puppet::SetPose(pure3d::Pose* pose)
	{
		if (mPoseObject != pose)
		{
			for (unsigned int i = 0; i < mDriverCount; i++)
			{
				mEntries[i].mDriver->Bind(*reinterpret_cast<DriverInfo*>(pose));
			}
			if (pose != 0)
			{
				mLimbs.Reset(pose->mSkeleton);
			}
		}
		core::RefAssign((pure3d::LockableRefCounted*&)mPoseObject, (pure3d::LockableRefCounted*)pose);
		if (pose != 0)
		{
			mPose = &pose->mData;
		}
	}

	// FUNCTION: ENGINE 0x109484A0
	// NONMATCHING: the engine keeps the running weight in xmm0 across the loop and passes it through a temporary; ours
	// spills it (30 %)
#ifdef NONMATCHING
	void Puppet::WriteAll(PoseBlendWriter* writer)
	{
		int firstPriority = mEntries[0].mPriority;
		float weight = mEntries[0].mFade * mEntries[0].mWeight;
		unsigned int first = 0;
		bool movesRoot = mEntries[0].mDriver->mFlag4;
		int priority = firstPriority;
		for (unsigned int i = 1; i < mDriverCount; i++)
		{
			if (movesRoot || mEntries[i].mDriver->mFlag4)
			{
				movesRoot = true;
			}
			int entryPriority = mEntries[i].mPriority;
			if (entryPriority != priority)
			{
				if (priority == firstPriority)
				{
					weight = 1.0f;
				}
				WriteGroup(first, i, weight, writer);
				first = i;
				priority = entryPriority;
				weight = mEntries[i].mFade * mEntries[i].mWeight;
			}
			else if (weight < mEntries[i].mFade * mEntries[i].mWeight)
			{
				weight = mEntries[i].mFade * mEntries[i].mWeight;
			}
		}
		if (priority == firstPriority)
		{
			weight = 1.0f;
		}
		WriteGroup(first, mDriverCount, weight, writer);
		mPose->mFlags ^= ((movesRoot << 2) ^ mPose->mFlags) & 4;
	}
#endif

	// FUNCTION: ENGINE 0x10948400
	Puppet::Puppet(pure3d::Pose* pose) : mRefCount(0), mUserData(0), mPoseObject(0), mPose(0), mTimeScale(1.0f),
		mDriverCount(0), mSortNeeded(false), mRemovedCount(0)
	{
		SetPose(pose);
	}

	// FUNCTION: ENGINE 0x10948470
	void Puppet::Release()
	{
		mRefCount--;
		if (mRefCount <= 0)
		{
			this->~Puppet();
			operator delete(this);
		}
	}

	// The engine calls the sort of the entries and does not expand it here
#pragma inline_depth(0)
	// FUNCTION: ENGINE 0x10948770
	void Puppet::BuildNodes(PuppetCounts* counts, PoseBlendCursors* cursors)
	{
		if (mDriverCount != 0 && mPose != 0)
		{
			bool any = false;
			if (0 < counts->count[0])
			{
				((BlendRootNode*)cursors->cursor[0])->mBegin = (PoseBlendNode*)cursors->cursor[3];
				((BlendRootNode*)cursors->cursor[0])->mEnd = (PoseBlendNode*)cursors->cursor[3];
				mPose->GetLayout(&((BlendRootNode*)cursors->cursor[0])->mLayout);
				mPose->mSkeleton->GetLimbInfo(&((BlendRootNode*)cursors->cursor[0])->mLimbInfo);
				((BlendRootNode*)cursors->cursor[0])->mPuppet = this;
				any = true;
			}
			if (0 < counts->count[2])
			{
				((PoseBlendRootRange*)cursors->cursor[1])->mBegin = (PoseBlendRootTask*)cursors->cursor[5];
				((PoseBlendRootRange*)cursors->cursor[1])->mEnd = (PoseBlendRootTask*)cursors->cursor[5];
				((PoseBlendRootRange*)cursors->cursor[1])->mPose = mPose;
				((PoseBlendRootRange*)cursors->cursor[1])->mPuppet = this;
				any = true;
			}
			if (0 < counts->count[3])
			{
				((PoseBlendLimbRange*)cursors->cursor[2])->mBegin = (PoseBlendLimbTask*)cursors->cursor[6];
				((PoseBlendLimbRange*)cursors->cursor[2])->mEnd = (PoseBlendLimbTask*)cursors->cursor[6];
				((PoseBlendLimbRange*)cursors->cursor[2])->mPose = mPose;
				((PoseBlendLimbRange*)cursors->cursor[2])->mPuppet = this;
			}
			else if (!any)
			{
				return;
			}
			PoseBlendWriter writer(cursors);
			WriteAll(&writer);
			mPose->mFlags |= 3;
		}
	}

	// The root node the evaluation builds on its stack (the engine reserves more than the node itself)
	struct __declspec(align(16)) RootNodeStorage : public BlendRootNode
	{
		unsigned char unknown30[0x10];
	};

	// FUNCTION: ENGINE 0x10948CB0
	// NONMATCHING: same operations; the engine's frame is 0x10 bytes larger with other offsets (89.7 %)
#ifdef NONMATCHING
	void Puppet::Evaluate()
	{
		if (mDriverCount != 0 && mPose != 0)
		{
			{
				ravenphysics::ScratchStackFrame frame;
				ravenphysics::ScratchStack stack;
				PuppetCounts counts;
				CountNodes(&counts);
				PoseBlendCursors cursors;
				RootNodeStorage root;
				PoseBlendRootRange rootRange;
				PoseBlendLimbRange limbRange;
				if (0 < counts.count[0])
				{
					cursors.cursor[0] = (unsigned char*)&root;
					cursors.cursor[3] = (unsigned char*)stack.Alloc(counts.count[0] * 0x70, 0x10);
					cursors.cursor[4] = (unsigned char*)stack.Alloc(counts.count[1] << 5, 0x10);
				}
				if (0 < counts.count[2])
				{
					cursors.cursor[1] = (unsigned char*)&rootRange;
					cursors.cursor[5] = (unsigned char*)stack.Alloc(counts.count[2] << 4, 0x10);
				}
				if (0 < counts.count[3])
				{
					cursors.cursor[2] = (unsigned char*)&limbRange;
					cursors.cursor[6] = (unsigned char*)stack.Alloc(counts.count[3] << 4, 0x10);
				}
				BuildNodes(&counts, &cursors);
				if (cursors.cursor[3])
				{
					root.Apply();
				}
				if (cursors.cursor[5])
				{
					rootRange.Apply();
				}
				if (cursors.cursor[6])
				{
					UpdatePose();
					limbRange.Apply();
				}
			}
			BuildRootDelta();
		}
	}
#endif

	// FUNCTION: ENGINE 0x10949040
	void Puppet::SortDrivers()
	{
		if (mSortNeeded)
		{
			mSortNeeded = false;
			std::sort(mEntries, mEntries + mDriverCount);
		}
	}
#pragma inline_depth()

	// FUNCTION: ENGINE 0x10949080
	// EQUIVALENT: the same operations in the same order; the engine loads the step into the x87 stack at the top of
	// the loop body (ours loads it where it is passed on) and keeps the address of the entry after the current one in
	// a stack slot of its own
	void Puppet::Update(float dt)
	{
		mRootDelta.Identity();
		dt = mTimeScale * dt;
		if (mPose->mArrays.mJointCount > 0)
		{
			math::Quaternion identity;
			identity.x = 0.0f;
			identity.y = 0.0f;
			identity.z = 0.0f;
			identity.w = 1.0f;
			*mPose->mArrays.mRotations = identity;
			mPose->mArrays.mTranslations->Set(0.0f, 0.0f, 0.0f);
			mPose->mArrays.mUnknown10->Set(0.0f, 0.0f, 0.0f);
			mPose->mArrays.mScales->Set(1.0f, 1.0f, 1.0f);
			mPose->mArrays.mUnknown14->Set(0.0f, 0.0f, 0.0f);
			mPose->mArrays.mUnknown1C->Set(0.0f, 0.0f, 0.0f);
		}
		unsigned int index = 0;
		for (DriverEntry* entry = mEntries; index < mDriverCount; )
		{
			Driver* driver = entry->mDriver;
			if ((entry->mLifetime < 0.0f && !entry->mEndless) || driver->mFlag5)
			{
				// Ending: fade out, and drop the driver once it is gone
				if (0.0f >= entry->mBlendOut)
				{
					entry->mFade = 0.0f;
				}
				else
				{
					entry->mFade = entry->mFade - dt / entry->mBlendOut;
				}
				if (0.0f >= entry->mFade)
				{
					mDriverCount--;
					memmove(entry, &mEntries[index + 1], (mDriverCount - index) * sizeof(DriverEntry));
					mEntries[mDriverCount].mDriver = driver;
					mRemovedCount++;
					continue;
				}
			}
			else
			{
				if (!entry->mEndless)
				{
					entry->mLifetime = entry->mLifetime - dt;
				}
				if (0.0f >= entry->mBlendIn)
				{
					entry->mFade = 1.0f;
				}
				else
				{
					entry->mFade = dt / entry->mBlendIn + entry->mFade;
					if (entry->mFade > 1.0f)
					{
						entry->mFade = 1.0f;
					}
				}
			}
			UpdateDriver(driver, dt);
			index++;
			entry++;
		}
		if (mDriverCount > 0)
		{
			SortDrivers();
		}
	}

	// FUNCTION: ENGINE 0x109492A0
	pure3d::Skeleton* LimbPoses::GetSkeleton() const
	{
		return mSkeleton;
	}

	// FUNCTION: ENGINE 0x109492B0
	unsigned int LimbPoses::GetCount() const
	{
		return mCount;
	}

	// FUNCTION: ENGINE 0x109492C0
	math::Matrix* LimbPoses::GetMatrix(int index)
	{
		return &mMatrices[index];
	}

	// FUNCTION: ENGINE 0x109492D0
	void LimbPoses::SetMatrix(int index, const math::Matrix& matrix)
	{
		mMatrices[index] = matrix;
	}

	// FUNCTION: ENGINE 0x109492F0
	float LimbPoses::GetWeight(int index) const
	{
		return mWeights[index];
	}

	// FUNCTION: ENGINE 0x10949300
	void LimbPoses::SetWeight(int index, float weight)
	{
		if (!(weight >= 0.0f))
		{
			weight = 0.0f;
		}
		if (0.0f <= weight - 1.0f)
		{
			mWeights[index] = 1.0f;
			return;
		}
		mWeights[index] = weight;
	}

	// FUNCTION: ENGINE 0x10949350
	// NONMATCHING: the engine loads the three components of both positions first and computes the three lerps together; ours interleaves them (64.5 %)
#ifdef NONMATCHING
	void LimbPoses::Blend(const LimbPoses& other, float t)
	{
		for (unsigned int i = 0; i < mCount; i++)
		{
			math::Matrix& m = mMatrices[i];
			const math::Matrix& o = other.mMatrices[i];
			math::Quaternion rotation;
			math::Quaternion target;
			rotation.FromMatrix(m);
			target.FromMatrix(o);
			rotation.Slerp(rotation, target, t);
			m.FromQuaternion(rotation);
			m.m[3][0] = (o.m[3][0] - m.m[3][0]) * t + m.m[3][0];
			m.m[3][1] = (o.m[3][1] - m.m[3][1]) * t + m.m[3][1];
			m.m[3][2] = (o.m[3][2] - m.m[3][2]) * t + m.m[3][2];
		}
	}
#endif

	// FUNCTION: ENGINE 0x10949440
	LimbPoses::LimbPoses()
	{
		mSkeleton = 0;
		mCount = 0;
	}

	// The members of the matrices are copied one by one, as the engine's inline copy does
	static __forceinline void CopyMatrix(math::Matrix& to, const math::Matrix& from)
	{
		float* t = &to.m[0][0];
		const float* f = &from.m[0][0];
		t[0] = f[0];
		t[1] = f[1];
		t[2] = f[2];
		t[3] = f[3];
		t[4] = f[4];
		t[5] = f[5];
		t[6] = f[6];
		t[7] = f[7];
		t[8] = f[8];
		t[9] = f[9];
		t[10] = f[10];
		t[11] = f[11];
		t[12] = f[12];
		t[13] = f[13];
		t[14] = f[14];
		t[15] = f[15];
	}

	// FUNCTION: ENGINE 0x10949460
	// EQUIVALENT: the same copy of the members in the same order; the engine anchors the pointers of the loop on the third member of the matrices and keeps the other pose in ebx, ours on the fourth with the other pose in edi (64.6 %)
	LimbPoses::LimbPoses(const LimbPoses& other)
	{
		mSkeleton = 0;
		mCount = other.mCount;
		core::RefAssign(mSkeleton, other.mSkeleton);
		for (unsigned int i = 0; i < mCount; i++)
		{
			CopyMatrix(mMatrices[i], other.mMatrices[i]);
			mWeights[i] = other.mWeights[i];
		}
	}

	// FUNCTION: ENGINE 0x10949530
	LimbPoses::~LimbPoses()
	{
		core::SafeRelease(mSkeleton);
	}

	// FUNCTION: ENGINE 0x10949540
	// EQUIVALENT: as the copy constructor (the pointers of the loop and the registers)
	LimbPoses& LimbPoses::operator=(const LimbPoses& other)
	{
		mCount = other.mCount;
		core::RefAssign(mSkeleton, other.mSkeleton);
		for (unsigned int i = 0; i < mCount; i++)
		{
			CopyMatrix(mMatrices[i], other.mMatrices[i]);
			mWeights[i] = other.mWeights[i];
		}
		return *this;
	}

	// FUNCTION: ENGINE 0x10949610
	void LimbPoses::Reset(pure3d::Skeleton* skeleton)
	{
		core::RefAssign(mSkeleton, skeleton);
		mCount = skeleton->mData.mLimbCount;
		for (unsigned int i = 0; i < mCount; i++)
		{
			skeleton->GetRestMatrix(i, &mMatrices[i]);
			mWeights[i] = 0.0f;
		}
	}
}
