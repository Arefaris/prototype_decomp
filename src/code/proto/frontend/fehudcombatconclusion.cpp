#include "code/proto/frontend/fehudcombatconclusion.h"

#include "code/engine/luascriptmanager.h"

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
	// The pop-up element of the head-up display (another unit)
	class FEHudPopup
	{
	public:
		// 0x104D1490: fades the pop-up out (or back in)
		void Unknown104D1490(bool faded);
	};

	class PopupController
	{
	public:
		unsigned char unknown0[0xC];
		FEHudPopup* popup;
	};

	class FrontEndHud
	{
	public:
		// 0x104B0CE0
		PopupController* GetPopups();
		// 0x104B1D30: plays the sound of a power selection (name unknown)
		void Unknown104B1D30(int index);
	};
	// 0x104B0A00
	FrontEndHud* GetFrontEndHud();

	// 0x11099DC4: the movie clip of the combat conclusion
	static const char* sCombatConclusionClip = "mcAnchor.ccrHUD";

	// FUNCTION: ENGINE 0x104CF680
	FEHudCombatConclusion::FEHudCombatConclusion() : visible("_level0.mcAnchor.ccrHUD._visible"), state(0)
	{
		visible.Set(FlashValue(true));
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("fehudcombatconclusion_Show", this, &FEHudCombatConclusion::Show);
		manager->RegisterMethod("fehudcombatconclusion_Hide", this, &FEHudCombatConclusion::Hide);
		manager->RegisterMethod("fehudcombatconclusion_OnHideComplete", this, &FEHudCombatConclusion::OnHideComplete);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x104CF520
	FEHudCombatConclusion::~FEHudCombatConclusion()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x104CF320
	void FEHudCombatConclusion::Update(bool force)
	{
		visible.Flush(force);
	}

	// FUNCTION: ENGINE 0x104CF460
	void FEHudCombatConclusion::OnShow(bool shown)
	{
		if (!shown)
		{
			Hide();
		}
	}

	// FUNCTION: ENGINE 0x104CF480
	void FEHudCombatConclusion::SetVisible(bool newVisible)
	{
		visible.Set(FlashValue(newVisible));
		visible.Flush(true);
	}

	// FUNCTION: ENGINE 0x104CF450
	void FEHudCombatConclusion::Reset()
	{
		state = 0;
	}

	// FUNCTION: ENGINE 0x104CF330
	void FEHudCombatConclusion::Show()
	{
		if (IsShown() && state == 0)
		{
			state = 1;
			PopupController* popups = GetFrontEndHud()->GetPopups();
			popups->popup->Unknown104D1490(true);
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", sCombatConclusionClip, "Show");
			GetFrontEndHud()->Unknown104B1D30(0x13);
		}
	}

	// FUNCTION: ENGINE 0x104CF3C0
	void FEHudCombatConclusion::Hide()
	{
		if (IsShown() && state == 1)
		{
			state = 2;
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", sCombatConclusionClip, "Hide");
		}
	}

	// FUNCTION: ENGINE 0x104CF420
	void FEHudCombatConclusion::OnHideComplete()
	{
		state = 0;
		PopupController* popups = GetFrontEndHud()->GetPopups();
		popups->popup->Unknown104D1490(false);
	}
}
