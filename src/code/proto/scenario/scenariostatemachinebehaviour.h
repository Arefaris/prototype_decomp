// proto::ScenarioStateMachineBehaviour (RTTI and reflection name, vftable 0x10E0B920, 9 slots, base
// engine::ScenarioTreeBehaviour, 0x1688 bytes): a state machine of the scenario. Its states are branches of the scenario
// tree; the machines of a mission form a tree of their own through the first child / first sibling / parent handles
// they keep, and they answer the messages of type 0x2D (the state machine messages). Unit 0x10495170 - 0x10497530
// (no assert path; the directory and file names are guesses). The names of the members are guesses.
#ifndef PROTO_SCENARIO_SCENARIOSTATEMACHINEBEHAVIOUR_H
#define PROTO_SCENARIO_SCENARIOSTATEMACHINEBEHAVIOUR_H

#include "code/container/string.h"
#include "code/container/stringdynamicnew.h"
#include "code/core/name.h"
#include "code/engine/fight/branch.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/scenario/scenariotreebehaviour.h"

namespace proto
{
	struct StateMachineSerializeMessage;
	struct StateMachineUnserializeMessage;

	// What a state machine writes of itself for a checkpoint (0x78 bytes; the layout is from Serialize / Unserialize, the
	// names are guesses): the paths of its branches and the names of the objects it is linked to
	struct StateMachineRecord
	{
		StateMachineRecord(const container::AllocatorNew& allocator) : rootPath(allocator), currentPath(allocator),
			nextPath(allocator), parentPath(allocator), unknownPath(allocator)
		{
		}

		core::Name<core::CaseSensitiveKey> name;  // +0x0
		container::StringDynamic<container::AllocatorNew> rootPath;  // +0x8
		container::StringDynamic<container::AllocatorNew> currentPath;  // +0x18
		container::StringDynamic<container::AllocatorNew> nextPath;  // +0x28
		container::StringDynamic<container::AllocatorNew> parentPath;  // +0x38
		container::StringDynamic<container::AllocatorNew> unknownPath;  // +0x48
		core::Name<core::CaseSensitiveKey> parentName;  // +0x58
		core::Name<core::CaseSensitiveKey> firstChildName;  // +0x60
		core::Name<core::CaseSensitiveKey> firstSiblingName;  // +0x68
		int phase;  // +0x70
		bool changePending;  // +0x74
		bool started;  // +0x75
	};

	class ScenarioStateMachineBehaviour : public engine::ScenarioTreeBehaviour
	{
	public:
		// 0x104958A0
		explicit ScenarioStateMachineBehaviour(engine::GameObject* newOwner);
		// 0x10496AF0: a machine with the root branch of its states, the handle of its parent, the Lua table of its arguments
		// and the branch of the parent's state it belongs to
		ScenarioStateMachineBehaviour(engine::GameObject* newOwner, fight::Branch* newRoot, engine::GameObjectHandle newParent,
			const char* argumentsTable, fight::Branch* newParentState);
		// 0x104955F0 (the deleting destructor is 0x104959E0)
		virtual ~ScenarioStateMachineBehaviour();

		// 0x104952F0 / 0x10496? (the members are in GetMembers, 0x104969D0)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10495A10): resets the machine: starts the first state (the machine's own tree) and sends the
		// first child and sibling to the new state's machine
		virtual void Slot1();
		// vftable slot 4 (0x10497420)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10497150): the messages of types 0xD and 0x2D
		virtual void OnMessage(engine::Message* message);

		// 0x10495530 / 0x10495540: the state the machine is in / the one it goes to next (the setters do nothing)
		fight::Branch* GetCurrentState() const;
		fight::Branch* GetNextState() const;
		void SetCurrentState(fight::Branch* state);
		void SetNextState(fight::Branch* state);
		// 0x104956A0: puts the machine into a state
		void ChangeState(fight::Branch* state, fight::Branch* next);
		// 0x10495740: runs the root once with a null message
		void Start();
		// 0x10495CF0: makes the Lua tables the states' scripts run in (the arguments table is looked up by name)
		void CreateLuaEnvironment(const char* argumentsTable);
		// 0x10495340 / 0x10495370: copies the name of the mode into the buffer
		void GetModeName(char* buffer, unsigned int size);
		void GetOtherModeName(char* buffer, unsigned int size);
		// 0x10495EA0: sets the info text
		void SetInfoText(const char* text);
		// 0x10495F00: sends a message to every sibling of the first child, in turn
		void SendToChildren(engine::Message* message);
		// 0x10495FF0: takes the children that have no parent state out of the chain (all of them when the flag is set)
		void PruneChildren(bool removeAll);
		// 0x104962C0 / 0x104965E0: writes the machine's state to / reads it from a stream
		void Serialize(StateMachineSerializeMessage* message);
		void Unserialize(StateMachineUnserializeMessage* message);
		// 0x10496C50: moves the machine to the state it was told to go to
		void Advance(float dt);

		core::Name<core::CaseSensitiveKey> name;  // +0x15A8
		bool unknown15B0;
		bool changePending;  // +0x15B1
		fight::BranchWatch currentState;  // +0x15B4
		fight::BranchWatch nextState;  // +0x15C0
		fight::BranchWatch parentState;  // +0x15CC
		fight::BranchWatch unknown15D8;  // +0x15D8
		engine::HandleBase parent;  // +0x15E4
		engine::HandleBase firstChild;  // +0x15E8
		engine::HandleBase firstSibling;  // +0x15EC
		int phase;  // +0x15F0
		bool unknown15F4;
		container::StringC<128> infoText;  // +0x15F8
		int publicReference;  // +0x167C
		bool started;  // +0x1680
	};
}

#endif
