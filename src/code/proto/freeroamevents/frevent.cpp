// The free roam event itself (proto::FREvent): how the scripts start, end and complete it from outside. All names
// except the class are guesses.
#include "code/engine/database/gamedatabase.h"
#include "code/proto/freeroamevents/freventmanager.h"

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
}
