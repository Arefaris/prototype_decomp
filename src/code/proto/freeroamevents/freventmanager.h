// proto::FREventManager (RTTI name; derives engine::DBObserver and has two virtual functions of its own), the free
// roam event system: the events the player finds in the open world (locomotion, kill, glide, war, opportunity and
// collectible events), their medals, the front end lists of them and the Lua natives (the `fre_` functions) that
// control them. The members here are the ones eventscripting.cpp (path from its asserts) uses; the manager's
// remaining members, the classes of the event and of its list record and every name except the manager's own and
// the Lua function names are guesses.
#ifndef PROTO_FREEROAMEVENTS_FREVENTMANAGER_H
#define PROTO_FREEROAMEVENTS_FREVENTMANAGER_H

#include "code/core/name.h"
#include "code/engine/dbobserver.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/vector.h"
#include "code/proto/freeroamevents/frobjects.h"

struct lua_State;

namespace proto
{
	// The object an event shows the player (a marker, a locator, a trigger volume; frobjects.h)
	typedef FREventObjectBase FREventObject;

	// One event (0x9D bytes at least): the list node (next at +4), the thresholds of the medals at +0x10, the name at
	// +0x28 and the flag at +0x9C that the unlock all call sets
	class FREvent
	{
	public:
		// 0x10584EC0: hands the event the game object that runs its state machine
		void SetStateMachine(engine::GameObjectHandle handle);
		// 0x10584FE0 / 0x10584FF0 / 0x10585030: the three ways the scripts drive an event from outside
		void Activate();
		void Deactivate(float time);
		void Complete(bool success, float time);
		// 0x10585A90: switches the object of the event that goes by name (the special names "_all" and
		// "_all_locators" switch every one)
		void ActivateObject(const char* name, bool active);
		// 0x105859D0: the object of the event with the name
		FREventObject* FindObject(const char* name);
		// 0x105862C0: the game object the event is attached to
		const engine::GameObjectHandle& GetHandle(engine::GameObjectHandle* result);

		unsigned char unknown0[4];
		FREvent* next;
		unsigned char unknown8[0x10 - 8];
		float medalThresholds[3];
		unsigned char unknown1C[0x28 - 0x1c];
		core::Name<core::CaseSensitiveKey> name;
		unsigned char unknown30[0x9c - 0x30];
		bool unlocked;
	};

	// The front end record of an event (next at +0, the name at +4, the category and the index in it): the strings
	// and numbers the event selection screens show
	class FREventInfo
	{
	public:
		// 0x10585CF0: one of the texts of the record ("%s_%s" of the name and a suffix, looked up in the game
		// database)
		const char* GetString(int index);
		// 0x10585C70 / 0x10585C90 / 0x10585CB0 / 0x10585CD0: the numbers stored per event name (the medal reached,
		// the best medal, the experience of the award, the experience earned)
		int GetAchievement();
		int GetLastMedal();
		int GetEPAward();
		int GetCurrentEPAward();
		// 0x10586800: the event can be chosen on the selection screen
		bool CanSelect();
		// 0x1058EE50: the name of the event as a key
		core::Name<core::CaseSensitiveKey> GetNameKey();

		FREventInfo* next;
		char name[8];
		int category;
		int index;
		int subType;
		core::Name<core::CaseSensitiveKey> nameKey;
	};

	// The pool of dynamic package slots the manager reserves for its events (0xA0 bytes at +0x40 of the manager)
	class PackageSlotPool
	{
	public:
		// 0x105910F0: the slots that are still free
		int GetNumFree();

		unsigned char unknown0[0xa0];
	};

	// A list of the collectibles of one kind that were picked up (24 bytes; two of them follow the slot pool)
	class CollectibleLog
	{
	public:
		// 0x1058D0D0: notes the collectible with the name
		void Add(const core::Name<core::CaseSensitiveKey>* name);

		unsigned char unknown0[0x18];
	};

	class FREventManager : public engine::DBObserver
	{
	public:
		virtual void OnDBSlot0(int a, int b);
		virtual void OnDBSlot1(int a, int b);

		// The Lua natives and helpers that run on the manager. A closure of the script context calls them with the
		// manager as this.
		void ActivateObject(const char* name);
		void DeactivateObject(const char* name);
		math::Vector GetObjectPosition(const char* name);
		void SetDebugString(const char* text);
		void SetDebugEventState(const char* name, const char* state);
		bool IsPlatinumEventsAvailable();
		void TriggerSave();
		int GetNumFreeDynamicPackageSlots();
		void UnlockAllEvents();
		void RemoveUnlockKey(const char* key);
		bool HasUnlockKeyBeenReceived(const char* key);
		int GetNumCategories();
		int GetCategoryEventAchievementByGOH(unsigned int high, unsigned int low);
		int GetEventAwardedEPByGOH(unsigned int high, unsigned int low);
		int GetEventTotalEPByGOH(unsigned int high, unsigned int low);
		int GetEventAchievement(engine::GameObjectHandle handle);
		bool GetCategoryEventCanSelectByGOH(unsigned int high, unsigned int low);
		void ShowEventEndPopup();
		float GetLuaFloat(const char* table, const char* key);
		int GetLuaInt(const char* table, const char* key);
		const char* GetLuaString(const char* table, const char* key);
		void AssociateStateMachine(const char* name, engine::LuaGOH handle);
		void SetFreeRoamState(bool active);
		void SetManagerActiveState(bool active);
		void ActivateEvent(const char* name);
		void DeactivateEvent(const char* name, float time);
		void CompleteEvent(const char* name, bool success, float time);
		float GetMedalThreshold(const char* name, int index);
		// 0x10587FC0: the Lua native fre_UpgradeMedalsToPlatinum's work
		int UpgradeMedalsToPlatinum(lua_State* L);

		bool IsFreeRoamActive();
		// 0x1058AE60 / 0x1058AEE0: leaves / enters the free roam mode
		void LeaveFreeRoam();
		void EnterFreeRoam();
		// 0x1058C1C0: the manager's active flag
		void SetActive(bool active);
		// 0x10588570: the event with the name, null when there is none
		FREvent* FindEvent(core::Name<core::CaseSensitiveKey> name);
		// 0x1058AE10: the same for a name as text (cut to seven characters, the length of the event names)
		FREvent* FindEventByText(const char* name);
		// 0x105885E0 / 0x105886B0: the record of the event that a saved / a live game object handle belongs to
		FREventInfo* FindInfoBySavedHandle(engine::SerializedHandle handle);
		FREventInfo* FindInfoByHandle(engine::GameObjectHandle handle);
		// 0x10587C80: the record of the event of a category with an index
		FREventInfo* FindInfo(int category, int index);
		// The lua arguments of a call select a record: (category, index) or the index into the list
		FREventInfo* GetInfoFromArguments(lua_State* L);

		unsigned char unknown4;
		bool unknown5;
		unsigned char unknown6[2];
		FREvent* events;
		FREventInfo* infos;
		unsigned char unknown10[0x18 - 0x10];
		FREvent* lastEvent;
		unsigned char unknown1C[0x3c - 0x1c];
		bool active;
		bool unlockedAll;
		unsigned char unknown3E[2];
		PackageSlotPool slotPool;
		CollectibleLog hintLog;  // +0xE0
		CollectibleLog locationLog;  // +0xF8
	};

	// The manager (0x11274F08)
	extern FREventManager* gFREventManager;
}

#endif
