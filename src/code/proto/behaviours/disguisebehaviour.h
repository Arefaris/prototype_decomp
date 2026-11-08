// proto::DisguiseBehaviour (RTTI and reflection names; bases engine::FightTreeBehaviour and engine::DBObserver): the
// alert state of an object that can be disguised or noticed: how far the people around it suspect it, the alert and
// the hud state that follow, the factions it counts as and the objects that watch it. It runs the "Alert" fight tree.
// Unit 0x103C9D50 - 0x103D0C79 (no assert path; the file name is a guess). The reflected names are original, the rest
// is guessed.
#ifndef PROTO_BEHAVIOURS_DISGUISEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_DISGUISEBEHAVIOUR_H

#include "code/container/arraycdynamic.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/dbobserver.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/behaviours/fighttreebehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/proto/disguiseconfig.h"
#include "code/proto/faction.h"

namespace proto
{
	
	class DisguiseBehaviour : public engine::FightTreeBehaviour, public engine::DBObserver
	{
	public:
		// How long an object of a faction is noticed and held (0x10 bytes)
		struct Watcher
		{
			Watcher() : suspicion(0.0f), hold(0.0f)
			{
			}

			Faction faction;
			float suspicion;  // +8
			float hold;  // +0xC
		};

		// What the observed database value tells (the player it belongs to and the value)
		struct ChangedValue
		{
			int unknown0;
			unsigned char player;  // +4
			int value;  // +8
		};

		// 0x103CF9B0
		explicit DisguiseBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// DBObserver slots 0 (0x103CA6F0) and 1 (0x103CA740)
		virtual void OnDBSlot0(int a, int b);
		virtual void OnDBSlot1(int a, int b);

		// 0x103CA100: the states the object counts as seen in
		int IsSeenState();
		// 0x103CA130
		bool IsNoState();
		// 0x103CA140: the hud shows the alert
		int IsHudAlert();
		// 0x103CA410 / 0x103CA440: counts of the things that hold the two watch lists
		void CountA(bool increase);
		void CountB(bool increase);
		// 0x103CA670 / 0x103CA6A0
		void CountC(bool increase);
		void CountD(bool increase);
		// 0x103CAE00 / 0x103CAE80: how much suspicion / alert the configuration takes away for the faction (0 without a
		// configuration)
		float GetSuspicionDecrease(const core::Name<core::CaseSensitiveKey>& disguiseType);
		float GetAlertDecrease(const core::Name<core::CaseSensitiveKey>& disguiseType);
		// 0x103CAF10 / 0x103CAFB0: how much suspicion / alert the configuration raises for the faction pair
		float GetSuspicionIncrease(const core::Name<core::CaseSensitiveKey>& disguiseType,
			const core::Name<core::CaseSensitiveKey>& enemyType);
		float GetAlertIncrease(const core::Name<core::CaseSensitiveKey>& disguiseType,
			const core::Name<core::CaseSensitiveKey>& enemyType);
		// 0x103CB0D0: lets the held and the noticed times of the watchers run out
		void UpdateWatchers(float dt);
		// 0x103CB1F0: the watcher of the faction, or the end of the list
		Watcher* FindWatcher(const core::Name<core::CaseSensitiveKey>& faction);
		// 0x103CD250: the watcher of the faction, made when there is room for one
		Watcher* FindOrAddWatcher(const core::Name<core::CaseSensitiveKey>& faction);
		// 0x103CD300: the faction notices the object (or, without the flag, forgets it)
		void SetBlown(const core::Name<core::CaseSensitiveKey>& faction, bool blown);
		// 0x103CD3E0
		void SetWatcherSuspicion(const core::Name<core::CaseSensitiveKey>& faction, float suspicion);
		// 0x103CD410: holds the suspicion of the faction the object is in
		void HoldOwnFaction();
		// 0x103CCDD0 / 0x103CCE30: puts a value into / takes it out of the list at +0x418
		void AddListed(int value);
		void RemoveListed(int value);
		// 0x103CD0D0: whether the faction of the owner notices the object, for how long and up to what, and whether it
		// holds the suspicion
		bool IsNoticed(float* time, float* limit, bool* held);
		// 0x103CD1B0: whether the faction of the owner holds the suspicion, and for how long
		bool IsHeld(float* time);
		// 0x103CB240: forgets the held suspicion of the watchers that ran out
		void ClearExpiredWatchers();
		// 0x103CCBE0: puts the behaviour back to its beginning
		void ResetState();
		// 0x103CA280: starts the sixteen pairs again (the values are kept when the first flag is set)
		void ResetPairs(bool keepValues, bool skipSecond);

		// +0x68 is the DBObserver
		int state;  // +0x6C
		bool unknown70;
		bool unknown71;
		bool unknown72;
		bool unknown73;
		bool unknown74;
		bool unknown75;
		unsigned char unknown76;
		float unknown78;
		float unknown7C;
		float unknown80;
		bool unknown84;
		bool unknown85;
		bool unknown86;
		float unknown88;
		float unknown8C;
		float unknown90;
		float unknown94;
		float unknown98;
		float unknown9C;
		float unknownA0;
		float unknownA4;
		int unknownA8;
		int unknownAC;
		container::ArrayCDynamic<int, 64> listB0;  // +0xB0
		container::ArrayCDynamic<int, 64> list1B4;  // +0x1B4
		bool unknown2B8;
		bool unknown2B9;
		int unknown2BC;
		int unknown2C0;
		bool unknown2C4;
		bool unknown2C5;
		bool unknown2C6;
		bool unknown2C7;
		float unknown2C8;
		float unknown2CC;
		float unknown2D0;
		int unknown2D4;
		unsigned int unknown2D8;
		float unknown2DC;
		float unknown2E0;
		float unknown2E4;
		float unknown2E8;
		float unknown2EC;
		bool unknown2F0;
		DisguiseConfig* config;  // +0x2F4
		int hudState;  // +0x2F8
		float unknown2FC;
		Faction faction;  // +0x300
		float unknown308;
		float unknown30C;
		bool unknown310;
		int unknown314;
		float unknown318;
		float unknown31C;
		float unknown320;
		int unknown324;
		engine::HandleBase unknown328;
		container::ArrayDynamic<Watcher, container::AllocatorNew> watchers;  // +0x32C
		int unknown338;
		float unknown33C;
		bool unknown340;
		float unknown344;
		float unknown348;
		engine::HandleBase unknown34C;
		engine::HandleBase unknown350;
		float unknown354;
		float unknown358;
		float unknown35C;
		float unknown360;
		int unknown364;
		int unknown368;
		int unknown36C;
		int unknown370;
		int unknown374;
		int unknown378;
		struct Pair
		{
			float value;
			float limit;
		};
		Pair pairs[16];  // +0x37C
		float unknown3FC;
		float unknown400;
		float unknown404;
		float unknown408;
		fight::BranchWatch watch;  // +0x40C
		container::ArrayCDynamic<int, 80> list418;  // +0x418
		int unknown55C;
	};
}

#endif
