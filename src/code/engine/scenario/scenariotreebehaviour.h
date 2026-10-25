// engine::ScenarioTreeBehaviour (RTTI and reflection name, vftable 0x10E74858, 9 slots, base engine::Behaviour): the
// behaviour that runs the scenario's fight tree. Scenario messages (type 0xD) reach it, are copied into a queue of
// 0x80-byte slots and, once a frame, are turned into script owners that walk the tree from its root: every branch
// the walk picks runs on a sequencer of its own (it has 75 of them). Unit 0x10875EB0 - 0x10876B60 (no assert path;
// the directory and file name are guesses). The reflected names ("scenarioRoot") are original, the rest is guessed.
#ifndef ENGINE_SCENARIO_SCENARIOTREEBEHAVIOUR_H
#define ENGINE_SCENARIO_SCENARIOTREEBEHAVIOUR_H

#include "code/container/arraydynamicnew.h"
#include "code/content/metatype.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/engine/scenario/scriptowner.h"
#include "code/engine/scenariomessage.h"

namespace engine
{
	// The room of one queued scenario message
	struct QueuedMessage
	{
		unsigned char storage[0x80];
	};

	// The scenario messages waiting for the next update
	class MessageQueue : public container::ArrayDynamicNew<QueuedMessage>
	{
	public:
		explicit MessageQueue(unsigned int count) : container::ArrayDynamicNew<QueuedMessage>(count)
		{
		}
		// 0x10497100 (another unit's copy): drops the messages between two places (they were destroyed already)
		void Discard(QueuedMessage* first, QueuedMessage* last);
	};

	// A sequencer slot: ends its sequencer when it goes
	struct SequencerSlot : public fight::Sequencer
	{
		~SequencerSlot()
		{
			End();
		}
	};

	class ScenarioTreeBehaviour : public Behaviour
	{
	public:
		// The sequencers a scenario can have running at once
		enum
		{
			SEQUENCER_COUNT = 75
		};
		// How many messages the queue has room for
		enum
		{
			QUEUE_SIZE = 96
		};

		// 0x10876770 (the second constructor, 0x10876840, starts with a root)
		explicit ScenarioTreeBehaviour(GameObject* newOwner);
		ScenarioTreeBehaviour(GameObject* newOwner, fight::Branch* newRoot);
		// 0x10876920 (deleting destructor 0x10876B40)
		virtual ~ScenarioTreeBehaviour();

		// 0x10875EB0 / 0x108765B0
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x108769C0): forgets what was queued and leaves the listener list
		virtual void Slot1();
		// vftable slot 4 (0x10876680): runs the queued messages, then the sequencers
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 5 (0x10876380): answers the queries for the root and the Lua reference
		virtual void OnPostedMessage(Message* message);
		// vftable slot 6 (0x10876A00)
		virtual void OnMessage(Message* message);
		// vftable slot 8 (0x108763B0): runs the tree for a scenario message
		virtual void Dispatch(ScenarioMessage* message, fight::Branch* root, float dt);

		// 0x10875EF0
		void SetUnknown1573(bool value);
		// 0x10875F00: marks every sequencer slot used or free
		void SetAllUsed(int value);
		// 0x108760F0 / 0x10876090: the branch the run started from / the root (both are watched by the branch)
		void SetStartBranch(fight::Branch* branch);
		void SetRoot(fight::Branch* branch);
		// 0x10876360 / 0x10876370
		fight::Branch* GetRoot() const;
		fight::Branch* GetStartBranch() const;
		// 0x108760C0: resets every sequencer
		bool ResetSequencers();
		// 0x10876710: destroys the queued messages
		void ClearQueue();
		// The first sequencer that is not busy (-1 for none)
		int FindFree()
		{
			for (unsigned int i = 0; i < SEQUENCER_COUNT; i++)
			{
				if (!sequencers[i].Unknown105A45A0(true))
				{
					return i;
				}
			}
			return -1;
		}
		// 0x10876120: puts the branch on a free sequencer, answers its index (-1 for none)
		int StartSequencer(fight::Branch* branch, ScriptOwner* scriptOwner);
		// 0x108761A0: how many sequencers are busy
		int CountBusy();
		// 0x108761D0: the busy sequencer of that rank, and its index
		fight::Sequencer* GetBusy(unsigned int rank, unsigned int* index);
		// 0x10876240: advances and updates a sequencer
		bool AdvanceSequencer(unsigned int index, float dt);
		// 0x108764A0: advances the sequencers that were used
		bool AdvanceUsed(float dt);
		// 0x108764F0: whether a sequencer runs the branch, has it pending or is below it
		bool IsRunning(fight::Branch* branch);

		bool enabled;  // +0xC
		SequencerSlot sequencers[SEQUENCER_COUNT];  // +0x10
		unsigned char used[SEQUENCER_COUNT];  // +0x1528
		bool unknown1573;
		bool updating;  // +0x1574
		bool paused;  // +0x1575
		unsigned char unknown1576[2];
		fight::BranchWatch startBranch;  // +0x1578
		MessageQueue queue;  // +0x1584
		int unknown1590;
		fight::BranchWatch root;  // +0x1594
		int luaReference;  // +0x15A0
	};
}

#endif
