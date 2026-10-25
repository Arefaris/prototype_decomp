#include "code/engine/frontend/feinputhandler.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/engine/display.h"
#include "code/engine/frontend/femovie.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	// The object at +0x2C of the frontend object (0x10886490 and the following, another unit; names guessed)
	class FrontendScreen
	{
	public:
		void SetValue(int index, bool value, int a, int b);
		void SetCursor(int x, int y);
		void SetFloat(int index, int a, float value);
	};

	// The front end's movie as this unit uses it (the object GetFrontend answers; 0x10872830: calls an ActionScript
	// function)
	class FrontendMovie
	{
	public:
		void Invoke(const char* name, const FEMovie::Value* arguments, int count);

		unsigned char unknown0[0x2C];
		FrontendScreen screen;
	};

	// The gate that decides which state gets the input (0x10890930, 0x108909E0; another unit; names guessed)
	struct StateGate
	{
		void SetFocus(const char* name);
	};
	StateGate* Unknown10890930();

	// One of a control's three events: the state value it is read as and the names the movie knows it by
	struct ControlEvent
	{
		int value;
		const char* name;
		const char* eventName;
	};

	// One control of the pads (a button or a stick) and which of the three events it reports to the movie
	struct ControlRow
	{
		int id;
		const char* name;
		bool enabled[4];
	};

	// GLOBAL: ENGINE 0x111D13F4
	float gDeadZone = 0.7f;
	// GLOBAL: ENGINE 0x111D13F8
	int gCursorX = -1;
	// GLOBAL: ENGINE 0x111D13FC
	int gCursorY = -1;
	// GLOBAL: ENGINE 0x111D1400
	ControlEvent gButtonEvents[3] =
	{
		{ 2, "Down", "BStateDown" },
		{ 1, "Press", "BStatePress" },
		{ 3, "Release", "BStateRelease" }
	};
	// GLOBAL: ENGINE 0x111D1424
	ControlEvent gAxisEvents[3] =
	{
		{ 0x24, "Down", "BStateDown" },
		{ 0x12, "Press", "BStatePress" },
		{ 0x48, "Release", "BStateRelease" }
	};
	// GLOBAL: ENGINE 0x111D1448
	ControlRow gButtonRows[13] =
	{
		{ 0x1A, "Y", { false, false, false, false } },
		{ 0x1B, "B", { false, false, false, false } },
		{ 0x1C, "A", { false, false, false, false } },
		{ 0x1D, "X", { false, false, false, false } },
		{ 0x1E, "Start", { false, false, false, false } },
		{ 0x1F, "Select", { false, false, false, false } },
		{ 0x20, "L1", { false, false, false, false } },
		{ 0x21, "R1", { false, false, false, false } },
		{ 0x22, "L2", { false, false, false, false } },
		{ 0x23, "R2", { false, false, false, false } },
		{ 0x24, "L3", { false, false, false, false } },
		{ 0x25, "R3", { false, false, false, false } },
		{ 0x26, "A", { false, false, false, false } }
	};
	// GLOBAL: ENGINE 0x111D14E8
	ControlRow gAxisRows[8] =
	{
		{ 9, "LAXC", { false, false, false, false } },
		{ 0xA, "LAYC", { false, false, false, false } },
		{ 0xB, "RAXC", { false, false, false, false } },
		{ 0xC, "RAYC", { false, false, false, false } },
		{ 0xD, "DPXC", { false, false, false, false } },
		{ 0xE, "DPYC", { false, false, false, false } },
		{ 0xF, "KBXC", { false, false, false, false } },
		{ 0x10, "KBYC", { false, false, false, false } }
	};

	// GLOBAL: ENGINE 0x11316C90
	FEInputHandler* gFEInputHandler = 0;
	// GLOBAL: ENGINE 0x11316C94
	bool gKeyboardListening = false;
	// GLOBAL: ENGINE 0x11316C95
	bool gInputEnabled = false;
	// GLOBAL: ENGINE 0x11316C96
	bool gHandleInput = false;
	// GLOBAL: ENGINE 0x11316C97
	bool gMouseVisible = false;
	// GLOBAL: ENGINE 0x11316C98
	bool gMouseVisibleOption = false;

	// FUNCTION: ENGINE 0x10881140
	void SetControlEnabled(const char* control, const char* event, bool enabled)
	{
		bool found = false;
		for (unsigned int i = 0; i < 13; i++)
		{
			if (core::StrCmp(gButtonRows[i].name, control) == 0)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					if (core::StrCmp(gButtonEvents[j].name, event) == 0)
					{
						gButtonRows[i].enabled[j] = enabled;
						found = true;
					}
				}
			}
		}
		if (!found)
		{
			for (unsigned int i = 0; i < 8; i++)
			{
				if (core::StrCmp(gAxisRows[i].name, control) == 0)
				{
					for (unsigned int j = 0; j < 3; j++)
					{
						if (core::StrCmp(gAxisEvents[j].name, event) == 0)
						{
							gAxisRows[i].enabled[j] = enabled;
						}
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10881210
	void SetInputEnabled(bool enabled)
	{
		gInputEnabled = enabled;
	}

	// FUNCTION: ENGINE 0x10881220
	void SetMouseVisible(bool visible, bool option)
	{
		gMouseVisibleOption = option;
		if (gMouseVisible != visible)
		{
			gMouseVisible = visible;
			FrontendMovie* movie = (FrontendMovie*)GetFrontend();
			if (movie != 0)
			{
				FEMovie::Value arguments[1];
				arguments[0].type = 2;
				*(bool*)&arguments[0].number = gMouseVisible;
				movie->Invoke("AS_SetMouseCursorVisibility", arguments, 1);
			}
		}
	}

	// FUNCTION: ENGINE 0x10881290
	bool GetMouseVisible()
	{
		return gMouseVisible;
	}

	// FUNCTION: ENGINE 0x108812A0
	bool FEInputHandler::IsMouseVisible()
	{
		return GetMouseVisible();
	}

	// FUNCTION: ENGINE 0x108812B0
	bool GetMouseVisibleOption()
	{
		return gMouseVisibleOption;
	}

	// FUNCTION: ENGINE 0x108812C0
	void SetHandleInput(bool handle)
	{
		gHandleInput = handle;
	}

	// FUNCTION: ENGINE 0x108812D0
	// EQUIVALENT: the engine keeps the two bytes of the string in a frame slot of their own (0x44 bytes of frame), ours
	// puts them into the stack slot of a parameter that is no longer used (0x40), 21.7 %
	void FEInputHandler::OnKey(controller::KeyEvent event)
	{
		FrontendMovie* movie = (FrontendMovie*)GetFrontend();
		if (movie != 0)
		{
			FEMovie::Value arguments[4];
			char text[2];
			arguments[0].type = 3;
			arguments[0].number = event.key;
			arguments[1].type = 3;
			arguments[1].number = event.state;
			arguments[2].type = 3;
			arguments[2].number = event.modifiers;
			text[0] = event.character;
			text[1] = 0;
			arguments[3].type = 4;
			arguments[3].string = text;
			movie->Invoke("AS_KeyboardEvent", arguments, 4);
		}
	}

	// FUNCTION: ENGINE 0x10881340
	void SetScreenValue(int index, bool value, int a, int b)
	{
		if (gInputEnabled)
		{
			FrontendMovie* movie = (FrontendMovie*)GetFrontend();
			if (movie != 0)
			{
				movie->screen.SetValue(index, value, a, b);
			}
		}
	}

	// FUNCTION: ENGINE 0x10881370
	void UpdateCursorPosition(int x, int y)
	{
		if (gInputEnabled)
		{
			FrontendMovie* movie = (FrontendMovie*)GetFrontend();
			if (movie != 0)
			{
				float screenHeight;
				float screenWidth;
				float ratio;
				float width;
				float height;
				float offsetX;
				float offsetY;
				float scaledWidth;
				float scaledHeight;
				width = (float)gDisplay->GetWidth();
				height = (float)gDisplay->GetUnknown8();
				screenWidth = GetScreenWidth();
				screenHeight = GetScreenHeight();
				ratio = gDisplay->GetUnknown804Ratio();
				if (screenWidth / screenHeight > ratio)
				{
					offsetX = 0.0f;
					scaledWidth = screenWidth;
					scaledHeight = screenWidth / ratio;
					offsetY = (scaledHeight - screenHeight) * 0.5f;
				}
				else
				{
					offsetY = 0.0f;
					scaledHeight = screenHeight;
					scaledWidth = ratio * screenHeight;
					offsetX = (scaledWidth - screenWidth) * 0.5f;
				}
				int cursorX = (int)(((float)x / width) * scaledWidth - offsetX);
				int cursorY = (int)(((float)y / height) * scaledHeight - offsetY);
				if (gCursorX != cursorX || gCursorY != cursorY)
				{
					FEMovie::Value arguments[2];
					arguments[0].type = 3;
					arguments[0].number = cursorX;
					arguments[1].type = 3;
					arguments[1].number = cursorY;
					movie->Invoke("AS_SetMouseCursor", arguments, 2);
					movie->screen.SetCursor(x, y);
					gCursorX = cursorX;
					gCursorY = cursorY;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x108814F0
	void SetScreenFloat(int index, int a, float value)
	{
		if (gInputEnabled)
		{
			FrontendMovie* movie = (FrontendMovie*)GetFrontend();
			if (movie != 0)
			{
				movie->screen.SetFloat(index, a, value);
			}
		}
	}

	// FUNCTION: ENGINE 0x10881520
	float SetDeadZoneValue(float deadZone)
	{
		float old = gDeadZone;
		gDeadZone = deadZone;
		return old;
	}

	// FUNCTION: ENGINE 0x10881540
	float FEInputHandler::SetDeadZone(float deadZone)
	{
		return SetDeadZoneValue(deadZone);
	}

	// FUNCTION: ENGINE 0x10881560
	void FEInputHandler::SetInputFocus(const char* name)
	{
		if (Unknown10890930() != 0)
		{
			Unknown10890930()->SetFocus(name);
		}
	}

	// FUNCTION: ENGINE 0x10881660
	void SetKeyboardListening(bool listen)
	{
		if (listen)
		{
			if (!gKeyboardListening)
			{
				FEInputHandler* handler = gFEInputHandler;
				gKeyboardListening = true;
				controller::SlotManager::GetKeyboard()->AddCallback(handler);
			}
		}
		else if (gKeyboardListening)
		{
			gKeyboardListening = false;
			controller::SlotManager::GetKeyboard()->RemoveCallback(gFEInputHandler);
		}
	}

	// FUNCTION: ENGINE 0x108816F0
	// EQUIVALENT: register allocation only (the engine loads the player's id into eax and the control row's id into
	// edx where ours uses ecx and eax), 99.1 %
	// tells the movie the state of the pads' buttons and sticks of every player in the front end's input contexts
	void UpdateFEInput()
	{
		FrontendMovie* movie = (FrontendMovie*)GetFrontend();
		if (movie != 0 && gHandleInput)
		{
			bool sent = false;
			FEMovie::Value arguments[4];
			for (controller::PlayerInfo* player = (controller::PlayerInfo*)controller::InputSystem::Get()->active.head;
				player != 0; player = player->GetNext())
			{
				if ((controller::InputSystem::Get()->GetContext(player->id) & 2) != 0)
				{
					float playerIndex = (float)(unsigned char)player->id;
					for (unsigned int i = 0; i < 13; i++)
					{
						int state = (player->context & 2) != 0 ? player->controlStates[gButtonRows[i].id] : 0;
						for (unsigned int j = 0; j < 3; j++)
						{
							if (state == gButtonEvents[j].value)
							{
								if (gButtonRows[i].enabled[j])
								{
									arguments[0].type = 3;
									arguments[0].number = playerIndex;
									arguments[1].type = 4;
									arguments[1].string = gButtonRows[i].name;
									arguments[2].type = 3;
									arguments[2].number = 1.0;
									arguments[3].type = 4;
									arguments[3].string = gButtonEvents[j].eventName;
									movie->Invoke("AS_HandleInput", arguments, 4);
									sent = true;
								}
								break;
							}
						}
					}
					for (unsigned int i = 0; i < 8; i++)
					{
						for (unsigned int j = 0; j < 3; j++)
						{
							unsigned int mask = gAxisEvents[j].value;
							if (player->IsControlSet(gAxisRows[i].id, mask, 2, 0) && gAxisRows[i].enabled[j])
							{
								float value = (player->context & 2) != 0 ? player->analog[gAxisRows[i].id].value : 0.0f;
								if (value > gDeadZone || value < -gDeadZone || mask == 0x48)
								{
									arguments[0].type = 3;
									arguments[0].number = playerIndex;
									arguments[1].type = 4;
									arguments[1].string = gAxisRows[i].name;
									arguments[2].type = 3;
									arguments[2].number = value;
									arguments[3].type = 4;
									arguments[3].string = gAxisEvents[j].eventName;
									movie->Invoke("AS_HandleInput", arguments, 4);
									sent = true;
								}
							}
						}
					}
				}
			}
			if (sent)
			{
				arguments[0].type = 3;
				arguments[0].number = -1.0;
				arguments[1].type = 4;
				arguments[1].string = "PollingComplete";
				arguments[2].type = 3;
				arguments[2].number = -1.0;
				arguments[3].type = 4;
				arguments[3].string = "";
				movie->Invoke("AS_HandleInput", arguments, 4);
			}
		}
	}

	// FUNCTION: ENGINE 0x108816E0
	void FEInputHandler::EnableOnInput(bool enable)
	{
		SetHandleInput(enable);
	}

	// FUNCTION: ENGINE 0x10881BF0
	// EQUIVALENT: the engine keeps this in esi across the calls, ours pushes it for the first call, 54.5 %
	FEInputHandler::~FEInputHandler()
	{
		GetScriptManager()->Unregister(this);
		SetKeyboardListening(false);
		SetHandleInput(false);
		SetInputEnabled(false);
	}

	// FUNCTION: ENGINE 0x10881FF0
	FEInputHandler::FEInputHandler()
	{
		SetInputEnabled(true);
		SetMouseVisible(true, false);
		SetHandleInput(true);
		LuaScriptManager* script = GetScriptManager();
		script->SetOwner(this);
		script->RegisterMethod("fe_EnableOnInput", this, &FEInputHandler::EnableOnInput);
		script->RegisterMethod("fe_SetDeadZone", this, &FEInputHandler::SetDeadZone);
		script->RegisterMethod("fe_IsMouseVisible", this, &FEInputHandler::IsMouseVisible);
		script->RegisterMethod("fe_SetInputFocus", this, &FEInputHandler::SetInputFocus);
		script->ClearOwner();
	}

	// FUNCTION: ENGINE 0x10881FC0
	void ReleaseSubsystem16C90()
	{
		delete gFEInputHandler;
		gFEInputHandler = 0;
	}

	// FUNCTION: ENGINE 0x108820F0
	void CreateFEInputHandler(int heap)
	{
		core::HeapScope scope(heap);
		gFEInputHandler = new FEInputHandler;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108810F0
// FUNCTION: ENGINE 0x10881130
// FUNCTION: ENGINE 0x10881580
// FUNCTION: ENGINE 0x108815A0
// FUNCTION: ENGINE 0x108815D0
// FUNCTION: ENGINE 0x10881610
// FUNCTION: ENGINE 0x10881E30
