// engine::ScenarioTreeBehaviour: see the header.
#include "code/core/heap.h"
#include "code/engine/scenario/scenariotreebehaviour.h"
#include "code/engine/fight/fightbranchref.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/luascriptmanager.h"
#include <new>

namespace engine
{
	// The channel the behaviour listens on for the scenario's messages (0x11316A50; name guessed)
	MessageListeners gScenarioTreeListeners("scenario", 0);
	// Set when a sequencer was started (0x111D0611; name guessed)
	extern bool gScenarioTreeRunning;

	// The messages the behaviour answers or is told (message type 0xD, ids as the code reads them; names guessed)
	struct ScenarioStartMessage : public Message
	{
		unsigned char unknownC[0x10];
		fight::Branch* branch;  // +0x1C
		ScriptOwner* scriptOwner;  // +0x20
		int result;  // +0x24
	};

	struct ScenarioReferenceMessage : public Message
	{
		unsigned char unknownC[0x10];
		int reference;  // +0x1C
	};

	struct ScenarioPauseMessage : public Message
	{
		bool pause;  // +0xC
		bool clear;  // +0xD
	};

	struct ScenarioQueryMessage : public Message
	{
		void* answer;  // +0xC
	};

	// FUNCTION: ENGINE 0x10876770
	ScenarioTreeBehaviour::ScenarioTreeBehaviour(GameObject* newOwner)
		: Behaviour(newOwner), enabled(true), unknown1573(false), updating(false), paused(false), startBranch(0),
		queue(QUEUE_SIZE), root(0)
	{
		luaReference = 0;
		Listen2(2, true);
		Listen(0xd, true);
		Listen(0x17, true);
	}

	// FUNCTION: ENGINE 0x10876840
	ScenarioTreeBehaviour::ScenarioTreeBehaviour(GameObject* newOwner, fight::Branch* newRoot)
		: Behaviour(newOwner), enabled(true), unknown1573(false), updating(false), paused(false), startBranch(0),
		queue(QUEUE_SIZE), root(newRoot)
	{
		luaReference = 0;
		Listen2(2, true);
		Listen(0xd, true);
		Listen(0x17, true);
	}

	// FUNCTION: ENGINE 0x10876920
	ScenarioTreeBehaviour::~ScenarioTreeBehaviour()
	{
		LuaScriptManager* scriptManager = GetScriptManager();
		scriptManager->ReleaseReference(luaReference);
		luaReference = 0;
		ClearQueue();
		ResetSequencers();
	}

	// The caster the class meta type carries and the object the "scenarioRoot" member reads and writes the branch
	// through, kept out of line by their own instantiations.
	template struct content::BaseClassCasterImpl<Behaviour, ScenarioTreeBehaviour>;

	// FUNCTION: ENGINE 0x10876320
	// FUNCTION: ENGINE 0x10876330
	// FUNCTION: ENGINE 0x10876300
	template class FightBranchRefMemberGetSetter<ScenarioTreeBehaviour>;

	// FUNCTION: ENGINE 0x10876550
	// FUNCTION: ENGINE 0x108765B0
	content::MemberList* ScenarioTreeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, ScenarioTreeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ GetFightBranchRefMetaType<ScenarioTreeBehaviour>("Scenario", &ScenarioTreeBehaviour::GetRoot,
				&ScenarioTreeBehaviour::SetRoot, "p"), 0, "scenarioRoot" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10875EB0
	content::ClassInfo* ScenarioTreeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ScenarioTreeBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10875EF0
	void ScenarioTreeBehaviour::SetUnknown1573(bool value)
	{
		unknown1573 = value;
	}

	// FUNCTION: ENGINE 0x10875F00
	void ScenarioTreeBehaviour::SetAllUsed(int value)
	{
		for (int i = 0; i < SEQUENCER_COUNT; i++)
		{
			used[i] = value;
		}
	}

	// FUNCTION: ENGINE 0x10876090
	void ScenarioTreeBehaviour::SetRoot(fight::Branch* branch)
	{
		if (branch != root.branch)
		{
			if (root.branch != 0)
			{
				root.branch->Unregister(&root);
			}
			root.branch = branch;
			if (branch != 0)
			{
				branch->Register(&root);
			}
		}
	}

	// FUNCTION: ENGINE 0x108760F0
	void ScenarioTreeBehaviour::SetStartBranch(fight::Branch* branch)
	{
		if (branch != startBranch.branch)
		{
			if (startBranch.branch != 0)
			{
				startBranch.branch->Unregister(&startBranch);
			}
			startBranch.branch = branch;
			if (branch != 0)
			{
				branch->Register(&startBranch);
			}
		}
	}

	// FUNCTION: ENGINE 0x10876360
	fight::Branch* ScenarioTreeBehaviour::GetRoot() const
	{
		return root.branch;
	}

	// FUNCTION: ENGINE 0x10876370
	fight::Branch* ScenarioTreeBehaviour::GetStartBranch() const
	{
		return startBranch.branch;
	}

	// FUNCTION: ENGINE 0x108760C0
	bool ScenarioTreeBehaviour::ResetSequencers()
	{
		for (int i = 0; i < SEQUENCER_COUNT; i++)
		{
			sequencers[i].Reset();
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10876710
	void ScenarioTreeBehaviour::ClearQueue()
	{
		for (QueuedMessage* item = queue.begin; item != queue.end; item++)
		{
			((ScenarioMessage*)item)->~ScenarioMessage();
		}
		queue.Clear();
	}

	// FUNCTION: ENGINE 0x10876120
	// EQUIVALENT: scheduling only: the engine stores the running flag right before the virtual call, after loading the
	// branch's vftable, ours stores it first, 83.5 %
	int ScenarioTreeBehaviour::StartSequencer(fight::Branch* branch, ScriptOwner* scriptOwner)
	{
		if (branch == 0)
		{
			return -1;
		}
		int index = FindFree();
		if (index == -1)
		{
			return -1;
		}
		gScenarioTreeRunning = true;
		branch->Slot11(&sequencers[index], scriptOwner, 0);
		return index;
	}

	// FUNCTION: ENGINE 0x108761A0
	int ScenarioTreeBehaviour::CountBusy()
	{
		int count = 0;
		for (int i = 0; i < SEQUENCER_COUNT; i++)
		{
			if (sequencers[i].Unknown105A45A0(true))
			{
				count++;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x108761D0
	fight::Sequencer* ScenarioTreeBehaviour::GetBusy(unsigned int rank, unsigned int* index)
	{
		if (rank <= SEQUENCER_COUNT - 1)
		{
			int busy = -1;
			*index = (unsigned int)-1;
			for (unsigned int i = 0; i < SEQUENCER_COUNT; i++)
			{
				if (sequencers[i].Unknown105A45A0(true))
				{
					busy++;
				}
				if (busy >= (int)rank)
				{
					*index = i;
					break;
				}
			}
			if (*index != (unsigned int)-1)
			{
				return &sequencers[*index];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10876240
	bool ScenarioTreeBehaviour::AdvanceSequencer(unsigned int index, float dt)
	{
		if (index <= SEQUENCER_COUNT)
		{
			core::HeapScope scope(0x75);
			fight::Sequencer* sequencer = &sequencers[index];
			sequencer->Advance(1, dt);
			sequencer->Update(0);
			sequencer->Unknown105A4910(true);
			used[index] = false;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108764A0
	bool ScenarioTreeBehaviour::AdvanceUsed(float dt)
	{
		for (unsigned int i = 0; i < SEQUENCER_COUNT; i++)
		{
			if (used[i])
			{
				if (sequencers[i].Unknown105A45A0(true))
				{
					AdvanceSequencer(i, dt);
				}
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108764F0
	bool ScenarioTreeBehaviour::IsRunning(fight::Branch* branch)
	{
		for (unsigned int i = 0; i < SEQUENCER_COUNT; i++)
		{
			fight::Branch* running = sequencers[i].track;
			fight::Branch* pending = sequencers[i].pendingTrack;
			bool below = sequencers[i].Unknown105A4540(branch);
			if (branch == running || branch == pending || below)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10876380
	void ScenarioTreeBehaviour::OnPostedMessage(Message* message)
	{
		if (message->type == 0xd)
		{
			switch ((unsigned short)message->id)
			{
			case 8:
				((ScenarioQueryMessage*)message)->answer = root.branch;
				break;
			case 9:
				((ScenarioQueryMessage*)message)->answer = (void*)luaReference;
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x108763B0
	// EQUIVALENT: register allocation only: the engine keeps the owner, the message and the tree in eax / edx / ecx where
	// ours picks the other of the three, 95.6 %
	void ScenarioTreeBehaviour::Dispatch(ScenarioMessage* message, fight::Branch* tree, float dt)
	{
		ScriptOwner* scriptOwner = new (0x75) ScriptOwner(message, 2);
		scriptOwner->AddRef();
		scriptOwner->handle = GetHandle(owner);
		if (tree != 0)
		{
			SetStartBranch(0);
			for (fight::Branch* branch = tree->PickChild(0, scriptOwner); branch != 0;
				branch = branch->RunNext(0, scriptOwner, tree))
			{
				int index = StartSequencer(branch, scriptOwner);
				if (index != -1)
				{
					bool inside = false;
					if (branch == startBranch.branch || branch->IsBelow(startBranch.branch))
					{
						inside = true;
					}
					if (message->id == 1 || inside)
					{
						AdvanceSequencer(index, dt);
					}
				}
			}
		}
		scriptOwner->Release();
	}

	// FUNCTION: ENGINE 0x10876680
	void ScenarioTreeBehaviour::Update(float dt, unsigned short mask)
	{
		updating = true;
		SetAllUsed(1);
		QueuedMessage* item = queue.begin;
		QueuedMessage* last = queue.end;
		if (item != last)
		{
			do
			{
				Dispatch((ScenarioMessage*)item, root.branch, dt);
				((ScenarioMessage*)item)->~ScenarioMessage();
				item++;
			}
			while (item != last);
			queue.Discard(queue.begin, last);
		}
		AdvanceUsed(dt);
		updating = false;
	}

	// FUNCTION: ENGINE 0x10876A00
	void ScenarioTreeBehaviour::OnMessage(Message* message)
	{
		switch (message->type)
		{
		case 0x17:
			if (message->id == 3)
			{
				for (int i = 10; i >= 0; i--)
				{
					if (queue.IsEmpty())
					{
						break;
					}
					Update(0.0f, 2);
				}
			}
			break;
		case 0xd:
			switch ((unsigned short)message->id)
			{
			case 7:
				{
					ScenarioStartMessage* start = (ScenarioStartMessage*)message;
					int index = StartSequencer(start->branch, start->scriptOwner);
					if (index >= 0)
					{
						AdvanceSequencer(index, 0.0f);
					}
					start->result = index;
				}
				break;
			case 10:
				luaReference = ((ScenarioReferenceMessage*)message)->reference;
				break;
			case 0x12:
				paused = ((ScenarioPauseMessage*)message)->pause;
				if (((ScenarioPauseMessage*)message)->pause && ((ScenarioPauseMessage*)message)->clear)
				{
					ClearQueue();
					ResetSequencers();
				}
				break;
			default:
				if (IsActive() && !paused && !queue.IsFull())
				{
					((ScenarioMessage*)message)->Clone(queue.Grow(), 0x80);
				}
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x108769C0
	void ScenarioTreeBehaviour::Slot1()
	{
		SetAllUsed(1);
		ClearQueue();
		unknown1573 = false;
		GameObject* object = owner;
		GetHandle(object).RouterRemove(gScenarioTreeListeners);
	}
}

namespace engine
{
	core::Name<core::CaseSensitiveKey> gUndefinedSlotGroup4("Undefined_SlotGroup", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D75D80
// FUNCTION: ENGINE 0x10D8A780


// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D75DA0
// FUNCTION: ENGINE 0x10D8A790


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10875F70
// FUNCTION: ENGINE 0x10875F80
// FUNCTION: ENGINE 0x10875F90
// FUNCTION: ENGINE 0x10875FB0
// FUNCTION: ENGINE 0x10876010
// FUNCTION: ENGINE 0x10876020
// FUNCTION: ENGINE 0x10876030
// FUNCTION: ENGINE 0x10876670
// FUNCTION: ENGINE 0x10876750
// FUNCTION: ENGINE 0x10876B40
