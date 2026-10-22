// The fight sequencer (RTTI names fight::Action / fight::Track / fight::Condition / fight::Param / fight::Item;
// the sequencer itself is not polymorphic). A sequencer owns a list of actions; each action is a node of the fight
// tree with flags, its schedule times and an optional child sequencer, and the track it currently runs. The unit runs
// 0x105A2440 - 0x105A7BF0 (no assert path; the directory and file names are guesses). Method and member names are
// guesses until the binary tells the real ones.
#ifndef ENGINE_FIGHT_SEQUENCER_H
#define ENGINE_FIGHT_SEQUENCER_H

#include "code/core/linklist.h"
#include "code/core/name.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/refptr.h"

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace engine
{
	class GameObjectParams;
}

namespace fight
{
	class Sequencer;
	class Action;
	class Track;
	class Condition;
	class Branch;
	class Reader;

	// A reference-counted fight node (RTTI: fight::RefCounted, base core::IRefCount; 3 vftable slots)
	class RefCounted : public core::IRefCount
	{
	public:
		virtual ~RefCounted()
		{
		}
		// 0x105A73E0
		virtual void AddRef();
		// 0x105A73F0: below two references the count is parked at 0x8000000 and the object deletes itself
		virtual void Release();

		unsigned long count;
	};

	// The action's flag word: the sequencer reads single bits out of it (each test compiles to a shift and a bit
	// test, so they are bit-fields) and uses the whole word for the update mask
	union ActionFlags
	{
		unsigned int all;
		struct
		{
			unsigned int unknown0 : 1;
			unsigned int unknown1 : 1;
			// Started: the action is running and its time is counted
			unsigned int started : 1;
			// Finished: it ended, but stays in the list until it is collected
			unsigned int finished : 1;
			unsigned int unknown4 : 1;
			unsigned int unknown5 : 1;
			unsigned int unknown6 : 1;
			unsigned int unknown7 : 1;
			// The action owns a child sequencer to advance after it
			unsigned int hasChild : 1;
			// Slot 5 is called with the action's time
			unsigned int usesTime : 1;
			// Slot 6 is called when the action is stopped
			unsigned int notifies : 1;
			unsigned int rest : 21;
		} bits;
	};

	// One node of a sequencer (RTTI: fight::Action, 9 vftable slots; bases fight::RefCounted / core::IRefCount)
	class Action : public RefCounted
	{
	public:
		// 0x105A23E0 (another unit): the action's flag word and the three timers
		explicit Action(int newFlags);
		virtual ~Action();

		// vftable slot 3 (0x105A2430): the child sequencer this action owns (or 0; the engine has no action with one)
		virtual Sequencer* GetChild();
		// vftable slot 4 (0x105A2460): accepts, the actions that care override it
		virtual bool Slot4(int mask, core::IRefCount* owner);
		// vftable slot 5 (0x105A2470; most action classes have their own): begins on the track, false ends the action at once
		virtual bool Slot5(int arg, float value);
		// vftable slot 6 (0x105A2480): the action was stopped; only actions without their own copy keep this one
		virtual void Slot6();
		// vftable slot 7 (0x105A2490): updates; only actions without their own copy keep this one
		virtual bool Slot7(int arg, float value);
		// vftable slot 8 (0x105A24A0): copies the action's flags and three times into another action (name guessed)
		virtual Action* Slot8(Action* other, core::IRefCount* effect, core::IRefCount* owner);

		// 0x105A2440: sets or clears one flag bit of the action
		void SetFlag(unsigned int flag, bool value);
		// 0x105A2580 (another function of this unit): ends the action and its children's
		void End(int reason);

		// The engine tests these bits through accessors returning bool: the value is materialised (a shift and a bit
		// test) where a direct bit-field test would be a mask test
		bool IsStarted() const
		{
			return flags.bits.started;
		}
		bool IsFinished() const
		{
			return flags.bits.finished;
		}
		bool HasChild() const
		{
			return flags.bits.hasChild;
		}
		bool UsesTime() const
		{
			return flags.bits.usesTime;
		}
		bool Notifies() const
		{
			return flags.bits.notifies;
		}

		Action* next;
		ActionFlags flags;
		float timeBegin;
		float unknown14;
		float timeEnd;
	};

	// A reflected property of a node's class (another unit's header; the node hands its properties out by index)
	class Property;

	// A reflected node base (RTTI: fight::Param, 2 vftable slots); no data of its own. Slot 0 is the list of the
	// node's own properties and slot 1 the one of the nodes below it, both by index.
	class Param
	{
	public:
		// vftable slot 0
		virtual Property* GetProperty(int index) = 0;
		// vftable slot 1 (0x10034324, another unit)
		virtual Property* Slot1(int index);
	};

	// RTTI: fight::Item (9 vftable slots, base fight::Param); no data of its own. Slots 2, 3 and 4 walk the
	// properties and hand an argument to each of them, slot 5 and 6 take two arguments and slot 8 passes one
	// through to every node below.
	class Item : public Param
	{
	public:
		virtual void Slot2(int arg);
		virtual void Slot3(int arg);
		virtual void Slot4(int arg);
		// vftable slot 5 (0x105A9B80): reads a node stored under a key from a reader (the key, the context, the reader)
		virtual bool Slot5(int key, int context, int reader);
		virtual void Slot6(int a, int b);
		// vftable slot 7: the object is destroyed (the compiler's scalar deleting destructor sits here)
		virtual ~Item();
		// vftable slot 8 (0x105A9B10): reads the values of the nodes below from a reader (the context, the reader)
		virtual bool Slot8(int context, void* reader);
	};

	// A condition predicate of the fight tree (RTTI: fight::Condition, 10 vftable slots). The base is the node of a
	// boolean expression: the op links it into the chain, and slot 9 evaluates it.
	class Condition : public Item
	{
	public:
		// 0x105A99E0 (another unit): the op, the next link cleared
		explicit Condition(int newOp);
		// 0x105A9A00 (another unit): the destructor of the derived conditions' chain
		virtual ~Condition();
		// vftable slot 5 (0x105A9910): the condition's own
		virtual bool Slot5(int key, int context, int reader);
		// vftable slot 9
		virtual bool Evaluate(int a, int b, int c, int d) = 0;

		// 0x105A98E0: deletes the condition that follows and makes another the next one
		void SetNext(Condition* newNext);

		Condition* next;
		int op;
	};

	// A run of a node (RTTI: fight::Track, 16 vftable slots); only slot 12 is touched here
	class Track : public Item
	{
	public:
		// 0x105AA160 (another unit): sets the vftable and clears the three words below
		Track();
		// the destructor slot (7): clears the watch list, then the base's
		virtual ~Track();

		// vftable slot 5 (0x105A9F90): the track's own: skips what is disabled and keeps the slave word
		virtual bool Slot5(int key, int context, int reader);
		// vftable slot 9: the time the track begins at
		virtual float GetTimeBegin() const = 0;
		// vftable slot 10: the time it ends at
		virtual float Slot10() const = 0;
		// vftable slot 11 (0x1002C7D7, another unit)
		virtual void Slot11();
		// vftable slot 12: begins the track on the sequencer
		virtual void Slot12(int a, core::IRefCount* b, Sequencer* sequencer);
		// vftable slot 13 (0x1003B9B2, another unit)
		virtual void Slot13();
		// vftable slot 14 (0x105AA0F0, another unit)
		virtual void Slot14(int a, int b);
		// vftable slot 15
		virtual Action* CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner) = 0;

		// 0x105A3590 (another unit): writes the path of the node the track hangs on (the listener is a branch) into a buffer
		bool GetPath(char* buffer, int size, int flag);
		// 0x105A3A40 (another function of this unit): enters the listener list (under the load listeners' lock)
		void Register(void* entry);
		// 0x105A3A90 (another function of this unit): leaves the listener list
		void Unregister(void* entry);
		// 0x105A9F60: deletes the track that follows and makes another the next one
		void SetNext(Track* newNext);

		// The next track of the list that owns this one
		Track* next;
		// The head of the list of the nodes that watch this track (0x105AA160 clears all three words)
		core::LinkList<Track> watchList;
		unsigned int unknownC;
	};

	// The head of a condition expression (name guessed)
	class ConditionList
	{
	public:
		// 0x105A7A60 (another unit): the list starts empty
		ConditionList();
		// 0x105A7B20 (another unit): frees the conditions
		~ConditionList();
		// 0x105A7BF0
		bool Evaluate(int a, int b, int c, int d);

		// 0x105A7A70: the number of conditions
		int GetCount() const;
		// 0x105A7A90 / 0x105A7AC0: the condition at an index (null past the end)
		Condition* GetAt(int index);
		const Condition* GetAtConst(int index) const;
		// 0x105A7AF0: the index of a condition (-1 when it is not in the list)
		int IndexOf(const Condition* item) const;
		// 0x105A7B60 / 0x105A7B90 / 0x105A7BC0: hands an argument to the slots 2, 3 and 4 of every condition
		void ForEachSlot2(int arg);
		void ForEachSlot3(int arg);
		void ForEachSlot4(int arg);
		// 0x105A7E10: reads the conditions of a node of the reader the list is stored as (the context is the registry
		// of conditions they are made by); false when there is none
		bool Load(const core::Name<core::CaseSensitiveKey>& key, int context, Reader* reader);
		// 0x105A7CA0 / 0x105A7E80: appends a condition / inserts it at an index; answer its index (-1 for none)
		int Add(Condition* item);
		int Insert(int index, Condition* item);

		Condition* head;
	};

	// The sequencer itself (name guessed): schedules and advances its actions
	class Sequencer
	{
	public:
		// 0x105A3E80 / 0x105A43F0 (the sequencer's own unit): the reflection data
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x105A4020: starts empty - the track nodes, the action lists and the clock zero, timeScale 1
		Sequencer();
		// 0x105A4140: stops every started action and empties the lists
		void Stop();
		// 0x105A44A0: stops the sequencer, empties it and unregisters both of its track nodes (a behaviour's
		// destructor calls it; name guess)
		void End();
		// 0x105A42F0: updates the actions that need it, then their children
		void Update(int arg);
		// 0x105A4780: advances the clock and begins / ends the actions due
		void Advance(int arg, float dt);
		// 0x105A45A0: whether the sequencer has actions (with the flag also when a track is pending; name unknown)
		bool Unknown105A45A0(bool flag);
		// 0x105A4270: hands the sequencer the flags the behaviour collected and the parameters (name unknown)
		void Unknown105A4270(unsigned int flags, engine::GameObjectParams* params);
		// 0x105A44D0: makes the track the sequencer's pending one (registered under it), with an argument, the owner it
		// is run for and a priority; refused when a pending track is there and the priority is not lower (name guess)
		bool SetPending(Branch* track, int arg, core::IRefCount* owner, int priority);
		// 0x105A45D0: copies the sequencer's state into another one (name guess)
		void CopyTo(Sequencer* other, core::IRefCount* effect, core::IRefCount* owner);
		// 0x105A4910: walks the actions and their children (name unknown)
		void Unknown105A4910(bool flag);
		// 0x105A41B0: stops and empties the sequencer and releases its members, as a behaviour does when it is reset
		void Reset();
		// 0x105A4120: releases the two scheduled members
		void Clear();
		// 0x105A3EC0: ends every action of the pending list (name guess)
		void EndPending();
		// 0x105A4070 (another function of this unit): registers the new track, unregisters the old. The engine types it
		// as the branch kind (its Register / Unregister are fight::Branch's); 0x10863B00 compares it with a branch
		void SetTrack(Branch* track);
		// 0x1007EE30: gives the sequencer the name of its fight context (the first two words are a core::Name)
		void SetContextName(const char* text);
		// 0x105A4200 (another function of this unit): schedules the action chain at the clock
		bool Schedule(Action* action);

		int unknown0;
		int unknown4;
		Branch* track;
		int unknownC;
		int unknown10;
		Branch* pendingTrack;
		int unknown18;
		int unknown1C;
		int unknown20;
		core::IRefCount* unknown24;
		int unknown28;
		Action* scheduled;
		Action* unknown30;
		float timeScale;
		float clock;
		Action* actions;
		Action* actions2;
	};

	// 0x105A7C80: makes a condition the first one of a list (the list's own address is the first argument)
	void SetHead(ConditionList* list, Condition* item);

	// 0x105A24D0 / 0x105A3FA0 (other functions of this unit): release a member and clear it
	void ReleaseActionList(Action*& action);
	void ReleaseAction(Action*& action);

	// The running-action counters the sequencer updates (names guessed)
	extern int gActiveActions;
	extern int gPeakActiveActions;
}

#endif
