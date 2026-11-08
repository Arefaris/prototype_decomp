// proto::GameFEControllerManager: see the header.
#include "code/proto/frontend/gamefecontrollermanager.h"

#include "code/core/name.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/frontend/frontend.h"

namespace engine
{
	void AddRealTimeTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveRealTimeTask(IRealTimeTask* task);
}

namespace proto
{
	// FUNCTION: ENGINE 0x104AD5F0
	GameFEControllerManager::GameFEControllerManager() :
		remapping(false),
		unknown9(false),
		unknownC(-1),
		unknown10(-1),
		unknown14(0)
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		engine::DBSubjectInfo info(false, 2, 1);
		database->AddIntSubject(core::Name<core::CaseSensitiveKey>("RemapStatus", 0), 0, -1, info);
		database->AddObserver(core::Name<core::CaseSensitiveKey>("SettingsMouseSensitivity", 0), this, 0, 0);
		engine::AddRealTimeTask(this, 1, 0, (unsigned int)"ControllerRemap Task");
	}

	// FUNCTION: ENGINE 0x104AD6D0
	GameFEControllerManager::~GameFEControllerManager()
	{
		engine::RemoveRealTimeTask(this);
		engine::GameDatabase* database = engine::gGameDatabase;
		database->ReleaseSubject(core::Name<core::CaseSensitiveKey>("RemapStatus", 0));
	}

	// FUNCTION: ENGINE 0x104AF370
	void GameFEControllerManager::Update(engine::UpdateContext context)
	{
		if (remapping)
		{
			Remap();
		}
	}

	// FUNCTION: ENGINE 0x104AECA0
	void GameFEControllerManager::OnDBSlot0(int a, int b)
	{
		if (*(const core::Name<core::CaseSensitiveKey>*)a == core::Name<core::CaseSensitiveKey>("SettingsMouseSensitivity", 0))
		{
			engine::SetCursorFade((float)*(int*)(b + 8) * 0.05f + 0.03f);
		}
	}
}
