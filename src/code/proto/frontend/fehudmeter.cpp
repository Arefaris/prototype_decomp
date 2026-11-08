#include "code/proto/frontend/fehudmeter.h"

#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

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

namespace engine
{
	namespace driving
	{
		// 0x10D94CC4
		extern const float gHalf;
	}
}

namespace proto
{
	// 0x10D977E0 / 0x10DA3664
	extern const float gHundred;
	extern const float gFifty;

	// 0x11099364: the movie clip of the meter
	static const char* sMeterClip = "mcAnchor.meterHUD";
	// 0x11099430: how many movie units one percent of the bar is
	static float sBarScale = 3.0f;

	// FUNCTION: ENGINE 0x104CDE60
	FEHudMeter::FEHudMeter() : unknown10(0.0f), unknown14(0.0f), unknown18(0.0f), unknown1C(0.0f), drainEnabled(false), visible("_level0.mcAnchor.meterHUD._visible"),
		pulseText0("_level0.mcAnchor.meterHUD.mcPulseText0.mcTextField.txtLabel.text"),
		pulseText2("_level0.mcAnchor.meterHUD.mcPulseText2.mcTextField.txtLabel.text"),
		barsCombinedX("_level0.mcAnchor.meterHUD.mcBar.mcBarsCombined._x"),
		cap1X("_level0.mcAnchor.meterHUD.mcCap1._x"),
		bar0Visible("_level0.mcAnchor.meterHUD.mcBar.mcBarsCombined.mcBar0._visible"),
		bar0X("_level0.mcAnchor.meterHUD.mcBar.mcBarsCombined.mcBar0._x"),
		bar0Width("_level0.mcAnchor.meterHUD.mcBar.mcBarsCombined.mcBar0._width"),
		bar2Visible("_level0.mcAnchor.meterHUD.mcBar.mcBarsCombined.mcBar2._visible"),
		bar2Width("_level0.mcAnchor.meterHUD.mcBar.mcBarsCombined.mcBar2._width"),
		webbing0Visible("_level0.mcAnchor.meterHUD.mcCap1.mcWebbing0._visible"),
		webbing2Visible("_level0.mcAnchor.meterHUD.mcCap1.mcWebbing2._visible"),
		flareX("_level0.mcAnchor.meterHUD.mcFlare._x"),
		drainMaskX("_level0.mcAnchor.meterHUD.mcDrain.mcMask._x"), visibleFlag(false)
	{
		capVisible[0].path.text = "_level0.mcAnchor.meterHUD.mcCap0._visible";
		capVisible[1].path.text = "_level0.mcAnchor.meterHUD.mcCap1._visible";
		capVisible[2].path.text = "_level0.mcAnchor.meterHUD.mcCap2._visible";
		visible.Set(FlashValue(false));
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("fehudmeter_Show", this, &FEHudMeter::ShowMeter);
		manager->RegisterMethod("fehudmeter_Hide", this, &FEHudMeter::Hide);
		manager->RegisterMethod("fehudmeter_UpdateIcon", this, &FEHudMeter::UpdateIcon);
		manager->RegisterMethod("fehudmeter_UpdateText", this, &FEHudMeter::UpdateText);
		manager->RegisterMethod("fehudmeter_UpdatePercentage", this, &FEHudMeter::UpdatePercentage);
		manager->RegisterMethod("fehudmeter_ToggleBars", this, &FEHudMeter::ToggleBars);
		manager->RegisterMethod("fehudmeter_UpdateBarColor", this, &FEHudMeter::UpdateBarColor);
		manager->RegisterMethod("fehudmeter_TriggerAttentionGrab", this, &FEHudMeter::TriggerAttentionGrab);
		manager->RegisterMethod("fehudmeter_SetDrainEnabled", this, &FEHudMeter::SetDrainEnabled);
		manager->RegisterCFunction("fehudwarmeter_Show", FEHudWarMeterShow);
		manager->RegisterMethod("fehudwarmeter_UpdatePercentage", this, &FEHudMeter::UpdateWarPercentage);
		manager->RegisterMethod("fehudwarmeter_Hide", this, &FEHudMeter::Hide);
		manager->RegisterMethod("fehudwarmeter_UpdateIcon", this, &FEHudMeter::UpdateIcon);
		manager->RegisterMethod("fehudwarmeter_UpdateText", this, &FEHudMeter::UpdateText);
		manager->RegisterMethod("fehudwarmeter_ToggleBars", this, &FEHudMeter::ToggleBars);
		manager->RegisterMethod("fehudwarmeter_UpdateBarColor", this, &FEHudMeter::UpdateBarColor);
		manager->ClearOwner();
		engine::AddSimulationTask((engine::IRealTimeTask*)static_cast<engine::ISimulationTask*>(this), 4, 1,
			(unsigned int)"FEHudMeter Task");
	}

	// FUNCTION: ENGINE 0x104CC990
	FEHudMeter::~FEHudMeter()
	{
		engine::RemoveSimulationTask((engine::IRealTimeTask*)static_cast<engine::ISimulationTask*>(this));
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x104CC0F0
	void FEHudMeter::Update(bool force)
	{
		visible.Flush(force);
		capVisible[0].Flush(force);
		capVisible[1].Flush(force);
		capVisible[2].Flush(force);
		pulseText0.Flush(force);
		pulseText2.Flush(force);
		barsCombinedX.Flush(force);
		cap1X.Flush(force);
		bar0Visible.Flush(force);
		bar0X.Flush(force);
		bar0Width.Flush(force);
		bar2Visible.Flush(force);
		bar2Width.Flush(force);
		webbing0Visible.Flush(force);
		webbing2Visible.Flush(force);
		flareX.Flush(force);
		drainMaskX.Flush(force);
	}

	// FUNCTION: ENGINE 0x104CCBC0
	void FEHudMeter::OnShow(bool shown)
	{
		SetVisible(visibleFlag && shown);
	}

	// FUNCTION: ENGINE 0x104CC750
	void FEHudMeter::SetVisible(bool newVisible)
	{
		visible.Set(FlashValue(newVisible));
		visible.Flush(true);
	}

	// FUNCTION: ENGINE 0x104CC200
	void FEHudMeter::Hide()
	{
		visibleFlag = false;
		visible.Set(FlashValue(false));
	}

	// FUNCTION: ENGINE 0x104CC720
	void FEHudMeter::SetDrainEnabled(bool enabled)
	{
		unknown10 = 0.0f;
		unknown14 = 0.0f;
		unknown18 = 0.0f;
		unknown1C = 0.0f;
		drainEnabled = enabled;
	}

	// FUNCTION: ENGINE 0x104CC5E0
	void FEHudMeter::ToggleBars(EPositions position, bool on)
	{
		switch (position)
		{
		case 0:
			bar0Visible.Set(FlashValue(on));
			webbing0Visible.Set(FlashValue(on));
			break;
		case 2:
			bar2Visible.Set(FlashValue(on));
			webbing2Visible.Set(FlashValue(on));
			break;
		}
	}

	// FUNCTION: ENGINE 0x104CC690
	void FEHudMeter::UpdateBarColor(EPositions position, EBarColors colour)
	{
		ToggleBars(position, colour != 0);
		if (colour != 0)
		{
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", sMeterClip, "SetBarColor", position, colour);
		}
	}

	// FUNCTION: ENGINE 0x104CC6F0
	void FEHudMeter::TriggerAttentionGrab()
	{
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", sMeterClip, "TriggerAttentionGrab");
	}

	// FUNCTION: ENGINE 0x104CC230
	void FEHudMeter::UpdateIcon(EPositions position, EIcons icon)
	{
		if (icon == 0)
		{
			capVisible[position].Set(FlashValue(false));
			return;
		}
		capVisible[position].Set(FlashValue(true));
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", sMeterClip, "SetIcon", position, icon);
	}

	// FUNCTION: ENGINE 0x104CCB00
	void FEHudMeter::UpdateText(EPositions position, const char* text)
	{
		switch (position)
		{
		case 0:
			pulseText0.Set(FlashValue(text));
			break;
		case 2:
			pulseText2.Set(FlashValue(text));
			break;
		}
	}

	// FUNCTION: ENGINE 0x104CC2E0
	// NONMATCHING: the engine spills the clamped percentage after the second test, ours after the first (93.9 %)
#ifdef NONMATCHING
	void FEHudMeter::UpdatePercentage(float percentage)
	{
		if (percentage < 0.0f)
		{
			percentage = 0.0f;
		}
		if (percentage - gHundred >= 0.0f)
		{
			percentage = gHundred;
		}
		if (unknown14 > percentage)
		{
			unknown10 = unknown14 - percentage + unknown18;
			unknown1C = 0.0f;
		}
		float scaled = sBarScale * percentage;
		unknown14 = percentage;
		bar0X.Set(FlashValue(0.0));
		bar0Width.Set(FlashValue(300.0));
		bar2Width.Set(FlashValue(300.0));
		barsCombinedX.Set(FlashValue((double)(scaled - 300.0f)));
		cap1X.Set(FlashValue((double)scaled));
		flareX.Set(FlashValue((double)scaled));
	}
#endif

	// FUNCTION: ENGINE 0x104CC470
	// NONMATCHING: the engine shares the tail that sets the bar variable between the two positions and writes its fields in another order (97.2 %)
#ifdef NONMATCHING
	void FEHudMeter::UpdateWarPercentage(EPositions position, float percentage)
	{
		if (!(percentage >= 0.0f))
		{
			percentage = 0.0f;
		}
		if (percentage - gHundred >= 0.0f)
		{
			percentage = gHundred;
		}
		float scaled = sBarScale * percentage;
		scaled = scaled * engine::driving::gHalf;
		switch (position)
		{
		case 0:
			bar0Width.Set(FlashValue((double)scaled));
			bar0X.Set(FlashValue((double)(300.0f - scaled)));
			break;
		case 2:
			bar2Width.Set(FlashValue((double)scaled));
			break;
		}
		barsCombinedX.Set(FlashValue(-150.0));
		cap1X.Set(FlashValue((double)(sBarScale * gFifty)));
		flareX.Set(FlashValue((double)(sBarScale * gFifty)));
	}
#endif
}
