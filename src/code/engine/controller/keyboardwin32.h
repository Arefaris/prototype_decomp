// engine::controller::KeyboardWin32 (RTTI name; base engine::controller::Keyboard): the PC keyboard. The window's key
// messages are turned into events (a state, the key, the modifier flags, the character and the scan code) that wait in
// a queue of 16; Update hands them to the keyboard's callbacks. Unit 0x108D6A80 - 0x108D6D90 (no assert path; the
// file name is a guess). Names other than the RTTI ones are guesses.
#ifndef ENGINE_CONTROLLER_KEYBOARDWIN32_H
#define ENGINE_CONTROLLER_KEYBOARDWIN32_H

#include "code/engine/controller/inputsystem.h"

namespace engine
{
	namespace controller
	{
		class KeyboardWin32 : public Keyboard
		{
		public:
			// 0x108D6C90: a queue for 16 events
			KeyboardWin32();
			// 0x108D6CE0 (the deleting destructor 0x108D6D40)
			~KeyboardWin32();

			// vftable slots 0 - 2 (0x108D6BE0, 0x108D6CC0, 0x108D6CD0): hands the events to the callbacks and empties the
			// queue; the keyboard is on while it listens
			virtual void Update(float time);
			virtual bool IsEnabled();
			virtual void SetEnabled(bool enabled);

			// 0x108D6A80 / 0x108D6A90
			void AddModifiers(unsigned int flags);
			void RemoveModifiers(unsigned int flags);
			// 0x108D6AA0: the one keyboard
			static KeyboardWin32* Get();
			// 0x108D6AD0: a key message of the window (message 0x100 and 0x101 are queued; the flags are the window's
			// repeat count flags)
			void OnKeyMessage(int message, int key, unsigned int flags, bool capsLock, bool numLock);
			// 0x108D6AB0: the scan code of a key on the keyboard layout of the thread
			unsigned int GetScanCode(unsigned int key);

			int eventCount;  // +0x2C
			KeyEvent* events;  // +0x30
			bool enabled;  // +0x34
			unsigned int modifiers;  // +0x38
		};

		// 0x108D6D10 / 0x108D6D60: make the one keyboard and take it down
		void CreateKeyboard();
		void DestroyKeyboard();
	}
}

#endif
