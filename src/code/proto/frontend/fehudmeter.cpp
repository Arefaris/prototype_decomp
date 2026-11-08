#include "code/proto/frontend/fehudmeter.h"

#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	// 0x10838900 / 0x10837AB0
	void AddSimulationTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveSimulationTask(IRealTimeTask* task);
}

namespace proto
{
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
}
