#include "code/proto/behaviours/disguisebehaviour.h"
#include "code/engine/driving/carattributes.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/scenariomessages.h"
#include <float.h>
#include <new>

namespace engine
{
	int GetControllingPlayer(GameObject* object);
	// 0x11265030: the scenario message listeners (charactertypenames.cpp)
	extern MessageListeners gScenario63;
}

namespace proto
{
	// 0x103BE3E0: the faction attribute of an object (name guess)
	Faction GetObjectFaction(engine::GameObject* object);

	// 0x11087D44: a float of the engine's data (0.5f; name guess)
	extern float gUnknown11087D44;

	// FUNCTION: ENGINE 0x103CA100
	int DisguiseBehaviour::IsSeenState()
	{
		if (state != 6 && state != 7 && state != 9 && state != 0x14)
		{
			return 0;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x103CA130
	bool DisguiseBehaviour::IsNoState()
	{
		return state == 0;
	}

	// FUNCTION: ENGINE 0x103CA140
	int DisguiseBehaviour::IsHudAlert()
	{
		if (hudState != 4 && hudState != 3)
		{
			return 0;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x103CA280
	// NONMATCHING: the engine loads the limit constant before clearing the zero register (93.9 %)
#ifdef NONMATCHING
	void DisguiseBehaviour::ResetPairs(bool keepValues, bool skipSecond)
	{
		for (int i = 0; i < 16; i++)
		{
			if (i != 1 || !skipSecond || !(gUnknown11087D44 > unknown98))
			{
				if (!keepValues)
				{
					pairs[i].value = 0.0f;
				}
				pairs[i].limit = 100.0f;
			}
		}
		unknown318 = 0.0f;
		unknown31C = 0.0f;
		unknown320 = -1.0f;
	}
#endif

	// FUNCTION: ENGINE 0x103CA6F0
	void DisguiseBehaviour::OnDBSlot0(int a, int b)
	{
		const ChangedValue* change = (const ChangedValue*)b;
		unsigned int player = change->player;
		if (player == engine::GetControllingPlayer(owner) && unknown364 != change->value)
		{
			unknown364 = change->value;
		}
	}

	// FUNCTION: ENGINE 0x103CA740
	void DisguiseBehaviour::OnDBSlot1(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x103CA410
	void DisguiseBehaviour::CountA(bool increase)
	{
		if (increase)
		{
			unknownA8++;
			return;
		}
		unknownA8--;
		if (unknownA8 < 0)
		{
			unknownA8 = 0;
		}
	}

	// FUNCTION: ENGINE 0x103CA440
	void DisguiseBehaviour::CountB(bool increase)
	{
		if (increase)
		{
			unknownAC++;
			return;
		}
		unknownAC--;
		if (unknownAC < 0)
		{
			unknownAC = 0;
		}
	}

	// FUNCTION: ENGINE 0x103CA670
	void DisguiseBehaviour::CountC(bool increase)
	{
		if (increase)
		{
			unknown2BC++;
			return;
		}
		unknown2BC--;
		if (unknown2BC < 0)
		{
			unknown2BC = 0;
		}
	}

	// FUNCTION: ENGINE 0x103CA6A0
	void DisguiseBehaviour::CountD(bool increase)
	{
		if (increase)
		{
			unknown2C0++;
			return;
		}
		unknown2C0--;
		if (unknown2C0 < 0)
		{
			unknown2C0 = 0;
		}
	}

	// FUNCTION: ENGINE 0x103CAE00
	float DisguiseBehaviour::GetSuspicionDecrease(const core::Name<core::CaseSensitiveKey>& disguiseType)
	{
		DisguiseConfig* current = config;
		if (current == 0)
		{
			return 0.0f;
		}
		DisguiseConfig::SuspicionDecrease* it = current->suspicionDecreases.Begin();
		DisguiseConfig::SuspicionDecrease* last = current->suspicionDecreases.End();
		float result = 0.0f;
		if (it != last)
		{
			do
			{
				if (it->disguiseType.name == disguiseType)
				{
					result = it->suspicion;
					break;
				}
				it++;
			}
			while (it != last);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x103CAE80
	// NONMATCHING: the engine stores the called getter's result in the result slot and reloads it at the joined exit (65 %)
#ifdef NONMATCHING
	float DisguiseBehaviour::GetAlertDecrease(const core::Name<core::CaseSensitiveKey>& disguiseType)
	{
		DisguiseConfig* current = config;
		if (current == 0)
		{
			return 0.0f;
		}
		DisguiseConfig::AlertDecrease* it = current->alertDecreases.Begin();
		DisguiseConfig::AlertDecrease* last = current->alertDecreases.End();
		float result = 0.0f;
		if (it != last)
		{
			do
			{
				if (it->disguiseType.name == disguiseType)
				{
					double value = it->GetAlert(0);
					result = (float)value;
					break;
				}
				it++;
			}
			while (it != last);
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x103CAF10
	float DisguiseBehaviour::GetSuspicionIncrease(const core::Name<core::CaseSensitiveKey>& disguiseType,
		const core::Name<core::CaseSensitiveKey>& enemyType)
	{
		DisguiseConfig* current = config;
		if (current == 0)
		{
			return 0.0f;
		}
		DisguiseConfig::SuspicionIncrease* it = current->suspicionIncreases.Begin();
		DisguiseConfig::SuspicionIncrease* last = current->suspicionIncreases.End();
		float result = 0.0f;
		if (it != last)
		{
			do
			{
				if (it->disguiseType.name == disguiseType && it->enemyType.name == enemyType)
				{
					result = it->suspicionLow;
					break;
				}
				it++;
			}
			while (it != last);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x103CAFB0
	// NONMATCHING: the engine stores the called getter's result in the result slot and reloads it at the joined exit (65 %)
#ifdef NONMATCHING
	float DisguiseBehaviour::GetAlertIncrease(const core::Name<core::CaseSensitiveKey>& disguiseType,
		const core::Name<core::CaseSensitiveKey>& enemyType)
	{
		DisguiseConfig* current = config;
		if (current == 0)
		{
			return 0.0f;
		}
		DisguiseConfig::AlertIncrease* it = current->alertIncreases.Begin();
		DisguiseConfig::AlertIncrease* last = current->alertIncreases.End();
		float result = 0.0f;
		if (it != last)
		{
			do
			{
				if (it->disguiseType.name == disguiseType && it->enemyType.name == enemyType)
				{
					double value = it->GetAlert(0);
					result = (float)value;
					break;
				}
				it++;
			}
			while (it != last);
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x103CB0D0
	// NONMATCHING: the engine reloads the delta time before the zero after the message is sent (95.9 %)
#ifdef NONMATCHING
	void DisguiseBehaviour::UpdateWatchers(float dt)
	{
		for (Watcher* it = watchers.Begin(); it != watchers.End(); it++)
		{
			if (0.0f < it->hold)
			{
				it->hold = it->hold - dt;
				if (it->hold < 0.0f || (unknown2BC == 0 && unknown2C0 == 0))
				{
					it->hold = 0.0f;
				}
			}
			if (0.0f < it->suspicion && it->suspicion < 1000.0f)
			{
				it->suspicion = it->suspicion - dt;
				if (it->suspicion < 0.0f)
				{
					it->suspicion = 0.0f;
					it->hold = 0.0f;
					DisguiseUnblownScenarioMsg message(engine::GetHandle(owner));
					engine::SendMessage(&message, &engine::gScenario63);
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x103CB1F0
	DisguiseBehaviour::Watcher* DisguiseBehaviour::FindWatcher(const core::Name<core::CaseSensitiveKey>& factionName)
	{
		Watcher* it = watchers.Begin();
		Watcher* last = watchers.End();
		while (true)
		{
			if (it == last)
			{
				return last;
			}
			if (it->faction.name == factionName)
			{
				break;
			}
			it++;
		}
		return it;
	}

	// FUNCTION: ENGINE 0x103CB240
	void DisguiseBehaviour::ClearExpiredWatchers()
	{
		Watcher* it = watchers.Begin();
		Watcher* last = watchers.End();
		for (; it != last; it++)
		{
			if (it->suspicion < 1000.0f)
			{
				it->suspicion = 0.0f;
			}
		}
	}

	// FUNCTION: ENGINE 0x103CCBE0
	// NONMATCHING: the order of the first stores and the constant loads differ (54 %)
#ifdef NONMATCHING
	void DisguiseBehaviour::ResetState()
	{
		unknown2CC = engine::driving::gOne;
		unknown78 = 0.0f;
		unknown2DC = 0.0f;
		unknownA0 = 0.0f;
		unknownA4 = 0.0f;
		unknown2E4 = 0.0f;
		unknown8C = 0.0f;
		unknown94 = 0.0f;
		unknown9C = 0.0f;
		state = 0;
		unknown2D8 = 0;
		unknown70 = false;
		unknown71 = false;
		unknown72 = false;
		unknown75 = false;
		unknown2D4 = 0;
		unknownA8 = 0;
		unknownAC = 0;
		unknown85 = false;
		unknown90 = 999999995904.0f;
		unknown98 = 999999995904.0f;
		unknown84 = false;
		unknown73 = false;
		unknown2BC = 0;
		unknown2C0 = 0;
		unknown86 = false;
		unknown34C.serial = 0;
		unknown34C.index = 0xffff;
		unknown350.index = 0xffff;
		unknown350.serial = 0;
		unknown2C4 = false;
		unknown2C5 = false;
		unknown2C6 = false;
		unknown2C7 = false;
		unknown2F0 = false;
		unknown2B8 = false;
		unknown2B9 = false;
		listB0.Clear();
		list1B4.Clear();
		unknown2FC = 0.0f;
		hudState = -1;
		unknown30C = -FLT_MAX;
		unknown308 = -FLT_MAX;
		faction.name = core::Name<core::CaseSensitiveKey>("NoFaction", 1);
		unknown310 = false;
		unknown314 = 0;
		unknown348 = -1.0f;
		ResetPairs(false, false);
	}
#endif

	// FUNCTION: ENGINE 0x103CF9B0
	DisguiseBehaviour::DisguiseBehaviour(engine::GameObject* newOwner) : engine::FightTreeBehaviour(newOwner, 0),
		unknown74(false), unknown76(0), unknown7C(1.0f), unknown80(1.0f), unknown88(50.0f), unknown2C8(50.0f),
		unknown2D0(6.0f), unknown2DC(0.0f), unknown2E0(-1.0f), unknown2E8(0.0f), unknown2EC(200.0f), config(0),
		watchers(10), unknown33C(20.0f), unknown344(50.0f), unknown340(false), unknown348(-1.0f), unknown354(-1.0f),
		unknown358(20.0f), unknown35C(0.0f), unknown360(0.0f), unknown364(0), unknown368(0), unknown36C(0),
		unknown370(0), unknown374(1), unknown378(9), watch(0)
	{
		unknown324 = 0;
		core::Name<core::CaseSensitiveKey>* contextName = (core::Name<core::CaseSensitiveKey>*)GetSequencer();
		contextName->SetText("Alert");
		ResetState();
		Listen(0x2a, true);
		Listen(0x2f, true);
		Listen(0x1e, true);
		Listen(2, true);
		Listen(0x39, true);
		Listen(0xb, true);
	}

	// FUNCTION: ENGINE 0x103CD250
	// NONMATCHING: the engine keeps the watcher in edi from the call on, ours splits the live range (21 %)
#ifdef NONMATCHING
	DisguiseBehaviour::Watcher* DisguiseBehaviour::FindOrAddWatcher(const core::Name<core::CaseSensitiveKey>& factionName)
	{
		Watcher* watcher = FindWatcher(factionName);
		if (watcher == watchers.End())
		{
			if (watchers.Size() < watchers.Capacity())
			{
				watcher = watchers.Grow();
				if (watcher != 0)
				{
					new (watcher) Watcher();
				}
				watcher->faction.name = factionName;
			}
		}
		return watcher;
	}
#endif

	// FUNCTION: ENGINE 0x103CD300
	void DisguiseBehaviour::SetBlown(const core::Name<core::CaseSensitiveKey>& factionName, bool blown)
	{
		Watcher* watcher = FindOrAddWatcher(factionName);
		if (watcher != watchers.End())
		{
			if (blown)
			{
				if (watcher->suspicion < 0.00001f && choreo::gZero < unknown33C)
				{
					DisguiseBlownScenarioMsg message(engine::GetHandle(owner));
					engine::SendMessage(&message, &engine::gScenario63);
				}
				if (watcher->suspicion < unknown33C)
				{
					watcher->suspicion = unknown33C;
				}
			}
			else
			{
				watcher->hold = 0.0f;
				watcher->suspicion = 0.0f;
			}
		}
	}

	// FUNCTION: ENGINE 0x103CD3E0
	void DisguiseBehaviour::SetWatcherSuspicion(const core::Name<core::CaseSensitiveKey>& factionName, float suspicion)
	{
		Watcher* watcher = FindOrAddWatcher(factionName);
		if (watcher != watchers.End())
		{
			watcher->suspicion = suspicion;
		}
	}

	// FUNCTION: ENGINE 0x103CD410
	void DisguiseBehaviour::HoldOwnFaction()
	{
		Faction ownFaction = GetObjectFaction(owner);
		Watcher* watcher = FindOrAddWatcher(ownFaction.name);
		if (watcher != watchers.End())
		{
			watcher->hold = unknown33C;
		}
	}
}
