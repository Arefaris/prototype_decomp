#include "code/proto/behaviours/encounterspawnerbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/luascriptmanager.h"

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gEncounter3;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10556C40
	content::ClassInfo* EncounterSpawnerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::EncounterSpawnerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105593D0
	EncounterSpawnerBehaviour::EncounterSpawnerBehaviour(engine::GameObject* newOwner) : SpawnerBehaviour(newOwner),
		min(0), max(0), total(0), delay(0.0f), locatorExpiry(0.0f), ignoreCameraCheckDistance(0.0f), unknown290(false),
		ignoreCamera(false), unknown292(false), unknown470(false), readyToSpawn(false), allZeroHealthSent(false),
		finishedSent(false), unknown474(0), unknown478(0.0f)
	{
		Slot12();
		Listen(0xd, true);
		Listen2(4, false);
		unknown293 = false;
	}

	// FUNCTION: ENGINE 0x105594D0
	EncounterSpawnerBehaviour::~EncounterSpawnerBehaviour()
	{
		engine::GetScriptManager();
	}

	// FUNCTION: ENGINE 0x10556C80
	void EncounterSpawnerBehaviour::Slot1()
	{
		Remove(0x1e);
		engine::GetHandle(owner).RouterRemove(*static_cast<const engine::MessageListeners*>(&engine::gEncounter3));
	}

	// FUNCTION: ENGINE 0x10558920
	void EncounterSpawnerBehaviour::Slot11()
	{
		SpawnerBehaviour::Slot11();
	}

	// FUNCTION: ENGINE 0x105577E0
	content::MemberList* EncounterSpawnerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<SpawnerBehaviour>();
		static content::BaseClassCasterImpl<SpawnerBehaviour, EncounterSpawnerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<EncounterSpawnerBehaviour, unsigned int, 0>("pn"),
				PROTO_OFFSET(EncounterSpawnerBehaviour, min), "min" },
			{ content::GetMemberPrimitiveMetaType<EncounterSpawnerBehaviour, unsigned int, 1>("pn"),
				PROTO_OFFSET(EncounterSpawnerBehaviour, max), "max" },
			{ content::GetMemberPrimitiveMetaType<EncounterSpawnerBehaviour, unsigned int, 2>("pn"),
				PROTO_OFFSET(EncounterSpawnerBehaviour, total), "total" },
			{ content::GetMemberPrimitiveMetaType<EncounterSpawnerBehaviour, float, 0>("pn"),
				PROTO_OFFSET(EncounterSpawnerBehaviour, delay), "delay" },
			{ content::GetMemberPrimitiveMetaType<EncounterSpawnerBehaviour, float, 1>("pn"),
				PROTO_OFFSET(EncounterSpawnerBehaviour, locatorExpiry), "locatorExpiry" },
			{ content::GetMemberPrimitiveMetaType<EncounterSpawnerBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(EncounterSpawnerBehaviour, ignoreCamera), "ignoreCamera" },
			{ content::GetMemberPrimitiveMetaType<EncounterSpawnerBehaviour, float, 2>("pn"),
				PROTO_OFFSET(EncounterSpawnerBehaviour, ignoreCameraCheckDistance), "ignoreCameraCheckDistance" },
			{ content::GetMemberPrimitiveMetaType<EncounterSpawnerBehaviour, bool, 1>("pn"),
				PROTO_OFFSET(EncounterSpawnerBehaviour, readyToSpawn), "readyToSpawn" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}
}

template class container::ArrayFixed<engine::GameObjectHandle, 30>;
template class container::ArrayFixed<proto::SpawnedEntry, 30>;
template class container::ArrayFixed<core::Name<core::CaseSensitiveKey>, 5>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10556E50
// FUNCTION: ENGINE 0x10556E80
// FUNCTION: ENGINE 0x10556EA0
// FUNCTION: ENGINE 0x10556EB0
// FUNCTION: ENGINE 0x10556EC0
// FUNCTION: ENGINE 0x10556F10
// FUNCTION: ENGINE 0x10557030
// FUNCTION: ENGINE 0x10557040
// FUNCTION: ENGINE 0x10557390
// FUNCTION: ENGINE 0x105573D0
// FUNCTION: ENGINE 0x105573F0
// FUNCTION: ENGINE 0x10557440
// FUNCTION: ENGINE 0x10557490
// FUNCTION: ENGINE 0x105574D0
// FUNCTION: ENGINE 0x10557500
// FUNCTION: ENGINE 0x10557540
// FUNCTION: ENGINE 0x10557580
// FUNCTION: ENGINE 0x105575D0
// FUNCTION: ENGINE 0x10557610
// FUNCTION: ENGINE 0x10557650
// FUNCTION: ENGINE 0x10557690
// FUNCTION: ENGINE 0x105576D0
// FUNCTION: ENGINE 0x10557710
// FUNCTION: ENGINE 0x10557750
// FUNCTION: ENGINE 0x10557790
// FUNCTION: ENGINE 0x10558A20
// FUNCTION: ENGINE 0x10558F50
// FUNCTION: ENGINE 0x10559550
