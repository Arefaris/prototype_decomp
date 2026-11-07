#include "code/proto/behaviours/targetablebehaviour.h"
#include "code/proto/fightitems/ai/aihelpers.h"
#include <new>

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102B1280
	content::ClassInfo* PropTargetableByAIBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PropTargetableByAIBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}


	// FUNCTION: ENGINE 0x102B12C0
	PropTargetableByAIBehaviour::PropTargetableByAIBehaviour(engine::GameObject* newOwner)
		: TargetableBehaviour(newOwner)
	{
		registered = false;
		Listen(0x2b, true);
	}

	// FUNCTION: ENGINE 0x102B1300
	PropTargetableByAIBehaviour::~PropTargetableByAIBehaviour()
	{
		if (registered)
		{
			gAISystem->RemoveTargetable(owner);
		}
	}

	// FUNCTION: ENGINE 0x102B1330
	void PropTargetableByAIBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type != 0x2b)
		{
			TargetableBehaviour::OnMessage(message);
			return;
		}
		if (message->id == 0)
		{
			if (((RegisterAIMsg*)message)->registerObject)
			{
				gAISystem->AddTargetable(owner);
				registered = true;
			}
			else
			{
				gAISystem->RemoveTargetable(owner);
				registered = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x102B1470
	content::MemberList* PropTargetableByAIBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<TargetableBehaviour>();
		static content::BaseClassCasterImpl<TargetableBehaviour, PropTargetableByAIBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B14F0
	content::ClassInfo* TargetableBehaviour::TargetPoint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TargetableBehaviour::TargetPoint";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B1530
	content::ClassInfo* TargetableBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TargetableBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B1570
	bool TargetableBehaviour::TargetPoint::TestFilter(unsigned int filter) const
	{
		return (filters && filter ? 1 : 0) != 0;
	}

	// FUNCTION: ENGINE 0x102B15B0
	void TargetableBehaviour::TargetPoint::SetFilter(unsigned int filter, bool on)
	{
		if (on)
		{
			filters |= filter;
		}
		else
		{
			filters &= ~filter;
		}
	}

	// FUNCTION: ENGINE 0x102B15E0
	bool TargetableBehaviour::GetRootTargetFilterClear() const
	{
		return rootTargetFilter == 0;
	}

	// FUNCTION: ENGINE 0x102B15F0
	void TargetableBehaviour::SetRootTargetFilterClear(bool clear)
	{
		rootTargetFilter = clear ? 0 : -1;
	}

	// FUNCTION: ENGINE 0x102B1610
	// NONMATCHING: the engine keeps the new tail in a register across the loop (81.0 %)
#ifdef NONMATCHING
	bool TargetableBehaviour::AddTargeters(Targeter* targeter)
	{
		if (targeter == 0)
		{
			return false;
		}
		targeter->target = owner;
		if (lastTargeter == 0)
		{
			firstTargeter = targeter;
		}
		else
		{
			lastTargeter->next = targeter;
		}
		lastTargeter = targeter;
		if (targeter->next != 0)
		{
			do
			{
				lastTargeter->next->target = owner;
				lastTargeter = lastTargeter->next;
			}
			while (lastTargeter->next != 0);
		}
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x102B1680
	bool TargetableBehaviour::RemoveTargeter(Targeter* targeter)
	{
		if (targeter == 0)
		{
			return false;
		}
		targeter->target = 0;
		Targeter* previous = 0;
		for (Targeter* current = firstTargeter; current != 0; current = current->next)
		{
			if (current == targeter)
			{
				if (lastTargeter == current)
				{
					lastTargeter = previous;
				}
				Targeter* next = current->next;
				if (previous == 0)
				{
					firstTargeter = next;
				}
				else
				{
					previous->next = next;
				}
				targeter->next = 0;
				return true;
			}
			previous = current;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x102B16F0
	// NONMATCHING: register allocation of the loop, the engine takes the address of the next link first (25.7 %)
#ifdef NONMATCHING
	void TargetableBehaviour::ClearTargeters()
	{
		for (Targeter* targeter = firstTargeter; targeter != 0;)
		{
			Targeter* next = targeter->next;
			targeter->target = 0;
			targeter->next = 0;
			targeter = next;
		}
		lastTargeter = 0;
	}
#endif

	// FUNCTION: ENGINE 0x102B1980
	bool TargetableBehaviour::TargetPoint::GetTargetFilterLockOn() const
	{
		return TestFilter(1);
	}

	// FUNCTION: ENGINE 0x102B1990
	void TargetableBehaviour::TargetPoint::SetTargetFilterLockOn(bool on)
	{
		SetFilter(1, on);
	}

	// FUNCTION: ENGINE 0x102B19B0
	bool TargetableBehaviour::TargetPoint::GetTargetFilterAttackMelee() const
	{
		return TestFilter(2);
	}

	// FUNCTION: ENGINE 0x102B19C0
	void TargetableBehaviour::TargetPoint::SetTargetFilterAttackMelee(bool on)
	{
		SetFilter(2, on);
	}

	// FUNCTION: ENGINE 0x102B19E0
	bool TargetableBehaviour::TargetPoint::GetTargetFilterAttackRanged() const
	{
		return TestFilter(4);
	}

	// FUNCTION: ENGINE 0x102B19F0
	void TargetableBehaviour::TargetPoint::SetTargetFilterAttackRanged(bool on)
	{
		SetFilter(4, on);
	}

	// FUNCTION: ENGINE 0x102B1A10
	bool TargetableBehaviour::TargetPoint::GetTargetFilterGrab() const
	{
		return TestFilter(8);
	}

	// FUNCTION: ENGINE 0x102B1A20
	void TargetableBehaviour::TargetPoint::SetTargetFilterGrab(bool on)
	{
		SetFilter(8, on);
	}

	// FUNCTION: ENGINE 0x102B1A40
	bool TargetableBehaviour::TargetPoint::GetTargetFilterFeet() const
	{
		return TestFilter(0x10);
	}

	// FUNCTION: ENGINE 0x102B1A50
	void TargetableBehaviour::TargetPoint::SetTargetFilterFeet(bool on)
	{
		SetFilter(0x10, on);
	}

	// FUNCTION: ENGINE 0x102B1A70
	bool TargetableBehaviour::TargetPoint::GetTargetFilterAlertObject() const
	{
		return TestFilter(0x20);
	}

	// FUNCTION: ENGINE 0x102B1A80
	void TargetableBehaviour::TargetPoint::SetTargetFilterAlertObject(bool on)
	{
		SetFilter(0x20, on);
	}

	// FUNCTION: ENGINE 0x102B1AE0
	TargetableBehaviour::TargetPoint::TargetPoint() : jointIndex(0xffff)
	{
		offset.x = 0.0f;
		offset.y = 0.0f;
		offset.z = 0.0f;
		filters = 0;
	}

	// FUNCTION: ENGINE 0x102B1B20
	void TargetableBehaviour::OnActiveChanged(bool active)
	{
		engine::Behaviour::OnActiveChanged(active);
		if (!active)
		{
			ClearTargeters();
		}
	}

	// FUNCTION: ENGINE 0x102B1B50
	void TargetableBehaviour::ResetTargeters()
	{
		currentTargetClass = targetClass;
		ClearTargeters();
	}

	// FUNCTION: ENGINE 0x102B3760
	content::MemberList* TargetableBehaviour::TargetPoint::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<TargetPoint>(true, true, "p"), PROTO_OFFSET(TargetPoint, jointName),
				"jointName" },
			{ content::GetMemberVectorMetaType<TargetPoint, 0>("p"), 0x10, "offset" },
			{ content::GetMemberMetaType<TargetPoint, bool, 0>(&TargetPoint::GetTargetFilterLockOn,
				&TargetPoint::SetTargetFilterLockOn, "p"), 0, "targetFilterLockOn" },
			{ content::GetMemberMetaType<TargetPoint, bool, 1>(&TargetPoint::GetTargetFilterAttackMelee,
				&TargetPoint::SetTargetFilterAttackMelee, "p"), 0, "targetFilterAttackMelee" },
			{ content::GetMemberMetaType<TargetPoint, bool, 2>(&TargetPoint::GetTargetFilterAttackRanged,
				&TargetPoint::SetTargetFilterAttackRanged, "p"), 0, "targetFilterAttackRanged" },
			{ content::GetMemberMetaType<TargetPoint, bool, 3>(&TargetPoint::GetTargetFilterGrab,
				&TargetPoint::SetTargetFilterGrab, "p"), 0, "targetFilterGrab" },
			{ content::GetMemberMetaType<TargetPoint, bool, 4>(&TargetPoint::GetTargetFilterFeet,
				&TargetPoint::SetTargetFilterFeet, "p"), 0, "targetFilterFeet" },
			{ content::GetMemberMetaType<TargetPoint, bool, 5>(&TargetPoint::GetTargetFilterAlertObject,
				&TargetPoint::SetTargetFilterAlertObject, "p"), 0, "targetFilterAlertObject" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B3970
	void TargetableBehaviour::Slot1()
	{
		RebuildTargetPoints();
		ResetTargeters();
	}

	// FUNCTION: ENGINE 0x102B3CE0
	content::MemberList* TargetableBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TargetableBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<TargetableBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(TargetableBehaviour, isTargetable), "isTargetable" },
			{ content::GetMemberPrimitiveMetaType<TargetableBehaviour, bool, 1>("p"),
				PROTO_OFFSET(TargetableBehaviour, targetableEvenWhenAttached), "targetableEvenWhenAttached" },
			{ content::GetMemberPrimitiveMetaType<TargetableBehaviour, bool, 2>("p"),
				PROTO_OFFSET(TargetableBehaviour, targetableWhenAttachedToTargeter),
				"targetableWhenAttachedToTargeter" },
			{ content::GetMemberPrimitiveMetaType<TargetableBehaviour, bool, 3>("p"),
				PROTO_OFFSET(TargetableBehaviour, canCauseStrikeTeamCall), "canCauseStrikeTeamCall" },
			{ content::GetEnumMetaType<TargetClass>(), 0x10, "targetClass" },
			{ content::GetMemberPrimitiveMetaType<TargetableBehaviour, float, 0>("p"),
				PROTO_OFFSET(TargetableBehaviour, targetRadius), "targetRadius" },
			{ content::GetMemberPrimitiveMetaType<TargetableBehaviour, float, 1>("p"),
				PROTO_OFFSET(TargetableBehaviour, lineOfSightRadius), "lineOfSightRadius" },
			{ content::GetMemberMetaType<TargetableBehaviour, bool, 0>(&TargetableBehaviour::GetRootTargetFilterClear,
				&TargetableBehaviour::SetRootTargetFilterClear, "p"), 0, "rootTargetFilterClear" },
			{ content::GetMemberVectorMetaType<TargetableBehaviour, 0>("p"), 0x24, "rootTargetOffset" },
			{ content::GetArrayDynamicMetaType<TargetableBehaviour, TargetPointArray>(
				content::GetClassMetaType<TargetPoint>(), "p"), PROTO_OFFSET(TargetableBehaviour, targetPoints),
				"targetPoints" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B4030
	TargetableBehaviour::TargetableBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		isTargetable(true), canCauseStrikeTeamCall(true), targetableEvenWhenAttached(false),
		targetableWhenAttachedToTargeter(false), targetClass(0), currentTargetClass(0), targetRadius(0.0f),
		lineOfSightRadius(0.0f), rootTargetFilter(-1), rootTargetOffset(0.0f, 0.0f, 0.0f), unknown40(0),
		firstTargeter(0), lastTargeter(0)
	{
		Listen(1, true);
		Listen(2, true);
		Listen(0x3b, true);
		AddToAll(this);
	}

	// FUNCTION: ENGINE 0x102B40F0
	TargetableBehaviour::~TargetableBehaviour()
	{
		ClearTargeters();
		RemoveFromAll(this);
	}

	container::DoubleListBase TargetableBehaviour::sAll;

	// FUNCTION: ENGINE 0x102B4450
	void TargetableBehaviour::AddToAll(TargetableBehaviour* behaviour)
	{
		Node* node = (Node*)operator new[](sizeof(Node));
		if (node != 0)
		{
			node->behaviour = behaviour;
			sAll.Insert(0, node);
		}
	}

	// FUNCTION: ENGINE 0x102B4480
	// NONMATCHING: the engine walks the list through out-of-line begin and end functions (0x102B43B0 / 0x102B43C0) (31.4 %)
#ifdef NONMATCHING
	void TargetableBehaviour::RemoveFromAll(TargetableBehaviour* behaviour)
	{
		for (container::DoubleListBase::Node* node = sAll.head; node != 0; node = node->next)
		{
			if (((Node*)node)->behaviour == behaviour)
			{
				sAll.Remove(node);
				operator delete[](node);
				return;
			}
		}
	}
#endif
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102B13A0
// FUNCTION: ENGINE 0x102B13B0
// FUNCTION: ENGINE 0x102B1870
// FUNCTION: ENGINE 0x102B18B0
// FUNCTION: ENGINE 0x102B1900
// FUNCTION: ENGINE 0x102B1940
// FUNCTION: ENGINE 0x102B1AA0
// FUNCTION: ENGINE 0x102B1AB0
// FUNCTION: ENGINE 0x102B1F60
// FUNCTION: ENGINE 0x102B1FA0
// FUNCTION: ENGINE 0x102B1FE0
// FUNCTION: ENGINE 0x102B2020
// FUNCTION: ENGINE 0x102B2060
// FUNCTION: ENGINE 0x102B20A0
// FUNCTION: ENGINE 0x102B3240
// FUNCTION: ENGINE 0x102B32C0
// FUNCTION: ENGINE 0x102B3340
// FUNCTION: ENGINE 0x102B33C0
// FUNCTION: ENGINE 0x102B3440
// FUNCTION: ENGINE 0x102B34C0
// FUNCTION: ENGINE 0x102B3540
// FUNCTION: ENGINE 0x102B35C0
// FUNCTION: ENGINE 0x102B3AE0
