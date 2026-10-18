#include <xmmintrin.h>

#include "code/core/name.h"
#include "code/core/report.h"
#include "code/ravenphysics/batch/buildcollisioninfolist.h"
#include "code/ravenphysics/collision/collisionobject.h"

#define BUILDCOLLISIONINFOLIST_FILE "..\\..\\..\\code\\ravenphysics\\batch\\src\\narrowphase\\buildcollisioninfolist.cpp"

// A message the report channel can switch off for good (the static flag), with the arguments of its format and the
// zero the engine ends them with
#define OLD_REPORT_AT(tag, line, format, ...) \
	do \
	{ \
		static bool sEnabled = true; \
		if (sEnabled) \
		{ \
			if (core::Report(0, tag, BUILDCOLLISIONINFOLIST_FILE, line, 0, format, __VA_ARGS__, 0) == 3) \
			{ \
				sEnabled = false; \
			} \
		} \
	} while (0)

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106B2970
	void ReportPair(const PairInfo* info)
	{
		static bool sEnabled = true;
		if (sEnabled)
		{
			unsigned char typeB = info->typeB;
			unsigned char typeA = info->typeA;
			if (core::Report(0, " Pre ", BUILDCOLLISIONINFOLIST_FILE, 96, 0, "Pair: volume type1: %d and %d", typeA, typeB, 0)
				== 3)
			{
				sEnabled = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x106B29C0
	void DoNothingFirst()
	{
	}

	// FUNCTION: ENGINE 0x106B29D0
	PairInfo& PairInfo::operator=(const PairInfo& other)
	{
		for (int i = 0; i < 10; i++)
		{
			values[i] = other.values[i];
		}
		unknown28 = other.unknown28;
		typeA = other.typeA;
		typeB = other.typeB;
		unknown2E = other.unknown2E;
		return *this;
	}

	// FUNCTION: ENGINE 0x106B2A30
	void InfoRecordArray::SetCount(int newCount)
	{
		count = newCount;
	}

	// FUNCTION: ENGINE 0x106B2A40
	void InfoRecordArraySecond::SetCount(int newCount)
	{
		count = newCount;
	}

	// FUNCTION: ENGINE 0x106B2A50
	InfoRecord* InfoRecordArray::At(int index)
	{
		return items + index;
	}

	// FUNCTION: ENGINE 0x106B2A60
	InfoRecord* InfoRecordArray::GetItems()
	{
		return items;
	}

	// FUNCTION: ENGINE 0x106B2A70
	int InfoRecordArray::GetCount()
	{
		return count;
	}

	// FUNCTION: ENGINE 0x106B2A80
	void DoNothingSecond()
	{
	}

	// FUNCTION: ENGINE 0x106B2A90
	// EQUIVALENT: the engine tests the count with `test` and a `je`, ours with a `jbe` behind the same `test` (the
	// carry is clear there, so both jump for zero only), 98.4 %
	void InfoRecordArray::Create(unsigned int newCount, int align)
	{
		if (newCount > 0)
		{
			items = (InfoRecord*)allocator.Alloc((newCount * sizeof(InfoRecord) + align - 1) & ~(align - 1), align);
			count = newCount;
		}
		else
		{
			count = newCount;
			items = 0;
		}
	}

	// FUNCTION: ENGINE 0x106B2AE0
	// NONMATCHING: the engine's loop checks the counts only behind the copies and leaves through two exits that each
	// run the remaining tails, 10 %
#ifdef NONMATCHING
	void MergeRecords(InfoRecord* out, const InfoRecord* first, unsigned int firstCount, const InfoRecord* second,
		unsigned int secondCount)
	{
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int k = 0;
		while (i < firstCount && j < secondCount)
		{
			if (second[j].key < first[i].key)
			{
				out[k++] = second[j++];
			}
			else
			{
				out[k++] = first[i++];
			}
		}
		while (i < firstCount)
		{
			out[k++] = first[i++];
		}
		while (j < secondCount)
		{
			out[k++] = second[j++];
		}
	}
#endif

	// FUNCTION: ENGINE 0x106B2BD0
	void CopyQuad(float* destination, const float* source)
	{
		_mm_store_ps(destination, _mm_load_ps(source));
	}

	// Finds the slot of a handle in the table and says whether the handle is still current
	inline bool FindEntry(CollisionObjectTable* table, const CollisionHandle* handle, CollisionHandleEntry** entry)
	{
		if (handle->index >= table->slotCount)
		{
			return false;
		}
		*entry = table->entries.begin + handle->index;
		return (*entry)->serial == handle->serial;
	}

	// FUNCTION: ENGINE 0x106B2BF0
	void ReportCollisions(int unused, const CollisionHandle* handleA, const CollisionHandle* handleB,
		unsigned int volumeA, unsigned int volumeB, int count)
	{
		CollisionObjectTable* table = gCollisionObjectTable;
		CollisionHandleEntry* entryA;
		CollisionHandleEntry* entryB;
		if (FindEntry(table, handleA, &entryA) && FindEntry(table, handleB, &entryB))
		{
			CollisionObject* objectA = (CollisionObject*)entryA->object;
			if (objectA != 0)
			{
				CollisionObject* objectB = (CollisionObject*)entryB->object;
				if (objectB != 0)
				{
					CollisionVolume* volumeOfA = objectA->volumes[volumeA];
					CollisionVolume* volumeOfB = objectB->volumes[volumeB];
					OLD_REPORT_AT(" Physics  Pre ", 52, " %d collisions, between %s (volume: %d, %s) and %s (volume: %d, %s)",
						count, objectA->name.GetText(), volumeA, volumeOfA->GetTypeName(), objectB->name.GetText(), volumeB,
						volumeOfB->GetTypeName());
				}
			}
		}
	}
}
