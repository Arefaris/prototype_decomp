// The PC keyboard (engine::controller::KeyboardWin32; 0x108D6A80 - 0x108D6D90).
#include "code/engine/controller/keyboardwin32.h"

// user32 / kernel32, dllimport with the relinker's undecorated slot names
extern "C"
{
	__declspec(dllimport) unsigned long __stdcall GetCurrentThreadId();
	__declspec(dllimport) void* __stdcall GetKeyboardLayout(unsigned long thread);
	__declspec(dllimport) unsigned int __stdcall MapVirtualKeyExA(unsigned int code, unsigned int mapType, void* layout);
}
#pragma comment(linker, "/alternatename:__imp__GetCurrentThreadId@0=__imp__GetCurrentThreadId")
#pragma comment(linker, "/alternatename:__imp__GetKeyboardLayout@4=__imp__GetKeyboardLayout")
#pragma comment(linker, "/alternatename:__imp__MapVirtualKeyExA@12=__imp__MapVirtualKeyExA")

namespace engine
{
	namespace controller
	{
		KeyboardWin32* gKeyboard;  // 0x11318A28

		void KeyboardWin32::AddModifiers(unsigned int flags)
		{
			modifiers |= flags;
		}

		void KeyboardWin32::RemoveModifiers(unsigned int flags)
		{
			modifiers &= ~flags;
		}

		KeyboardWin32* KeyboardWin32::Get()
		{
			return gKeyboard;
		}

		unsigned int KeyboardWin32::GetScanCode(unsigned int key)
		{
			return MapVirtualKeyExA(key, 0, GetKeyboardLayout(GetCurrentThreadId()));
		}

		// FUNCTION: ENGINE 0x108D6AD0
		// EQUIVALENT: register allocation of the flags and the modifier, and the engine zero-extends the shifted byte before it masks the repeat bit (43.0 %)
		void KeyboardWin32::OnKeyMessage(int message, int key, unsigned int flags, bool capsLock, bool numLock)
		{
			if (enabled)
			{
				if (capsLock)
				{
					modifiers |= 8;
				}
				else
				{
					modifiers &= ~8u;
				}
				if (numLock)
				{
					modifiers |= 0x10;
				}
				else
				{
					modifiers &= ~0x10u;
				}
				if (flags & 0x20000000)
				{
					modifiers |= 1;
				}
				else
				{
					modifiers &= ~1u;
				}
				unsigned int flag = 0;
				switch (key)
				{
				case 0x10:
					flag = 4;
					break;
				case 0x11:
					flag = 2;
					break;
				}
				int state;
				switch (message)
				{
				case 0x100:
					state = (unsigned char)(flags >> 30) & 1;
					modifiers |= flag;
					break;
				case 0x101:
					modifiers &= ~flag;
					state = 2;
					break;
				default:
					return;
				}
				if (eventCount < 16)
				{
					events[eventCount].state = state;
					events[eventCount].key = key;
					events[eventCount].modifiers = modifiers;
					events[eventCount].character = GetCharacter(key, modifiers);
					events[eventCount].scanCode = GetScanCode(key);
					eventCount++;
				}
			}
		}

		void KeyboardWin32::Update(float time)
		{
			if (callbacks.count != 0)
			{
				for (int i = 0; i < eventCount; i++)
				{
					for (Callback* callback = callbacks.First(); callback != 0; callback = callbacks.Next(callback))
					{
						callback->OnKey(events[i]);
					}
				}
			}
			eventCount = 0;
		}

		KeyboardWin32::KeyboardWin32() :
			eventCount(0),
			events(0),
			enabled(false),
			modifiers(0)
		{
			events = new KeyEvent[16];
		}

		bool KeyboardWin32::IsEnabled()
		{
			return enabled;
		}

		void KeyboardWin32::SetEnabled(bool newEnabled)
		{
			enabled = newEnabled;
		}

		KeyboardWin32::~KeyboardWin32()
		{
			delete events;
		}

		void CreateKeyboard()
		{
			if (gKeyboard == 0)
			{
				gKeyboard = new KeyboardWin32();
			}
		}

		void DestroyKeyboard()
		{
			if (gKeyboard != 0)
			{
				delete gKeyboard;
				gKeyboard = 0;
			}
		}
	}
}

// ---- annotations of the functions mapped in symbols.txt (generated) ----

// FUNCTION: ENGINE 0x108D6A80 @ void engine::controller::KeyboardWin32::AddModifiers(unsigned int)
// FUNCTION: ENGINE 0x108D6A90 @ void engine::controller::KeyboardWin32::RemoveModifiers(unsigned int)
// FUNCTION: ENGINE 0x108D6AA0 @ engine::controller::KeyboardWin32 * engine::controller::KeyboardWin32::Get(void)
// FUNCTION: ENGINE 0x108D6BC0 @ engine::controller::Keyboard::Callback * container::SListLite<engine::controller::Keyboard::Callback>::First(void)const  (name guess; identical copies)
// FUNCTION: ENGINE 0x108D6BE0 @ void engine::controller::KeyboardWin32::Update(float)
// FUNCTION: ENGINE 0x108D6C70 @ engine::controller::Keyboard::~Keyboard(void)
// FUNCTION: ENGINE 0x108D6C90 @ engine::controller::KeyboardWin32::KeyboardWin32(void)
// FUNCTION: ENGINE 0x108D6CC0 @ bool engine::controller::KeyboardWin32::IsEnabled(void)
// FUNCTION: ENGINE 0x108D6CD0 @ void engine::controller::KeyboardWin32::SetEnabled(bool)
// FUNCTION: ENGINE 0x108D6CE0 @ engine::controller::KeyboardWin32::~KeyboardWin32(void)
// FUNCTION: ENGINE 0x108D6D10 @ void engine::controller::CreateKeyboard(void)
// FUNCTION: ENGINE 0x108D6D40 @ void * engine::controller::KeyboardWin32::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108D6D60 @ void engine::controller::DestroyKeyboard(void)
