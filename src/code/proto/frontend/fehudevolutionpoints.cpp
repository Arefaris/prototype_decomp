#include "code/proto/frontend/fehudevolutionpoints.h"

#include "code/core/name.h"
#include "code/engine/database/gamedatabase.h"

namespace engine
{
	namespace camera
	{
		// 0x10D95F28
		extern const float gThree;
	}
	namespace driving
	{
		// 0x10D946E0 / 0x10D95578 / 0x10D94CC4
		extern const float gOne;
		extern const float gTwo;
		extern const float gHalf;
	}
	// 0x10838900 / 0x10837AB0
	void AddSimulationTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveSimulationTask(IRealTimeTask* task);
}

namespace ravenphysics
{
	// 0x10D977E4
	extern const float gDefaultMaxForce;
}

namespace proto
{
	// 0x10D977E0
	extern const float gHundred;
	// 0x1126E4C0 (profilekeys.cpp)
	extern core::Name<core::CaseSensitiveKey> gSmartHintSettingName;

	// FUNCTION: ENGINE 0x104D0480
	// NONMATCHING: the engine loads the float constants early and stores them in another order than the members' (66 %)
#ifdef NONMATCHING
	FEHudEvolutionPoints::FEHudEvolutionPoints() : epText("_level0.mcAnchor.epHUD.mcEPText.txtEPTotal.text"),
		epShadowText("_level0.mcAnchor.epHUD.mcShadowText.txtEPTotal.text"),
		gainText("_level0.mcAnchor.epHUD.mcLargeGain.mcGainText.txtEPTotal.text"),
		gainShadowText("_level0.mcAnchor.epHUD.mcLargeGain.mcGainShadowText.txtEPTotal.text"),
		visible("_level0.mcAnchor.epHUD._visible"), unknown360(0), unknown364(0), unknown368(0), unknown36C(0),
		unknown370(0), unknown374(10), unknown378(100), unknown384(0.0f), unknown388(false), unknown389(false),
		unknown38A(false), unknown38C(engine::camera::gThree), unknown390(engine::driving::gOne), unknown394(gHundred),
		unknown398(ravenphysics::gDefaultMaxForce), unknown39C(0.0f), unknown3A0(engine::driving::gTwo),
		unknown3A4(engine::driving::gHalf), taskActive(false)
	{
		SetTaskActive(true);
		engine::gGameDatabase->AddObserver(gSmartHintSettingName, static_cast<engine::DBObserver*>(this), 0, 0);
		visible.Set(FlashValue(true));
	}
#endif

	// FUNCTION: ENGINE 0x104D0020
	FEHudEvolutionPoints::~FEHudEvolutionPoints()
	{
		engine::gGameDatabase->RemoveObserver(gSmartHintSettingName, static_cast<engine::DBObserver*>(this));
		SetTaskActive(false);
	}

	// FUNCTION: ENGINE 0x104CFE70
	void FEHudEvolutionPoints::Update(bool force)
	{
		epText.Flush(force);
		gainText.Flush(force);
		epShadowText.Flush(force);
		gainShadowText.Flush(force);
		visible.Flush(force);
	}

	// FUNCTION: ENGINE 0x104D00C0
	void FEHudEvolutionPoints::OnShow(bool shown)
	{
		SetVisible(shown);
		SetTaskActive(shown);
	}

	// FUNCTION: ENGINE 0x104CFF40
	void FEHudEvolutionPoints::SetVisible(bool newVisible)
	{
		visible.Set(FlashValue(newVisible));
		visible.Flush(true);
	}

	// FUNCTION: ENGINE 0x104CFF90
	void FEHudEvolutionPoints::SetTaskActive(bool active)
	{
		if (active)
		{
			if (!taskActive)
			{
				engine::AddSimulationTask((engine::IRealTimeTask*)static_cast<engine::ISimulationTask*>(this), 4, 1,
					(unsigned int)"FEHudEP Task");
			}
		}
		else if (taskActive)
		{
			engine::RemoveSimulationTask((engine::IRealTimeTask*)static_cast<engine::ISimulationTask*>(this));
		}
		taskActive = active;
	}

	// FUNCTION: ENGINE 0x104CFEE0
	void FEHudEvolutionPoints::SetFloats(float a, float b, float c, float d)
	{
		unknown394 = a;
		unknown398 = b;
		unknown390 = c;
		unknown38C = d;
	}

	// FUNCTION: ENGINE 0x104D0A90
	void FEHudEvolutionPoints::Unknown104D0A90()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		Unknown104D00F0(database->GetInt(gSmartHintSettingName, 0, 0));
		Unknown104D0870(database->GetInt(gSmartHintSettingName, 0, 0), true);
	}

	// FUNCTION: ENGINE 0x104D0AE0
	void FEHudEvolutionPoints::OnDBSlot0(int a, int b)
	{
		Unknown104D0870(engine::gGameDatabase->GetInt(gSmartHintSettingName, 0, 0), false);
	}

	// FUNCTION: ENGINE 0x104CFF30
	void FEHudEvolutionPoints::OnDBSlot1(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x104CFED0
	void FEHudEvolutionPoints::Unknown104CFED0()
	{
	}
}
