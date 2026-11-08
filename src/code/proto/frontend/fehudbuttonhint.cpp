#include "code/proto/frontend/fehudbuttonhint.h"

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
	// 0x10838900 / 0x10837AB0
	void AddSimulationTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveSimulationTask(IRealTimeTask* task);
}

namespace proto
{
	// 0x11099BC4: the movie clip of the button hint
	static const char* sButtonHintClip = "mcAnchor.buttonhintHUD";

	// FUNCTION: ENGINE 0x104CE960
	FEHudButtonHint::FEHudButtonHint() : frontText("_level0.mcAnchor.buttonhintHUD.buttonHintText.buttonHintTextFront.text"),
		backText("_level0.mcAnchor.buttonhintHUD.buttonHintText.buttonHintTextBack.text"),
		keyboardUpText("_level0.mcAnchor.buttonhintHUD.keyboardButtonUpHintText.text"),
		keyboardDownText("_level0.mcAnchor.buttonhintHUD.keyboardButtonDownHintText.text"),
		visible("_level0.mcAnchor.buttonhintHUD._visible"), visibleFlag(true), unknown35C(-1), unknown360(-1),
		unknown364(true), unknown365(false), unknown366(false), taskActive(false)
	{
		SetTaskActive(true);
		frontText.Set(FlashValue(""));
		backText.Set(FlashValue(""));
		keyboardUpText.Set(FlashValue(""));
		keyboardDownText.Set(FlashValue(""));
		visible.Set(FlashValue(false));
	}

	// FUNCTION: ENGINE 0x104CE570
	FEHudButtonHint::~FEHudButtonHint()
	{
		SetTaskActive(false);
	}

	// FUNCTION: ENGINE 0x104CE430
	void FEHudButtonHint::Update(bool force)
	{
		visible.Flush(force);
		backText.Flush(force);
		frontText.Flush(force);
		keyboardUpText.Flush(force);
		keyboardDownText.Flush(force);
	}

	// FUNCTION: ENGINE 0x104CEC80
	void FEHudButtonHint::OnShow(bool shown)
	{
		SetVisible(shown);
		SetTaskActive(shown);
	}

	// FUNCTION: ENGINE 0x104CE5F0
	void FEHudButtonHint::SetVisible(bool newVisible)
	{
		visibleFlag = newVisible;
		visible.Set(FlashValue(newVisible));
		visible.Flush(true);
		SetTaskActive(newVisible);
	}

	// FUNCTION: ENGINE 0x104CE4A0
	void FEHudButtonHint::SetTaskActive(bool active)
	{
		if (active)
		{
			if (!taskActive)
			{
				engine::AddSimulationTask((engine::IRealTimeTask*)static_cast<engine::ISimulationTask*>(this), 2, 1,
					(unsigned int)"FEHudButtonHint Task");
			}
		}
		else if (taskActive)
		{
			engine::RemoveSimulationTask((engine::IRealTimeTask*)static_cast<engine::ISimulationTask*>(this));
		}
		taskActive = active;
	}

	// FUNCTION: ENGINE 0x104CE650
	void FEHudButtonHint::Reset()
	{
		unknown365 = false;
		unknown35C = -1;
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%s%s%s", sButtonHintClip, "ButtonHint", "", "", "");
		visible.Set(FlashValue(false));
		frontText.Set(FlashValue(""));
		backText.Set(FlashValue(""));
		keyboardUpText.Set(FlashValue(""));
		keyboardDownText.Set(FlashValue(""));
	}

	// FUNCTION: ENGINE 0x104CE490
	void FEHudButtonHint::Unknown104CE490()
	{
	}

	// FUNCTION: ENGINE 0x104CEC30
	void FEHudButtonHint::UpdateSimulation(engine::UpdateContext context)
	{
		if (!unknown366 && (!unknown364 || unknown365))
		{
			unknown364 = true;
			Reset();
		}
		unknown366 = false;
	}
}
