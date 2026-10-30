// engine::DialogState and engine::FEPopUpDialogState (RTTI names): the modal dialogs of the front end. A dialog state
// keeps the implementation object that talks to the movie (0xC0 bytes, another unit) and answers the overlay calls;
// the pop-up dialog adds a title, a message and the buttons the movie asks for (GetTitle, GetMessage, GetButtonCount,
// GetButton) and takes the answer (SetButton). Unit 0x10883CB0 - 0x10883FE0 (no assert path; the directory and file
// name are guesses). Names other than the RTTI ones are guesses.
#ifndef ENGINE_FRONTEND_DIALOGSTATE_H
#define ENGINE_FRONTEND_DIALOGSTATE_H

#include "code/engine/frontend/femovie.h"

namespace engine
{
	class PrivateDialogState;

	// What the movie calls a dialog with (0x10883EB0: the name of the function at +8, the first argument at +0x18)
	struct DialogCall
	{
		unsigned char unknown0[8];
		const char* name;
		unsigned char unknownC[0x18 - 0xC];
		double argument;
	};

	class DialogState
	{
	public:
		// 0x10883CB0: makes the implementation object
		DialogState(int a, int b, const char* overlay, int c);
		// 0x10883DF0 (deleting destructor 0x10883E10)
		virtual ~DialogState();

		// vftable slots 1 - 7: the defaults do nothing (0x10883D00, 0x108829B0, 0x108829C0, 0x108829D0, 0x108829E0,
		// 0x10883D10, 0x10883D20)
		virtual void Slot1()
		{
		}
		virtual void Slot2()
		{
		}
		virtual void Slot3(int a, int b, int c)
		{
		}
		virtual void Slot4()
		{
		}
		virtual void Slot5()
		{
		}
		virtual void Slot6()
		{
		}
		// The movie calls a function of the dialog
		virtual void OnCall(DialogCall* call, int unused, FEMovie::Value* result)
		{
		}

		// 0x10883D50, 0x10883D60, 0x10883D70: forwarded to the implementation object (names unknown)
		bool Unknown10883D50(int controller, int flag);
		void Unknown10883D60();
		bool Unknown10883D70();
		// 0x10883D80
		bool Unknown10883D80();
		// 0x10883D90: the icon of the dialog and whether it is shown
		void SetIcon(int icon, bool visible);
		// 0x10883DA0, 0x10883DB0, 0x10883DC0
		void Unknown10883DA0();
		void Unknown10883DB0();
		void Unknown10883DC0();
		// 0x10883DD0: the controller the dialog listens to
		void GetController(int* controller);

		PrivateDialogState* impl;  // +4
	};

	class FEPopUpDialogState : public DialogState
	{
	public:
		// 0x10883E30
		FEPopUpDialogState(const char* newTitle, const char* newMessage, const char** newButtons, int newButtonCount,
			int a, int b, int c, const char* overlay);
		// 0x10883E80 (deleting destructor 0x10883FC0)
		virtual ~FEPopUpDialogState();

		// vftable slot 7 (0x10883EB0)
		virtual void OnCall(DialogCall* call, int unused, FEMovie::Value* result);

		// 0x10883E90: the button picked: -1 for none and -2 while the dialog is still open
		int GetResult();

		const char* title;  // +8
		const char* message;  // +0xC
		const char** buttons;  // +0x10
		int buttonCount;  // +0x14
		int selected;  // +0x18
	};
}

#endif
