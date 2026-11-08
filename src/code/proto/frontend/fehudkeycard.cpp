#include "code/proto/frontend/fehudkeycard.h"

#include "code/engine/luascriptmanager.h"

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and two text arguments (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
}

namespace proto
{
	// 0x1109A0D0: the key card's movie clip
	static const char* sKeyCardClip = "mcAnchor.keycardHUD";

	// FUNCTION: ENGINE 0x104D0DF0
	FEHudKeyCard::FEHudKeyCard() : visible("_level0.mcAnchor.keycardHUD._visible"), icon("_level0.mcAnchor.keycardHUD.mcIcon._visible")
	{
		visible.Set(FlashValue(true));
		icon.Set(FlashValue(false));
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("fehudkeycard_Show", this, &FEHudKeyCard::ShowIcon);
		manager->RegisterMethod("fehudkeycard_Hide", this, &FEHudKeyCard::HideIcon);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x104D0C70
	FEHudKeyCard::~FEHudKeyCard()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x104D0B10
	void FEHudKeyCard::Update(bool force)
	{
		visible.Flush(force);
		icon.Flush(force);
	}

	// FUNCTION: ENGINE 0x104D0CC0
	void FEHudKeyCard::OnShow(bool shown)
	{
		SetShown(shown);
	}

	// FUNCTION: ENGINE 0x104D0BD0
	void FEHudKeyCard::SetShown(bool shown)
	{
		visible.Set(FlashValue(shown));
		visible.Flush(true);
	}

	// FUNCTION: ENGINE 0x104D0B40
	void FEHudKeyCard::ShowIcon()
	{
		icon.Set(FlashValue(true));
		engine::Unknown10872840(engine::Unknown10864330(), "AS_GotoAndPlay", "%s%s", sKeyCardClip, "INTRO");
	}

	// FUNCTION: ENGINE 0x104D0BA0
	void FEHudKeyCard::HideIcon()
	{
		icon.Set(FlashValue(false));
	}
}
