// The storage manager's dialog (unit 0x108E24D0 - 0x108E2E50; no assert path, file name guessed).
#include "code/engine/frontend/storagedialog.h"
#include "code/engine/frontend/feoverlay.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/core/thread.h"

namespace core
{
	// 0x1063B990 (the count returning form)
	int SNPrintfCount(char* buffer, int size, const char* format, ...);
}

namespace engine
{
	int GetGameStateStatus(int id);
}

namespace engine
{
	namespace StorageManager
	{
		// The dialog (0x1131AA70)
		StorageDialogState* gDialog;

		// FUNCTION: ENGINE 0x108E24D0
		void DestroyDialog()
		{
			delete gDialog;
		}

		// FUNCTION: ENGINE 0x108E24F0
		void CloseDialog(core::Fiber* fiber)
		{
			if (gDialog->Unknown10883D80())
			{
				if (fiber != 0)
				{
					while (!gDialog->Unknown10883D70())
					{
						core::SwitchFiber(fiber);
					}
				}
				gDialog->Unknown10883D60();
				if (fiber != 0)
				{
					while (gDialog->Unknown10883D80())
					{
						core::SwitchFiber(fiber);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x108E2570
		bool IsDialogDone()
		{
			return gDialog->Unknown10883D80();
		}

		// FUNCTION: ENGINE 0x108E2580
		void ShowAutoSaveIcon()
		{
			FEMovie::Value argument;
			argument.type = 2;
			argument.flag = true;
			((FrontendMovie*)Unknown10864330())->Invoke("AS_ShowAutoSaveIcon", &argument, 1);
		}

		// FUNCTION: ENGINE 0x108E2620
		int StorageDialogState::GetResult()
		{
			return result;
		}

		// FUNCTION: ENGINE 0x108E2610
		int StorageDialogState::GetSelection()
		{
			return selection;
		}

		// FUNCTION: ENGINE 0x108E25E0
		StorageDialogState::StorageDialogState() : DialogState(5, 0x13, "STORAGE_OVERLAY", (int)"StorageDialog")
		{
		}

		// FUNCTION: ENGINE 0x108E2600
		StorageDialogState::~StorageDialogState()
		{
		}

		// FUNCTION: ENGINE 0x108E2C00
		void StorageDialogState::Slot5()
		{
			result = 7;
			selection = -1;
		}

		// FUNCTION: ENGINE 0x108E2630
		void StorageDialogState::SetupButtons()
		{
			switch (kind)
			{
			case 0:
				buttonCount = 0;
				return;
			case 1:
				buttonCount = 1;
				buttons[0].id = 1;
				buttons[0].label = "$OK";
				return;
			case 2:
				buttonCount = 2;
				buttons[1].id = 2;
				break;
			case 3:
				buttonCount = 2;
				buttons[1].label = "$SELECTDEVICE";
				buttons[1].id = 6;
				buttons[0].id = 1;
				buttons[0].label = "$OK";
				return;
			case 4:
				buttonCount = 2;
				buttons[0].label = "$RETRY";
				buttons[0].id = 3;
				buttons[1].label = "$CANCEL";
				buttons[1].id = 2;
				return;
			case 5:
				buttonCount = 2;
				buttons[0].label = "$YES";
				buttons[0].id = 4;
				buttons[1].label = "$NO";
				buttons[1].id = 5;
				return;
			case 6:
				buttonCount = 3;
				buttons[0].label = "$YES";
				buttons[0].id = 4;
				buttons[1].label = "$NO";
				buttons[1].id = 5;
				buttons[2].label = "$CANCEL";
				buttons[2].id = 2;
				return;
			case 7:
				buttonCount = 3;
				buttons[0].label = "$YES";
				buttons[0].id = 4;
				buttons[1].label = "$NO";
				buttons[1].id = 5;
				buttons[2].label = "$SELECTDEVICE";
				buttons[2].id = 6;
				return;
			case 8:
				buttonCount = 3;
				buttons[1].id = 2;
				buttons[2].label = "$SELECTDEVICE";
				buttons[2].id = 6;
				break;
			default:
				return;
			}
			buttons[1].label = "$CANCEL";
			buttons[0].id = 1;
			buttons[0].label = "$OK";
		}

		// FUNCTION: ENGINE 0x108E27A0
		// NONMATCHING: the chain of comparisons is laid out like the engine's but every return is scheduled differently (25.7 %)
#ifdef NONMATCHING
		// The text of a slot's date (0x1131AAF8) and of its time (0x1131AA78)
		static char sDateText[0x80];
		static char sTimeText[0x80];

		void StorageDialogState::OnCall(DialogCall* call, int unused, FEMovie::Value* result)
		{
			if (core::StrCmp(call->name, "GetTitle") == 0)
			{
				result->string = title;
				result->type = 4;
			}
			else if (core::StrCmp(call->name, "GetMessage") == 0)
			{
				result->string = message;
				result->type = 4;
			}
			else if (core::StrCmp(call->name, "GetSlotName") == 0)
			{
				result->type = 5;
				if (slotName == 0)
				{
					result->string = (const char*)L"";
				}
				else
				{
					result->string = (const char*)slotName;
				}
			}
			else if (core::StrCmp(call->name, "GetButtonCount") == 0)
			{
				result->number = (unsigned int)buttonCount;
				result->type = 3;
			}
			else if (core::StrCmp(call->name, "GetButton") == 0)
			{
				int index = (unsigned int)call->argument;
				result->type = 4;
				result->string = buttons[index].label;
			}
			else if (core::StrCmp(call->name, "GetSelectionCount") == 0)
			{
				result->number = (unsigned int)count;
				result->type = 3;
			}
			else if (core::StrCmp(call->name, "GetDefaultSelection") == 0)
			{
				result->number = (unsigned int)defaultSelection;
				result->type = 3;
			}
			else if (core::StrCmp(call->name, "GetNumSlots") == 0)
			{
				result->number = (unsigned int)count;
				result->type = 3;
			}
			else if (core::StrCmp(call->name, "GetSelectionIcon") == 0)
			{
				int index = (unsigned int)call->argument;
				result->type = 3;
				result->number = icons[index];
			}
			else if (core::StrCmp(call->name, "GetSelectionDetail") == 0)
			{
				int index = (unsigned int)call->argument;
				result->type = 5;
				result->string = (const char*)details[index];
			}
			else if (core::StrCmp(call->name, "GetSelectionName") == 0)
			{
				int index = (unsigned int)call->argument;
				result->type = 5;
				result->string = (const char*)names[index];
			}
			else if (core::StrCmp(call->name, "GetSelectionDate") == 0)
			{
				int index = (unsigned int)call->argument;
				SlotTime* time = dates[index];
				if (time->hour < 0x18)
				{
					core::SNPrintfCount(sDateText, 0x80, "%d/%d/%d", time->month, time->day, time->year);
					result->type = 4;
					result->string = sDateText;
				}
				else
				{
					result->type = 4;
					result->string = "";
				}
			}
			else if (core::StrCmp(call->name, "GetSelectionTime") == 0)
			{
				int index = (unsigned int)call->argument;
				SlotTime* time = dates[index];
				unsigned int hour = time->hour;
				if (hour < 0x18)
				{
					const char* suffix = "AM";
					if (hour == 0)
					{
						hour = 12;
					}
					else if (hour >= 12)
					{
						if (hour > 12)
						{
							hour -= 12;
						}
						suffix = "PM";
					}
					core::SNPrintfCount(sTimeText, 0x80, "%d:%.2d %s", hour, time->minute, suffix);
					result->type = 4;
					result->string = sTimeText;
				}
				else
				{
					result->type = 4;
					result->string = "";
				}
			}
			else if (core::StrCmp(call->name, "SetSelection") == 0)
			{
				selection = (unsigned int)call->argument;
			}
			else if (core::StrCmp(call->name, "SetButton") == 0)
			{
				int index = (unsigned int)call->argument;
				this->result = buttons[index].id;
			}
		}
#endif

		// FUNCTION: ENGINE 0x108E2C10
		void CreateDialog(int heap)
		{
			core::HeapScope scope(heap);
			gDialog = new StorageDialogState;
		}

		// FUNCTION: ENGINE 0x108E2C80
		void StorageDialogState::SetupMessage(const char* newTitle, const char* newMessage, int newKind,
			const unsigned short* newSlotName)
		{
			title = newTitle;
			message = newMessage;
			kind = newKind;
			slotName = newSlotName;
			count = 0;
			defaultSelection = 0;
			result = 0;
			SetupButtons();
		}

		// FUNCTION: ENGINE 0x108E2CB0
		// NONMATCHING: the engine loads and stores the argument pairs in another order (81.4 %)
#ifdef NONMATCHING
		void StorageDialogState::SetupSelection(const char* newTitle, const char* newMessage, int newKind,
			const unsigned short** newNames, SlotTime** newDates, int* newIcons, const unsigned short** newDetails,
			int newCount, int newDefault)
		{
			title = newTitle;
			kind = newKind;
			message = newMessage;
			dates = newDates;
			names = newNames;
			details = newDetails;
			icons = newIcons;
			defaultSelection = newDefault;
			count = newCount;
			slotName = 0;
			result = 0;
			selection = -1;
			SetupButtons();
		}
#endif

		// FUNCTION: ENGINE 0x108E2D10
		// NONMATCHING: the engine passes the controller -1 through eax (87.7 %)
#ifdef NONMATCHING
		int ShowMessage(const char* title, const char* message, int kind, core::Fiber* fiber,
			const unsigned short* slotName)
		{
			if (GetGameStateStatus(2) == 2)
			{
				return 1;
			}
			gDialog->SetupMessage(title, message, kind, slotName);
			gDialog->Unknown10883D50(-1, false);
			while (true)
			{
				int result = gDialog->GetResult();
				if (result != 0 && !gDialog->Unknown10883D80())
				{
					return result;
				}
				core::SwitchFiber(fiber);
			}
		}
#endif

		// FUNCTION: ENGINE 0x108E2D90
		// NONMATCHING: the engine passes the controller -1 through eax (86.4 %)
#ifdef NONMATCHING
		bool ShowMessageNoWait(const char* title, const char* message, const unsigned short* slotName)
		{
			gDialog->SetupMessage(title, message, 0, slotName);
			return gDialog->Unknown10883D50(-1, false);
		}
#endif

		// FUNCTION: ENGINE 0x108E2DC0
		// NONMATCHING: the engine passes the controller -1 through eax (91.4 %)
#ifdef NONMATCHING
		int ShowSelection(const char* title, const char* message, int kind, core::Fiber* fiber, int* selection,
			const unsigned short** names, SlotTime** dates, int* icons, const unsigned short** details, int count,
			int defaultSelection)
		{
			gDialog->SetupSelection(title, message, kind, names, dates, icons, details, count, defaultSelection);
			gDialog->Unknown10883D50(-1, false);
			int result;
			while (true)
			{
				result = gDialog->GetResult();
				if (result != 0 && !gDialog->Unknown10883D80())
				{
					break;
				}
				core::SwitchFiber(fiber);
			}
			*selection = gDialog->GetSelection();
			return result;
		}
#endif
	}
}

// Kept copies (compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E2C60
