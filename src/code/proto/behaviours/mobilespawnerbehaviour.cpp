#include "code/proto/behaviours/encounterspawnerbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gEncounter4;
}

namespace proto
{
	// FUNCTION: ENGINE 0x10559900
	content::ClassInfo* MobileSpawnerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MobileSpawnerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10559AC0
	// NONMATCHING: the bytes are identical, but the call of the slot 12 override (a jump to an incremental link thunk) leads through three thunks and the check follows two (97.6 %)
#ifdef NONMATCHING
	MobileSpawnerBehaviour::MobileSpawnerBehaviour(engine::GameObject* newOwner) : EncounterSpawnerBehaviour(newOwner)
	{
		unknown480 = 0;
		Slot12();
	}
#endif

	// FUNCTION: ENGINE 0x10559940
	MobileSpawnerBehaviour::~MobileSpawnerBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10559950
	void MobileSpawnerBehaviour::Slot1()
	{
		Listen2(4, true);
		Remove(0x1e);
		engine::GameObject* object = owner;
		engine::GetHandle(object).RouterRemove(*static_cast<const engine::MessageListeners*>(&engine::gEncounter4));
	}

	// FUNCTION: ENGINE 0x105599A0
	void MobileSpawnerBehaviour::Update(float dt, unsigned short mask)
	{
		SpawnerBehaviour::Update(dt, mask);
		if (!readyToSpawn)
		{
			if (PruneSpawned() < (int)min)
			{
				readyToSpawn = true;
			}
		}
	}

	// FUNCTION: ENGINE 0x10559A90
	void MobileSpawnerBehaviour::Slot12()
	{
		EncounterSpawnerBehaviour::Slot12();
	}

	// FUNCTION: ENGINE 0x10559AA0
	void MobileSpawnerBehaviour::Slot9()
	{
		EncounterSpawnerBehaviour::Slot9();
	}

	// FUNCTION: ENGINE 0x10559AB0
	void MobileSpawnerBehaviour::Slot10()
	{
		EncounterSpawnerBehaviour::Slot10();
	}

	// FUNCTION: ENGINE 0x10559C40
	content::MemberList* MobileSpawnerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<EncounterSpawnerBehaviour>();
		static content::BaseClassCasterImpl<EncounterSpawnerBehaviour, MobileSpawnerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10559B00
// FUNCTION: ENGINE 0x10559B10
// FUNCTION: ENGINE 0x10559B40
