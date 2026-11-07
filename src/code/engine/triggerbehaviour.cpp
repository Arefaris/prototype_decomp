#include "code/engine/triggerbehaviour.h"
#include "code/content/enummetatype.h"
#include "code/content/stringmetatype.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/surfacedefinition.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace engine
{
	GameObject* __fastcall GameObjectHandleGet(const GameObjectHandle* handle);
	// 0x1006B210 (another unit; name guess): the out-of-line copy of GameObjectHandle::IsValid
	bool __fastcall GameObjectHandleIsValid(const GameObjectHandle* handle);

	namespace trigger
	{
		// 0x10899D10 / 0x10899D70 (another unit; name guesses): send the messages of the occupants the volume has in
		// the world's list (the second one marks them as leaving first)
		void SendPendingMessages(TriggerBehaviour* behaviour, Volume* volume);
		void SendLeaveMessages(TriggerBehaviour* behaviour, Volume* volume);
		// 0x10899FB0 / 0x1089A030 (another unit; name guesses): put the volume into the world's list / take it out
		void AddVolume(Volume* volume);
		void RemoveVolume(Volume* volume);
	}

	extern MessageListeners gScenario14;

	// The query a trigger answers (message type 3, id 0x18): the handle of its volume
	struct VolumeHandleMessage : public Message
	{
		unsigned int volumeHandle;  // +0x0C
	};

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	static const content::EnumValue sTargetValues[] =
	{
		{ "Self", 0 },
		{ "Touch", 1 },
		{ "MasterScenario", 2 },
		{ "Other", 3 }
	};
}

namespace content
{
	// FUNCTION: ENGINE 0x1083AD20
	template<> void EnumInfo<engine::TriggerBehaviour::Target>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "engine::TriggerBehaviour::Target";
		*code = "pn";
		*values = engine::sTargetValues;
		*count = 4;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x1083AD50
	content::ClassInfo* TriggerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::TriggerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1083AD90
	content::ClassInfo* MovingTriggerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::MovingTriggerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1083ADD0
	void TriggerBehaviour::Slot0()
	{
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x1083ADE0
	void TriggerBehaviour::Update(float dt, unsigned short mask)
	{
		trigger::SendPendingMessages(this, volume);
	}

	// FUNCTION: ENGINE 0x1083ADF0
	void TriggerBehaviour::SetTargetMode(Target newTarget)
	{
		targetMode = newTarget;
	}

	// FUNCTION: ENGINE 0x1083AE00
	void TriggerBehaviour::OnPostedMessage(Message* message)
	{
		if (message->type == 3 && message->id == 0x18 && volume != 0)
		{
			((VolumeHandleMessage*)message)->volumeHandle = volume->GetHandle()->value;
		}
	}

	// FUNCTION: ENGINE 0x1083AFC0
	TriggerBehaviour::~TriggerBehaviour()
	{
		if (volume != 0 && volume->GetHandle()->IsValid())
		{
			trigger::SendLeaveMessages(this, volume);
			trigger::RemoveVolume(volume);
		}
		delete volume;
		delete onEnter;
		delete onExit;
	}

	// FUNCTION: ENGINE 0x1083B060
	void TriggerBehaviour::Slot1()
	{
		volume->SetKind(0);
		OnActiveChanged(IsActive());
		volume->SetOwner(GetHandle(owner));
		volume->SetObjectTransform(owner->transform->value);
		if (!targetName.IsEmpty())
		{
			core::Name<core::CaseSensitiveKey> name(targetName.Data(), 1);
			targetHandle = FindGameObject(name, *(const content::ObjectName*)"");
		}
	}

	// FUNCTION: ENGINE 0x1083B100
	void TriggerBehaviour::OnActiveChanged(bool active)
	{
		Behaviour::OnActiveChanged(active);
		if (volume != 0 && volume->GetHandle()->IsValid())
		{
			if (active)
			{
				trigger::AddVolume(volume);
				return;
			}
			trigger::SendLeaveMessages(this, volume);
			trigger::RemoveVolume(volume);
		}
	}

	// FUNCTION: ENGINE 0x1083B170
	void TriggerBehaviour::SetEnterText(const char* text)
	{
		EnterTriggerMessage* message = (EnterTriggerMessage*)onEnter;
		core::Name<core::CaseSensitiveKey> name(text, 1);
		message->extraString = name;
	}

	// FUNCTION: ENGINE 0x1083B1A0
	void TriggerBehaviour::SetExitText(const char* text)
	{
		ExitTriggerMessage* message = (ExitTriggerMessage*)onExit;
		core::Name<core::CaseSensitiveKey> name(text, 1);
		message->extraString = name;
	}

	// FUNCTION: ENGINE 0x1083B1D0
	void TriggerBehaviour::OnMessage(Message* message)
	{
		if (message->type == 0x1a)
		{
			volume->SetObjectTransform(owner->transform->value);
		}
	}

	// FUNCTION: ENGINE 0x1083B200
	void MovingTriggerBehaviour::Update(float dt, unsigned short mask)
	{
		volume->SetObjectTransform(owner->transform->value);
		TriggerBehaviour::Update(dt, mask);
	}

	// FUNCTION: ENGINE 0x1083B2B0
	// NONMATCHING: the engine builds the result of FindGameObject in the dead slot of the first argument (best 99.7 %)
#ifdef NONMATCHING
	void TriggerBehaviour::SendTriggerMessage(GameObjectHandle other, int exit)
	{
		IntrusiveMessage* message = 0;
		if (onEnter != 0 && exit == 0)
		{
			message = onEnter;
		}
		else if (onExit != 0 && exit == 1)
		{
			message = onExit;
		}
		if (message == 0)
		{
			return;
		}
		if (message->type == 0xd)
		{
			((ScenarioMessage*)message)->SetHandle(0, GetHandle(owner));
			((ScenarioMessage*)message)->SetHandle(1, other);
		}
		switch (targetMode)
		{
		case TARGET_SELF:
			owner->SendMessage(message);
			return;
		case TARGET_TOUCH:
		{
			GameObject* object = GameObjectHandleGet(&other);
			if (object != 0)
			{
				object->SendMessage(message);
				return;
			}
			break;
		}
		case TARGET_MASTER_SCENARIO:
			engine::SendMessage(message, &gScenario14);
			return;
		case TARGET_OTHER:
			if (!GameObjectHandleIsValid(&targetHandle))
			{
				core::Name<core::CaseSensitiveKey> name(targetName.Data(), 1);
				targetHandle = FindGameObject(name, *(const content::ObjectName*)"");
			}
			if (GameObjectHandleIsValid(&targetHandle))
			{
				GameObjectHandleGet(&targetHandle)->SendMessage(message);
			}
		}
	}

#endif

	// FUNCTION: ENGINE 0x1083B4E0
	content::MemberList* TriggerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, TriggerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetObjectMetaTypeCopy<trigger::Volume>("pnr"), ENGINE_OFFSET(TriggerBehaviour, volume), "volume" },
			{ content::GetEnumMetaType<Target>(), (int)&((TriggerBehaviour*)0)->targetMode, "targetMode" },
			{ content::GetMemberStringMetaType<1>(&((TriggerBehaviour*)content::gStringMemberBase)->targetName, "pn"),
				content::StringBufferOffset(&((TriggerBehaviour*)content::gStringMemberBase)->targetName)
				+ (int)&((TriggerBehaviour*)0)->targetName, "targetName" },
			{ content::GetObjectMetaType<IntrusiveMessage>("pn"), ENGINE_OFFSET(TriggerBehaviour, onEnter), "onEnter" },
			{ content::GetObjectMetaTypeCopy<IntrusiveMessage>("pn"), ENGINE_OFFSET(TriggerBehaviour, onExit), "onExit" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1083B660
	content::MemberList* MovingTriggerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<TriggerBehaviour>();
		static content::BaseClassCasterImpl<TriggerBehaviour, MovingTriggerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1083B6C0
	TriggerBehaviour::TriggerBehaviour(GameObject* newOwner) : Behaviour(newOwner), volume(0), targetMode(TARGET_SELF),
		onEnter(0), onExit(0)
	{
		Listen(3, true);
		Listen(0x1a, true);
		core::Name<core::CaseSensitiveKey> value("", 1);
		core::Name<core::CaseSensitiveKey> key("TriggerClass", 1);
		owner->SetAttribute(key, value, false);
	}

	// FUNCTION: ENGINE 0x1083B760
	TriggerBehaviour::TriggerBehaviour(GameObject* newOwner, trigger::Volume* newVolume) : Behaviour(newOwner),
		volume(newVolume), targetMode(TARGET_SELF), onEnter(new EnterTriggerMessage), onExit(new ExitTriggerMessage)
	{
		Listen(3, true);
		Listen(0x1a, true);
		core::Name<core::CaseSensitiveKey> value("", 1);
		core::Name<core::CaseSensitiveKey> key("TriggerClass", 1);
		owner->SetAttribute(key, value, false);
	}

	// FUNCTION: ENGINE 0x1083B860
	TriggerBehaviour::TriggerBehaviour(GameObject* newOwner, trigger::Volume* newVolume, Target newTarget)
		: Behaviour(newOwner), volume(newVolume), targetMode(newTarget), onEnter(new EnterTriggerMessage),
		onExit(new ExitTriggerMessage)
	{
		Listen(3, true);
		Listen(0x1a, true);
		core::Name<core::CaseSensitiveKey> value("", 1);
		core::Name<core::CaseSensitiveKey> key("TriggerClass", 1);
		owner->SetAttribute(key, value, false);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1083AE30
// FUNCTION: ENGINE 0x1083AE90
// FUNCTION: ENGINE 0x1083AEB0
// FUNCTION: ENGINE 0x1083AEE0
// FUNCTION: ENGINE 0x1083AEF0
// FUNCTION: ENGINE 0x1083AF40
// FUNCTION: ENGINE 0x1083AF50
// FUNCTION: ENGINE 0x1083AF80
// FUNCTION: ENGINE 0x1083AF90
// FUNCTION: ENGINE 0x1083B230
// FUNCTION: ENGINE 0x1083B240
// FUNCTION: ENGINE 0x1083B260
// FUNCTION: ENGINE 0x1083B270
// FUNCTION: ENGINE 0x1083B290
// FUNCTION: ENGINE 0x1083B3F0
// FUNCTION: ENGINE 0x1083B440
// FUNCTION: ENGINE 0x1083B490
