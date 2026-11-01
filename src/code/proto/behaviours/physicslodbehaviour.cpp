#include "code/proto/behaviours/physicslodbehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/messages/physicsmessages.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// The message that asks for the table of levels (id 0x20; no RTTI name): the table's address comes back
	struct GetPhysicsLODTableMessage : public PhysicsMessage
	{
		GetPhysicsLODTableMessage() : PhysicsMessage(0x20)
		{
		}

		PhysicsLODBehaviour::LodArray* table;  // +0xC
	};

	// FUNCTION: ENGINE 0x102F1B50
	PhysicsLOD::PhysicsLOD() : physicsObject(0)
	{
	}

	// FUNCTION: ENGINE 0x102F1B80
	PhysicsLOD::~PhysicsLOD()
	{
		core::SafeRelease(physicsObject);
	}

	// FUNCTION: ENGINE 0x102F1AA0
	content::ClassInfo* PhysicsLOD::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PhysicsLOD";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F1C70
	content::MemberList* PhysicsLOD::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<PhysicsLOD>(true, true, "p"), PROTO_NAME_OFFSET(PhysicsLOD, name), "name" },
			{ content::GetReferenceMetaType<PhysicsLOD, ravenphysics::AbstractPhysicsObjectFactory>("p"),
				PROTO_OFFSET(PhysicsLOD, physicsObject), "physicsObject" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102F35E0
	// EQUIVALENT: scheduling; the engine stores the two object handles before it pushes the first Listen argument, ours after it (82 %)
	PhysicsLODBehaviour::PhysicsLODBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), currentLOD(-1)
	{
		physicsObject.value = 0xffffffff;
		savedPhysicsObject.value = 0xffffffff;
		saveInitialPhysicsObject = false;
		isNotAmbientVehicle = false;
		Listen(3, true);
		Listen(2, true);
	}

	// FUNCTION: ENGINE 0x102F2500
	content::ClassInfo* PhysicsLODBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PhysicsLODBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102F3660
	// NONMATCHING: the engine empties the table with the array's out-of-line Clear and frees its block; the array's destructor here destroys the elements inline (22 %)
#ifdef NONMATCHING
	PhysicsLODBehaviour::~PhysicsLODBehaviour()
	{
		if (physicsObject.IsValid())
		{
			physicsObject.DestroyObject();
		}
		if (savedPhysicsObject.IsValid())
		{
			savedPhysicsObject.DestroyObject();
		}
	}
#endif

	// FUNCTION: ENGINE 0x102F33D0
	void PhysicsLODBehaviour::Slot1()
	{
		if (!initial.IsEmpty())
		{
			SetPhysicsLODMessage message(&initial);
			SwitchLOD(&message);
			if (saveInitialPhysicsObject)
			{
				savedPhysicsObject = physicsObject;
			}
		}
	}

	// FUNCTION: ENGINE 0x102F3440
	void PhysicsLODBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			SwitchToInitial();
			break;
		case 3:
			if (message->id == 0x1f)
			{
				GetCurrentLOD((GetPhysicsLODMessage*)message);
			}
			if (message->id == 0x20)
			{
				GetTable((GetPhysicsLODTableMessage*)message);
				return;
			}
			if (message->id == 0x22)
			{
				SwitchLOD((SetPhysicsLODMessage*)message);
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x102F2F80
	void PhysicsLODBehaviour::SwitchToInitial()
	{
		if (!initial.IsEmpty())
		{
			SetPhysicsLODMessage message(&initial);
			SwitchLOD(&message);
		}
	}

	// FUNCTION: ENGINE 0x102F2820
	void PhysicsLODBehaviour::GetCurrentLOD(GetPhysicsLODMessage* message)
	{
		message->lod = currentName;
	}

	// FUNCTION: ENGINE 0x102F2540
	void PhysicsLODBehaviour::GetTable(GetPhysicsLODTableMessage* message)
	{
		message->table = &physicsLODTable;
	}

	// FUNCTION: ENGINE 0x102F3250
	content::MemberList* PhysicsLODBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, PhysicsLODBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<PhysicsLODBehaviour, LodArray>(content::GetClassMetaType<PhysicsLOD>(), "p"),
				PROTO_OFFSET(PhysicsLODBehaviour, physicsLODTable), "physicsLODTable" },
			{ content::GetNameMetaType<PhysicsLODBehaviour>(true, true, "p"),
				PROTO_NAME_OFFSET(PhysicsLODBehaviour, initial), "initial" },
			{ content::GetMemberPrimitiveMetaType<PhysicsLODBehaviour, bool, 0>("p"),
				PROTO_OFFSET(PhysicsLODBehaviour, saveInitialPhysicsObject), "saveInitialPhysicsObject" },
			{ content::GetMemberPrimitiveMetaType<PhysicsLODBehaviour, bool, 1>("p"),
				PROTO_OFFSET(PhysicsLODBehaviour, isNotAmbientVehicle), "isNotAmbientVehicle" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102F1AE0
// FUNCTION: ENGINE 0x102F1B20
// FUNCTION: ENGINE 0x102F1B30
// FUNCTION: ENGINE 0x102F1BA0
// FUNCTION: ENGINE 0x102F1BB0
// FUNCTION: ENGINE 0x102F1BE0
// FUNCTION: ENGINE 0x102F1C10
// FUNCTION: ENGINE 0x102F23C0
// FUNCTION: ENGINE 0x102F23D0
// FUNCTION: ENGINE 0x102F2400
// FUNCTION: ENGINE 0x102F2410
// FUNCTION: ENGINE 0x102F2550
// FUNCTION: ENGINE 0x102F2590
// FUNCTION: ENGINE 0x102F2680
// FUNCTION: ENGINE 0x102F2690
// FUNCTION: ENGINE 0x102F26D0
// FUNCTION: ENGINE 0x102F2710
// FUNCTION: ENGINE 0x102F2740
// FUNCTION: ENGINE 0x102F2770
// FUNCTION: ENGINE 0x102F2780
// FUNCTION: ENGINE 0x102F2840
// FUNCTION: ENGINE 0x102F2850
// FUNCTION: ENGINE 0x102F2890
// FUNCTION: ENGINE 0x102F28D0
// FUNCTION: ENGINE 0x102F2900
// FUNCTION: ENGINE 0x102F2910
// FUNCTION: ENGINE 0x102F2940
// FUNCTION: ENGINE 0x102F2960
// FUNCTION: ENGINE 0x102F29C0
// FUNCTION: ENGINE 0x102F2A70
// FUNCTION: ENGINE 0x102F2A90
// FUNCTION: ENGINE 0x102F3020
// FUNCTION: ENGINE 0x102F31A0
// FUNCTION: ENGINE 0x102F34D0
// FUNCTION: ENGINE 0x102F3520
// FUNCTION: ENGINE 0x102F3590
// FUNCTION: ENGINE 0x102F3750
// FUNCTION: ENGINE 0x102F3780

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102F2A10
// FUNCTION: ENGINE 0x102F2A40
// FUNCTION: ENGINE 0x102F2B60
// FUNCTION: ENGINE 0x102F2BA0
// FUNCTION: ENGINE 0x102F2BF0
// FUNCTION: ENGINE 0x102F31E0
