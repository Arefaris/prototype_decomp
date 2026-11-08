#include "code/proto/frontend/fehudhealth.h"

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
	// The pause menu's state (another unit)
	class PauseMenuState
	{
	public:
		// 0x1049B8A0: starts or stops the sound of the poison effect (name guessed)
		void Unknown1049B8A0(bool poisoned);
	};
	// 0x1049B3D0
	PauseMenuState* GetPauseMenuState();

	// 0x1109AA74 / 0x1109AA78: the movie clips of the health meter and of the poison effect
	static const char* sHealthClip = "mcAnchor.healthHUD";
	static const char* sPoisonClip = "mcAnchor.poisonHUD";

	// FUNCTION: ENGINE 0x104D4BF0
	FEHudHealth::FEHudHealth() : unknown10(0.0f), unknown14(0.0f), unknown18(0.0f), unknown1C(0.0f), unknown20(0.0f),
		unknown2C(0.0f), visible(true), unknown31(false), unknown32(false), unknown33(false), taskActive(false),
		unknown3C(0.0f), unknown40(0.0f), unknown44(0.0f), unknown48(0.0f), unknown50(0.0f), unknown54(0.0f),
		unknown58(false), unknown5C(0.0f), unknown60(0.0f), unknown64(true), unknown65(false),
		visibleVariable("_level0.mcAnchor.healthHUD._visible"),
		normHealthMask("_level0.mcAnchor.healthHUD.normHealth.normHPMask._x"),
		damageMask("_level0.mcAnchor.healthHUD.normHealth.damageHPMask._x"),
		backgroundMask("_level0.mcAnchor.healthHUD.normHealth.BGMask._x"),
		criticalMassMask("_level0.mcAnchor.healthHUD.normHealth.cMassMask._x"),
		criticalMass("_level0.mcAnchor.healthHUD.normHealth.criticalMass._x"),
		gainMask("_level0.mcAnchor.healthHUD.normHealth.gainHPMask._x"),
		gain("_level0.mcAnchor.healthHUD.normHealth.mcGain._x"),
		criticalMassIndicator("_level0.mcAnchor.healthHUD.normHealth.critMassIndicator._x"),
		criticalMassBottomMask("_level0.mcAnchor.healthHUD.normHealth.critMassBottomMask._x"),
		ekgMask("_level0.mcAnchor.healthHUD.normHealth.EKGMask._x"),
		scanlines("_level0.mcAnchor.healthHUD.normHealth.mcScanlines._width")
	{
		SetTaskActive(true);
		GetPauseMenuState()->Unknown1049B8A0(unknown65);
	}

	// FUNCTION: ENGINE 0x104D4370
	FEHudHealth::~FEHudHealth()
	{
		SetTaskActive(false);
	}

	// FUNCTION: ENGINE 0x104D3E10
	void FEHudHealth::Update(bool force)
	{
		visibleVariable.Flush(force);
		normHealthMask.Flush(force);
		damageMask.Flush(force);
		criticalMassMask.Flush(force);
		backgroundMask.Flush(force);
		criticalMass.Flush(force);
		criticalMassIndicator.Flush(force);
		criticalMassBottomMask.Flush(force);
		ekgMask.Flush(force);
		gainMask.Flush(force);
		gain.Flush(force);
		scanlines.Flush(force);
	}

	// FUNCTION: ENGINE 0x104D5150
	void FEHudHealth::OnShow(bool shown)
	{
		SetVisible(shown);
		SetTaskActive(shown);
	}

	// FUNCTION: ENGINE 0x104D4B90
	void FEHudHealth::SetVisible(bool newVisible)
	{
		visible = newVisible;
		visibleVariable.Set(FlashValue(newVisible));
		visibleVariable.Flush(true);
		if (unknown65)
		{
			ShowPoison(newVisible);
		}
	}

	// FUNCTION: ENGINE 0x104D4280
	void FEHudHealth::SetTaskActive(bool active)
	{
		if (active)
		{
			if (!taskActive)
			{
				engine::AddSimulationTask((engine::IRealTimeTask*)static_cast<engine::ISimulationTask*>(this), 4, 1,
					(unsigned int)"FEHudHealth Task");
			}
		}
		else if (taskActive)
		{
			engine::RemoveSimulationTask((engine::IRealTimeTask*)static_cast<engine::ISimulationTask*>(this));
		}
		taskActive = active;
	}

	// FUNCTION: ENGINE 0x104D4230
	void FEHudHealth::ShowPoison(bool poisoned)
	{
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", sPoisonClip, "ShowPoison", poisoned);
		GetPauseMenuState()->Unknown1049B8A0(poisoned);
	}

	// FUNCTION: ENGINE 0x104D4160
	// NONMATCHING: the engine puts the two early exits behind the switch, the first for [+0x31] and the second for [+0x32]; ours puts them in the other order (35 %)
#ifdef NONMATCHING
	void FEHudHealth::SetDevastatorState(int newState)
	{
		if (unknown31)
		{
			devastatorState = newState;
		}
		else if (unknown32)
		{
			devastatorState = newState;
		}
		else
		{
			switch (newState)
			{
			case 0:
			{
				int shown = 0;
				if (devastatorState == 1)
				{
					shown = 6;
				}
				if (devastatorState == 2)
				{
					shown = 7;
				}
				engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", sHealthClip, "ShowDevastatorDisplay", shown);
				break;
			}
			case 1:
				engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", sHealthClip, "ShowDevastatorDisplay", 4);
				break;
			case 2:
				engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", sHealthClip, "ShowDevastatorDisplay", 5);
				break;
			}
			devastatorState = newState;
		}
	}
#endif

	// FUNCTION: ENGINE 0x104D3EE0
	void FEHudHealth::SetUnknown64(bool value)
	{
		unknown64 = value;
	}

	// FUNCTION: ENGINE 0x104D3EF0
	bool FEHudHealth::GetUnknown64()
	{
		return unknown64;
	}

	// FUNCTION: ENGINE 0x104D3F00
	float FEHudHealth::GetUnknown5C()
	{
		return unknown5C;
	}

	// FUNCTION: ENGINE 0x104D3F10
	void FEHudHealth::ClearUnknown5C()
	{
		unknown5C = 0.0f;
	}

	// FUNCTION: ENGINE 0x104D3ED0
	void FEHudHealth::Unknown104D3ED0()
	{
	}
}
