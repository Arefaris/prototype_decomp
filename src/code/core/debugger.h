// The debugger link of the core module (unit 0x10644760 - 0x10644880, file name debugger.cpp and all names
// guessed): stubs in this build (empty functions, getters of globals nothing writes) and a reference-counted lock.
// Engine start-up calls DebugInit after the memory set-up, shut-down calls DebugShutdown; the auto tester asks
// IsDebugLinkClosed.
#ifndef CORE_DEBUGGER_H
#define CORE_DEBUGGER_H

namespace core
{
	void DebugSignal(int value);
	void DebugInit();
	void DebugShutdown();
	int DebugGetZero();
	int DebugGetValue();
	bool DebugIsLinkOpen();
	bool IsDebugLinkClosed();
	int DebugHasPending();
	void DebugWait(int value);
	const char* CoreName();
	void DebugLockInit();
	void DebugLockShutdown();
	void DebugLockEnter();
	void DebugLockLeave();
	void DebugGetRange(int* start, int* end);
	void DebugNop();
}

#endif
