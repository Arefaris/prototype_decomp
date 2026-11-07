// The script side of the free roam event manager (path from the unit's own assert strings:
// code\proto\freeroamevents\eventscripting.cpp): the methods the `fre_` script functions are bound to and the Lua
// C functions that answer questions about the event lists. The unit's other half (registration of the natives, the
// event bookkeeping, the second group of natives) is not part of this reconstruction. All names except the Lua
// function names and the class are guesses.
#include "code/proto/freeroamevents/freventmanager.h"

#include "code/core/report.h"
#include "code/core/strings.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/luascriptmanager.h"
#include "code/lua/lua.h"
#include <string.h>

namespace engine
{
	// 0x108024C0: reads a name argument of a script function; the scenario message listeners of the free roam events
	void LuaGetNameArgument(lua_State* L, int index, core::Name<core::CaseSensitiveKey>* name);
	extern MessageListeners gScenario12;
}

namespace core
{
	int SNPrintfCount(char* destination, int size, const char* format, ...);
}

namespace math
{
	// The zero vector (another unit's constant)
	extern const Vector kZeroVector;
}

namespace engine
{
	// 0x108020D0 (the Lua script unit): reads the integer field of the table on top of the stack
	void LuaGetIntField(lua_State* L, const char* key, int* value);
}

namespace proto
{
	// The table of the progress flags (the global at 0x112738B8): the medals and unlocks of the front end
	class UnlockTable
	{
	public:
		// 0x10579390: tests one flag of the database's unlock array
		bool IsUnlocked(int player, int index);
	};
	extern UnlockTable* gUnlockTable;

	// The save manager (the global at 0x1126B474)
	class SaveManager
	{
	public:
		// 0x1047FAF0
		void RequestSave();
	};
	SaveManager* GetSaveManager();

	// The pieces of the heads up display the end popup of an event goes through
	class PopupWidget
	{
	public:
		// 0x104CFB30
		void Hide(bool a, bool b);
	};
	class PopupController
	{
	public:
		unsigned char unknown0[0x30];
		PopupWidget* popup;
	};
	class FrontEndHud
	{
	public:
		// 0x104B0CE0: the popup controller inside the hud object (+0x180)
		PopupController* GetPopups();
	};
	// 0x104B0A00
	FrontEndHud* GetFrontEndHud();

	// 0x10367640 / 0x103675E0 / 0x103676D0 / 0x10590400 (the script value readers): read a value of the table on
	// top of the stack (by key) or the value on top into the pointer; false when it is not of the type
	bool GetFloatField(lua_State* L, const char* key, float* value);
	bool GetNumber(lua_State* L, float* value);
	bool GetBoolean(lua_State* L, bool* value);
	void GetStringField(lua_State* L, const char* key, char* buffer, int size);
	// 0x10590390 / 0x10590440 / 0x105904B0 / 0x10590500 / 0x10590540: the readers of the string and game object
	// values, a check for a table field and the removal of the value on top (names guessed)
	bool ReadStringValue(lua_State* L, char* buffer, int size);
	bool GetHandleValue(lua_State* L, engine::GameObjectHandle* handle);
	bool GetHandleField(lua_State* L, const char* key, engine::GameObjectHandle* handle);
	bool IsTableField(lua_State* L, const char* key);
	void PopValue(lua_State* L);

	// The game database's text of the unlock keys received so far (the name at 0x1126E4B8)
	core::Name<core::CaseSensitiveKey> gUnlockKeysName("Proto_Save_EventKeys", 0);

	// The texts the manager's constructor sets for the six kinds of event (0x11274F38 the descriptions, 0x11274F78 the
	// tutorials, 0x11274F60 the labels of the best score, 0x11274F90 the labels of the current score)
	extern const char* gCategoryDescriptionStrings[];
	extern const char* gCategoryTutorialStrings[];
	extern const char* gCategoryBestScoreLabels[];
	extern const char* gCategoryCurrentScoreLabels[];

	// The text of the category event description the script asks for ("$" and the event's name)
	static char sCategoryEventDescription[8] = "$freXXX";
	// The answer of GetLuaString
	static char sLuaString[0x80];

	#define EVENTSCRIPTING_FILE "..\\..\\..\\code\\proto\\freeroamevents\\eventscripting.cpp"

	// FUNCTION: ENGINE 0x1058E3A0
	bool FREventManager::IsFreeRoamActive()
	{
		return active;
	}

	// FUNCTION: ENGINE 0x1058E3B0
	void FREventManager::SetManagerActiveState(bool active)
	{
		SetActive(active);
	}

	// FUNCTION: ENGINE 0x1058E3C0
	void FREventManager::ActivateObject(const char* name)
	{
		FREvent* event = FindEventByText(name);
		if (event != 0)
		{
			event->ActivateObject(name, true);
			return;
		}
		static bool sReported = true;
		if (sReported)
		{
			sReported = false;
			core::Report(0, "fre", EVENTSCRIPTING_FILE, 171, 0, "ActivateObject failed to find event from name: %s", name,
				0);
		}
	}

	// FUNCTION: ENGINE 0x1058E430
	void FREventManager::DeactivateObject(const char* name)
	{
		FREvent* event = FindEventByText(name);
		if (event != 0)
		{
			event->ActivateObject(name, false);
			return;
		}
		static bool sReported = true;
		if (sReported)
		{
			sReported = false;
			core::Report(0, "fre", EVENTSCRIPTING_FILE, 188, 0, "DeactivateObject failed to find event from name: %s",
				name, 0);
		}
	}

	// FUNCTION: ENGINE 0x1058E4A0
	math::Vector FREventManager::GetObjectPosition(const char* name)
	{
		FREvent* event = FindEventByText(name);
		if (event != 0)
		{
			FREventObject* object = event->FindObject(name);
			if (object != 0)
			{
				return object->GetPosition();
			}
			static bool sObjectReported = true;
			if (sObjectReported)
			{
				sObjectReported = false;
				core::Report(0, "fre", EVENTSCRIPTING_FILE, 260, 0, "GetObjectPosition failed to find object: %s", name,
					0);
			}
		}
		else
		{
			static bool sEventReported = true;
			if (sEventReported)
			{
				sEventReported = false;
				core::Report(0, "fre", EVENTSCRIPTING_FILE, 265, 0,
					"GetObjectPosition failed to find event from name: %s", name, 0);
			}
		}
		return math::kZeroVector;
	}

	// FUNCTION: ENGINE 0x1058E580
	void FREventManager::SetDebugString(const char* text)
	{
	}

	// FUNCTION: ENGINE 0x1058E590
	void FREventManager::SetDebugEventState(const char* name, const char* state)
	{
	}

	// FUNCTION: ENGINE 0x1058E5A0
	bool FREventManager::IsPlatinumEventsAvailable()
	{
		return gUnlockTable->IsUnlocked(0, 0x1e0);
	}

	// FUNCTION: ENGINE 0x1058E5C0
	int fre_UpgradeMedalsToPlatinum(lua_State* L)
	{
		return gFREventManager->UpgradeMedalsToPlatinum(L);
	}

	// FUNCTION: ENGINE 0x1058E5E0
	void FREventManager::TriggerSave()
	{
		GetSaveManager()->RequestSave();
	}

	// FUNCTION: ENGINE 0x1058E5F0
	// Takes a key out of the text of the received unlock keys
	void FREventManager::RemoveUnlockKey(const char* key)
	{
		char keys[0x400];
		engine::GameDatabase* database = engine::gGameDatabase;
		core::StrCpy(keys, database->GetString(gUnlockKeysName, 0, 0));
		char* found = strstr(keys, key);
		if (found != 0)
		{
			int length = (int)strlen(keys);
			int keyLength = (int)strlen(key);
			int rest = length - keyLength - (int)(found - keys);
			if (rest > 0)
			{
				memcpy(found, found + keyLength, rest);
			}
			keys[length - keyLength] = 0;
			database->SetString(gUnlockKeysName, 0, keys, 0);
		}
	}

	// FUNCTION: ENGINE 0x1058E6D0
	bool FREventManager::HasUnlockKeyBeenReceived(const char* key)
	{
		char keys[0x400];
		if (unlockedAll)
		{
			return true;
		}
		core::StrCpy(keys, engine::gGameDatabase->GetString(gUnlockKeysName, 0, 0));
		return strstr(keys, key);
	}

	// FUNCTION: ENGINE 0x1058E740
	int FREventManager::GetNumFreeDynamicPackageSlots()
	{
		return slotPool.GetNumFree();
	}

	// FUNCTION: ENGINE 0x1058E750
	void FREventManager::UnlockAllEvents()
	{
		for (FREvent* event = events; event != 0; event = event->next)
		{
			event->unlocked = true;
		}
		unlockedAll = true;
	}

	// FUNCTION: ENGINE 0x1058E780
	FREventInfo* FREventManager::GetInfoFromArguments(lua_State* L)
	{
		if (lua_gettop(L) == 2)
		{
			int category = luaL_checkinteger(L, 1);
			int index = luaL_checkinteger(L, 2);
			return FindInfo(category, index);
		}
		int index = luaL_checkinteger(L, 1);
		FREventInfo* info = infos;
		for (; index != 0; index--)
		{
			info = info->next;
		}
		return info;
	}

	// FUNCTION: ENGINE 0x1058E800
	int FREventManager::GetNumCategories()
	{
		return 5;
	}

	// FUNCTION: ENGINE 0x1058E810
	int fre_GetCategoryEventBestString(lua_State* L)
	{
		FREventInfo* info = gFREventManager->GetInfoFromArguments(L);
		lua_pushstring(L, info->GetString(0));
		return 1;
	}

	// FUNCTION: ENGINE 0x1058E850
	int fre_GetCategoryEventCurrentScoreString(lua_State* L)
	{
		FREventInfo* info = gFREventManager->GetInfoFromArguments(L);
		lua_pushstring(L, info->GetString(1));
		return 1;
	}

	// FUNCTION: ENGINE 0x1058E890
	int fre_GetCategoryEventDescriptionString(lua_State* L)
	{
		FREventInfo* info = gFREventManager->GetInfoFromArguments(L);
		core::StrNCpy(sCategoryEventDescription + 1, info->name, 7u);
		lua_pushstring(L, sCategoryEventDescription);
		return 1;
	}

	// FUNCTION: ENGINE 0x1058E8E0
	int fre_GetCategoryEventSubType(lua_State* L)
	{
		lua_pushnumber(L, (float)gFREventManager->GetInfoFromArguments(L)->subType);
		return 1;
	}

	// FUNCTION: ENGINE 0x1058E920
	int fre_GetCategoryEventEPAward(lua_State* L)
	{
		lua_pushnumber(L, (float)gFREventManager->GetInfoFromArguments(L)->GetEPAward());
		return 1;
	}

	// FUNCTION: ENGINE 0x1058E960
	int fre_GetCategoryEventCurrentEPAward(lua_State* L)
	{
		lua_pushnumber(L, (float)gFREventManager->GetInfoFromArguments(L)->GetCurrentEPAward());
		return 1;
	}

	// FUNCTION: ENGINE 0x1058E9A0
	int fre_GetCategoryEventAchievement(lua_State* L)
	{
		lua_pushnumber(L, (float)gFREventManager->GetInfoFromArguments(L)->GetAchievement());
		return 1;
	}

	// FUNCTION: ENGINE 0x1058E9E0
	int FREventManager::GetCategoryEventAchievementByGOH(unsigned int high, unsigned int low)
	{
		engine::SerializedHandle handle;
		handle.value = high << 16 | (unsigned short)low;
		FREventInfo* info = FindInfoBySavedHandle(handle);
		if (info != 0)
		{
			return info->GetAchievement();
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1058EA10
	int FREventManager::GetEventAwardedEPByGOH(unsigned int high, unsigned int low)
	{
		engine::SerializedHandle handle;
		handle.value = high << 16 | (unsigned short)low;
		FREventInfo* info = FindInfoBySavedHandle(handle);
		if (info != 0)
		{
			return info->GetEPAward();
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1058EA40
	int FREventManager::GetEventTotalEPByGOH(unsigned int high, unsigned int low)
	{
		int total = 0;
		engine::SerializedHandle handle;
		handle.value = high << 16 | (unsigned short)low;
		FREventInfo* info = FindInfoBySavedHandle(handle);
		if (info != 0)
		{
			engine::LuaScriptManager* script = engine::GetScriptManager();
			if (script->OpenTable("FreeRoamEventsEPAwards", true, true))
			{
				if (script->OpenTable(info->name, false, true))
				{
					int value = 0;
					engine::LuaGetIntField(script->state, "bronze", &value);
					total = value;
					engine::LuaGetIntField(script->state, "silver", &value);
					total += value;
					engine::LuaGetIntField(script->state, "gold", &value);
					total += value;
					if (IsPlatinumEventsAvailable())
					{
						engine::LuaGetIntField(script->state, "platinum", &value);
						total += value;
					}
					script->Pop(1);
				}
				script->Pop(1);
			}
		}
		return total;
	}

	// FUNCTION: ENGINE 0x1058EB70
	int FREventManager::GetEventAchievement(engine::GameObjectHandle handle)
	{
		FREventInfo* info = FindInfoByHandle(handle);
		if (info != 0)
		{
			return info->GetAchievement();
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1058EBA0
	int fre_GetCategoryEventLastMedal(lua_State* L)
	{
		lua_pushnumber(L, (float)gFREventManager->GetInfoFromArguments(L)->GetLastMedal());
		return 1;
	}

	// FUNCTION: ENGINE 0x1058EBE0
	int fre_GetCategoryEventCanSelect(lua_State* L)
	{
		lua_pushboolean(L, gFREventManager->GetInfoFromArguments(L)->CanSelect());
		return 1;
	}

	// FUNCTION: ENGINE 0x1058EC20
	bool FREventManager::GetCategoryEventCanSelectByGOH(unsigned int high, unsigned int low)
	{
		engine::SerializedHandle handle;
		handle.value = high << 16 | (unsigned short)low;
		FREventInfo* info = FindInfoBySavedHandle(handle);
		if (info != 0)
		{
			return info->CanSelect();
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1058EC50
	void FREventManager::ShowEventEndPopup()
	{
		PopupController* popups = GetFrontEndHud()->GetPopups();
		popups->popup->Hide(false, false);
	}

	// FUNCTION: ENGINE 0x1058EC70
	float FREventManager::GetLuaFloat(const char* table, const char* key)
	{
		lua_State* L = engine::GetScriptManager()->state;
		lua_getfield(L, LUA_GLOBALSINDEX, table);
		float value = 0.0f;
		if (lua_type(L, -1) == LUA_TTABLE)
		{
			GetFloatField(L, key, &value);
		}
		lua_settop(L, -2);
		return value;
	}

	// FUNCTION: ENGINE 0x1058ECE0
	int FREventManager::GetLuaInt(const char* table, const char* key)
	{
		lua_State* L = engine::GetScriptManager()->state;
		lua_getfield(L, LUA_GLOBALSINDEX, table);
		int result = 0;
		if (lua_type(L, -1) == LUA_TTABLE)
		{
			lua_pushstring(L, key);
			lua_rawget(L, -2);
			if (lua_type(L, -1) == LUA_TBOOLEAN)
			{
				bool flag;
				if (GetBoolean(L, &flag))
				{
					result = flag;
					lua_settop(L, -2);
					return result;
				}
			}
			else
			{
				float number;
				if (GetNumber(L, &number))
				{
					result = (int)(number + 0.5f);
				}
			}
		}
		lua_settop(L, -2);
		return result;
	}

	// FUNCTION: ENGINE 0x1058EDC0
	const char* FREventManager::GetLuaString(const char* table, const char* key)
	{
		lua_State* L = engine::GetScriptManager()->state;
		lua_getfield(L, LUA_GLOBALSINDEX, table);
		if (lua_type(L, -1) == LUA_TTABLE)
		{
			GetStringField(L, key, sLuaString, 0x80);
		}
		else
		{
			sLuaString[0] = 0;
		}
		lua_settop(L, -2);
		return sLuaString;
	}

	// FUNCTION: ENGINE 0x1058EE50
	core::Name<core::CaseSensitiveKey> FREventInfo::GetNameKey()
	{
		return nameKey;
	}

	// FUNCTION: ENGINE 0x1058EE70
	void FREventManager::AssociateStateMachine(const char* name, engine::LuaGOH handle)
	{
		FREventManager* manager = gFREventManager;
		FREvent* event = manager->FindEvent(core::Name<core::CaseSensitiveKey>(name, 1));
		if (event != 0)
		{
			event->SetStateMachine(engine::DeserializeHandle(handle));
		}
	}

	// FUNCTION: ENGINE 0x1058EED0
	void FREventManager::SetFreeRoamState(bool active)
	{
		if (active != IsFreeRoamActive())
		{
			if (active)
			{
				EnterFreeRoam();
				return;
			}
			LeaveFreeRoam();
		}
	}

	// FUNCTION: ENGINE 0x1058EF00
	void FREventManager::ActivateEvent(const char* name)
	{
		FREvent* event = FindEvent(core::Name<core::CaseSensitiveKey>(name, 1));
		if (event != 0)
		{
			event->Activate();
			return;
		}
		static bool sReported = true;
		if (sReported)
		{
			sReported = false;
			core::Report(0, "fre", EVENTSCRIPTING_FILE, 205, 0, "ActivateEvent failed to find event from name: %s", name,
				0);
		}
	}

	// FUNCTION: ENGINE 0x1058EF80
	void FREventManager::DeactivateEvent(const char* name, float time)
	{
		FREvent* event = FindEvent(core::Name<core::CaseSensitiveKey>(name, 1));
		if (event != 0)
		{
			event->Deactivate(time);
			return;
		}
		static bool sReported = true;
		if (sReported)
		{
			sReported = false;
			core::Report(0, "fre", EVENTSCRIPTING_FILE, 223, 0, "DeactivateEvent failed to find event from name: %s",
				name, 0);
		}
	}

	// FUNCTION: ENGINE 0x1058F010
	void FREventManager::CompleteEvent(const char* name, bool success, float time)
	{
		FREvent* event = FindEvent(core::Name<core::CaseSensitiveKey>(name, 1));
		if (event != 0)
		{
			event->Complete(success, time);
			return;
		}
		static bool sReported = true;
		if (sReported)
		{
			sReported = false;
			core::Report(0, "fre", EVENTSCRIPTING_FILE, 240, 0, "DeactivateEvent failed to find event from name: %s",
				name, 0);
		}
	}

	// FUNCTION: ENGINE 0x1058F0A0
	float FREventManager::GetMedalThreshold(const char* name, int index)
	{
		FREvent* event = FindEvent(core::Name<core::CaseSensitiveKey>(name, 1));
		if (event != 0)
		{
			return event->medalThresholds[index];
		}
		static bool sReported = true;
		if (sReported)
		{
			sReported = false;
			core::Report(0, "fre", EVENTSCRIPTING_FILE, 333, 0, "GetMedalThreshold failed to find event from name: %s",
				name, 0);
		}
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x1058F440
	bool FREventManager::UnlockEventsByKey(core::Name<core::CaseSensitiveKey> key)
	{
		bool unlocked = false;
		for (FREvent* event = events; event != 0; event = event->next)
		{
			if (event->Unlock(key))
			{
				unlocked = true;
			}
		}
		return unlocked;
	}

	// FUNCTION: ENGINE 0x1058F650
	void FREventManager::SetLastEvent(const char* name, bool remember)
	{
		FREvent* event = FindEvent(core::Name<core::CaseSensitiveKey>(name, 1));
		if (event != 0)
		{
			lastEvent = remember ? event : 0;
		}
	}

	// FUNCTION: ENGINE 0x1058F830
	int fre_GetCategoryDescriptionString(lua_State* L)
	{
		FREventInfo* info = gFREventManager->GetInfoFromArguments(L);
		lua_pushstring(L, gCategoryDescriptionStrings[info->category]);
		return 1;
	}

	// FUNCTION: ENGINE 0x1058F870
	int fre_GetCategoryTutorialString(lua_State* L)
	{
		FREventInfo* info = gFREventManager->GetInfoFromArguments(L);
		lua_pushstring(L, gCategoryTutorialStrings[info->category]);
		return 1;
	}

	// FUNCTION: ENGINE 0x1058F900
	int fre_GetCategoryEventAvailability(lua_State* L)
	{
		FREventInfo* info = gFREventManager->GetInfoFromArguments(L);
		FREventManager* manager = gFREventManager;
		FREvent* event = manager->FindEvent(core::Name<core::CaseSensitiveKey>(info->name, 1));
		lua_pushboolean(L, event->Unknown105865D0(1));
		return 1;
	}

	// FUNCTION: ENGINE 0x1058FA00
	int fre_GetCategoryBestScoreLabel(lua_State* L)
	{
		FREventInfo* info = gFREventManager->GetInfoFromArguments(L);
		lua_pushstring(L, gCategoryBestScoreLabels[info->category]);
		return 1;
	}

	// FUNCTION: ENGINE 0x1058FA40
	int fre_GetCategoryCurrentScoreLabel(lua_State* L)
	{
		FREventInfo* info = gFREventManager->GetInfoFromArguments(L);
		lua_pushstring(L, gCategoryCurrentScoreLabels[info->category]);
		return 1;
	}

	// FUNCTION: ENGINE 0x10590390
	bool ReadStringValue(lua_State* L, char* buffer, int size)
	{
		const char* text = lua_tolstring(L, -1, 0);
		bool found = true;
		if (text == 0)
		{
			found = false;
		}
		else
		{
			core::SNPrintfCount(buffer, size, "%s", text);
		}
		lua_settop(L, -2);
		return found;
	}

	// FUNCTION: ENGINE 0x10590400
	void GetStringField(lua_State* L, const char* key, char* buffer, int size)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		ReadStringValue(L, buffer, size);
	}

	// FUNCTION: ENGINE 0x10590440
	bool GetHandleValue(lua_State* L, engine::GameObjectHandle* handle)
	{
		if (handle != 0)
		{
			if (lua_gettop(L) != 0 && lua_type(L, -1) == 2)
			{
				engine::LuaGOH object;
				object.value = (unsigned int)lua_touserdata(L, -1);
				*handle = engine::DeserializeHandle(object);
				return true;
			}
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105904B0
	bool GetHandleField(lua_State* L, const char* key, engine::GameObjectHandle* handle)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		bool found = GetHandleValue(L, handle);
		lua_settop(L, -2);
		return found;
	}

	// FUNCTION: ENGINE 0x10590500
	bool IsTableField(lua_State* L, const char* key)
	{
		lua_pushstring(L, key);
		lua_rawget(L, -2);
		bool isTable = lua_type(L, -1) == 5;
		return isTable;
	}

	// FUNCTION: ENGINE 0x10590540
	void PopValue(lua_State* L)
	{
		lua_settop(L, -2);
	}

	// FUNCTION: ENGINE 0x1058F1D0
	int fre_PostEventMessage(lua_State* L)
	{
		core::Name<core::CaseSensitiveKey> first;
		core::Name<core::CaseSensitiveKey> third;
		if (lua_gettop(L) == 3)
		{
			engine::LuaGetNameArgument(L, 1, &first);
			int number = luaL_checkinteger(L, 2);
			engine::LuaGetNameArgument(L, 3, &third);
			core::Name<core::CaseSensitiveKey> second((const char*)0, 1);
			FreeRoamEventScenarioMessage message(number, first, second, third);
			engine::SendMessage(&message, &engine::gScenario12);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1058F2C0
	int fre_PostEventMessageLocal(lua_State* L)
	{
		core::Name<core::CaseSensitiveKey> first;
		core::Name<core::CaseSensitiveKey> third;
		if (lua_gettop(L) == 3)
		{
			engine::LuaGetNameArgument(L, 1, &first);
			int number = luaL_checkinteger(L, 2);
			engine::LuaGetNameArgument(L, 3, &third);
			FREventManager* manager = gFREventManager;
			FREvent* event = manager->FindEvent(first);
			if (event != 0)
			{
				event->PostMessage(number, third, 0);
			}
		}
		return 0;
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D607F0
// FUNCTION: ENGINE 0x10D85790
