#include "code/proto/behaviours/grabbablebehaviour.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobjectspawner.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

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
	};

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
