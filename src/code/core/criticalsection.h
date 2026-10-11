// Thin wrappers around the kernel32 critical-section calls (0x1063D260 - 0x1063D290, names guessed): each takes
// the address of a CRITICAL_SECTION (24 bytes) and calls Initialize / Delete / Leave / Enter through the import.
#ifndef CORE_CRITICALSECTION_H
#define CORE_CRITICALSECTION_H

namespace core
{
	void CriticalSectionInit(void* section);
	void CriticalSectionDelete(void* section);
	void CriticalSectionLeave(void* section);
	void CriticalSectionEnter(void* section);
}

#endif
