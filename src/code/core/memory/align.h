// The rounding helpers the core units call out of line (unit 0x10645300 - 0x1064536D, file name memory/align.cpp and
// the names guessed): the same code as the AlignUp / AlignDown templates of allocatorbase.h, which
// twowayallocator.cpp instantiates right behind them.
#ifndef CORE_MEMORY_ALIGN_H
#define CORE_MEMORY_ALIGN_H

namespace core
{
	// size rounded up to a multiple of align (align 0: size)
	unsigned int RoundUp(unsigned int size, unsigned int align);
	unsigned int RoundDown(unsigned int size, unsigned int align);
	bool IsRoundedUp(unsigned int size, unsigned int align);
}

#endif
