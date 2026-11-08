// engine::StorageManager::StorageDialogState (RTTI name): the dialog the storage manager shows for its messages and for the
// choice of a save slot (the overlay "STORAGE_OVERLAY"). It is a DialogState that answers the calls of the overlay's
// script (titles, buttons, the slots with their names, icons, dates) and keeps the button that was picked and the slot
// that was selected. Unit 0x108E24D0 - 0x108E2E50 (no assert path; file name guessed; the names other than the RTTI
// ones are guesses).
#ifndef ENGINE_FRONTEND_STORAGEDIALOG_H
#define ENGINE_FRONTEND_STORAGEDIALOG_H

#include "code/engine/frontend/dialogstate.h"

namespace core
{
	struct Fiber;
}

namespace engine
{
	namespace StorageManager
	{
		// The time a save slot was made at (the dialog shows it as a date and a time)
		struct SlotTime
		{
			unsigned short year;  // +0
			unsigned char month;  // +2
			unsigned char day;  // +3
			unsigned char hour;  // +4
			unsigned char minute;  // +5
		};

		// RTTI: engine::StorageManager::StorageDialogState (8 vftable slots, 0x54 bytes)
		class StorageDialogState : public DialogState
		{
		public:
			struct Button
			{
				const char* label;  // +0
				int id;  // +4
			};

			// 0x108E25E0
			StorageDialogState();
			// 0x108E2600 (deleting destructor 0x108E2C60)
			virtual ~StorageDialogState();

			// vftable slot 5 (0x108E2C00): the dialog was closed from outside
			virtual void Slot5();
			// vftable slot 7 (0x108E27A0)
			virtual void OnCall(DialogCall* call, int unused, FEMovie::Value* result);

			// 0x108E2620 / 0x108E2610: the button that was picked (0: none yet) and the slot that was selected
			int GetResult();
			int GetSelection();
			// 0x108E2630: the buttons of the kind of message
			void SetupButtons();
			// 0x108E2C80: a message
			void SetupMessage(const char* newTitle, const char* newMessage, int newKind, const unsigned short* newSlotName);
			// 0x108E2CB0: the choice of a slot
			void SetupSelection(const char* newTitle, const char* newMessage, int newKind, const unsigned short** newNames,
				SlotTime** newDates, int* newIcons, const unsigned short** newDetails, int newCount, int newDefault);

			const char* title;  // +8
			const char* message;  // +0xC
			int kind;  // +0x10
			const unsigned short* slotName;  // +0x14
			int* icons;  // +0x18
			const unsigned short** details;  // +0x1C
			const unsigned short** names;  // +0x20
			SlotTime** dates;  // +0x24
			int count;  // +0x28
			int defaultSelection;  // +0x2C
			int result;  // +0x30
			int selection;  // +0x34
			Button buttons[3];  // +0x38
			int buttonCount;  // +0x50
		};

		// 0x108E2C10: makes the dialog in the heap
		void CreateDialog(int heap);
		// 0x108E24D0
		void DestroyDialog();
		// 0x108E2570: whether the dialog is over
		bool IsDialogDone();
		// 0x108E2580: shows the icon of the auto save
		void ShowAutoSaveIcon();
		// 0x108E24F0: closes the dialog and waits for it to go (switching to the fiber while it does)
		void CloseDialog(core::Fiber* fiber);
		// 0x108E2D10: shows a message and waits for the button (answers 1 when the storage state is up already)
		int ShowMessage(const char* title, const char* message, int kind, core::Fiber* fiber,
			const unsigned short* slotName);
		// 0x108E2D90: shows a message without waiting
		bool ShowMessageNoWait(const char* title, const char* message, const unsigned short* slotName);
		// 0x108E2DC0: shows the choice of a slot and waits; the slot goes to selection
		int ShowSelection(const char* title, const char* message, int kind, core::Fiber* fiber, int* selection,
			const unsigned short** names, SlotTime** dates, int* icons, const unsigned short** details, int count,
			int defaultSelection);
	}
}

#endif
