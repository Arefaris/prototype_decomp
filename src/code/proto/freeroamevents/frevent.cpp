// The free roam event itself (proto::FREvent): how the scripts start, end and complete it from outside. All names
// except the class are guesses.
#include "code/engine/database/gamedatabase.h"
#include "code/proto/freeroamevents/freventmanager.h"

namespace core
{
	int SNPrintfCount(char* destination, int size, const char* format, ...);
}

namespace proto
{
	// FUNCTION: ENGINE 0x10584EC0
	void FREvent::SetStateMachine(engine::GameObjectHandle handle)
	{
		stateMachine = handle;
	}

	// FUNCTION: ENGINE 0x10584FE0
	void FREvent::Activate()
	{
		targetState = 2;
	}

	// FUNCTION: ENGINE 0x10584FF0
	void FREvent::Deactivate(float time)
	{
		if (state == 2 || state == 1)
		{
			targetState = 0;
			timer = time;
		}
	}

	// FUNCTION: ENGINE 0x10585030
	void FREvent::Complete(bool success, float time)
	{
		if (state == 2 && success)
		{
			targetState = 0;
		}
		engine::GameDatabase* database = engine::gGameDatabase;
		if (!success)
		{
			if (state != 3)
			{
				targetState = 3;
				timer = 0.0f;
				database->SetInt(stateKey, 0, -1, 0);
			}
		}
		else
		{
			timer = time;
			int count = database->GetInt(stateKey, 0, 0);
			database->SetInt(stateKey, 0, count + 1, 0);
		}
	}

	// FUNCTION: ENGINE 0x105859A0
	bool FREvent::Unlock(const core::Name<core::CaseSensitiveKey>& key)
	{
		if (unlockKey == key)
		{
			unlocked = true;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105862C0
	const engine::GameObjectHandle& FREvent::GetHandle(engine::GameObjectHandle* result)
	{
		if (locator == 0)
		{
			MakeLocator();
		}
		*result = locator->handle;
		return *result;
	}

	// FUNCTION: ENGINE 0x105850E0
	int FREvent::GetCompletionCount()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		return database->GetInt(stateKey, 0, 0);
	}

	// FUNCTION: ENGINE 0x10585100
	int FREvent::GetAchievement()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		return database->GetInt(stateKey, 0, 1);
	}

	// FUNCTION: ENGINE 0x105851A0
	int FREvent::GetEPAward()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		return database->GetInt(stateKey, 0, 3);
	}

	// FUNCTION: ENGINE 0x105852E0
	int FREventInfo::HasMedals()
	{
		if (category != 4 && category != 5)
		{
			return 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10585C10
	int GetEventStatistic(const char* eventName, int index)
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		char text[64];
		core::SNPrintfCount(text, 0x40, "%s_stateData", eventName);
		core::Name<core::CaseSensitiveKey> key(text, 1);
		return database->GetInt(key, 0, index);
	}

	// FUNCTION: ENGINE 0x10585C70
	int FREventInfo::GetAchievement()
	{
		return GetEventStatistic(name, 1);
	}

	// FUNCTION: ENGINE 0x10585C90
	int FREventInfo::GetLastMedal()
	{
		return GetEventStatistic(name, 2);
	}

	// FUNCTION: ENGINE 0x10585CB0
	int FREventInfo::GetEPAward()
	{
		return GetEventStatistic(name, 3);
	}

	// FUNCTION: ENGINE 0x10585CD0
	int FREventInfo::GetCurrentEPAward()
	{
		return GetEventStatistic(name, 4);
	}

	// FUNCTION: ENGINE 0x10586800
	bool FREventInfo::CanSelect()
	{
		FREventManager* manager = gFREventManager;
		FREvent* event = manager->FindEvent(core::Name<core::CaseSensitiveKey>(name, 1));
		bool available = event->IsAvailable() != 0;
		return available;
	}

	// FUNCTION: ENGINE 0x10587300
	void FREvent::Unknown10587300(bool active)
	{
		if (!active)
		{
			Unknown10587140();
			unlocked = false;
		}
	}
}
