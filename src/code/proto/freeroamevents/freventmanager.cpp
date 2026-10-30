// The event bookkeeping of proto::FREventManager (path of the unit's other half from its asserts:
// code\proto\freeroamevents\eventscripting.cpp): looking events and their records up, entering and leaving free roam
// and switching the manager on and off. The registration of the natives and the rest of the manager are not part of
// this reconstruction. All names except the class are guesses.
#include "code/proto/freeroamevents/freventmanager.h"

#include "code/core/strings.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/scenariomessage.h"
#include "code/lua/lua.h"

namespace proto
{
	// The listeners of the free roam events' scenario messages (0x11274F18)
	extern engine::MessageListeners gFREventListeners;
	// A number the free roam entry resets (0x110B1188)
	extern int gFREventLastIndex;
	// 0x104DF2C0: tells the stats unit that the free roam state changed (name guess)
	void NotifyFreeRoamChanged();

	// True when the two handles are the same word
	static inline bool SameHandle(const engine::GameObjectHandle& a, const engine::GameObjectHandle& b)
	{
		return *(const unsigned int*)&a == *(const unsigned int*)&b;
	}

	// FUNCTION: ENGINE 0x10585120
	int FREvent::UpgradeToPlatinum()
	{
		engine::GameDatabase* database = engine::gGameDatabase;
		int award = database->GetInt(stateKey, 0, 5);
		if (award != 0)
		{
			database->SetInt(stateKey, 0, 4, 1);
			int total = database->GetInt(stateKey, 0, 3);
			database->SetInt(stateKey, 0, total + award, 3);
			database->SetInt(stateKey, 0, award, 4);
			return award;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10587C80
	FREventInfo* FREventManager::FindInfo(int category, int index)
	{
		FREventInfo* info = infos;
		while (info != 0)
		{
			if (category == info->category && index == info->index)
			{
				return info;
			}
			info = info->next;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10587FC0
	int FREventManager::UpgradeMedalsToPlatinum(lua_State* L)
	{
		int count = 0;
		int total = 0;
		for (FREvent* event = events; event != 0; event = event->next)
		{
			int award = event->UpgradeToPlatinum();
			if (award != 0)
			{
				count++;
				total += award;
			}
		}
		lua_pushinteger(L, count);
		lua_pushinteger(L, total);
		return 2;
	}

	// FUNCTION: ENGINE 0x10588570
	FREvent* FREventManager::FindEvent(core::Name<core::CaseSensitiveKey> name)
	{
		FREvent* event = lastEvent;
		if (event != 0 && name == event->name)
		{
			return event;
		}
		for (event = events; event != 0; event = event->next)
		{
			if (event->name == name)
			{
				return event;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1058AE10
	FREvent* FREventManager::FindEventByText(const char* name)
	{
		char text[8];
		core::StrNCpy(text, name, 7u);
		return FindEvent(core::Name<core::CaseSensitiveKey>(text, 1));
	}

	// FUNCTION: ENGINE 0x1058AE60
	void FREventManager::LeaveFreeRoam()
	{
		active = false;
		slotPool.Unknown10592DC0();
		timers.Unknown10587920();
		Unknown1058A290();
		core::Name<core::CaseSensitiveKey> name("FRE_enterMission", 1);
		engine::StringMessage message(name);
		engine::SendMessage(&message, &gFREventListeners);
		NotifyFreeRoamChanged();
	}

	// FUNCTION: ENGINE 0x1058AEE0
	void FREventManager::EnterFreeRoam()
	{
		active = true;
		Unknown1058A290();
		core::Name<core::CaseSensitiveKey> name("FRE_enterFreeRoam", 1);
		engine::StringMessage message(name);
		engine::SendMessage(&message, &gFREventListeners);
		gFREventLastIndex = -1;
		unknown160 = 0;
		NotifyFreeRoamChanged();
	}

	// FUNCTION: ENGINE 0x1058C1C0
	void FREventManager::SetActive(bool newActive)
	{
		unknown4 = newActive;
		if (newActive)
		{
			Unknown10587B70();
		}
		else
		{
			Unknown10587AF0();
			Unknown10587B90();
		}
		for (FREvent* event = events; event != 0; event = event->next)
		{
			event->Unknown10587300(newActive);
		}
		Unknown1058A290();
	}

	// FUNCTION: ENGINE 0x105885E0
	// NONMATCHING: the engine's frame holds an 8-aligned name temporary (push ebp / and esp, -8) and tracks the temporary's
	// construction in a flag; ours is a 4-aligned frame, 12-24 %
#ifdef NONMATCHING
	FREventInfo* FREventManager::FindInfoBySavedHandle(engine::SerializedHandle handle)
	{
		engine::GameObjectHandle target = engine::DeserializeHandle(handle);
		FREvent* event = events;
		while (event != 0)
		{
			engine::GameObjectHandle eventHandle;
			if (SameHandle(event->GetHandle(&eventHandle), target))
			{
				break;
			}
			event = event->next;
		}
		if (event == 0)
		{
			return 0;
		}
		FREventInfo* info = infos;
		while (info != 0 && event->name != core::Name<core::CaseSensitiveKey>(info->name, 1))
		{
			info = info->next;
		}
		return info;
	}
#endif

	// FUNCTION: ENGINE 0x105886B0
	// NONMATCHING: the engine's frame holds an 8-aligned name temporary (push ebp / and esp, -8) and tracks the temporary's
	// construction in a flag; ours is a 4-aligned frame, 12-24 %
#ifdef NONMATCHING
	FREventInfo* FREventManager::FindInfoByHandle(engine::GameObjectHandle handle)
	{
		FREvent* event = events;
		while (event != 0)
		{
			engine::GameObjectHandle eventHandle;
			if (SameHandle(event->GetHandle(&eventHandle), handle))
			{
				break;
			}
			event = event->next;
		}
		if (event == 0)
		{
			return 0;
		}
		FREventInfo* info = infos;
		while (info != 0 && event->name != core::Name<core::CaseSensitiveKey>(info->name, 1))
		{
			info = info->next;
		}
		return info;
	}
#endif
}
