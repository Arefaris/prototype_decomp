// The actions of the fight core's own tracks (spawn, wait, print, track group, stop, sequence, opportunity and execute)
// and the evaluate functions of its conditions. Part of the unit 0x105A2440 - 0x105B3680 (no assert path; file name
// guessed). The tracks and conditions themselves are in coretracks.h and coreconditions.h.
#ifndef ENGINE_FIGHT_COREACTIONS_H
#define ENGINE_FIGHT_COREACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/coreconditions.h"
#include "code/engine/fight/coretracks.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/lodactions.h"

namespace fight
{
	// The message sink the 'print' tracks and conditions write to: a channel and a text; the game installs the callback
	// (0x105B2150, set with SetPlatformCallback) and the sink answers -1 without one
	typedef int (*PrintCallback)(int owner, const char* channel, const char* text, int argument);
	// 0x105B2130 / 0x105B2140: the callback and its argument
	PrintCallback GetPrintCallback();
	int GetPrintCallbackArgument();
	// 0x105B2170: hands a text to the callback
	int SendPrint(int owner, const char* channel, const char* text);
	// 0x105B21A0: formats a text (up to 1 KiB) and hands it to the callback
	void FormatPrint(int owner, const char* channel, const char* format, ...);

	// 0x105A7510: a random number between 0 and 1 from the callback the game installs (0x105A74F0), 0 without one
	float GetRandomValue(core::IRefCount* owner);

	// The function the opportunity actions pick their branches with (0x105B2E00 sets it; 0x105B2DE0 / 0x105B2DF0 read it)
	typedef void (*OpportunityCallback)(int listener, int owner, int argument, int* first, int* second);
	OpportunityCallback GetOpportunityCallback();
	int GetOpportunityCallbackArgument();
	void SetOpportunityCallback(OpportunityCallback function, int argument);

	// The fight's random source: 0x105A7470 draws from the generator at 0x111BBD5C points to; 0x105A74F0 installs another
	// source (SetRandomCallback) and 0x105A74D0 / 0x105A74E0 read it back
	typedef float (*RandomCallback)(core::IRefCount* owner, int argument);
	RandomCallback GetRandomCallback();
	int GetRandomCallbackArgument();
	// 0x105A7440: whether two numbers are within a tolerance of each other
	bool IsNearlyEqual(const float* a, const float* b);

	// RTTI: fight::OnEventAction (9 vftable slots, 0x58 bytes)
	class OnEventAction : public Action
	{
	public:
		// 0x105A7030
		OnEventAction(Track* listener, OnEventTrack* newTrack, Sequencer* newEffect, core::IRefCount* newOwner);
		virtual ~OnEventAction();

		// vftable slot 4 (0x105A7180), 5 (0x105A6EF0), 6 (0x105A7360) and 7 (0x105A7260)
		virtual bool Slot4(int mask, core::IRefCount* ownerArg);
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		// 0x105A6DD0 / 0x105A6DF0 (nothing calls them)
		void SetFlag80(bool value);
		void SetFlag200(bool value);

		engine::TrackWatch watch;  // +0x1C
		core::Link<OnEventTrack> link;  // +0x28
		Sequencer* effect;  // +0x34
		float duration;  // +0x38
		float hook;  // +0x3C
		float elapsed;  // +0x40
		BranchWatch started;  // +0x44
		core::IRefCount* owner;  // +0x50
		bool fired;  // +0x54
	};

	// RTTI: fight::SpawnAction (9 vftable slots, 0x80 bytes): runs the track's branch in a sequencer of its own
	class SpawnAction : public Action
	{
	public:
		// 0x105B1B20
		SpawnAction(Track* listener, SpawnTrack* newTrack, int effect, core::IRefCount* newOwner);
		virtual ~SpawnAction();

		// vftable slot 3 (0x105B19D0), 5 (0x105B1BC0), 6 (0x105B19E0)
		virtual Sequencer* GetChild();
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		engine::TrackWatch watch;  // +0x1C
		core::Link<SpawnTrack> link;  // +0x28
		core::IRefCount* owner;  // +0x34
		Sequencer sequencer;  // +0x38
		int unknown7C;
	};

	// RTTI: fight::WaitAction (9 vftable slots, 0x30 bytes): ends after a time drawn between the track's two limits
	class WaitAction : public Action
	{
	public:
		// 0x105B1DB0
		WaitAction(WaitTrack* newTrack, core::IRefCount* newOwner);
		virtual ~WaitAction();

		// vftable slot 5 (0x105B1E40) and 7 (0x105B1EF0)
		virtual bool Slot5(int arg, float value);
		virtual bool Slot7(int arg, float value);

		core::Link<WaitTrack> link;  // +0x1C
		core::IRefCount* owner;  // +0x28
		float timeEnd;  // +0x2C
	};

	// RTTI: fight::PrintAction (9 vftable slots, 0x2C bytes)
	class PrintAction : public Action
	{
	public:
		// 0x105B2330
		PrintAction(PrintTrack* newTrack, core::IRefCount* newOwner);
		virtual ~PrintAction();

		// vftable slot 5 (0x105B23C0)
		virtual bool Slot5(int arg, float value);

		core::Link<PrintTrack> link;  // +0x1C
		core::IRefCount* owner;  // +0x28
	};

	// RTTI: fight::TrackGroupAction (9 vftable slots, 0x88 bytes): creates the actions of the group's tracks in a
	// sequencer of its own
	class TrackGroupAction : public Action
	{
	public:
		// 0x105B25D0
		TrackGroupAction(Track* listener, TrackGroupTrack* newTrack, Sequencer* newParent, core::IRefCount* newOwner);
		virtual ~TrackGroupAction();

		// vftable slot 3 (0x105B2480), 5 (0x105B2680), 6 (0x105B2490)
		virtual Sequencer* GetChild();
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		engine::TrackWatch watch;  // +0x1C
		core::Link<TrackGroupTrack> link;  // +0x28
		Sequencer* parent;  // +0x34
		core::IRefCount* owner;  // +0x38
		int unknown3C;
		Sequencer sequencer;  // +0x40
		int unknown84;
	};

	// RTTI: fight::StopAction (9 vftable slots, 0x3C bytes): ends what its parent sequencer has pending
	class StopAction : public Action
	{
	public:
		// 0x105B29B0
		StopAction(Track* listener, StopTrack* newTrack, Sequencer* newParent, core::IRefCount* newOwner);
		virtual ~StopAction();

		// vftable slot 5 (0x105B2880) and 7 (0x105B2A50)
		virtual bool Slot5(int arg, float value);
		virtual bool Slot7(int arg, float value);

		engine::TrackWatch watch;  // +0x1C
		core::Link<StopTrack> link;  // +0x28
		Sequencer* parent;  // +0x34
		core::IRefCount* owner;  // +0x38
	};

	// RTTI: fight::SequenceAction (9 vftable slots, 0x4C bytes): runs a branch on its parent sequencer
	class SequenceAction : public Action
	{
	public:
		// 0x105B2C10
		SequenceAction(Track* listener, SequenceTrack* newTrack, Branch* newBranch, int newPriority, Sequencer* newParent,
			core::IRefCount* newOwner);
		virtual ~SequenceAction();

		// vftable slot 6 (0x105B2CD0) and 8 (0x105B2D30)
		virtual void Slot6();
		virtual Action* Slot8(Action* other, core::IRefCount* effect, core::IRefCount* owner);

		engine::TrackWatch watch;  // +0x1C
		core::Link<SequenceTrack> link;  // +0x28
		BranchWatch branchWatch;  // +0x34
		int priority;  // +0x40
		Sequencer* parent;  // +0x44
		core::IRefCount* owner;  // +0x48
	};

	// RTTI: fight::OpportunityAction (9 vftable slots, 0x6C bytes)
	class OpportunityAction : public Action
	{
	public:
		// 0x105B3000
		OpportunityAction(Track* listener, OpportunityTrack* newTrack, float newDuration, float newHook, Branch* newBranch,
			int newPriority, Sequencer* newParent, core::IRefCount* newOwner);
		virtual ~OpportunityAction();

		// vftable slot 5 (0x105B2F00), 6 (0x105B2F70), 7 (0x105B30F0) and 8 (0x105B3210)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);
		virtual Action* Slot8(Action* other, core::IRefCount* effect, core::IRefCount* owner);

		engine::TrackWatch watch;  // +0x1C
		core::Link<OpportunityTrack> link;  // +0x28
		float duration;  // +0x34
		float hook;  // +0x38
		BranchWatch branchWatch;  // +0x3C
		int priority;  // +0x48
		Sequencer* parent;  // +0x4C
		core::IRefCount* owner;  // +0x50
		int first;  // +0x54
		int second;  // +0x58
		float elapsed;  // +0x5C
		BranchWatch started;  // +0x60
	};

	// RTTI: fight::ExecuteAction (9 vftable slots, 0x88 bytes)
	class ExecuteAction : public Action
	{
	public:
		// 0x105B34B0
		ExecuteAction(Track* listener, ExecuteTrack* newTrack, Sequencer* newParent, core::IRefCount* newOwner);
		virtual ~ExecuteAction();

		// vftable slot 3 (0x105B3360), 5 (0x105B3560), 6 (0x105B3370) and 8 (0x105B35F0)
		virtual Sequencer* GetChild();
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual Action* Slot8(Action* other, core::IRefCount* effect, core::IRefCount* owner);

		engine::TrackWatch watch;  // +0x1C
		core::Link<ExecuteTrack> link;  // +0x28
		Sequencer* parent;  // +0x34
		core::IRefCount* owner;  // +0x38
		int unknown3C;
		Sequencer sequencer;  // +0x40
		int unknown84;
	};
}

#endif
