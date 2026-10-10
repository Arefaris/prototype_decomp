#include <string.h>

#include "code/core/memutils.h"

namespace core
{
	// The static helpers come first, as in the original's layout; the compiler gives them register arguments

	// FUNCTION: ENGINE 0x10645EE0
	static void CopyMemory1(void* destination, const void* source, unsigned int size)
	{
		memcpy(destination, source, size);
	}

	// FUNCTION: ENGINE 0x10645EF0
	static void CopyMemory2(void* destination, const void* source, unsigned int size)
	{
		memcpy(destination, source, size);
	}

	// FUNCTION: ENGINE 0x10645F00
	static void FillMemory1(void* destination, unsigned char value, unsigned int size)
	{
		memset(destination, value, size);
	}

	// FUNCTION: ENGINE 0x10645F10
	static void FillMemory2(void* destination, unsigned char value, unsigned int size)
	{
		memset(destination, value, size);
	}

	// FUNCTION: ENGINE 0x10645F20
	void MemCopy(void* destination, const void* source, unsigned int size)
	{
		if (size != 0)
		{
			CopyMemory1(destination, source, size);
		}
	}

	// FUNCTION: ENGINE 0x10645F40
	void MemCopy2(void* destination, const void* source, unsigned int size)
	{
		if (size != 0)
		{
			CopyMemory2(destination, source, size);
		}
	}

	// FUNCTION: ENGINE 0x10645F60
	void MemSet(void* destination, unsigned char value, unsigned int size)
	{
		if (size != 0)
		{
			FillMemory1(destination, value, size);
		}
	}

	// FUNCTION: ENGINE 0x10645F80
	void MemSet2(void* destination, unsigned char value, unsigned int size)
	{
		if (size != 0)
		{
			FillMemory2(destination, value, size);
		}
	}

	// FUNCTION: ENGINE 0x10645FA0
	static void CopyMemory3(void* destination, const void* source, unsigned int size)
	{
		memcpy(destination, source, size);
	}

	// FUNCTION: ENGINE 0x10645FB0
	static void CopyMemory4(void* destination, const void* source, unsigned int size)
	{
		memcpy(destination, source, size);
	}

	// FUNCTION: ENGINE 0x10645FC0
	static void FillMemory3(void* destination, unsigned char value, unsigned int size)
	{
		memset(destination, value, size);
	}

	// FUNCTION: ENGINE 0x10645FD0
	void MemCopyUnchecked(void* destination, const void* source, unsigned int size)
	{
		CopyMemory3(destination, source, size);
	}

	// FUNCTION: ENGINE 0x10645FF0
	void MemCopy4(void* destination, const void* source, unsigned int size)
	{
		if (size != 0)
		{
			CopyMemory4(destination, source, size);
		}
	}

	// FUNCTION: ENGINE 0x10646010
	void MemSet3(void* destination, unsigned char value, unsigned int size)
	{
		if (size != 0)
		{
			FillMemory3(destination, value, size);
		}
	}

	// FUNCTION: ENGINE 0x10646030
	void MemSet4(void* destination, unsigned char value, unsigned int size)
	{
		if (size != 0)
		{
			FillMemory3(destination, value, size);
		}
	}
}
