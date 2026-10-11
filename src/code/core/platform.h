// core::IPlatformWin32 and core::Platform (RTTI names; vftables 0x10E47584 / 0x10E475AC, 9 slots): the Win32
// platform object, built in static storage by PlatformInit: the application window and instance, COM
// initialisation, a chain of window-message hooks that subclass the window, and two 256-byte strings. Unit
// 0x10647BF0 - 0x10647F5A (no assert path; file name platform.cpp and all names guessed). Windows types are plain
// pointers and integers (the toolchain has no SDK headers).
#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

#include "code/core/memory/imemoryallocator.h"

namespace core
{
	// Told about every message of the subclassed window, in the order the hooks were added (newest first)
	struct IWindowHook
	{
		virtual void OnMessage(void* window, unsigned int message, unsigned int wParam, long lParam) = 0;

		IWindowHook* next;
	};

	struct IPlatformWin32 : IRefCount
	{
		// The application window, else the foreground window, else the desktop
		virtual void* GetWindow() = 0;
		virtual void* GetInstance() = 0;
		// The first hook subclasses the window, removing the last one restores its procedure
		virtual void AddHook(IWindowHook* hook) = 0;
		virtual void RemoveHook(IWindowHook* hook) = 0;
		// Copy the two strings given to PlatformInit (256 bytes)
		virtual void GetName(char* buffer) = 0;
		virtual void GetPath(char* buffer) = 0;
	};

	class Platform : public IPlatformWin32
	{
	public:
		virtual ~Platform();
		// A plain count; nothing is destroyed when it reaches zero
		virtual void AddRef();
		virtual void Release();
		virtual void* GetWindow();
		virtual void* GetInstance();
		virtual void AddHook(IWindowHook* hook);
		virtual void RemoveHook(IWindowHook* hook);
		virtual void GetName(char* buffer);
		virtual void GetPath(char* buffer);

		// The object lives in static storage
		static void* operator new(unsigned int size, void* place);
		void Reset(int value);
		void Init(void* window, void* instance, int value, const char* name, const char* path);
		void Uninit();

		void* window;
		void* instance;
		// The window procedure the hooks replaced
		long previousProc;
		IWindowHook* hooks;
		int refCount;
		bool comInitialised;
		int value;
		char name[0x100];
		char path[0x100];
	};

	// 0x1127ABE4: the platform object (in static storage), null before PlatformInit
	extern Platform* gPlatform;

	IPlatformWin32* GetPlatform();
	void GetPlatformInfo(int* a, int* b);
	void PlatformInit(void* window, void* instance, int value, const char* name, const char* path);
	void PlatformShutdown();
}

#endif
