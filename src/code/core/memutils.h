// memcpy / memset wrappers of the core module (file and function names guessed; the unit is
// 0x10645EE0 - 0x10646045). Each public function checks the size and forwards to a static helper that calls the
// CRT; the helpers take their arguments in registers (edx, ecx, eax), so the public ones end in a jump.
// Why the original has four copies of the same copy wrapper and four of the fill wrapper is not known (typed
// overloads collapsed to void* are one guess); they are kept apart here because each has its own address.
#ifndef CORE_MEMUTILS_H
#define CORE_MEMUTILS_H

namespace core
{
	// memcpy when size is not zero
	void MemCopy(void* destination, const void* source, unsigned int size);
	void MemCopy2(void* destination, const void* source, unsigned int size);
	void MemCopy4(void* destination, const void* source, unsigned int size);
	// memcpy without the size check
	void MemCopyUnchecked(void* destination, const void* source, unsigned int size);
	// memset when size is not zero
	void MemSet(void* destination, unsigned char value, unsigned int size);
	void MemSet2(void* destination, unsigned char value, unsigned int size);
	void MemSet3(void* destination, unsigned char value, unsigned int size);
	void MemSet4(void* destination, unsigned char value, unsigned int size);
}

#endif
