#include "code/core/strings.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/scenariomessage.h"

namespace engine
{
	// FUNCTION: ENGINE 0x107F09E0
	content::ClassInfo* EnterTriggerMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::EnterTriggerMessage";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107F0A20
	content::ClassInfo* ExitTriggerMessage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ExitTriggerMessage";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107F0A60
	GameObjectHandle ScenarioMessage::GetHandle(unsigned int index) const
	{
		if (index < HANDLE_COUNT)
		{
			return handles[index];
		}
		return GameObjectHandle();
	}

	// FUNCTION: ENGINE 0x107F0A90
	void ScenarioMessage::SetHandle(unsigned int index, GameObjectHandle handle)
	{
		if (index < HANDLE_COUNT)
		{
			handles[index] = handle;
		}
	}

	// FUNCTION: ENGINE 0x107F0AB0
	bool ScenarioMessage::WriteEvent()
	{
		ScriptContext* context = GetScriptContext();
		if (context == 0)
		{
			return false;
		}
		if (!context->OpenEvent())
		{
			return false;
		}
		WriteFields(context);
		context->Close();
		return true;
	}

	// FUNCTION: ENGINE 0x107F0AF0
	void EnterTriggerMessage::WriteFields(ScriptContext* context)
	{
		context->SetHandle("trigger", SerializeHandle(handles[0]));
		context->SetHandle("touch", SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x107F0B40
	void ExitTriggerMessage::WriteFields(ScriptContext* context)
	{
		context->SetHandle("trigger", SerializeHandle(handles[0]));
		context->SetHandle("touch", SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x107F0B90
	void StringMessage::WriteFields(ScriptContext* context)
	{
		context->SetName("string", string);
		for (int i = 0; i < HANDLE_COUNT; i++)
		{
			char key[0x20];
			core::SNPrintf(key, sizeof(key), "object%d", i);
			context->SetHandle(key, SerializeHandle(handles[i]));
		}
	}

	// FUNCTION: ENGINE 0x107F0C00
	void ObjectDestroyedMessage::WriteFields(ScriptContext* context)
	{
		context->SetHandle("object", SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x107F0C30
	void ObjectStateChangedMessage::WriteFields(ScriptContext* context)
	{
		context->SetHandle("object", SerializeHandle(handles[0]));
		context->SetHandle("prop", SerializeHandle(handles[0]));
		context->SetName("newState", newState);
	}

	// FUNCTION: ENGINE 0x107F0C90
	void ScenarioNISBeginMessage::WriteFields(ScriptContext* context)
	{
		context->SetName("NISName", name);
	}

	// FUNCTION: ENGINE 0x107F0CB0
	void ScenarioNISEndMessage::WriteFields(ScriptContext* context)
	{
		context->SetName("NISName", name);
	}

	// FUNCTION: ENGINE 0x107F0CD0
	void ScenarioNISLoadCompleteMessage::WriteFields(ScriptContext* context)
	{
		context->SetName("NISName", name);
	}

	// FUNCTION: ENGINE 0x107F0CF0
	void ScenarioNISStallMessage::WriteFields(ScriptContext* context)
	{
		context->SetName("NISName", name);
	}

	// FUNCTION: ENGINE 0x107F0D10
	void ScenarioNISResumeMessage::WriteFields(ScriptContext* context)
	{
		context->SetName("NISName", name);
	}

	// FUNCTION: ENGINE 0x107F0D30
	void ScenarioStreamPackageLoadedMessage::WriteFields(ScriptContext* context)
	{
		context->SetName("packageName", name);
	}

	// FUNCTION: ENGINE 0x107F0D50
	void ScenarioStreamPackageUnloadedMessage::WriteFields(ScriptContext* context)
	{
		context->SetName("packageName", name);
	}

	// FUNCTION: ENGINE 0x107F10B0
	ScenarioMessage* NullMessage::Clone(void* memory, int unused)
	{
		return new (memory) NullMessage;
	}

	// FUNCTION: ENGINE 0x107F10E0
	ScenarioMessage* ScenarioInitializeMessage::Clone(void* memory, int unused)
	{
		return new (memory) ScenarioInitializeMessage;
	}

	// FUNCTION: ENGINE 0x107F1110
	TriggerMessage::TriggerMessage(int event) : ScenarioMessage(event)
	{
	}

	// FUNCTION: ENGINE 0x107F1150
	StringMessage::StringMessage(const core::Name<core::CaseSensitiveKey>& value) : ScenarioMessage(2)
	{
		string = value;
	}

	// The copy of the handles every Clone ends with
#define ENGINE_COPY_HANDLES(clone) \
	for (unsigned int i = 0; i < sHandleInfo.count; i++) \
	{ \
		(clone)->handles[i] = handles[i]; \
	}

	// FUNCTION: ENGINE 0x107F1180
	ScenarioMessage* StringMessage::Clone(void* memory, int unused)
	{
		StringMessage* clone = new (memory) StringMessage(string);
		ENGINE_COPY_HANDLES(clone)
		return clone;
	}

	// FUNCTION: ENGINE 0x107F11C0
	ScenarioMessage* ObjectDestroyedMessage::Clone(void* memory, int unused)
	{
		ObjectDestroyedMessage* clone = new (memory) ObjectDestroyedMessage;
		ENGINE_COPY_HANDLES(clone)
		return clone;
	}

	// FUNCTION: ENGINE 0x107F1210
	ScenarioMessage* ObjectStateChangedMessage::Clone(void* memory, int unused)
	{
		ObjectStateChangedMessage* clone = new (memory) ObjectStateChangedMessage;
		ENGINE_COPY_HANDLES(clone)
		clone->newState = newState;
		return clone;
	}

#define ENGINE_NAMED_CLONE(Class) \
	ScenarioMessage* Class::Clone(void* memory, int unused) \
	{ \
		Class* clone = new (memory) Class(name); \
		ENGINE_COPY_HANDLES(clone) \
		return clone; \
	}

	// FUNCTION: ENGINE 0x107F1280
	ENGINE_NAMED_CLONE(ScenarioNISBeginMessage)
	// FUNCTION: ENGINE 0x107F12F0
	ENGINE_NAMED_CLONE(ScenarioNISEndMessage)
	// FUNCTION: ENGINE 0x107F1360
	ENGINE_NAMED_CLONE(ScenarioNISLoadCompleteMessage)
	// FUNCTION: ENGINE 0x107F13D0
	ENGINE_NAMED_CLONE(ScenarioNISStallMessage)
	// FUNCTION: ENGINE 0x107F1440
	ENGINE_NAMED_CLONE(ScenarioNISResumeMessage)
	// FUNCTION: ENGINE 0x107F14B0
	ENGINE_NAMED_CLONE(ScenarioStreamPackageLoadedMessage)
	// FUNCTION: ENGINE 0x107F1520
	ENGINE_NAMED_CLONE(ScenarioStreamPackageUnloadedMessage)

	// FUNCTION: ENGINE 0x107F1750
	content::MemberList* EnterTriggerMessage::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IntrusiveMessage>();
		static content::BaseClassCasterImpl<IntrusiveMessage, EnterTriggerMessage> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<EnterTriggerMessage>(true, true, "pn"),
				content::MemberOffset(&((EnterTriggerMessage*)0)->extraString,
				(int)&((EnterTriggerMessage*)0)->extraString), "extraString" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107F1800
	content::MemberList* ExitTriggerMessage::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<IntrusiveMessage>();
		static content::BaseClassCasterImpl<IntrusiveMessage, ExitTriggerMessage> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<ExitTriggerMessage>(true, true, "pn"),
				content::MemberOffset(&((ExitTriggerMessage*)0)->extraString,
				(int)&((ExitTriggerMessage*)0)->extraString), "extraString" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107F18B0
	ScenarioMessage* EnterTriggerMessage::Clone(void* memory, int unused)
	{
		EnterTriggerMessage* clone = new (memory) EnterTriggerMessage;
		ENGINE_COPY_HANDLES(clone)
		return clone;
	}

	// FUNCTION: ENGINE 0x107F1900
	ScenarioMessage* ExitTriggerMessage::Clone(void* memory, int unused)
	{
		ExitTriggerMessage* clone = new (memory) ExitTriggerMessage;
		ENGINE_COPY_HANDLES(clone)
		return clone;
	}

	// Kept copies: the messages' scalar deleting destructors, their constructors and destructors, the base class
	// casters and the name meta types of the trigger messages
	// FUNCTION: ENGINE 0x107F0E20
	// FUNCTION: ENGINE 0x107F1130
	// FUNCTION: ENGINE 0x107F15C0
	// FUNCTION: ENGINE 0x107F1610
	// FUNCTION: ENGINE 0x107F1630
	// FUNCTION: ENGINE 0x107F1650
	// FUNCTION: ENGINE 0x107F1670
	// FUNCTION: ENGINE 0x107F1690
	// FUNCTION: ENGINE 0x107F16B0
	// FUNCTION: ENGINE 0x107F16D0
	// FUNCTION: ENGINE 0x107F16F0
	// FUNCTION: ENGINE 0x107F1710
	// FUNCTION: ENGINE 0x107F1730
	// FUNCTION: ENGINE 0x107F0DF0
	// FUNCTION: ENGINE 0x107F0E10
	// FUNCTION: ENGINE 0x107F0E40
	// FUNCTION: ENGINE 0x107F0E60
	// FUNCTION: ENGINE 0x107F0E70
	// FUNCTION: ENGINE 0x107F0EA0
	// FUNCTION: ENGINE 0x107F0EB0
	// FUNCTION: ENGINE 0x107F0EE0
	// FUNCTION: ENGINE 0x107F0EF0
	// FUNCTION: ENGINE 0x107F0F20
	// FUNCTION: ENGINE 0x107F0F30
	// FUNCTION: ENGINE 0x107F0F60
	// FUNCTION: ENGINE 0x107F0F70
	// FUNCTION: ENGINE 0x107F0FA0
	// FUNCTION: ENGINE 0x107F0FB0
	// FUNCTION: ENGINE 0x107F0FE0
	// FUNCTION: ENGINE 0x107F0FF0
	// FUNCTION: ENGINE 0x107F1020
	// FUNCTION: ENGINE 0x107F1590
	// FUNCTION: ENGINE 0x107F15B0
	// FUNCTION: ENGINE 0x107F15E0
	// FUNCTION: ENGINE 0x107F1600
	// FUNCTION: ENGINE 0x107F1030
	// FUNCTION: ENGINE 0x107F1040
	// FUNCTION: ENGINE 0x107F1070
	// FUNCTION: ENGINE 0x107F1080
	// FUNCTION: ENGINE 0x107F0D70
	// FUNCTION: ENGINE 0x107F0DB0
}
