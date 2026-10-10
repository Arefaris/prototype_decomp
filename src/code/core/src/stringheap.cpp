// The string heap: a small unit of its own (0x1063B730 - 0x1063B7E0; file name guessed). StrDup here calls StrLen
// and StrCpy as external functions (the compiler of the original did not know their register use, which is how
// the two forwarders below became plain jumps), so it is not part of strings.cpp.
#include "code/core/heap.h"
#include "code/core/strings.h"

namespace core
{
	// GLOBAL: ENGINE 0x110BC5AC
	static const char* sDefaultString = "?Name?";
	// GLOBAL: ENGINE 0x11278FC0
	static int sStringHeap;
	// GLOBAL: ENGINE 0x11278FC4
	static int sStringHeapCounter2;
	// GLOBAL: ENGINE 0x11278FC8
	static int sStringHeapCounter1;

	// FUNCTION: ENGINE 0x1063B730
	const char* GetDefaultString()
	{
		return sDefaultString;
	}

	// FUNCTION: ENGINE 0x1063B740
	int* GetStringHeapCounter1()
	{
		return &sStringHeapCounter1;
	}

	// FUNCTION: ENGINE 0x1063B750
	int* GetStringHeapCounter2()
	{
		return &sStringHeapCounter2;
	}

	// FUNCTION: ENGINE 0x1063B760
	void SetStringHeap(int heap)
	{
		sStringHeap = heap;
	}

	// FUNCTION: ENGINE 0x1063B770
	int GetStringHeap()
	{
		return sStringHeap;
	}

	// FUNCTION: ENGINE 0x1063B780
	char* StrCpyAlias(char* destination, const char* source)
	{
		return StrCpy(destination, source);
	}

	// FUNCTION: ENGINE 0x1063B790
	unsigned int StrLenAlias(const char* string)
	{
		return StrLen(string);
	}

	// FUNCTION: ENGINE 0x1063B7A0
	// Without a heap (sStringHeap == -1) hands out the "?Name?" placeholder instead of a copy
	char* StrDup(const char* string)
	{
		if (sStringHeap == -1)
		{
			return (char*)GetDefaultString();
		}
		char* copy = (char*)HeapAlloc(sStringHeap, StrLen(string) + 1);
		StrCpy(copy, string);
		return copy;
	}

	// 0x1063B7E0 is one more forwarder, a jump to 0x1063AC00 (another unit); not reconstructed
}
