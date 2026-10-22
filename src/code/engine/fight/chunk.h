// The branches a fight file is made of (RTTI: fight::Reference, fight::Chunk, fight::Bank, fight::Store and fight::Node,
// each with the 18 vftable slots of a fight::Branch and the 2 of its fight::Param), the action that starts a branch once
// a chunk is loaded (fight::QueuedBranchAction) and the notes a chunk keeps for what waits for it. Unit 0x105A2440 -
// 0x105B3680 (no assert path; the file name is a guess). Names are guesses.
#ifndef ENGINE_FIGHT_CHUNK_H
#define ENGINE_FIGHT_CHUNK_H

#include "code/engine/fight/branch.h"
#include "code/engine/fight/trackfactory.h"

namespace fight
{
	// A branch that stands for another one (named in its own 'reference' property): running it runs the branch it
	// names, when its conditions hold
	class Reference : public Branch
	{
	public:
		// 0x105AA3A0
		Reference();
		// vftable slot 2 (0x105AA4F0 is the deleting destructor, 0x105AA3E0 the body)
		virtual ~Reference();

		// vftable slot 10 (0x105AA480)
		virtual Branch* Slot10(Sequencer* sequencer, void* params, int a, bool b);
		// vftable slot 0 of the Param part (0x105AA380)
		virtual Property* GetProperty(int index);

		// 0x105AA360 / 0x105AA370: the members the properties hand out
		BranchHolder* GetTarget();
		ConditionList* GetConditions();
		// 0x105AA410: the branch the reference leads to, following references that lead to references (null when it
		// goes in circles or nowhere)
		Branch* ResolveTarget();

		// 0x105AA630 / 0x105AA390: the properties of the class, built once / freed
		static void RegisterProperties();
		static void ClearProperties();

		BranchHolder target;  // +0x28
		ConditionList conditions;  // +0x4C
		unsigned int running;  // +0x50: set while the branch it names is run
	};

	// The note a chunk keeps of a branch and the item that wants to hear when the chunk is loaded (12 bytes)
	struct ChunkNotification
	{
		// 0x105AA9E0 (the engine keeps a copy)
		ChunkNotification(Branch* newBranch, Item* newItem)
			: branch(newBranch), item(newItem), next(0)
		{
		}

		Branch* branch;
		Item* item;
		ChunkNotification* next;  // +8
	};

	// The root branch of a loaded fight file (RTTI: fight::Chunk): hangs below the context's tree once it is read
	class Chunk : public Branch
	{
	public:
		// 0x105AAA00
		Chunk();
		// vftable slot 2 (0x105AAE90 is the deleting destructor, 0x105AAE30 the body)
		virtual ~Chunk();

		// vftable slot 3 (0x105AACE0): the chunk is loaded - it takes its place in the context's tree and tells what
		// waited for it
		virtual void Slot3(int argument);
		// vftable slot 4 (0x105AADB0): lets the chunk go from the tree
		virtual bool IsReady();
		// vftable slot 5 (0x105AAA30)
		virtual bool IsChunkRoot() const;
		// vftable slot 6 (0x105AAA40)
		virtual TrackRegistry* Slot6();
		// vftable slot 13 (0x105AAB90)
		virtual bool Slot13(const core::Name<core::CaseSensitiveKey>* key, Chunk* owner, Reader* reader, int position);
		// vftable slot 17 (0x105AAA50)
		virtual void Slot17(Branch* other, int argument);

		// 0x105AAAB0: the index the next branch of the chunk gets
		int NextIndex();
		// 0x105AAAC0: asks to be told when the chunk is loaded
		void AddNotification(Branch* branch, Item* item);
		// 0x105AAB30 / 0x105AAB50: puts a chunk of the same name below this one in the order it is loaded / takes it out
		void AddDependent(Chunk* chunk);
		void RemoveDependent(Chunk* chunk);

		TrackRegistry* context;  // +0x28
		// The last index handed out to a branch of the chunk (0x105AAAB0 counts it up)
		int indexCounter;  // +0x2C
		int offset;  // +0x30: where the chunk is put among the children of the tree's root
		Chunk* pendingNext;  // +0x34: the next chunk of the context's list of chunks that wait to be loaded
		int loaded;  // +0x38: 1 while the chunk is part of the tree
		Chunk* dependents;  // +0x3C: the chunks of the same name that were loaded after this one
		Chunk* dependentOf;  // +0x40: the chunk this one is a dependent of
		ChunkNotification* notifications;  // +0x44
		ChunkNotification* lastNotification;  // +0x48
	};

	// A branch that gathers conditions (RTTI: fight::Bank)
	class Bank : public Branch
	{
	public:
		// 0x105AD310
		Bank();
		// vftable slot 2 (0x105AD3B0 is the deleting destructor, 0x105AD340 the body)
		virtual ~Bank();

		// vftable slot 10 (0x105AD360)
		virtual Branch* Slot10(Sequencer* sequencer, void* params, int a, bool b);
		// vftable slot 0 of the Param part (0x105AD2F0)
		virtual Property* GetProperty(int index);

		// 0x105AD2E0
		ConditionList* GetConditions();

		// 0x105AD490 / 0x105AD300: the properties of the class (the store's too), built once / freed
		static void RegisterProperties();
		static void ClearProperties();

		ConditionList conditions;  // +0x28
	};

	// A bank that is not picked from by a branch that is picking (RTTI: fight::Store)
	class Store : public Bank
	{
	public:
		// 0x105AD0D0
		Store();
		// vftable slot 2 (0x105AD130 is the deleting destructor, 0x105AD0F0 the body)
		virtual ~Store();

		// vftable slot 10 (0x105AD110)
		virtual Branch* Slot10(Sequencer* sequencer, void* params, int a, bool b);
	};

	// A branch with a flag, conditions and tracks (RTTI: fight::Node)
	class Node : public Branch
	{
	public:
		// 0x105AD680
		Node();
		// vftable slot 2 (0x105AD780 is the deleting destructor, 0x105AD6B0 the body)
		virtual ~Node();

		// vftable slot 10 (0x105AD6F0)
		virtual Branch* Slot10(Sequencer* sequencer, void* params, int a, bool b);
		// vftable slot 11 (0x105AD720): runs the node on a sequencer
		virtual bool Slot11(Sequencer* sequencer, void* params, int a);
		// vftable slot 12 (0x105AD760)
		virtual void Slot12(int a, core::IRefCount* b, Sequencer* sequencer);
		// vftable slot 0 of the Param part (0x105AD660)
		virtual Property* GetProperty(int index);

		// 0x105AD640 / 0x105AD650 / (0x103B8190, a copy shared with other classes): the members the properties hand out
		bool SetImmediate(bool value);
		ConditionList* GetConditions();
		TrackGroup* GetTracks();

		// 0x105AD940 / 0x105AD670: the properties of the class, built once / freed
		static void RegisterProperties();
		static void ClearProperties();

		bool immediate;  // +0x28: the node's tracks are put on the sequencer at once instead of being started later
		ConditionList conditions;  // +0x2C
		TrackGroup tracks;  // +0x30
	};

	// The action that starts a branch on a sequencer of its own (RTTI: fight::QueuedBranchAction, 0x78 bytes)
	class QueuedBranchAction : public Action
	{
	public:
		// 0x105AAED0
		QueuedBranchAction(Branch* newBranch, int newArgument, core::IRefCount* newOwner);
		// vftable slot 2 (0x105AAF90 is the deleting destructor, 0x105AAF50 the body)
		virtual ~QueuedBranchAction();

		// vftable slot 3 (0x105AAEB0)
		virtual Sequencer* GetChild();
		// vftable slot 5 (0x105AAFB0)
		virtual bool Slot5(int arg, float value);
		// vftable slot 6 (0x105AAEC0)
		virtual void Slot6();

		BranchWatch link;  // +0x1C
		int argument;  // +0x28
		core::IRefCount* owner;  // +0x2C
		Sequencer sequencer;  // +0x30
	};

	// 0x105AA6F0 / 0x105AD510 / 0x105AD2B0: add the branch factory of a kind to a context (0x105ADA30 is the node's, in
	// fightsystem.h)
	void RegisterReferenceBranchFactory(TrackRegistry* registry);
	void RegisterBankBranchFactory(TrackRegistry* registry);
	void RegisterStoreBranchFactory(TrackRegistry* registry);
}

#endif
