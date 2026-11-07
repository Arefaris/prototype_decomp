#include "code/proto/behaviours/grabbablebehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobjectspawner.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102C5410
	GrabbableBehaviour::GrabbableBehaviour(engine::GameObject* newOwner) : engine::animation::AttachableBehaviour(newOwner),
		uninterruptible(0), unknown54(0), grabbingForbidden(false), unknown59(false)
	{
		Listen(0x3C, true);
		Listen(0xF, true);
		Listen(2, true);
	}

	// FUNCTION: ENGINE 0x102C5480
	GrabbableBehaviour::~GrabbableBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x102C4FB0
	void GrabbableBehaviour::Slot1()
	{
		unknown59 = grabbingForbidden;
		engine::animation::AttachableBehaviour::Slot1();
	}

	// FUNCTION: ENGINE 0x102C5070
	void GrabbableBehaviour::Slot8()
	{
		Listen(4, false);
		unknown59 = grabbingForbidden;
	}

	// FUNCTION: ENGINE 0x102C54E0
	GrabbableStaticBehaviour::GrabbableStaticBehaviour(engine::GameObject* newOwner) : GrabbableBehaviour(newOwner),
		playbackTreeName("", 1), playbackTreeState("initial", 1), spawnedObjectTemplate(0), parentTransitionState(0),
		childTransitionState(0)
	{
	}

	// FUNCTION: ENGINE 0x102C4F30
	content::ClassInfo* GrabbableBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "GrabbableBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C4F70
	content::ClassInfo* GrabbableStaticBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GrabbableStaticBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C50D0
	const char* GrabbableStaticBehaviour::GetParentTransitionState()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x102C50E0
	const char* GrabbableStaticBehaviour::GetChildTransitionState()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x102C50A0
	engine::UnpackedInitialState* GrabbableStaticBehaviour::CreateTransitionState(const char* packed,
		content::LoadInventory* inventory)
	{
		return new engine::UnpackedInitialState(packed);
	}

	// This unit's own copy of core::RefAssign for the transition states (the engine keeps one per unit)
	struct TransitionStateRef
	{
		static void Assign(engine::UnpackedInitialState*& pointer, engine::UnpackedInitialState* object);
		static void Release(engine::UnpackedInitialState*& pointer);
	};

	// FUNCTION: ENGINE 0x102C5230
	void TransitionStateRef::Release(engine::UnpackedInitialState*& pointer)
	{
		if (pointer != 0)
		{
			pointer->Release();
			pointer = 0;
		}
	}

	// FUNCTION: ENGINE 0x102C5250
	void TransitionStateRef::Assign(engine::UnpackedInitialState*& pointer, engine::UnpackedInitialState* object)
	{
		if (object != 0)
		{
			object->AddRef();
		}
		if (pointer != 0)
		{
			pointer->Release();
		}
		pointer = object;
	}

	// FUNCTION: ENGINE 0x102C5090
	void GrabbableStaticBehaviour::Slot1()
	{
		GrabbableBehaviour::Slot1();
	}

	// FUNCTION: ENGINE 0x102C5540
	GrabbableStaticBehaviour::~GrabbableStaticBehaviour()
	{
		core::SafeRelease(spawnedObjectTemplate);
		TransitionStateRef::Release(parentTransitionState);
		TransitionStateRef::Release(childTransitionState);
	}

	// FUNCTION: ENGINE 0x102C5580
	void GrabbableStaticBehaviour::SetParentTransitionState(const char* packed, content::LoadInventory* inventory)
	{
		TransitionStateRef::Assign(parentTransitionState, CreateTransitionState(packed, inventory));
	}

	// FUNCTION: ENGINE 0x102C55B0
	void GrabbableStaticBehaviour::SetChildTransitionState(const char* packed, content::LoadInventory* inventory)
	{
		TransitionStateRef::Assign(childTransitionState, CreateTransitionState(packed, inventory));
	}

	// FUNCTION: ENGINE 0x102C5700
	content::MemberList* GrabbableBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::animation::AttachableBehaviour>();
		static content::BaseClassCasterImpl<engine::animation::AttachableBehaviour, GrabbableBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<GrabbableBehaviour>(true, true, "p"),
				PROTO_NAME_OFFSET(GrabbableBehaviour, grabbableClass), "grabbableClass" },
			{ content::GetMemberPrimitiveMetaType<GrabbableBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(GrabbableBehaviour, grabbingForbidden), "grabbingForbidden" },
			{ content::GetMemberPrimitiveMetaType<GrabbableBehaviour, int, 0>("pn"),
				PROTO_OFFSET(GrabbableBehaviour, uninterruptible), "uninterruptible" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102C5BA0
	content::MemberList* GrabbableStaticBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<GrabbableBehaviour>();
		static content::BaseClassCasterImpl<GrabbableBehaviour, GrabbableStaticBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<GrabbableStaticBehaviour>(true, true, "p"),
				PROTO_NAME_OFFSET(GrabbableStaticBehaviour, playbackTreeName), "playbackTreeName" },
			{ content::GetMemberNameMetaType<GrabbableStaticBehaviour, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(GrabbableStaticBehaviour, playbackTreeState), "playbackTreeState" },
			{ content::GetReferenceMetaType<GrabbableStaticBehaviour, content::MetaObjectTemplate>("p"),
				PROTO_OFFSET(GrabbableStaticBehaviour, spawnedObjectTemplate), "spawnedObjectTemplate" },
			{ content::GetStringMemberWithResolverMetaType<GrabbableStaticBehaviour, 0>(
				&GrabbableStaticBehaviour::GetParentTransitionState,
				&GrabbableStaticBehaviour::SetParentTransitionState, "pn"), 0, "parentTransitionState" },
			{ content::GetStringMemberWithResolverMetaType<GrabbableStaticBehaviour, 1>(
				&GrabbableStaticBehaviour::GetChildTransitionState,
				&GrabbableStaticBehaviour::SetChildTransitionState, "pn"), 0, "childTransitionState" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102C4E40
// FUNCTION: ENGINE 0x102C4E80
// FUNCTION: ENGINE 0x102C4ED0
// FUNCTION: ENGINE 0x102C5100
// FUNCTION: ENGINE 0x102C5170
// FUNCTION: ENGINE 0x102C51B0
// FUNCTION: ENGINE 0x102C51F0
// FUNCTION: ENGINE 0x102C5290
// FUNCTION: ENGINE 0x102C5390
// FUNCTION: ENGINE 0x102C53A0
// FUNCTION: ENGINE 0x102C53D0
// FUNCTION: ENGINE 0x102C53E0
// FUNCTION: ENGINE 0x102C55F0
// FUNCTION: ENGINE 0x102C5630
// FUNCTION: ENGINE 0x102C5670
// FUNCTION: ENGINE 0x102C5690
// FUNCTION: ENGINE 0x102C56B0
// FUNCTION: ENGINE 0x102C5A20
// FUNCTION: ENGINE 0x102C5A80
// FUNCTION: ENGINE 0x102C5B10

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102C4E10
// FUNCTION: ENGINE 0x102C5840
// FUNCTION: ENGINE 0x102C59F0
