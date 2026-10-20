#include "code/core/criticalsection.h"
#include "code/core/strings.h"
#include "code/core/thread.h"

// The kernel32 imports (see controllerdirectinput.cpp)
extern "C"
{
	struct OSVERSIONINFOA
	{
		unsigned long dwOSVersionInfoSize;
		unsigned long dwMajorVersion;
		unsigned long dwMinorVersion;
		unsigned long dwBuildNumber;
		unsigned long dwPlatformId;
		char szCSDVersion[128];
	};

	__declspec(dllimport) int __stdcall GetVersionExA(OSVERSIONINFOA* information);
	__declspec(dllimport) int __stdcall ConvertFiberToThread();
	__declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
	__declspec(dllimport) unsigned long __stdcall GetCurrentThreadId();
	__declspec(dllimport) int __stdcall CloseHandle(void* handle);
	__declspec(dllimport) __declspec(noreturn) void __stdcall ExitThread(unsigned long code);
	__declspec(dllimport) int __stdcall TerminateThread(void* thread, unsigned long code);
	__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void* handle, unsigned long milliseconds);
	__declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);
	__declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
	__declspec(dllimport) void* __stdcall ConvertThreadToFiber(void* parameter);
	__declspec(dllimport) int __stdcall SetThreadPriority(void* thread, int priority);
	__declspec(dllimport) unsigned long __stdcall SuspendThread(void* thread);
	__declspec(dllimport) unsigned long __stdcall ResumeThread(void* thread);
	__declspec(dllimport) int __stdcall GetExitCodeThread(void* thread, unsigned long* code);
	__declspec(dllimport) void __stdcall DeleteFiber(void* fiber);
	__declspec(dllimport) void __stdcall SwitchToFiber(void* fiber);
	__declspec(dllimport) void* __stdcall GetCurrentThread();
	__declspec(dllimport) void* __stdcall CreateThread(void* security, unsigned long stackSize,
		unsigned long (__stdcall* start)(void* parameter), void* parameter, unsigned long flags, unsigned long* id);
	__declspec(dllimport) void* __stdcall GetCurrentProcess();
	__declspec(dllimport) int __stdcall GetProcessAffinityMask(void* process, unsigned long* processMask,
		unsigned long* systemMask);
	__declspec(dllimport) unsigned long __stdcall SetThreadAffinityMask(void* thread, unsigned long mask);
	__declspec(dllimport) unsigned long __stdcall TlsAlloc();
	__declspec(dllimport) int __stdcall TlsFree(unsigned long index);
	__declspec(dllimport) void* __stdcall CreateFiber(unsigned long stackSize, void (__stdcall* start)(void* parameter),
		void* parameter);
}
#pragma comment(linker, "/alternatename:__imp__GetVersionExA@4=__imp__GetVersionExA")
#pragma comment(linker, "/alternatename:__imp__ConvertFiberToThread@0=__imp__ConvertFiberToThread")
#pragma comment(linker, "/alternatename:__imp__Sleep@4=__imp__Sleep")
#pragma comment(linker, "/alternatename:__imp__GetCurrentThreadId@0=__imp__GetCurrentThreadId")
#pragma comment(linker, "/alternatename:__imp__CloseHandle@4=__imp__CloseHandle")
#pragma comment(linker, "/alternatename:__imp__ExitThread@4=__imp__ExitThread")
#pragma comment(linker, "/alternatename:__imp__TerminateThread@8=__imp__TerminateThread")
#pragma comment(linker, "/alternatename:__imp__WaitForSingleObject@8=__imp__WaitForSingleObject")
#pragma comment(linker, "/alternatename:__imp__TlsSetValue@8=__imp__TlsSetValue")
#pragma comment(linker, "/alternatename:__imp__TlsGetValue@4=__imp__TlsGetValue")
#pragma comment(linker, "/alternatename:__imp__ConvertThreadToFiber@4=__imp__ConvertThreadToFiber")
#pragma comment(linker, "/alternatename:__imp__SetThreadPriority@8=__imp__SetThreadPriority")
#pragma comment(linker, "/alternatename:__imp__SuspendThread@4=__imp__SuspendThread")
#pragma comment(linker, "/alternatename:__imp__ResumeThread@4=__imp__ResumeThread")
#pragma comment(linker, "/alternatename:__imp__GetExitCodeThread@8=__imp__GetExitCodeThread")
#pragma comment(linker, "/alternatename:__imp__DeleteFiber@4=__imp__DeleteFiber")
#pragma comment(linker, "/alternatename:__imp__SwitchToFiber@4=__imp__SwitchToFiber")
#pragma comment(linker, "/alternatename:__imp__GetCurrentThread@0=__imp__GetCurrentThread")
#pragma comment(linker, "/alternatename:__imp__CreateThread@24=__imp__CreateThread")
#pragma comment(linker, "/alternatename:__imp__GetCurrentProcess@0=__imp__GetCurrentProcess")
#pragma comment(linker, "/alternatename:__imp__GetProcessAffinityMask@12=__imp__GetProcessAffinityMask")
#pragma comment(linker, "/alternatename:__imp__SetThreadAffinityMask@8=__imp__SetThreadAffinityMask")
#pragma comment(linker, "/alternatename:__imp__TlsAlloc@0=__imp__TlsAlloc")
#pragma comment(linker, "/alternatename:__imp__TlsFree@4=__imp__TlsFree")
#pragma comment(linker, "/alternatename:__imp__CreateFiber@12=__imp__CreateFiber")

namespace core
{
	// 0x110BCCC8: the Win32 priority of each thread priority level
	extern int gThreadPriorities[];

	// GLOBAL: ENGINE 0x1127A470
	unsigned long sThreadTls;
	// GLOBAL: ENGINE 0x1127A8A0
	Thread gMainThread;
	// GLOBAL: ENGINE 0x1127A954
	Thread* gLastThread;
	// GLOBAL: ENGINE 0x1127A958
	Thread* gThreads;
	// GLOBAL: ENGINE 0x1127A95C
	int gFiberSlotDefaults[8];
	// GLOBAL: ENGINE 0x1127A97C
	int gThreadSlotDefaults[8];
	// GLOBAL: ENGINE 0x1127A99C
	unsigned char gThreadLock[0x18];
	// GLOBAL: ENGINE 0x1127A9BC
	bool gThreadsReady;

	// FUNCTION: ENGINE 0x10644890
	void InitThreadLock()
	{
		CriticalSectionInit(gThreadLock);
		gThreadsReady = true;
		InitThreadHook();
	}

	// FUNCTION: ENGINE 0x106448B0
	void ShutdownThreadLock()
	{
		ShutdownThreadHook();
		gThreadsReady = false;
		CriticalSectionDelete(gThreadLock);
	}

	// FUNCTION: ENGINE 0x106448D0
	inline void GetThreadSlotDefaults(Thread* thread)
	{
		thread->slots[0] = gThreadSlotDefaults[0];
		thread->slots[1] = gThreadSlotDefaults[1];
		thread->slots[2] = gThreadSlotDefaults[2];
		thread->slots[3] = gThreadSlotDefaults[3];
		thread->slots[4] = gThreadSlotDefaults[4];
		thread->slots[5] = gThreadSlotDefaults[5];
		thread->slots[6] = gThreadSlotDefaults[6];
		thread->slots[7] = gThreadSlotDefaults[7];
	}

	// FUNCTION: ENGINE 0x10644970
	void AddThread(Thread* thread)
	{
		CriticalSectionEnter(gThreadLock);
		if (gThreads == 0)
		{
			gThreads = thread;
			thread->previous = 0;
		}
		else
		{
			gLastThread->next = thread;
			thread->previous = gLastThread;
		}
		gLastThread = thread;
		thread->next = 0;
		CriticalSectionLeave(gThreadLock);
	}

	// FUNCTION: ENGINE 0x106449D0
	void RemoveThread(Thread* thread)
	{
		CriticalSectionEnter(gThreadLock);
		if (thread->previous == 0)
		{
			gThreads = thread->next;
		}
		else
		{
			thread->previous->next = thread->next;
		}
		if (thread->next == 0)
		{
			gLastThread = thread->previous;
		}
		else
		{
			thread->next->previous = thread->previous;
		}
		CriticalSectionLeave(gThreadLock);
	}

	// FUNCTION: ENGINE 0x10644A30
	void AddFiber(Thread* thread, Fiber* fiber)
	{
		fiber->slots[0] = gFiberSlotDefaults[0];
		fiber->slots[1] = gFiberSlotDefaults[1];
		fiber->slots[2] = gFiberSlotDefaults[2];
		fiber->slots[3] = gFiberSlotDefaults[3];
		fiber->slots[4] = gFiberSlotDefaults[4];
		fiber->slots[5] = gFiberSlotDefaults[5];
		fiber->slots[6] = gFiberSlotDefaults[6];
		fiber->slots[7] = gFiberSlotDefaults[7];
		if (thread->fibers == 0)
		{
			thread->fibers = fiber;
			fiber->previous = 0;
		}
		else
		{
			thread->lastFiber->next = fiber;
			fiber->previous = thread->lastFiber;
		}
		thread->lastFiber = fiber;
		fiber->next = 0;
	}

	// FUNCTION: ENGINE 0x10644AB0
	inline void RemoveFiber(Thread* thread, Fiber* fiber)
	{
		if (fiber->previous == 0)
		{
			thread->fibers = fiber->next;
		}
		else
		{
			fiber->previous->next = fiber->next;
		}
		if (fiber->next == 0)
		{
			thread->lastFiber = fiber->previous;
		}
		else
		{
			fiber->next->previous = fiber->previous;
		}
	}

	// FUNCTION: ENGINE 0x10644AF0
	void ThreadNop()
	{
	}

	// FUNCTION: ENGINE 0x10644B00
	void LeaveFiberMode()
	{
		OSVERSIONINFOA version;
		version.dwOSVersionInfoSize = sizeof(version);
		GetVersionExA(&version);
		if (version.dwMajorVersion >= 5 && version.dwMinorVersion >= 1)
		{
			ConvertFiberToThread();
		}
	}

	// FUNCTION: ENGINE 0x10644B40
	void ThreadSleep(int milliseconds)
	{
		Sleep(milliseconds);
	}

	// FUNCTION: ENGINE 0x10644B50
	bool IsCurrentThread(Thread* thread)
	{
		return thread->id == GetCurrentThreadId();
	}

	// FUNCTION: ENGINE 0x10644B70
	void DestroyThread(Thread* thread)
	{
		RemoveThread(thread);
		CriticalSectionEnter(gThreadLock);
		if (thread->running)
		{
			if (IsCurrentThread(thread))
			{
				CriticalSectionLeave(gThreadLock);
				CloseHandle(thread->handle);
				ExitThread(0);
			}
			TerminateThread(thread->handle, 0);
			CloseHandle(thread->handle);
			CriticalSectionLeave(gThreadLock);
			return;
		}
		CriticalSectionLeave(gThreadLock);
		WaitForSingleObject(thread->handle, 0xFFFFFFFF);
		CloseHandle(thread->handle);
	}

	// FUNCTION: ENGINE 0x10644C20
	int GetThreadValue(Thread* thread)
	{
		CriticalSectionEnter(gThreadLock);
		int value = thread->unknown88;
		CriticalSectionLeave(gThreadLock);
		return value;
	}

	// FUNCTION: ENGINE 0x10644C50
	bool IsThreadBusy(Thread* thread)
	{
		CriticalSectionEnter(gThreadLock);
		bool busy = thread->unknown84 != 0 || thread->unknown88 > 0;
		CriticalSectionLeave(gThreadLock);
		return busy;
	}

	// FUNCTION: ENGINE 0x10644CA0
	static unsigned long __stdcall ThreadEntry(void* parameter)
	{
		Thread* thread = (Thread*)parameter;
		TlsSetValue(sThreadTls, thread);
		thread->fiber.handle = ConvertThreadToFiber(0);
		thread->exitCode = thread->fiber.function(thread->fiber.argument);
		LeaveFiberMode();
		thread->running = false;
		return 0;
	}

	// FUNCTION: ENGINE 0x10644CE0
	int GetZero()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10644CF0
	void SetThreadPriority(Thread* thread, int priority)
	{
		thread->priority = priority;
		::SetThreadPriority(thread->handle, gThreadPriorities[priority]);
	}

	// FUNCTION: ENGINE 0x10644D20
	int GetThreadPriority(Thread* thread)
	{
		return thread->priority;
	}

	// FUNCTION: ENGINE 0x10644D30
	unsigned long SuspendThread(Thread* thread)
	{
		return ::SuspendThread(thread->handle);
	}

	// FUNCTION: ENGINE 0x10644D50
	unsigned long ResumeThread(Thread* thread)
	{
		return ::ResumeThread(thread->handle);
	}

	// FUNCTION: ENGINE 0x10644D70
	bool IsThreadRunning(Thread* thread, int* exitCode)
	{
		if (thread->running)
		{
			return true;
		}
		*exitCode = thread->exitCode;
		return false;
	}

	// FUNCTION: ENGINE 0x10644D90
	int WaitThread(Thread* thread)
	{
		unsigned long code;
		WaitForSingleObject(thread->handle, 0xFFFFFFFF);
		GetExitCodeThread(thread->handle, &code);
		return code;
	}

	// FUNCTION: ENGINE 0x10644DC0
	int GetThreadData()
	{
		return (int)TlsGetValue(sThreadTls);
	}

	// FUNCTION: ENGINE 0x10644DD0
	Fiber* GetCurrentFiber()
	{
		Thread* thread = (Thread*)GetThreadData();
		if (thread == 0)
		{
			return 0;
		}
		return thread->current;
	}

	// FUNCTION: ENGINE 0x10644DE0
	// The fibers threads run as are not deleted, only unlinked
	void DestroyFiber(Fiber* fiber)
	{
		if (fiber != &gMainThread.fiber && fiber != &fiber->thread->fiber)
		{
			DeleteFiber(fiber->handle);
		}
		RemoveFiber(fiber->thread, fiber);
	}

	// FUNCTION: ENGINE 0x10644E30
	void SwitchFiber(Fiber* fiber)
	{
		Fiber* current = GetCurrentFiber();
		((Thread*)GetThreadData())->current = fiber;
		if (current->trackStack)
		{
			void* stack;
			__asm mov stack, esp
		}
		SwitchToFiber(fiber->handle);
	}

	// FUNCTION: ENGINE 0x10644E60
	static void __stdcall FiberEntry(void* parameter)
	{
		Fiber* fiber = GetCurrentFiber();
		if (fiber->trackStack)
		{
			void* stack;
			__asm mov stack, esp
			fiber->stack = stack;
		}
		fiber->function(fiber->argument);
	}

	// FUNCTION: ENGINE 0x10644E90
	int GetZero2()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10644EA0
	int GetZero3()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10644EB0
	void* GetFiberArgument(Fiber* fiber)
	{
		return fiber->argument;
	}

	// FUNCTION: ENGINE 0x10644EC0
	// EQUIVALENT: the push of ConvertThreadToFiber's argument is scheduled one store earlier (before the last slot
	// copy); every statement order tried keeps it there
	// Makes the calling thread a Thread of its own (its fiber included)
	void InitMainThread(Thread* thread)
	{
		thread->fibers = 0;
		thread->lastFiber = 0;
		thread->running = true;
		thread->id = GetCurrentThreadId();
		thread->handle = GetCurrentThread();
		thread->fiber.function = 0;
		thread->fiber.argument = 0;
		thread->unknown84 = 0;
		thread->unknown88 = 0;
		TlsSetValue(sThreadTls, thread);
		GetThreadSlotDefaults(thread);
		thread->fiber.stack = 0;
		thread->fiber.handle = ConvertThreadToFiber(0);
		thread->fiber.thread = thread;
		thread->current = &thread->fiber;
		AddFiber(thread, &thread->fiber);
		AddThread(thread);
		SetThreadPriority(thread, 2);
	}

	// FUNCTION: ENGINE 0x10644F90
	void ShutdownMainThread()
	{
		DestroyFiber(&gMainThread.fiber);
		RemoveThread(&gMainThread);
		LeaveFiberMode();
	}

	// FUNCTION: ENGINE 0x10644FB0
	// The thread starts suspended, gets its priority, processor (-1: any of the process) and name, then runs
	unsigned long CreateThread(Thread* thread, int (*function)(void* argument), void* argument, int priority,
		int stackSize, int* processor, const char* name)
	{
		thread->running = true;
		thread->fibers = 0;
		thread->current = &thread->fiber;
		thread->fiber.function = function;
		thread->fiber.argument = argument;
		thread->fiber.thread = thread;
		thread->fiber.handle = 0;
		thread->fiber.trackStack = false;
		thread->fiber.unknown3C = 0;
		thread->unknown88 = 0;
		thread->unknown84 = 0;
		AddFiber(thread, &thread->fiber);
		AddThread(thread);
		GetThreadSlotDefaults(thread);
		thread->handle = ::CreateThread(0, stackSize, ThreadEntry, thread, 4, &thread->id);
		SetThreadPriority(thread, priority);
		if (processor != 0)
		{
			if (*processor == -1)
			{
				unsigned long processMask;
				unsigned long systemMask;
				GetProcessAffinityMask(GetCurrentProcess(), &processMask, &systemMask);
				SetThreadAffinityMask(thread->handle, processMask);
			}
			else
			{
				SetThreadAffinityMask(thread->handle, 1 << *processor);
			}
		}
		StrNCpy(thread->name, name, sizeof(thread->name));
		return ::ResumeThread(thread->handle);
	}

	// FUNCTION: ENGINE 0x106450F0
	void StartThread(Thread* thread, int (*function)(void* argument), void* argument, int priority, int stackSize,
		int unused, int* processor, const char* name)
	{
		CreateThread(thread, function, argument, priority, stackSize, processor, name);
	}

	// FUNCTION: ENGINE 0x10645120
	void InitMemoryStage3(int count)
	{
		CriticalSectionInit(gThreadLock);
		gThreadsReady = true;
		InitThreadHook();
		sThreadTls = TlsAlloc();
		InitMainThread(&gMainThread);
	}

	// FUNCTION: ENGINE 0x10645160
	void ShutdownThreads()
	{
		ShutdownMainThread();
		TlsFree(sThreadTls);
		ShutdownThreadHook();
		gThreadsReady = false;
		CriticalSectionDelete(gThreadLock);
	}

	// FUNCTION: ENGINE 0x10645190
	// EQUIVALENT: the original keeps the Enter argument on the stack until after the Leave call (one add esp, 8)
	// instead of ending in a jump to Leave; ClearThreadValue right below does end in the jump
	void SetThreadValue(int value)
	{
		Thread* thread = (Thread*)GetThreadData();
		CriticalSectionEnter(gThreadLock);
		thread->unknown88 = value;
		CriticalSectionLeave(gThreadLock);
	}

	// FUNCTION: ENGINE 0x106451C0
	void ClearThreadValue(int unused)
	{
		Thread* thread = (Thread*)GetThreadData();
		CriticalSectionEnter(gThreadLock);
		thread->unknown88 = 0;
		CriticalSectionLeave(gThreadLock);
	}

	// FUNCTION: ENGINE 0x106451F0
	void CreateFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int unused1, int stackSize,
		int track, int unused2, int unused3)
	{
		fiber->trackStack = track != 0;
		fiber->function = function;
		fiber->unknown3C = track;
		fiber->argument = argument;
		fiber->thread = (Thread*)GetThreadData();
		AddFiber(fiber->thread, fiber);
		fiber->handle = ::CreateFiber(stackSize, FiberEntry, fiber);
		fiber->stack = 0;
	}

	// FUNCTION: ENGINE 0x10645240
	void CreateFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int stackSize, int a, int b)
	{
		CreateFiber(fiber, function, argument, 0, stackSize, 0, a, b);
	}

	// FUNCTION: ENGINE 0x10645270
	void CreateFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int stackSize, int b)
	{
		CreateFiber(fiber, function, argument, 0, stackSize, 0, -1, b);
	}

	// FUNCTION: ENGINE 0x106452A0
	void CreateTrackedFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int stackSize, int a, int b)
	{
		CreateFiber(fiber, function, argument, 0, stackSize, stackSize, a, b);
	}

	// FUNCTION: ENGINE 0x106452D0
	void CreateTrackedFiber(Fiber* fiber, int (*function)(void* argument), void* argument, int stackSize, int b)
	{
		CreateFiber(fiber, function, argument, 0, stackSize, stackSize, -1, b);
	}
}
