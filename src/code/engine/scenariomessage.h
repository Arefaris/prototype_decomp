// engine::ScenarioMessage and the engine's own scenario messages (names from the RTTI). A scenario message is an
// IntrusiveMessage of type 0xD whose id is the event number; it carries up to four object handles and the class's own
// fields after them, and writes them into the script's context.event table (vftable slot 2, slot 3 per class).
// Slot 1 copies the message into caller memory. The unit (0x107F09D0 - 0x107F1960, no assert path) is named
// scenariomessage.cpp here; the base constructor and WriteFields are in another unit.
#ifndef ENGINE_SCENARIOMESSAGE_H
#define ENGINE_SCENARIOMESSAGE_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/engine/luascriptmanager.h"
#include <new>

namespace engine
{
	// The handles a message class carries: their number, then the names of the handles in the editor (20 bytes)
	struct ScenarioHandleInfo
	{
		unsigned int count;
		const char* names[4];
	};

	struct ScenarioMessage : public IntrusiveMessage
	{
		enum
		{
			HANDLE_COUNT = 4
		};

		// 0x10075450 (another unit): type 0xD, id = the event number
		explicit ScenarioMessage(int event);
		virtual ~ScenarioMessage()
		{
		}

		// Constructs a copy in memory (null: none); the second argument is not used
		virtual ScenarioMessage* Clone(void* memory, int unused) = 0;
		virtual bool WriteEvent();
		// 0x10007C2A (the incremental link thunk of the other unit's copy)
		virtual void WriteFields(LuaScriptManager* context);

		GameObjectHandle GetHandle(unsigned int index) const;
		void SetHandle(unsigned int index, GameObjectHandle handle);

		GameObjectHandle handles[HANDLE_COUNT];
		int unknown1C;
	};

	struct NullMessage : ScenarioMessage
	{
		NullMessage() : ScenarioMessage(0)
		{
		}
		virtual ~NullMessage()
		{
		}
		virtual ScenarioMessage* Clone(void* memory, int unused);
	};

	struct ScenarioInitializeMessage : ScenarioMessage
	{
		ScenarioInitializeMessage() : ScenarioMessage(1)
		{
		}
		virtual ~ScenarioInitializeMessage()
		{
		}
		virtual ScenarioMessage* Clone(void* memory, int unused);

		// 0x1082FAD0
		static ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static ScenarioHandleInfo sHandleInfo;
	};

	struct StringMessage : ScenarioMessage
	{
		explicit StringMessage(const core::Name<core::CaseSensitiveKey>& value);
		virtual ~StringMessage()
		{
		}
		virtual ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(LuaScriptManager* context);

		static ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static ScenarioHandleInfo sHandleInfo;
		core::Name<core::CaseSensitiveKey> string;
	};

	struct TriggerMessage : ScenarioMessage
	{
		explicit TriggerMessage(int event);
		virtual ~TriggerMessage()
		{
		}
	};

	struct EnterTriggerMessage : TriggerMessage
	{
		EnterTriggerMessage() : TriggerMessage(3)
		{
		}
		virtual ~EnterTriggerMessage()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		virtual ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(LuaScriptManager* context);

		static ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static ScenarioHandleInfo sHandleInfo;
		core::Name<core::CaseSensitiveKey> extraString;
	};

	struct ExitTriggerMessage : TriggerMessage
	{
		ExitTriggerMessage() : TriggerMessage(4)
		{
		}
		virtual ~ExitTriggerMessage()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		virtual ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(LuaScriptManager* context);

		static ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static ScenarioHandleInfo sHandleInfo;
		core::Name<core::CaseSensitiveKey> extraString;
	};

	struct ObjectDestroyedMessage : ScenarioMessage
	{
		ObjectDestroyedMessage() : ScenarioMessage(5)
		{
		}
		virtual ~ObjectDestroyedMessage()
		{
		}
		virtual ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(LuaScriptManager* context);

		static ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static ScenarioHandleInfo sHandleInfo;
	};

	struct ObjectStateChangedMessage : ScenarioMessage
	{
		ObjectStateChangedMessage() : ScenarioMessage(6)
		{
		}
		virtual ~ObjectStateChangedMessage()
		{
		}
		virtual ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(LuaScriptManager* context);

		static ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static ScenarioHandleInfo sHandleInfo;
		core::Name<core::CaseSensitiveKey> newState;
	};

	// The messages that carry one name: the NIS events (field "NISName") and the stream package events
	// ("packageName")
#define ENGINE_NAMED_SCENARIO_MESSAGE(Class, event) \
	struct Class : ScenarioMessage \
	{ \
		explicit Class(core::Name<core::CaseSensitiveKey> newName) : ScenarioMessage(event), name(newName) \
		{ \
		} \
		virtual ScenarioMessage* Clone(void* memory, int unused); \
		virtual void WriteFields(LuaScriptManager* context); \
\
		static ScenarioHandleInfo GetHandleInfo() \
		{ \
			return sHandleInfo; \
		} \
\
		static ScenarioHandleInfo sHandleInfo; \
		core::Name<core::CaseSensitiveKey> name; \
	};

	ENGINE_NAMED_SCENARIO_MESSAGE(ScenarioNISBeginMessage, 0xb)
	ENGINE_NAMED_SCENARIO_MESSAGE(ScenarioNISEndMessage, 0xc)
	ENGINE_NAMED_SCENARIO_MESSAGE(ScenarioNISLoadCompleteMessage, 0xd)
	ENGINE_NAMED_SCENARIO_MESSAGE(ScenarioNISStallMessage, 0xe)
	ENGINE_NAMED_SCENARIO_MESSAGE(ScenarioNISResumeMessage, 0xf)
	ENGINE_NAMED_SCENARIO_MESSAGE(ScenarioStreamPackageLoadedMessage, 0x10)
	ENGINE_NAMED_SCENARIO_MESSAGE(ScenarioStreamPackageUnloadedMessage, 0x11)

#undef ENGINE_NAMED_SCENARIO_MESSAGE
}

#endif
