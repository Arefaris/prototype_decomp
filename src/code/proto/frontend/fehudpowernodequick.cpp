#include "code/proto/frontend/fehudpowernodequick.h"

#include "code/engine/database/gamedatabase.h"
#include "code/proto/observerhelper.h"

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
	// 0x1126CB90: the key of the game database value that holds the power the player transformed into
	extern core::Name<core::CaseSensitiveKey> gHUDPlayerTransform;
}

namespace proto
{
	// 0x1126E4A0 (profilekeys.cpp)
	extern core::Name<core::CaseSensitiveKey> gProtoSaveQuickPowerSelect;

	class FrontEndHud
	{
	public:
		// 0x104B1D30: plays the sound of a power selection (name unknown)
		void Unknown104B1D30(int index);
	};
	// 0x104B0A00
	FrontEndHud* GetFrontEndHud();

	// 0x110983E4: the movie clip of the powers
	static const char* sPowersClip = "mcAnchor.powersHUD";

	// FUNCTION: ENGINE 0x104C54E0
	FEHudPowerNodeQuick::FEHudPowerNodeQuick(int newSlot, int newPower, bool newLocked) : slot(newSlot), power(newPower),
		shown(false), selectionPending(false), selected(-1), locked(newLocked)
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		database->AddObserver(gProtoSaveQuickPowerSelect, this, 0, 0);
		database->AddObserver(engine::gHUDPlayerTransform, this, 0, 0);
	}

	// FUNCTION: ENGINE 0x104C52F0
	FEHudPowerNodeQuick::~FEHudPowerNodeQuick()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		database->RemoveObserver(gProtoSaveQuickPowerSelect, this);
		database->RemoveObserver(engine::gHUDPlayerTransform, this);
	}

	// FUNCTION: ENGINE 0x104C5490
	void FEHudPowerNodeQuick::OnDBSlot1(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x104C55D0
	void FEHudPowerNodeQuick::OnDBSlot0(int key, int change)
	{
		const DBChange* record = (const DBChange*)change;
		if (record->index == slot)
		{
			if (*(const core::Name<core::CaseSensitiveKey>*)key == engine::gHUDPlayerTransform)
			{
				int value = record->value;
				if (!locked && value != power && value != 0 && value != 0xd)
				{
					SetPower(value, false);
					SendQuickSelect();
					return;
				}
			}
			else
			{
				int value = record->value;
				if (!locked && power != value)
				{
					SetPower(value, true);
					engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", sPowersClip, "SetQuickSelect", slot, power);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x104C5330
	void FEHudPowerNodeQuick::SetPower(int newPower, bool silent)
	{
		if (!locked && power != newPower)
		{
			if (!silent)
			{
				engine::gGameDatabase->SetInt(gProtoSaveQuickPowerSelect, 0, newPower, slot);
			}
			power = newPower;
		}
	}

	// FUNCTION: ENGINE 0x104C5380
	void FEHudPowerNodeQuick::Select()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		int current = database->GetInt(engine::gHUDPlayerTransform, 0, slot);
		if (current != 0 && current != 0xd)
		{
			database->SetInt(engine::gHUDPlayerTransform, 0, 0, slot);
			selected = 0;
			selectionPending = true;
			return;
		}
		database->SetInt(engine::gHUDPlayerTransform, 0, power, slot);
		selected = power;
		selectionPending = true;
	}

	// FUNCTION: ENGINE 0x104C5440
	void FEHudPowerNodeQuick::ShowQuickSelect(const char* text, bool newShown)
	{
		shown = newShown;
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%s", sPowersClip, "ShowQuickSelect", slot, text);
	}

	// FUNCTION: ENGINE 0x104C54A0
	void FEHudPowerNodeQuick::SendQuickSelect()
	{
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", sPowersClip, "SetQuickSelect", slot, power);
	}

	// FUNCTION: ENGINE 0x104C5560
	void FEHudPowerNodeQuick::Update()
	{
		if (selectionPending)
		{
			int current = engine::gGameDatabase->GetInt(engine::gHUDPlayerTransform, 0, slot);
			if (selected == current)
			{
				if (selected == 0)
				{
					GetFrontEndHud()->Unknown104B1D30(4);
				}
				else
				{
					GetFrontEndHud()->Unknown104B1D30(3);
				}
				ShowQuickSelect("TOGGLE", false);
			}
			selectionPending = false;
		}
	}

	// FUNCTION: ENGINE 0x104C56A0
	void FEHudPowerNodeQuick::Reload()
	{
		int saved = engine::gGameDatabase->GetInt(gProtoSaveQuickPowerSelect, 0, slot);
		SetPower(saved, false);
		SendQuickSelect();
	}
}
