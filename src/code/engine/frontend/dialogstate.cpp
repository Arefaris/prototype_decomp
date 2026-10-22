#include "code/engine/frontend/dialogstate.h"
#include "code/core/strings.h"

namespace engine
{
	// The object that does the dialog's work (0xC0 bytes; another unit, names guessed)
	class DialogStateImpl
	{
	public:
		// 0x108E42D0
		DialogStateImpl(DialogState* owner, int a, int b, const char* overlay, int c);
		// 0x108E3E10
		~DialogStateImpl();
		// 0x108E3E50, 0x108E4390, 0x108E3F60, 0x108E3F70, 0x108E3FA0 (the icon), 0x108E3FC0, 0x108E3FD0, 0x108E4230
		void Unknown108E3E50(int controller, bool flag);
		void Unknown108E4390();
		bool Unknown108E3F60();
		bool Unknown108E3F70();
		void SetIcon(int icon, bool visible);
		void Unknown108E3FC0();
		void Unknown108E3FD0();
		void Unknown108E4230();

		unsigned char unknown0[0xB8];
		int controller;  // +0xB8
		unsigned char unknownBC[4];
	};

	// FUNCTION: ENGINE 0x10883CB0
	DialogState::DialogState(int a, int b, const char* overlay, int c)
	{
		impl = new DialogStateImpl(this, a, b, overlay, c);
	}

	// FUNCTION: ENGINE 0x10883D50
	void DialogState::Unknown10883D50(int controller, bool flag)
	{
		impl->Unknown108E3E50(controller, flag);
	}

	// FUNCTION: ENGINE 0x10883D60
	void DialogState::Unknown10883D60()
	{
		impl->Unknown108E4390();
	}

	// FUNCTION: ENGINE 0x10883D70
	bool DialogState::Unknown10883D70()
	{
		return impl->Unknown108E3F60();
	}

	// FUNCTION: ENGINE 0x10883D80
	bool DialogState::Unknown10883D80()
	{
		return impl->Unknown108E3F70();
	}

	// FUNCTION: ENGINE 0x10883D90
	void DialogState::SetIcon(int icon, bool visible)
	{
		impl->SetIcon(icon, visible);
	}

	// FUNCTION: ENGINE 0x10883DA0
	void DialogState::Unknown10883DA0()
	{
		impl->Unknown108E3FC0();
	}

	// FUNCTION: ENGINE 0x10883DB0
	void DialogState::Unknown10883DB0()
	{
		impl->Unknown108E3FD0();
	}

	// FUNCTION: ENGINE 0x10883DC0
	void DialogState::Unknown10883DC0()
	{
		impl->Unknown108E4230();
	}

	// FUNCTION: ENGINE 0x10883DD0
	// EQUIVALENT: the engine loads the output pointer into eax, ours into edx, 88.9 %
	void DialogState::GetController(int* controller)
	{
		*controller = impl->controller;
	}

	// FUNCTION: ENGINE 0x10883DF0
	DialogState::~DialogState()
	{
		delete impl;
	}

	// FUNCTION: ENGINE 0x10883E30
	FEPopUpDialogState::FEPopUpDialogState(const char* newTitle, const char* newMessage, const char** newButtons,
		int newButtonCount, int a, int b, int c, const char* overlay) : DialogState(a, b, overlay, c)
	{
		title = newTitle;
		message = newMessage;
		buttons = newButtons;
		buttonCount = newButtonCount;
		selected = -1;
	}

	// FUNCTION: ENGINE 0x10883E80
	FEPopUpDialogState::~FEPopUpDialogState()
	{
	}

	// FUNCTION: ENGINE 0x10883E90
	int FEPopUpDialogState::GetResult()
	{
		if (Unknown10883D80())
		{
			return -1;
		}
		int result = selected;
		if (result == -1)
		{
			result = -2;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10883EB0
	// EQUIVALENT: the engine keeps the call in esi and this in edi, ours the other way round, 82.3 %
	void FEPopUpDialogState::OnCall(DialogCall* call, int unused, FEMovie::Value* result)
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
		else if (core::StrCmp(call->name, "GetButtonCount") == 0)
		{
			result->type = 3;
			result->number = buttonCount;
		}
		else if (core::StrCmp(call->name, "GetButton") == 0)
		{
			int index = (int)call->argument;
			const char* button = buttons[index];
			result->type = 4;
			result->string = button;
		}
		else if (core::StrCmp(call->name, "SetButton") == 0)
		{
			selected = (unsigned int)call->argument;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10883D00
// FUNCTION: ENGINE 0x10883D10
// FUNCTION: ENGINE 0x10883D20
// FUNCTION: ENGINE 0x10883D30
// FUNCTION: ENGINE 0x10883E10
// FUNCTION: ENGINE 0x10883FC0
