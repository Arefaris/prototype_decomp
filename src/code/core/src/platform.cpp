#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "code/core/platform.h"
#include "code/core/strings.h"

// The user32 / ole32 imports, declared as the import-table slots (see sync.cpp)
extern "C"
{
	extern void* (__stdcall* _imp__GetForegroundWindow)();
	extern void* (__stdcall* _imp__GetDesktopWindow)();
	extern long (__stdcall* _imp__SetWindowLongA)(void* window, int index, long value);
	extern long (__stdcall* _imp__CallWindowProcA)(long procedure, void* window, unsigned int message, unsigned int wParam, long lParam);
	extern long (__stdcall* _imp__CoInitialize)(void* reserved);
	extern void (__stdcall* _imp__CoUninitialize)();
}

namespace core
{
	const char* CoreName();

	// GLOBAL: ENGINE 0x1127A9C0
	static unsigned char sPlatformStorage[0x220];
	// GLOBAL: ENGINE 0x1127ABE4
	Platform* gPlatform;
	// Read by GetPlatformInfo only (nothing writes them)
	// GLOBAL: ENGINE 0x1127ABE8
	static int sPlatformInfoA;
	// GLOBAL: ENGINE 0x110BCF18
	static int sPlatformInfoB = -1;

	// FUNCTION: ENGINE 0x10647C00
	// Installed with _set_purecall_handler: a pure call does nothing
	static void __cdecl PurecallHandler()
	{
	}

	// FUNCTION: ENGINE 0x10647C10
	// Empty and unreferenced
	void PlatformUpdate()
	{
	}

	// FUNCTION: ENGINE 0x10647C20
	void GetPlatformInfo(int* a, int* b)
	{
		*a = sPlatformInfoA;
		*b = sPlatformInfoB;
	}

	// FUNCTION: ENGINE 0x10647C40
	IPlatformWin32* GetPlatform()
	{
		return gPlatform;
	}

	// FUNCTION: ENGINE 0x10647C50
	Platform::~Platform()
	{
	}

	// FUNCTION: ENGINE 0x10647C60
	void* Platform::operator new(unsigned int size, void* place)
	{
		return place;
	}

	// FUNCTION: ENGINE 0x10647C70
	void Platform::Reset(int value)
	{
		window = 0;
		instance = 0;
		refCount = 0;
		comInitialised = false;
		this->value = value;
	}

	// FUNCTION: ENGINE 0x10647C90
	void Platform::AddRef()
	{
		refCount++;
	}

	// FUNCTION: ENGINE 0x10647CA0
	void Platform::Release()
	{
		refCount--;
	}

	// FUNCTION: ENGINE 0x10647CB0
	void Platform::Uninit()
	{
		comInitialised = false;
		_imp__CoUninitialize();
	}

	// FUNCTION: ENGINE 0x10647CC0
	void* Platform::GetWindow()
	{
		if (window != 0)
		{
			return window;
		}
		void* foreground = _imp__GetForegroundWindow();
		if (foreground != 0)
		{
			return foreground;
		}
		return _imp__GetDesktopWindow();
	}

	// FUNCTION: ENGINE 0x10647CE0
	void* Platform::GetInstance()
	{
		return instance;
	}

	// FUNCTION: ENGINE 0x10647CF0
	void Platform::RemoveHook(IWindowHook* hook)
	{
		for (IWindowHook** link = &hooks; *link != 0; link = &(*link)->next)
		{
			if (*link == hook)
			{
				*link = hook->next;
				break;
			}
		}
		if (hooks == 0 && window != 0)
		{
			_imp__SetWindowLongA(window, -4, previousProc);
		}
	}

	// FUNCTION: ENGINE 0x10647D40
	void Platform::GetName(char* buffer)
	{
		StrNCpy(buffer, name, 0x100u);
	}

	// FUNCTION: ENGINE 0x10647D60
	void Platform::GetPath(char* buffer)
	{
		StrNCpy(buffer, path, 0x100u);
	}

	// FUNCTION: ENGINE 0x10647D80
	// The procedure of the subclassed window: every hook sees the message, then the previous procedure handles it
	static long __stdcall PlatformWindowProc(void* window, unsigned int message, unsigned int wParam, long lParam)
	{
		for (IWindowHook* hook = gPlatform->hooks; hook != 0; hook = hook->next)
		{
			hook->OnMessage(window, message, wParam, lParam);
		}
		return _imp__CallWindowProcA(gPlatform->previousProc, window, message, wParam, lParam);
	}

	// FUNCTION: ENGINE 0x10647DF0
	void PlatformShutdown()
	{
		gPlatform->Uninit();
		gPlatform->~Platform();
	}

	// FUNCTION: ENGINE 0x10647E10
	void Platform::Init(void* window, void* instance, int value, const char* name, const char* path)
	{
		StrNCpy(this->name, name, 0x100u);
		StrNCpy(this->path, path, 0x100u);
		CoreName();
		this->value = value;
		comInitialised = true;
		this->window = window;
		this->instance = instance;
		hooks = 0;
		_imp__CoInitialize(0);
		_set_purecall_handler(PurecallHandler);
	}

	// FUNCTION: ENGINE 0x10647E80
	void Platform::AddHook(IWindowHook* hook)
	{
		if (hooks == 0 && window != 0)
		{
			previousProc = _imp__SetWindowLongA(window, -4, (long)PlatformWindowProc);
		}
		hook->next = hooks;
		hooks = hook;
	}

	// FUNCTION: ENGINE 0x10647EF0
	// Builds the platform object; the x87 precision is set to 64 bits
	void PlatformInit(void* window, void* instance, int value, const char* name, const char* path)
	{
		unsigned int control;
		_set_printf_count_output(1);
		Platform* platform = new(sPlatformStorage) Platform;
		gPlatform = platform;
		platform->Reset(value);
		platform->Init(window, instance, value, name, path);
		_controlfp_s(&control, 0x30000, 0);
	}
}
