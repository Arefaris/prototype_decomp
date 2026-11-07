#include "code/proto/behaviours/doortriggerbehaviour.h"
#include "code/content/stringmetatype.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/setproplogicstatemessage.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/physics/physicsmessages.h"
#include "code/engine/surfacedefinition.h"
#include "code/ravenphysics/collision/collisioninfo.h"
#include "code/ravenphysics/physicsobject.h"

namespace engine
{
	GameObject* __fastcall GameObjectHandleGet(const GameObjectHandle* handle);
}

namespace proto
{
	// The notification of a trigger volume (message type 0xd; id 3: an object entered, id 4: it left): the object and
	// the name of the volume (member names guessed)
	struct VolumeNotifyMessage : public engine::Message
	{
		int unknownC;
		engine::GameObjectHandle object;  // +0x10
		int unknown14[3];
		core::Name<core::CaseSensitiveKey> volumeName;  // +0x20
	};

	// The contacts of a physics step (message type 4): the records of 0x70 bytes
	struct CollisionNotifyMessage : public engine::Message
	{
		ravenphysics::CollisionInfo* contactsBegin;  // +0xC
		ravenphysics::CollisionInfo* contactsEnd;  // +0x10
	};

	// The engine compares both words of a handle at once
	static inline bool SameHandle(const engine::GameObjectHandle& first, const engine::GameObjectHandle& second)
	{
		return *(const int*)&first == *(const int*)&second;
	}

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10555C00
	content::ClassInfo* DoorTriggerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DoorTriggerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105566F0
	DoorTriggerBehaviour::DoorTriggerBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), useFilter(true),
		filterAttributeKey(""), filterAttributeValue("", 1), inVolumeStateName("", 1), outVolumeStateName("", 1),
		toggleCollision(false), forcePropLogicState(false), useTwoVolumes(false)
	{
		Listen(2, true);
		Listen(0xd, true);
	}

	// FUNCTION: ENGINE 0x105567E0
	DoorTriggerBehaviour::~DoorTriggerBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10555E50
	void DoorTriggerBehaviour::SendInVolumeState()
	{
		engine::SetPropLogicStateMessage message("", inVolumeStateName,
			!forcePropLogicState, false);
		owner->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x10555F10
	void DoorTriggerBehaviour::SendOutVolumeState()
	{
		engine::SetPropLogicStateMessage message("", outVolumeStateName,
			!forcePropLogicState, false);
		owner->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x10556420
	void DoorTriggerBehaviour::ClearInVolume()
	{
		Listen(4, false);
		inVolume.Reset();
	}

	// FUNCTION: ENGINE 0x10556440
	// NONMATCHING: the engine reloads the end word of the array for every size test (best 22 %)
#ifdef NONMATCHING
	void DoorTriggerBehaviour::AddInVolume(const engine::GameObjectHandle& handle)
	{
		container::ArrayFixed<engine::GameObjectHandle, 10>& array = inVolume;
		if ((unsigned int)array.Size() < 10)
		{
			unsigned int i = 0;
			if (array.Size() > 0)
			{
				engine::GameObjectHandle* at = array.Begin();
				do
				{
					if (SameHandle(*at, handle))
					{
						return;
					}
					i++;
					at++;
				}
				while (i < (unsigned int)array.Size());
			}
			array.PushBack(handle);
		}
	}
#endif

	// FUNCTION: ENGINE 0x105564C0
	// NONMATCHING: register allocation of the loop (best 89 %)
#ifdef NONMATCHING
	void DoorTriggerBehaviour::RemoveInVolume(const engine::GameObjectHandle& handle)
	{
		container::ArrayFixed<engine::GameObjectHandle, 10>& array = inVolume;
		unsigned int i = 0;
		if (array.Size() > 0)
		{
			engine::GameObjectHandle* at = array.Begin();
			do
			{
				if (!at->IsValid() || SameHandle(*at, handle))
				{
					array.end--;
					if (at < array.end)
					{
						*at = *array.end;
					}
				}
				else
				{
					i++;
					at++;
				}
			}
			while (i < (unsigned int)array.Size());
		}
	}
#endif

	// FUNCTION: ENGINE 0x10556810
	// NONMATCHING: the engine shares one stack slot between the two intersection messages (best 18 %)
#ifdef NONMATCHING
	void DoorTriggerBehaviour::OnMessage(engine::Message* message)
	{
		engine::AttributePtr<core::Name<core::CaseSensitiveKey> > attribute;
		attribute.value = 0;
		switch (message->type)
		{
		case 2:
			ClearInVolume();
			return;
		case 4:
		{
			CollisionNotifyMessage* collisions = (CollisionNotifyMessage*)message;
			for (unsigned int i = 0; i < (unsigned int)(collisions->contactsEnd - collisions->contactsBegin); i++)
			{
				ravenphysics::CollisionInfo* info = &collisions->contactsBegin[i];
				if (info->contact.unknown2A[4] == 0 && info->bodyHandles[0].IsValid() && info->bodyHandles[1].IsValid()
					&& info->contact.faceIndex != 0xffff && info->GetOtherSide((int)owner) == 0)
				{
					engine::GameObjectHandle other = engine::GetHandle(
						(engine::GameObject*)info->bodyHandles[0].GetObjectSecond()->GetUnknown48());
					engine::GameObjectHandle* found = inVolume.Begin();
					while (found != inVolume.End() && found->index != other.index)
					{
						found++;
					}
					if (found != inVolume.End())
					{
						info->contact.unknown2A[4] = 2;
					}
				}
			}
			return;
		}
		case 0xd:
		{
			VolumeNotifyMessage* notify = (VolumeNotifyMessage*)message;
			switch (message->id)
			{
			case 3:
			{
				if (!useTwoVolumes)
				{
					return;
				}
				if (!(notify->volumeName == core::Name<core::CaseSensitiveKey>("inVolume", 1)))
				{
					return;
				}
				engine::GameObjectHandle object = notify->object;
				container::String* keyString = &filterAttributeKey;
				core::Name<core::CaseSensitiveKey> key(keyString->Data(), 1);
				attribute = engine::GameObjectHandleGet(&object)->GetAttributePtr<core::Name<core::CaseSensitiveKey> >(key);
				if (useFilter)
				{
					if (attribute.value == 0 || !(*attribute.value == filterAttributeValue))
					{
						return;
					}
				}
				if (toggleCollision)
				{
					engine::SetIntersectionPropertiesMessage properties(0x400001, false, 1, false);
					engine::GameObjectHandleGet(&object)->SendMessage(&properties);
				}
				AddInVolume(object);
				Listen(4, true);
				SendInVolumeState();
				return;
			}
			case 4:
			{
				if (!useTwoVolumes)
				{
					return;
				}
				if (!(notify->volumeName == core::Name<core::CaseSensitiveKey>("outVolume", 1)))
				{
					return;
				}
				if (inVolume.IsEmpty())
				{
					return;
				}
				engine::GameObject* object = engine::GameObjectHandleGet(&notify->object);
				if (object == 0)
				{
					return;
				}
				container::String* keyString = &filterAttributeKey;
				core::Name<core::CaseSensitiveKey> key(keyString->Data(), 1);
				attribute = object->GetAttributePtr<core::Name<core::CaseSensitiveKey> >(key);
				if (useFilter)
				{
					if (attribute.value == 0 || !(*attribute.value == filterAttributeValue))
					{
						return;
					}
				}
				if (toggleCollision)
				{
					engine::SetIntersectionPropertiesMessage properties(0x400001, true, 1, false);
					object->SendMessage(&properties);
				}
				RemoveInVolume(notify->object);
				if (inVolume.IsEmpty())
				{
					SendOutVolumeState();
					Listen(4, false);
				}
				return;
			}
			}
		}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10556180
	content::MemberList* DoorTriggerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, DoorTriggerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<DoorTriggerBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(DoorTriggerBehaviour, useFilter), "useFilter" },
			{ content::GetMemberStringMetaType<0>(&((DoorTriggerBehaviour*)content::gStringMemberBase)->filterAttributeKey, "p"),
				content::StringBufferOffset(&((DoorTriggerBehaviour*)content::gStringMemberBase)->filterAttributeKey)
				+ (int)&((DoorTriggerBehaviour*)0)->filterAttributeKey, "filterAttributeKey" },
			{ content::GetMemberNameMetaType<DoorTriggerBehaviour, 0>(true, true, "p"),
				PROTO_OFFSET(DoorTriggerBehaviour, filterAttributeValue), "filterAttributeValue" },
			{ content::GetMemberNameMetaType<DoorTriggerBehaviour, 1>(true, true, "p"),
				PROTO_OFFSET(DoorTriggerBehaviour, inVolumeStateName), "inVolumeStateName" },
			{ content::GetMemberNameMetaType<DoorTriggerBehaviour, 2>(true, true, "p"),
				PROTO_OFFSET(DoorTriggerBehaviour, outVolumeStateName), "outVolumeStateName" },
			{ content::GetMemberPrimitiveMetaType<DoorTriggerBehaviour, bool, 1>("pn"),
				PROTO_OFFSET(DoorTriggerBehaviour, toggleCollision), "toggleCollision" },
			{ content::GetMemberPrimitiveMetaType<DoorTriggerBehaviour, bool, 2>("p"),
				PROTO_OFFSET(DoorTriggerBehaviour, forcePropLogicState), "forcePropLogicState" },
			{ content::GetMemberPrimitiveMetaType<DoorTriggerBehaviour, bool, 3>("p"),
				PROTO_OFFSET(DoorTriggerBehaviour, useTwoVolumes), "useTwoVolumes" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10555C40
// FUNCTION: ENGINE 0x10555C50
// FUNCTION: ENGINE 0x10555CB0
// FUNCTION: ENGINE 0x10555CC0
// FUNCTION: ENGINE 0x10555D00
// FUNCTION: ENGINE 0x10555D40
// FUNCTION: ENGINE 0x10555D80
// FUNCTION: ENGINE 0x10555E10
// FUNCTION: ENGINE 0x10555E20
// FUNCTION: ENGINE 0x10556070
// FUNCTION: ENGINE 0x105560B0
// FUNCTION: ENGINE 0x105560C0
// FUNCTION: ENGINE 0x10556100
// FUNCTION: ENGINE 0x10556140
// FUNCTION: ENGINE 0x10556AD0
