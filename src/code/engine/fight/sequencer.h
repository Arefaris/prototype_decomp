// The fight sequencer (RTTI names fight::Action / fight::Track / fight::Condition / fight::Param / fight::Item;
// the sequencer itself is not polymorphic). A sequencer owns a list of actions; each action is a node of the fight
// tree with flags, its schedule times and an optional child sequencer, and the track it currently runs. The unit runs
// 0x105A2440 - 0x105A7BF0 (no assert path; the directory and file names are guesses). Method and member names are
// guesses until the binary tells the real ones.
#ifndef ENGINE_FIGHT_SEQUENCER_H
#define ENGINE_FIGHT_SEQUENCER_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/refptr.h"

namespace fight
{
	class Sequencer;
	class Action;
	class Track;
	class Condition;

	// A reference-counted fight node (RTTI: fight::RefCounted, base core::IRefCount; 3 vftable slots)
	class RefCounted : public core::IRefCount
	{
	public:
		virtual ~RefCounted()
		{
		}

		long count;
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

		// vftable slot 3: the child sequencer this action owns (or 0)
		virtual Sequencer* GetChild() = 0;
		virtual void Slot4() = 0;
		// vftable slot 5
		virtual bool Slot5(int arg, float value) = 0;
		// vftable slot 6
		virtual void Slot6() = 0;
		// vftable slot 7
		virtual bool Slot7(int arg, float value) = 0;
		virtual void Slot8() = 0;

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
		int unknown14;
		float timeEnd;
	};

	// A reflected property base (RTTI: fight::Param, 2 vftable slots); no data of its own
	class Param
	{
	public:
		virtual void Slot0() = 0;
		virtual void Slot1() = 0;
	};

	// RTTI: fight::Item (9 vftable slots, base fight::Param); no data of its own
	class Item : public Param
	{
	public:
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		virtual void Slot5() = 0;
		virtual void Slot6() = 0;
		virtual void Slot7() = 0;
		virtual void Slot8() = 0;
	};

	// A condition predicate of the fight tree (RTTI: fight::Condition, 10 vftable slots). The base is the node of a
	// boolean expression: the op links it into the chain, and slot 9 evaluates it.
	class Condition : public Item
	{
	public:
		// vftable slot 9
		virtual bool Evaluate(int a, int b, int c, int d) = 0;

		Condition* next;
		int op;
	};

	// A run of a node (RTTI: fight::Track, 16 vftable slots); only slot 12 is touched here
	class Track : public Item
	{
	public:
		virtual void Slot9() = 0;
		virtual void Slot10() = 0;
		virtual void Slot11() = 0;
		// vftable slot 12: begins the track on the sequencer
		virtual void Slot12(int a, core::IRefCount* b, Sequencer* sequencer) = 0;
		virtual void Slot13() = 0;
		virtual void Slot14() = 0;
		virtual void Slot15() = 0;

		// 0x105A3A40 (another function of this unit): enters the listener list (under the load listeners' lock)
		void Register(void* entry);
		// 0x105A3A90 (another function of this unit): leaves the listener list
		void Unregister(void* entry);
	};

	// The head of a condition expression (name guessed)
	class ConditionList
	{
	public:
		// 0x105A7BF0
		bool Evaluate(int a, int b, int c, int d);

		Condition* head;
	};

	// The sequencer itself (name guessed): schedules and advances its actions
	class Sequencer
	{
	public:
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
		// 0x105A4120: releases the two scheduled members
		void Clear();
		// 0x105A3EC0: ends every action of the pending list (name guess)
		void EndPending();
		// 0x105A4070 (another function of this unit): registers the new track, unregisters the old
		void SetTrack(Track* track);
		// 0x105A4200 (another function of this unit): schedules the action chain at the clock
		bool Schedule(Action* action);

		int unknown0;
		int unknown4;
		Track* track;
		int unknownC;
		int unknown10;
		Track* pendingTrack;
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

	// 0x105A24D0 / 0x105A3FA0 (other functions of this unit): release a member and clear it
	void ReleaseActionList(Action*& action);
	void ReleaseAction(Action*& action);

	// The running-action counters the sequencer updates (names guessed)
	extern int gActiveActions;
	extern int gPeakActiveActions;
}

#endif
