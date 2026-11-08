// proto::ScenarioStateMachineBehaviour: see the header.
#include "code/proto/scenario/scenariostatemachinebehaviour.h"
#include "code/core/heap.h"
#include "code/engine/fight/fightbranchref.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luaenvironmentmessage.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/scenario/scriptowner.h"
#include "code/lua/lua.h"
#include "code/proto/messages/statemachinemessages.h"
#include <new>

namespace engine
{
	// 0x111C17D4: the name of the scenario fight context
	extern const char* const gScenarioContextName;
}

namespace proto
{
	// The object a handle names (null for none), as the engine's code expands it
	static inline engine::GameObject* Resolve(const engine::HandleBase& handle)
	{
		return handle.index != 0xffff && engine::GetGameObjectEntries()[handle.index].serial == handle.serial
			? engine::GetGameObjectEntries()[handle.index].object : 0;
	}

	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::State: a state of a state machine (the branch the machine is in); its
			// definition is with the scenario fight items
			class State : public fight::Branch
			{
			};
		}
	}

	// The messages of the state machine that only the machine reads or answers (ids as the code reads them; names guessed)
	struct StateMachineAnswerMessage : public engine::Message
	{
		void* first;  // +0xC
		void* second;  // +0x10
	};

	struct StateMachineParentMessage : public engine::Message
	{
		engine::HandleBase parent;  // +0xC
		fight::Branch* parentState;  // +0x10
	};

	struct StateMachineBufferMessage : public engine::Message
	{
		char* buffer;  // +0xC
		unsigned int size;  // +0x10
	};

	struct StateMachineNameMessage : public engine::Message
	{
		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// FUNCTION: ENGINE 0x104952F0
	content::ClassInfo* ScenarioStateMachineBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ScenarioStateMachineBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104958A0
	ScenarioStateMachineBehaviour::ScenarioStateMachineBehaviour(engine::GameObject* newOwner)
		: engine::ScenarioTreeBehaviour(newOwner), changePending(false), currentState(0), nextState(0), parentState(0),
		unknown15D8(0), phase(0), unknown15F4(false), infoText("/mission/FSM"), publicReference(0), started(false)
	{
		Listen(0x2d, true);
	}

	// FUNCTION: ENGINE 0x104955F0
	ScenarioStateMachineBehaviour::~ScenarioStateMachineBehaviour()
	{
		engine::LuaScriptManager* scriptManager = engine::GetScriptManager();
		scriptManager->ReleaseReference(publicReference);
		publicReference = 0;
	}

	// FUNCTION: ENGINE 0x10495530
	fight::Branch* ScenarioStateMachineBehaviour::GetCurrentState() const
	{
		return currentState.branch;
	}

	// FUNCTION: ENGINE 0x10495540
	fight::Branch* ScenarioStateMachineBehaviour::GetNextState() const
	{
		return nextState.branch;
	}

	// FUNCTION: ENGINE 0x104951E0
	void ScenarioStateMachineBehaviour::SetCurrentState(fight::Branch* state)
	{
	}

	// FUNCTION: ENGINE 0x104951F0
	void ScenarioStateMachineBehaviour::SetNextState(fight::Branch* state)
	{
	}

	// FUNCTION: ENGINE 0x104956A0
	void ScenarioStateMachineBehaviour::ChangeState(fight::Branch* state, fight::Branch* next)
	{
		if (!changePending || state == 0)
		{
			if (state != nextState.branch)
			{
				if (nextState.branch != 0)
				{
					nextState.branch->Unregister(&nextState);
				}
				nextState.branch = state;
				if (state != 0)
				{
					state->Register(&nextState);
				}
			}
			changePending = true;
			if (next != 0)
			{
				if (next != unknown15D8.branch)
				{
					if (unknown15D8.branch != 0)
					{
						unknown15D8.branch->Unregister(&unknown15D8);
					}
					unknown15D8.branch = next;
					next->Register(&unknown15D8);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10495340
	void ScenarioStateMachineBehaviour::GetModeName(char* buffer, unsigned int size)
	{
		if (buffer != 0)
		{
			core::StrNCpy(buffer, "--Release--", size);
		}
	}

	// FUNCTION: ENGINE 0x10495370
	void ScenarioStateMachineBehaviour::GetOtherModeName(char* buffer, unsigned int size)
	{
		if (buffer != 0)
		{
			core::StrNCpy(buffer, "--Release--", size);
		}
	}

	// FUNCTION: ENGINE 0x10495EA0
	void ScenarioStateMachineBehaviour::SetInfoText(const char* text)
	{
		infoText = text;
	}

	// FUNCTION: ENGINE 0x10496AF0
	ScenarioStateMachineBehaviour::ScenarioStateMachineBehaviour(engine::GameObject* newOwner, fight::Branch* newRoot,
		engine::GameObjectHandle newParent, const char* argumentsTable, fight::Branch* newParentState)
		: engine::ScenarioTreeBehaviour(newOwner, newRoot), unknown15B0(false), changePending(false), currentState(0),
		nextState(0), parentState(newParentState), unknown15D8(0), parent(newParent), phase(0), unknown15F4(false),
		infoText("/mission/FSM"), publicReference(0), started(false)
	{
		Listen(0x2d, true);
		CreateLuaEnvironment(argumentsTable);
	}

	// FUNCTION: ENGINE 0x10495740
	// NONMATCHING: 98.4 %: the virtual release call loads the vftable into eax in the engine, edx in ours
#ifdef NONMATCHING
	void ScenarioStateMachineBehaviour::Start()
	{
		int savedPhase = phase;
		phase = 3;
		engine::ScriptOwner* scriptOwner = new engine::ScriptOwner(
			&const_cast<engine::NullMessage&>((const engine::NullMessage&)engine::NullMessage()), 2);
		scriptOwner->AddRef();
		scriptOwner->handle = engine::GetHandle(owner);
		fight::Branch* tree = root.branch;
		int index = StartSequencer(tree, scriptOwner);
		AdvanceSequencer(index, 0.0f);
		scriptOwner->Release();
		phase = savedPhase;
	}
#endif

	// FUNCTION: ENGINE 0x10495CF0
	void ScenarioStateMachineBehaviour::CreateLuaEnvironment(const char* argumentsTable)
	{
		engine::GameObject* parentObject = Resolve(parent);
		if (parentObject != 0)
		{
			engine::LuaScriptManager* script = engine::GetScriptManager();
			lua_State* L = script->state;
			lua_createtable(L, 0, 1);
			lua_createtable(L, 0, 1);
			engine::GetLuaEnvironmentMessage message;
			parentObject->PostMessage(&message);
			int environment = message.reference;
			script->PushReference(environment);
			lua_setfield(L, -2, "__index");
			lua_setmetatable(L, -2);
			script->PushReference(environment);
			lua_setfield(L, -2, "_Parent");
			lua_pushvalue(L, -1);
			lua_setfield(L, -2, "_Self");
			if (argumentsTable != 0 && script->OpenTable(argumentsTable, true, false))
			{
				lua_setfield(L, -2, "_Args");
			}
			lua_createtable(L, 0, 1);
			lua_pushvalue(L, -1);
			publicReference = script->MakeReference();
			lua_setfield(L, -2, "_Public");
			luaReference = script->MakeReference();
		}
	}

	// FUNCTION: ENGINE 0x10495F00
	// NONMATCHING: 76 %: shrink-wrap, the engine pushes esi before the first handle test
#ifdef NONMATCHING
	void ScenarioStateMachineBehaviour::SendToChildren(engine::Message* message)
	{
		engine::GameObject* child = Resolve(firstChild);
		if (child != 0)
		{
			do
			{
				child->SendMessage(message);
				StateMachineGetFirstSiblingMessage siblingMessage;
				child->SendMessage(&siblingMessage);
				child = Resolve(siblingMessage.sibling);
			}
			while (child != 0);
		}
	}
#endif

	// Looks the branch of a recorded path up in the scenario's tree and makes the watch follow it
	static inline void RestoreWatch(fight::BranchWatch& watch, container::String& path, fight::TrackRegistry* context)
	{
		if (path.ConstData() != 0)
		{
			fight::Branch* found = context->branches->FindInTree(path.ConstData());
			if (found != watch.branch)
			{
				if (watch.branch != 0)
				{
					watch.branch->Unregister(&watch);
				}
				watch.branch = found;
				if (found != 0)
				{
					found->Register(&watch);
				}
			}
		}
	}

	// Writes the path of a branch of the machine into a string of the record
#define WRITE_PATH(field, watch) 	{ 		unsigned int size = watch.branch->GetPathLength(0) + 1; 		((StateMachineRecord*)message->stream)->field.Allocate(size); 		container::String& string = ((StateMachineRecord*)message->stream)->field; 		watch.branch->GetPath(string.Data(), size, 0); 	}

	// FUNCTION: ENGINE 0x104962C0
	// NONMATCHING: 27 %: registers of the machine, the message and the path size, the engine loads the branch before the buffer
#ifdef NONMATCHING
	void ScenarioStateMachineBehaviour::Serialize(StateMachineSerializeMessage* message)
	{
		((StateMachineRecord*)message->stream)->name = name;
		if (root.branch != 0)
		{
			WRITE_PATH(rootPath, root)
		}
		if (currentState.branch != 0)
		{
			WRITE_PATH(currentPath, currentState)
		}
		if (nextState.branch != 0)
		{
			WRITE_PATH(nextPath, nextState)
		}
		if (parentState.branch != 0)
		{
			WRITE_PATH(parentPath, parentState)
		}
		if (unknown15D8.branch != 0)
		{
			WRITE_PATH(unknownPath, unknown15D8)
		}
		engine::GameObject* parentObject = Resolve(parent);
		if (parentObject == engine::GetMasterScenarioObject())
		{
			((StateMachineRecord*)message->stream)->parentName = engine::gMasterScenario;
		}
		else
		{
			((StateMachineRecord*)message->stream)->parentName =
				engine::GetGameObjectName(static_cast<const engine::GameObjectHandle&>(parent));
		}
		((StateMachineRecord*)message->stream)->firstChildName =
			engine::GetGameObjectName(static_cast<const engine::GameObjectHandle&>(firstChild));
		((StateMachineRecord*)message->stream)->firstSiblingName =
			engine::GetGameObjectName(static_cast<const engine::GameObjectHandle&>(firstSibling));
		((StateMachineRecord*)message->stream)->phase = phase;
		((StateMachineRecord*)message->stream)->changePending = changePending;
		((StateMachineRecord*)message->stream)->started = started;
	}
#endif
#undef WRITE_PATH

	// FUNCTION: ENGINE 0x104965E0
	// NONMATCHING: 22.6 %: registers and the order of the lookups
#ifdef NONMATCHING
	void ScenarioStateMachineBehaviour::Unserialize(StateMachineUnserializeMessage* message)
	{
		fight::TrackRegistry* context = engine::gLoadListeners->FindContext(
			core::Name<core::CaseSensitiveKey>(engine::gScenarioContextName, 1));
		ClearAll();
		started = ((StateMachineRecord*)message->stream)->started;
		RestoreWatch(parentState, ((StateMachineRecord*)message->stream)->parentPath, context);
		RestoreWatch(root, ((StateMachineRecord*)message->stream)->rootPath, context);
		RestoreWatch(currentState, ((StateMachineRecord*)message->stream)->currentPath, context);
		if (unknown15D8.branch != 0)
		{
			unknown15D8.branch->Unregister(&unknown15D8);
			unknown15D8.branch = 0;
		}
		changePending = ((StateMachineRecord*)message->stream)->changePending;
		RestoreWatch(nextState, ((StateMachineRecord*)message->stream)->nextPath, context);
		parent = engine::FindGameObject(((StateMachineRecord*)message->stream)->parentName,
			*(const content::ObjectName*)"");
		firstChild = engine::FindGameObject(((StateMachineRecord*)message->stream)->firstChildName,
			*(const content::ObjectName*)"");
		firstSibling = engine::FindGameObject(((StateMachineRecord*)message->stream)->firstSiblingName,
			*(const content::ObjectName*)"");
		phase = 0;
		CreateLuaEnvironment(0);
		Start();
	}
#endif

	// FUNCTION: ENGINE 0x10495FF0
	// NONMATCHING: 97.7 %: the engine keeps the previous child in edi and the message type 0x2D in ebp, ours the other way round
#ifdef NONMATCHING
	void ScenarioStateMachineBehaviour::PruneChildren(bool removeAll)
	{
		engine::GameObject* child = Resolve(firstChild);
		engine::GameObject* previous = 0;
		engine::GameObject* first = 0;
		while (child != 0)
		{
			bool remove = true;
			if (!removeAll)
			{
				StateMachineGetParentMessage parentMessage;
				child->SendMessage(&parentMessage);
				remove = parentMessage.unknown10 != 0;
			}
			StateMachineGetFirstSiblingMessage siblingMessage;
			child->SendMessage(&siblingMessage);
			engine::GameObject* next = Resolve(siblingMessage.sibling);
			if (remove)
			{
				StateMachineSetStateMessage stateMessage;
				child->SendMessage(&stateMessage);
				StateMachineSetFirstSiblingMessage clearMessage;
				engine::HandleBase none;
				clearMessage.sibling = none;
				child->SendMessage(&clearMessage);
			}
			else
			{
				if (first == 0)
				{
					first = child;
				}
				if (previous != 0)
				{
					StateMachineSetFirstSiblingMessage linkMessage(engine::GetHandle(child));
					previous->SendMessage(&linkMessage);
				}
				previous = child;
			}
			child = next;
		}
		firstChild = engine::GetHandle(first);
		if (previous != 0)
		{
			StateMachineSetFirstSiblingMessage endMessage;
			engine::HandleBase none;
			endMessage.sibling = none;
			previous->SendMessage(&endMessage);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10495A10
	// NONMATCHING: 99.5 %: the virtual release call loads the vftable into eax in the engine, edx in ours
#ifdef NONMATCHING
	void ScenarioStateMachineBehaviour::Slot1()
	{
		engine::ScenarioTreeBehaviour::Slot1();
		if (unknown15B0)
		{
			unknown15B0 = false;
			return;
		}
		StateMachineGetFirstChildMessage getChildMessage;
		Resolve(parent)->SendMessage(&getChildMessage);
		engine::GameObject* previousChild = Resolve(getChildMessage.child);
		StateMachineSetFirstChildMessage setChildMessage(engine::GetHandle(owner));
		Resolve(parent)->SendMessage(&setChildMessage);
		if (previousChild != 0)
		{
			StateMachineSetFirstSiblingMessage setSiblingMessage(engine::GetHandle(previousChild));
			owner->SendMessage(&setSiblingMessage);
		}
		fight::Branch* initial = 0;
		fight::Branch* child = root.branch->firstChild;
		while (child != 0 && initial == 0)
		{
			initial = dynamic_cast<fightitems::scenario::State*>(child);
			if (initial == 0)
			{
				child = child->nextSibling;
			}
		}
		if (initial != 0)
		{
			phase = 1;
			engine::ScriptOwner* scriptOwner = new engine::ScriptOwner(
				&const_cast<engine::NullMessage&>((const engine::NullMessage&)engine::NullMessage()), 2);
			scriptOwner->AddRef();
			scriptOwner->handle = engine::GetHandle(owner);
			fight::Branch* tree = root.branch;
			int index = StartSequencer(tree, scriptOwner);
			AdvanceSequencer(index, 1.0f);
			phase = 0;
			scriptOwner->Release();
		}
		ChangeState(initial, 0);
	}
#endif

	// FUNCTION: ENGINE 0x10497150
	void ScenarioStateMachineBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 0x2d:
			switch ((unsigned short)message->id)
			{
			case 0:
				((StateMachineAnswerMessage*)message)->first = currentState.branch;
				break;
			case 1:
				ChangeState(((StateMachineSetStateMessage*)message)->state, ((StateMachineSetStateMessage*)message)->nextState);
				break;
			case 2:
				((StateMachineGetFirstChildMessage*)message)->child = firstChild;
				break;
			case 3:
				firstChild = ((StateMachineSetFirstChildMessage*)message)->child;
				break;
			case 4:
				((StateMachineGetFirstSiblingMessage*)message)->sibling = firstSibling;
				break;
			case 5:
				firstSibling = ((StateMachineSetFirstSiblingMessage*)message)->sibling;
				break;
			case 8:
				GetModeName(((StateMachineBufferMessage*)message)->buffer, ((StateMachineBufferMessage*)message)->size);
				break;
			case 10:
				GetOtherModeName(((StateMachineBufferMessage*)message)->buffer, ((StateMachineBufferMessage*)message)->size);
				break;
			case 9:
				{
					StateMachineGetLastTransitionMessage* transitionMessage = (StateMachineGetLastTransitionMessage*)message;
					fight::Branch* transition = unknown15D8.branch;
					fight::BranchWatch* watch = &transitionMessage->transition;
					if (transition != watch->branch)
					{
						if (watch->branch != 0)
						{
							watch->branch->Unregister(watch);
						}
						watch->branch = transition;
						if (transition != 0)
						{
							transition->Register(watch);
						}
					}
				}
				break;
			case 7:
				((StateMachineParentMessage*)message)->parent = parent;
				((StateMachineParentMessage*)message)->parentState = parentState.branch;
				break;
			case 6:
				parent = ((StateMachineParentMessage*)message)->parent;
				parentState.Assign(((StateMachineParentMessage*)message)->parentState);
				break;
			case 0xb:
				((StateMachineAnswerMessage*)message)->first = (void*)phase;
				break;
			case 0xc:
				unknown15F4 = ((StateMachineSetInfoMessageProperties*)message)->enabled;
				infoText = ((StateMachineSetInfoMessageProperties*)message)->text;
				break;
			case 0x12:
				unknown15B0 = true;
				break;
			case 0x13:
				Start();
				break;
			case 0xd:
				owner->SendMessage(((StateMachinePropagateMessage*)message)->message);
				SendToChildren(message);
				break;
			case 0xe:
				Serialize((StateMachineSerializeMessage*)message);
				break;
			case 0xf:
				Unserialize((StateMachineUnserializeMessage*)message);
				break;
			case 0x10:
				((StateMachineNameMessage*)message)->name = name;
				break;
			case 0x11:
				name = ((StateMachineNameMessage*)message)->name;
				break;
			case 0x14:
				((GetPublicLuaEnvironmentMessage*)message)->reference = publicReference;
				break;
			case 0x15:
				ChangeState(0, 0);
				Advance(0.0f);
				break;
			}
			break;
		case 0xd:
			engine::ScenarioTreeBehaviour::OnMessage(message);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10497420
	void ScenarioStateMachineBehaviour::Update(float dt, unsigned short mask)
	{
		if (started)
		{
			engine::GetHandle(owner).DeferUpdate(true);
			return;
		}
		Advance(dt);
		if (currentState.branch == 0)
		{
			ClearQueue();
			return;
		}
		SetAllUsed(1);
		engine::QueuedMessage* item = queue.begin;
		engine::QueuedMessage* last = queue.end;
		if (item != last)
		{
			do
			{
				Dispatch((engine::ScenarioMessage*)item, root.branch, dt);
				Dispatch((engine::ScenarioMessage*)item, currentState.branch, dt);
				((engine::ScenarioMessage*)item)->~ScenarioMessage();
				item++;
			}
			while (item != last);
			queue.Discard(queue.begin, last);
		}
		AdvanceUsed(dt);
	}

	// The caster the class meta type carries and the object the "currentState" and "nextState" members read and write
	// the branches through, kept out of line by their own instantiations.
	// FUNCTION: ENGINE 0x104955B0
	// FUNCTION: ENGINE 0x104955C0
	template struct content::BaseClassCasterImpl<engine::ScenarioTreeBehaviour, ScenarioStateMachineBehaviour>;

	// FUNCTION: ENGINE 0x10495830
	// FUNCTION: ENGINE 0x10495850
	// FUNCTION: ENGINE 0x10495870
	template class engine::FightBranchRefMemberGetSetter<ScenarioStateMachineBehaviour>;

	// FUNCTION: ENGINE 0x104968E0
	template content::MetaType* engine::GetFightBranchRefMetaTypeAt<ScenarioStateMachineBehaviour, 0>(const char*,
		fight::Branch* (ScenarioStateMachineBehaviour::*)() const, void (ScenarioStateMachineBehaviour::*)(fight::Branch*),
		const char*);

	// FUNCTION: ENGINE 0x10496950
	template content::MetaType* engine::GetFightBranchRefMetaTypeAt<ScenarioStateMachineBehaviour, 1>(const char*,
		fight::Branch* (ScenarioStateMachineBehaviour::*)() const, void (ScenarioStateMachineBehaviour::*)(fight::Branch*),
		const char*);

	// FUNCTION: ENGINE 0x104969D0
	content::MemberList* ScenarioStateMachineBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::ScenarioTreeBehaviour>();
		static content::BaseClassCasterImpl<engine::ScenarioTreeBehaviour, ScenarioStateMachineBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ engine::GetFightBranchRefMetaTypeAt<ScenarioStateMachineBehaviour, 0>("Scenario",
				&ScenarioStateMachineBehaviour::GetCurrentState, &ScenarioStateMachineBehaviour::SetCurrentState, "p"), 0,
				"currentState" },
			{ engine::GetFightBranchRefMetaTypeAt<ScenarioStateMachineBehaviour, 1>("Scenario",
				&ScenarioStateMachineBehaviour::GetNextState, &ScenarioStateMachineBehaviour::SetNextState, "p"), 0,
				"nextState" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10495440
	template content::ClassMetaType* content::GetClassMetaType<engine::ScenarioTreeBehaviour>();
}
