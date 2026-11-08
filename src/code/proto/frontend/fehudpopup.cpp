#include "code/proto/frontend/fehudpopup.h"

#include "code/core/strings.h"
#include "code/engine/frontend/fesubtitle.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/proto/pausemenustate.h"
#include "code/proto/smarthint/smarthintmanager.h"

namespace core
{
	// 0x1063B0D0: the copy with an unsigned size (the one the head-up display's pop-ups call)
	char* StrNCpy(char* destination, const char* source, unsigned int size);
}

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
}

namespace proto
{
	// 0x11097848: the movie clip the head-up display elements sit in
	extern const char* gHudAnchorName;
	// 0x1109A344 / 0x1109A348 / 0x1109A34C: the movie clips of the passive, hint and objective pop-ups
	static const char* sPassiveClip = "mcAnchor.managedPopupHUD";
	static const char* sHintClip = "mcAnchor.hintHUD";
	static const char* sObjectiveClip = "mcAnchor.popupHUD";

	// FUNCTION: ENGINE 0x104D1550
	FEHudPopup::Slot::Slot()
	{
		flag = false;
		state = 2;
		unknown18 = false;
		texts[0] = 0;
		texts[1] = 0;
		texts[2] = 0;
		texts[3] = 0;
	}

	// FUNCTION: ENGINE 0x104D1580
	FEHudPopup::Slot::~Slot()
	{
		for (int i = 0; i < 4; i++)
		{
			if (texts[i] != 0)
			{
				delete[] texts[i];
				texts[i] = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x104D15C0
	void FEHudPopup::Slot::Open(bool newFlag)
	{
		flag = newFlag;
		state = 0;
	}

	// FUNCTION: ENGINE 0x104D15E0
	void FEHudPopup::Slot::StartClosing()
	{
		state = 1;
		flag = false;
	}

	// FUNCTION: ENGINE 0x104D15F0
	void FEHudPopup::Slot::SetClosed()
	{
		state = 2;
		flag = false;
	}

	// FUNCTION: ENGINE 0x104D1660
	FEHudPopup::~FEHudPopup()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x104D1500
	void FEHudPopup::ShowPopups(bool show)
	{
		if (popupsShown != show)
		{
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", gHudAnchorName, "ShowPopups", show);
		}
		popupsShown = show;
	}

	// FUNCTION: ENGINE 0x104D1B80
	void FEHudPopup::OnShow(bool shown)
	{
		ShowPopups(shown);
	}

	// FUNCTION: ENGINE 0x104D1430
	bool FEHudPopup::IsPassiveOpen()
	{
		return slots[0].state == 0;
	}

	// FUNCTION: ENGINE 0x104D1440
	bool FEHudPopup::IsHintOpen()
	{
		return slots[1].state == 0;
	}

	// FUNCTION: ENGINE 0x104D1450
	bool FEHudPopup::IsMissionOpen()
	{
		return slots[2].state == 0;
	}

	// FUNCTION: ENGINE 0x104D1460
	bool FEHudPopup::IsObjectiveOpen()
	{
		return slots[3].state == 0;
	}

	// FUNCTION: ENGINE 0x104D1470
	bool FEHudPopup::GetPassiveFlag()
	{
		return slots[0].flag;
	}

	// FUNCTION: ENGINE 0x104D1480
	bool FEHudPopup::GetHintFlag()
	{
		return slots[1].flag;
	}

	// FUNCTION: ENGINE 0x104D14E0
	void FEHudPopup::SetMissionActive(bool value)
	{
		missionActive = value;
	}

	// FUNCTION: ENGINE 0x104D14F0
	bool FEHudPopup::GetMissionActive()
	{
		return missionActive;
	}

	// FUNCTION: ENGINE 0x104D1490
	void FEHudPopup::Unknown104D1490(bool faded)
	{
		if (faded)
		{
			alpha.Set(FlashValue(0.0));
		}
		else
		{
			alpha.Set(FlashValue(100.0));
		}
	}

	// FUNCTION: ENGINE 0x104D17A0
	void FEHudPopup::ShowHintPopup(bool newFlag, const char* text)
	{
		if ((char)engine::ShouldHideHUD() == 0)
		{
			if (slots[1].texts[0] != 0)
			{
				core::StrNCpy(slots[1].texts[0], text, 0x100u);
			}
			slots[1].Open(newFlag);
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%s", sHintClip, "ShowHintPopup", newFlag, text);
		}
	}

	// FUNCTION: ENGINE 0x104D1940
	void FEHudPopup::ShowObjectivePopup(const char* title, const char* text)
	{
		if ((char)engine::ShouldHideHUD() == 0)
		{
			engine::gSubtitleOptions->SetEnabled(false);
			slots[3].Open(false);
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%s%s", sObjectiveClip, "ShowObjectivePopup", title, text);
			GetPauseMenuState()->Unknown1049BA60();
		}
	}

	// FUNCTION: ENGINE 0x104D19C0
	void FEHudPopup::ClosePassivePopup()
	{
		if (slots[0].flag)
		{
			slots[0].StartClosing();
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s", sPassiveClip, "ClosePassivePopup");
			gSmartHintManager->Unknown1059DCF0();
		}
	}

	// FUNCTION: ENGINE 0x104D1A50
	void FEHudPopup::ClosePassivePopupUnflagged()
	{
		if (!slots[0].flag)
		{
			slots[0].StartClosing();
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s", sPassiveClip, "ClosePassivePopup");
			gSmartHintManager->Unknown1059DCF0();
		}
	}

	// FUNCTION: ENGINE 0x104D1A10
	void FEHudPopup::CloseHintPopup()
	{
		if (slots[1].flag)
		{
			slots[1].StartClosing();
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s", sHintClip, "CloseHintPopup");
		}
	}

	// FUNCTION: ENGINE 0x104D1AA0
	void FEHudPopup::CloseMissionPopup()
	{
		slots[2].StartClosing();
		SetMissionActive(false);
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s", gHudAnchorName, "CloseMissionPopup");
	}

	// FUNCTION: ENGINE 0x104D1AF0
	void FEHudPopup::CloseAll()
	{
		ClosePassivePopup();
		ClosePassivePopupUnflagged();
		CloseHintPopup();
		CloseMissionPopup();
	}

	// FUNCTION: ENGINE 0x104D1B20
	void FEHudPopup::ResetPassive()
	{
		slots[0].SetClosed();
		gSmartHintManager->Unknown1059DCF0();
	}

	// FUNCTION: ENGINE 0x104D1B40
	void FEHudPopup::ResetHint()
	{
		slots[1].SetClosed();
	}

	// FUNCTION: ENGINE 0x104D1B50
	void FEHudPopup::ResetMission()
	{
		slots[2].SetClosed();
	}

	// FUNCTION: ENGINE 0x104D1B60
	void FEHudPopup::ResetObjective()
	{
		slots[3].SetClosed();
		engine::gSubtitleOptions->SetEnabled(true);
	}

	// FUNCTION: ENGINE 0x104D1820
	void FEHudPopup::ShowMissionPopup(bool newFlag, bool newUnknown18, const char* text0, const char* text1, const char* text2,
		const char* text3)
	{
		if ((char)engine::ShouldHideHUD() == 0)
		{
			if (slots[2].texts[0] != 0)
			{
				core::StrNCpy(slots[2].texts[0], text0, 0x100u);
			}
			if (slots[2].texts[1] != 0)
			{
				core::StrNCpy(slots[2].texts[1], text1, 0x100u);
			}
			if (slots[2].texts[2] != 0)
			{
				core::StrNCpy(slots[2].texts[2], text2, 0x100u);
			}
			if (slots[2].texts[3] != 0)
			{
				core::StrNCpy(slots[2].texts[3], text3, 0x100u);
			}
			SetMissionActive(false);
			slots[2].Open(newFlag);
			slots[2].unknown18 = newUnknown18;
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d%s%s%s%s", gHudAnchorName, "ShowMissionPopup", newFlag, newUnknown18, text0, text1, text2, text3);
			GetPauseMenuState()->Unknown1049BA60();
		}
	}

	// FUNCTION: ENGINE 0x104D2010
	void FEHudPopup::Update(bool force)
	{
		alpha.Flush(force);
		if (force)
		{
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", gHudAnchorName, "ShowPopups", popupsShown);
			if (slots[1].state == 0)
			{
				ShowHintPopup(slots[1].flag, slots[1].texts[0]);
			}
			if (slots[0].state == 0)
			{
				ShowPassivePopup(slots[0].flag, slots[0].texts[0]);
			}
			if (slots[2].state == 0)
			{
				ShowMissionPopup(slots[2].flag, slots[2].unknown18, slots[2].texts[0], slots[2].texts[1], slots[2].texts[2], slots[2].texts[3]);
			}
		}
	}
}
