#include "code/proto/frontend/fehuddisguiseactions.h"

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
	// 0x11099FBC: the movie clip of the disguise actions
	static const char* sDisguiseActionsClip = "mcAnchor.disguiseActionsHUD";

	// FUNCTION: ENGINE 0x104CFA70
	FEHudDisguiseActions::FEHudDisguiseActions() : patsyProgress(-1), airStrikeA(-1),
		visible("_level0.mcAnchor.disguiseActionsHUD._visible")
	{
		visible.Set(FlashValue(true));
	}

	// FUNCTION: ENGINE 0x104CF760
	void FEHudDisguiseActions::Update(bool force)
	{
		visible.Flush(force);
		if (force)
		{
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d%d", sDisguiseActionsClip, "SetPatsyState", patsyAvailable, patsyActive, patsyProgress);
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d%d%d", sDisguiseActionsClip, "SetAirStrikeState", airStrikeAvailable, airStrikeActive, airStrikeA, airStrikeB);
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", sDisguiseActionsClip, "SetStealthConsumeState", stealthAvailable, stealthActive);
		}
	}

	// FUNCTION: ENGINE 0x104CFA60
	void FEHudDisguiseActions::OnShow(bool shown)
	{
		SetVisible(shown);
	}

	// FUNCTION: ENGINE 0x104CFA20
	void FEHudDisguiseActions::SetVisible(bool newVisible)
	{
		visible.Set(FlashValue(newVisible));
		visible.Flush(true);
	}

	// FUNCTION: ENGINE 0x104CF840
	void FEHudDisguiseActions::Show()
	{
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s", sDisguiseActionsClip, "Show");
	}

	// FUNCTION: ENGINE 0x104CF870
	void FEHudDisguiseActions::Hide()
	{
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s", sDisguiseActionsClip, "Hide");
	}

	// FUNCTION: ENGINE 0x104CF8A0
	void FEHudDisguiseActions::SetPatsyState(bool available, bool active, float progress)
	{
		int remaining = 100 - (int)(progress * 100.0f);
		if (available != patsyAvailable || remaining != patsyProgress || patsyActive != active)
		{
			patsyProgress = remaining;
			patsyAvailable = available;
			patsyActive = active;
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d%d", sDisguiseActionsClip, "SetPatsyState", available, active, remaining);
		}
	}

	// FUNCTION: ENGINE 0x104CF930
	void FEHudDisguiseActions::SetAirStrikeState(bool available, bool active, int a, int b)
	{
		if (available != airStrikeAvailable || a != airStrikeA || b != airStrikeB || airStrikeActive != active)
		{
			airStrikeActive = active;
			airStrikeAvailable = available;
			airStrikeA = a;
			airStrikeB = b;
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d%d%d", sDisguiseActionsClip, "SetAirStrikeState", available, active, a, b);
		}
	}

	// FUNCTION: ENGINE 0x104CF9B0
	void FEHudDisguiseActions::SetStealthConsumeState(bool available, bool active, bool consuming)
	{
		if (available != stealthAvailable || stealthActive != active || stealthConsuming != consuming)
		{
			stealthAvailable = available;
			stealthConsuming = consuming;
			stealthActive = active;
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d%d", sDisguiseActionsClip, "SetStealthConsumeState", available, active, consuming);
		}
	}
}
