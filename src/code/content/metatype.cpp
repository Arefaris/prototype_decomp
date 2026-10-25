// content::MetaType, the base of the content library's meta types, and the heaps the meta system makes its values in
// (code/content/src/meta/metatype.cpp, path from the reports; the unit runs from 0x105FBB20 to 0x105FBF70).
#include "code/content/metatype.h"
#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/memory/twowayallocator.h"
#include "code/core/report.h"
#include "code/core/strings.h"
#include <new>

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guess) and what the heaps it makes are
	// (names guess): the allocators, the indices they are registered under and the address ranges they own
	int gMetaHeap;
	core::MemoryRange gMetaTwoWayRange;
	core::MemoryRange gMetaHeapRange;
	int gMetaTwoWayIndex;
	int gMetaHeapIndex;
	bool gMetaFlag;
	core::IMemoryAllocator* gMetaHeapAllocator;
	core::IMemoryTwoWayAllocator* gMetaTwoWayAllocator;

	// FUNCTION: ENGINE 0x105FBB20
	unsigned int MetaType::GetKey() const
	{
		return key;
	}

	// FUNCTION: ENGINE 0x105FBB30
	bool MetaType::HasKey(unsigned int mask) const
	{
		return (key & mask) != 0;
	}

	// FUNCTION: ENGINE 0x105FBB40
	bool MetaType::Matches(unsigned int flags, void* object)
	{
		return HasKey(flags);
	}

	// FUNCTION: ENGINE 0x105FBB50
	unsigned int MetaType::ParseCode(const char* code)
	{
		unsigned int flags = 0;
		if (core::StrChr(code, 'p') != 0)
		{
			flags = 1;
		}
		if (core::StrChr(code, 'n') != 0)
		{
			flags |= 2;
		}
		if (core::StrChr(code, 'd') != 0)
		{
			flags |= 4;
		}
		if (core::StrChr(code, 'o') != 0)
		{
			flags |= 8;
		}
		if (core::StrChr(code, 'm') != 0)
		{
			flags |= 0x10;
		}
		if (core::StrChr(code, 'r') != 0)
		{
			flags |= 0x40000000;
		}
		if (core::StrChr(code, 'w') != 0)
		{
			flags |= 0x80000000;
		}
		return flags;
	}

	// FUNCTION: ENGINE 0x105FBBF0
	void InitMetaHeaps(unsigned int heapSize, int heapIndex, unsigned int twoWaySize, int twoWayIndex, bool flag)
	{
		gMetaFlag = flag;
		if (twoWaySize != 0)
		{
			gMetaTwoWayAllocator = core::NewTwoWayAllocator(twoWaySize, core::GetCurrentHeap(),
				"MetaSystemTemplateTwoWayHeap", 4);
			gMetaTwoWayAllocator->AddRef();
			gMetaTwoWayAllocator->SetSafetyMode(2);
			core::RegisterHeap(twoWayIndex, core::GetCurrentHeap(), gMetaTwoWayAllocator);
			gMetaTwoWayIndex = twoWayIndex;
			gMetaTwoWayAllocator->GetRange(&gMetaTwoWayRange, 0);
			gMetaHeap = gMetaTwoWayIndex;
		}
		if (heapSize != 0)
		{
			gMetaHeapAllocator = core::NewHeapAllocator(heapSize, core::GetCurrentHeap(), "MetaSystemTemplateHeap", 0x10,
				false, false);
			gMetaHeapAllocator->AddRef();
			gMetaHeapAllocator->SetSafetyMode(2);
			core::RegisterHeap(heapIndex, core::GetCurrentHeap(), gMetaHeapAllocator);
			gMetaHeapIndex = heapIndex;
			gMetaHeapAllocator->GetRange(&gMetaHeapRange, 0);
			gMetaHeap = gMetaHeapIndex;
		}
	}

	// FUNCTION: ENGINE 0x105FBD00
	void ShutdownMetaHeaps()
	{
		if (gMetaHeapAllocator != 0)
		{
			int count = 0;
			gMetaHeapAllocator->GetStat(0, &count);
			static bool sReportHeap = true;
			if (count != 0 && sReportHeap)
			{
				if (core::Report(0, 0, "..\\..\\..\\code\\content\\src\\meta\\metatype.cpp", 0x1C1, 0, "", count, 0) == 3)
				{
					sReportHeap = false;
				}
			}
			core::UnregisterHeap(gMetaHeapIndex);
			gMetaHeapAllocator->Release();
			gMetaHeapAllocator = 0;
		}
		if (gMetaTwoWayAllocator != 0)
		{
			int count = 0;
			gMetaTwoWayAllocator->GetStat(0, &count);
			static bool sReportTwoWay = true;
			if (count != 0 && sReportTwoWay)
			{
				if (core::Report(0, 0, "..\\..\\..\\code\\content\\src\\meta\\metatype.cpp", 0x1D2, 0, "", count, 0) == 3)
				{
					sReportTwoWay = false;
				}
			}
			core::UnregisterHeap(gMetaTwoWayIndex);
			gMetaTwoWayAllocator->Release();
			gMetaTwoWayAllocator = 0;
		}
	}

	// FUNCTION: ENGINE 0x105FBDF0
	void SetMetaHeap(int heap)
	{
		gMetaHeap = heap;
	}

	// FUNCTION: ENGINE 0x105FBE00
	void ResetMetaTwoWayHeap()
	{
		gMetaTwoWayAllocator->ResetSide(0);
	}

	// FUNCTION: ENGINE 0x105FBE10
	bool MetaType::IsDirect(const void* object)
	{
		if (gMetaTwoWayAllocator != 0 && (unsigned int)object >= gMetaTwoWayRange.start && (unsigned int)object < gMetaTwoWayRange.end)
		{
			return true;
		}
		if (gMetaHeapAllocator != 0 && (unsigned int)object >= gMetaHeapRange.start && (unsigned int)object < gMetaHeapRange.end)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FBE50
	MemberTable::MemberTable()
	{
		entries = 0;
		count = 0;
	}

	// The vftable of a meta type with slot 10 as a virtual function that takes its arguments
	struct DescribeView
	{
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Describe(MemberEntry** cursor, void* object, int unused);
	};

	// FUNCTION: ENGINE 0x105FBE60
	void MemberTable::Build(MetaType* type, void* object, int a, int heap)
	{
		count = (unsigned short)type->InvokeCount(object, a);
		{
			core::HeapScope scope(heap);
			entries = new MemberEntry[count];
		}
		MemberEntry* cursor = entries;
		((DescribeView*)type)->Describe(&cursor, object, a);
	}

	// FUNCTION: ENGINE 0x105FBEE0
	void MemberTable::Free()
	{
		if (entries != 0)
		{
			delete[] entries;
			entries = 0;
		}
	}

	// FUNCTION: ENGINE 0x105FBF00
	void MemberTable::Write(WriteContext* context)
	{
		MemberEntry* entry = entries;
		for (unsigned int i = 0; i < count; i++)
		{
			entry->type->InvokeWriteBinaryShort(context, entry->object);
			entry += 1;
		}
	}

	// FUNCTION: ENGINE 0x105FBF40
	MetaType::MetaType(const char* code)
	{
		key = ParseCode(code);
	}

	// FUNCTION: ENGINE 0x105FBF60
	MemberTable::~MemberTable()
	{
		Free();
	}
}
