// The actions of the fight core's own tracks (see coreactions.h).
#include "code/engine/fight/coreactions.h"
#include "code/math/random.h"
#include "code/math/mathutils.h"
#include <math.h>
#include <stdarg.h>

namespace core
{
	// 0x1063B960: the formatted length (the arguments are the address of the variable ones)
	int VSNPrintfResult(char* buffer, int size, const char* format, const char* arguments);
}

namespace math
{
	class Random;
}

namespace fight
{
	// the generator the fight's default random source draws from (0x111BBD5C points at it)
	extern math::Random* gFightRandom;

	// GLOBAL: ENGINE 0x112762B0
	PrintCallback gPrintCallback;
	// GLOBAL: ENGINE 0x112762B4
	int gPrintCallbackArgument;
	// GLOBAL: ENGINE 0x112762D0
	OpportunityCallback gOpportunityCallback;
	// GLOBAL: ENGINE 0x112762D4
	int gOpportunityCallbackArgument;

	// ---- the print sink ------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B2130
	PrintCallback GetPrintCallback()
	{
		return gPrintCallback;
	}

	// FUNCTION: ENGINE 0x105B2140
	int GetPrintCallbackArgument()
	{
		return gPrintCallbackArgument;
	}

	// FUNCTION: ENGINE 0x105B2150
	void SetPlatformCallback(int (*function)(), int argument)
	{
		gPrintCallback = (PrintCallback)function;
		gPrintCallbackArgument = argument;
	}

	// FUNCTION: ENGINE 0x105B2170
	int SendPrint(int owner, const char* channel, const char* text)
	{
		if (gPrintCallback == 0)
		{
			return -1;
		}
		return gPrintCallback(owner, channel, text, gPrintCallbackArgument);
	}

	// ---- the random source, fight::OnEventAction -----------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A6DD0
	void OnEventAction::SetFlag80(bool value)
	{
		SetFlag(0x80, value);
	}

	// FUNCTION: ENGINE 0x105A6DF0
	void OnEventAction::SetFlag200(bool value)
	{
		SetFlag(0x200, value);
	}

	// FUNCTION: ENGINE 0x105A6EF0
	bool OnEventAction::Slot5(int arg, float value)
	{
		SetFlag(0x800 << (arg - 1), true);
		return true;
	}

	// FUNCTION: ENGINE 0x105A6F80
	OnEventAction::~OnEventAction()
	{
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x105A7030
	// EQUIVALENT: register allocation (the engine keeps the link's address in ebp across the calls, ours the address of the owner; 14.8 %)
	OnEventAction::OnEventAction(Track* listener, OnEventTrack* newTrack, Sequencer* newEffect, core::IRefCount* newOwner)
		: Action(0x80), watch(listener), link(newTrack), effect(newEffect), duration(0.0f), hook(0.0f), elapsed(0.0f), started(0),
		owner(0), fired(false)
	{
		float begin = newTrack->GetTimeBegin();
		duration = newTrack->timeEnd - begin;
		float newHook = newTrack->timeHook;
		hook = newHook - begin;
		if (hook < 0.0f && 0.0f <= newHook)
		{
			hook = 0.0f;
		}
		SetFlag(0x200, hook > 0.0f || duration > 0.0f || newTrack->initialTest);
		SetFlag(0x400, hook < 0.0f);
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105A7180
	// EQUIVALENT: shrink-wrap (the engine saves ebp ahead of the first tests and ebx / edi behind them, ours saves all three on entry)
	bool OnEventAction::Slot4(int mask, core::IRefCount* ownerArg)
	{
		if (link.object == 0)
		{
			return false;
		}
		if (started.branch != 0 || (link.object->eventMask & mask) == 0)
		{
			return true;
		}
		fired = true;
		Branch* branch = link.object->branch.GetBranch();
		if (branch == 0)
		{
			return true;
		}
		ConditionList* conditions = &link.object->conditions;
		if (conditions != 0)
		{
			int listener = (int)watch.track;
			if (!conditions->Evaluate(listener, (int)effect, (int)ownerArg, 0))
			{
				return true;
			}
		}
		Branch* result = branch->Slot10(effect, ownerArg, 0, 0);
		if (result == 0 || result == effect->track)
		{
			return true;
		}
		started.Assign(result);
		engine::AssignRefCounted(&owner, ownerArg);
		if (0.0f <= hook && hook <= elapsed)
		{
			result->Slot11(effect, ownerArg, link.object->priority);
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A7260
	// EQUIVALENT: the engine tests the branch pointer again on the path that leaves the hook test (85.2 %)
	bool OnEventAction::Slot7(int arg, float value)
	{
		OnEventTrack* track = link.object;
		if (track == 0)
		{
			return false;
		}
		if (!fired && track->initialTest)
		{
			Slot4(-1, owner);
			bool active;
			if (hook > 0.0f || duration > 0.0f)
			{
				active = true;
			}
			else
			{
				active = false;
			}
			SetFlag(0x800 << arg, active);
		}
		elapsed = elapsed + value;
		if (started.branch != 0 || (duration >= 0.0f && elapsed > duration))
		{
			SetFlag(0x80, false);
		}
		Branch* branch = started.branch;
		if (branch != 0)
		{
			if (hook >= 0.0f && hook <= elapsed)
			{
				branch->Slot11(effect, owner, link.object->priority);
				return false;
			}
		}
		return branch != 0 || duration < 0.0f || duration >= elapsed;
	}

	// FUNCTION: ENGINE 0x105A7360
	void OnEventAction::Slot6()
	{
		OnEventTrack* track = link.object;
		if (track != 0)
		{
			Branch* branch = started.branch;
			if (branch != 0 && hook < 0.0f)
			{
				branch->Slot11(effect, owner, track->priority);
			}
		}
	}

	// FUNCTION: ENGINE 0x105A7390
	Action* OnEventTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new OnEventAction(listener, this, (Sequencer*)effect, owner);
	}

	// FUNCTION: ENGINE 0x105A7440
	bool IsNearlyEqual(const float* a, const float* b)
	{
		return fabsf(*a - *b) <= 0.00001f;
	}

	// FUNCTION: ENGINE 0x105A7470
	// EQUIVALENT: register allocation (the engine keeps the address of the second state in a register and saves esi; 19 %)
	float DefaultRandom()
	{
		return gFightRandom->NextFloat01();
	}

	// GLOBAL: ENGINE 0x110B4298
	RandomCallback gRandomCallback = (RandomCallback)DefaultRandom;
	// GLOBAL: ENGINE 0x11276200
	int gRandomCallbackArgument;

	// FUNCTION: ENGINE 0x105A74D0
	RandomCallback GetRandomCallback()
	{
		return gRandomCallback;
	}

	// FUNCTION: ENGINE 0x105A74E0
	int GetRandomCallbackArgument()
	{
		return gRandomCallbackArgument;
	}

	// FUNCTION: ENGINE 0x105A74F0
	void SetRandomCallback(float (*function)(), int argument)
	{
		gRandomCallback = (RandomCallback)function;
		gRandomCallbackArgument = argument;
	}

	// FUNCTION: ENGINE 0x105A7510
	float GetRandomValue(core::IRefCount* owner)
	{
		if (gRandomCallback == 0)
		{
			return 0.0f;
		}
		return gRandomCallback(owner, gRandomCallbackArgument);
	}

	// FUNCTION: ENGINE 0x105A7540
	bool RandomCondition::Evaluate(int a, int b, int c, int d)
	{
		float* total = (float*)d;
		if (total != 0)
		{
			*total = weight + *total;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A7560
	bool MaybeCondition::Evaluate(int a, int b, int c, int d)
	{
		return GetRandomValue((core::IRefCount*)c) * 100.0f < percent;
	}

	template struct core::Link<OnEventTrack>;

	// ---- fight::SpawnAction --------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B19D0
	Sequencer* SpawnAction::GetChild()
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x105B19E0
	void SpawnAction::Slot6()
	{
		sequencer.Reset();
	}

	// FUNCTION: ENGINE 0x105B1A70
	SpawnAction::~SpawnAction()
	{
		core::SafeReleaseRef(owner);
		sequencer.End();
	}

	// FUNCTION: ENGINE 0x105B1B20
	SpawnAction::SpawnAction(Track* listener, SpawnTrack* newTrack, int effect, core::IRefCount* newOwner)
		: Action(0x740), watch(listener), link(newTrack), owner(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105B1BC0
	bool SpawnAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		Branch* branch = link.object->branch.GetBranch();
		if (branch == 0)
		{
			return false;
		}
		SpawnTrack* track = link.object;
		int listener = (int)watch.track;
		if (!track->conditions.Evaluate(listener, (int)&sequencer, (int)owner, 0))
		{
			return false;
		}
		Branch* started = branch->Slot10(&sequencer, owner, 0, 0);
		if (started == 0)
		{
			return false;
		}
		sequencer.SetPending(started, (int)&sequencer, owner, 0);
		return sequencer.Unknown105A45A0(true);
	}

	// FUNCTION: ENGINE 0x105B1C40
	Action* SpawnTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* newOwner)
	{
		return new SpawnAction(listener, this, (int)effect, newOwner);
	}

	// ---- fight::WaitAction ---------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B1D20
	WaitAction::~WaitAction()
	{
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x105B1DB0
	WaitAction::WaitAction(WaitTrack* newTrack, core::IRefCount* newOwner) : Action(0xA00), link(newTrack), owner(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105B1E40
	bool WaitAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		float begin = link.object->GetTimeBegin();
		float latest = link.object->timeEndMin - begin;
		float earliest = link.object->timeEndMax - begin;
		float span = latest - earliest;
		if (fabsf(span) <= 0.00001f)
		{
			timeEnd = latest;
			return true;
		}
		float base;
		float length;
		if (latest < earliest)
		{
			base = latest;
			length = earliest - latest;
		}
		else
		{
			base = earliest;
			length = span;
		}
		timeEnd = GetRandomValue(owner) * length + base;
		return true;
	}

	// FUNCTION: ENGINE 0x105B1EF0
	bool WaitAction::Slot7(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		if (arg == 0)
		{
			timeEnd = timeEnd - value;
			return timeEnd > 0.0f;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105B1F30
	Action* WaitTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new WaitAction(this, owner);
	}

	// ---- the sequencer conditions' evaluate functions ------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B1F80
	bool SequencerTimeCondition::Evaluate(int a, int b, int c, int d)
	{
		Sequencer* sequencer = (Sequencer*)b;
		if (sequencer == 0)
		{
			return false;
		}
		float clock = sequencer->clock;
		switch (compare)
		{
		case 0:
			return clock < time;
		case 1:
			return clock <= time;
		case 2:
			return math::IsEqual(clock, time, 0.00001f);
		case 3:
			return !math::IsEqual(clock, time, 0.00001f);
		case 4:
			return time <= clock;
		case 5:
			return time < clock;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B2060
	bool SequencerIsBusyCondition::Evaluate(int a, int b, int c, int d)
	{
		bool expected = match;
		bool actual = ((Sequencer*)b)->Unknown105A45A0(true);
		bool same = expected == actual;
		return same;
	}

	// FUNCTION: ENGINE 0x105B2080
	bool SequencerBranchCondition::Evaluate(int a, int b, int c, int d)
	{
		Sequencer* sequencer = (Sequencer*)b;
		if (sequencer == 0)
		{
			return false;
		}
		Branch* current = sequencer->track;
		Branch* target = branch.GetBranch();
		if (recurse)
		{
			for (Branch* node = current; node != 0; node = node->unknown18)
			{
				if (node == target)
				{
					return compare == 0;
				}
			}
			return compare == 1;
		}
		switch (compare)
		{
		case 0:
			return current == target;
		case 1:
			return current != target;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B21A0
	void FormatPrint(int owner, const char* channel, const char* format, ...)
	{
		char buffer[1024];
		va_list arguments;
		va_start(arguments, format);
		core::VSNPrintfResult(buffer, 1024, format, arguments);
		SendPrint(owner, channel, buffer);
	}

	// FUNCTION: ENGINE 0x105B21F0
	bool PrintCondition::Evaluate(int a, int b, int c, int d)
	{
		if (text != 0)
		{
			FormatPrint(c, channel, "%s\n", text);
		}
		return true;
	}

	// ---- fight::PrintAction --------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B22A0
	PrintAction::~PrintAction()
	{
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x105B2330
	PrintAction::PrintAction(PrintTrack* newTrack, core::IRefCount* newOwner) : Action(0x200), link(newTrack), owner(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105B23C0
	bool PrintAction::Slot5(int arg, float value)
	{
		PrintTrack* track = link.object;
		if (track != 0)
		{
			char* text = track->text;
			if (text != 0)
			{
				FormatPrint((int)owner, track->channel, "%s\n", text);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B23F0
	Action* PrintTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new PrintAction(this, owner);
	}

	// ---- fight::TrackGroupAction ---------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B2480
	Sequencer* TrackGroupAction::GetChild()
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x105B2490
	void TrackGroupAction::Slot6()
	{
		sequencer.Reset();
	}

	// FUNCTION: ENGINE 0x105B2520
	TrackGroupAction::~TrackGroupAction()
	{
		core::SafeReleaseRef(owner);
		sequencer.End();
	}

	// FUNCTION: ENGINE 0x105B25D0
	TrackGroupAction::TrackGroupAction(Track* listener, TrackGroupTrack* newTrack, Sequencer* newParent, core::IRefCount* newOwner)
		: Action(0x760), watch(listener), link(newTrack), parent(newParent), owner(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105B2680
	bool TrackGroupAction::Slot5(int arg, float value)
	{
		TrackGroupTrack* track = link.object;
		if (track == 0)
		{
			return false;
		}
		int listener = (int)watch.track;
		if (!track->conditions.Evaluate(listener, (int)parent, (int)owner, 0))
		{
			return false;
		}
		link.object->tracks.Unknown105A80A0((int)watch.track, (int)parent, (int)owner, &sequencer);
		return sequencer.Unknown105A45A0(true);
	}

	// FUNCTION: ENGINE 0x105B26E0
	Action* TrackGroupTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new TrackGroupAction(listener, this, (Sequencer*)effect, owner);
	}

	// ---- the evaluate functions of the logic conditions ----------------------------------------------------------

	// FUNCTION: ENGINE 0x105B2420
	bool PlatformCondition::Evaluate(int a, int b, int c, int d)
	{
		return win32;
	}

	// FUNCTION: ENGINE 0x105B2450
	bool OrCondition::Evaluate(int a, int b, int c, int d)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105B2460
	bool NotCondition::Evaluate(int a, int b, int c, int d)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105B2470
	bool ConditionGroupCondition::Evaluate(int a, int b, int c, int d)
	{
		return conditions.Evaluate(a, b, c, d);
	}

	// FUNCTION: ENGINE 0x105B2720
	bool FalseCondition::Evaluate(int a, int b, int c, int d)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105B2730
	bool DebugCondition::Evaluate(int a, int b, int c, int d)
	{
		switch (compare)
		{
		case 0:
			return mode == 2;
		case 1:
			return mode != 2;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B2760
	int DebugCondition::GetCompare() const
	{
		return compare;
	}

	// FUNCTION: ENGINE 0x105B2770
	int DebugCondition::GetMode() const
	{
		return mode;
	}

	// FUNCTION: ENGINE 0x105B2780
	bool CommentCondition::Evaluate(int a, int b, int c, int d)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105B2790
	Action* CommentTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105B27A0
	bool IsCommentCondition(Condition* condition)
	{
		return dynamic_cast<CommentCondition*>(condition) != 0;
	}

	// FUNCTION: ENGINE 0x105B27D0
	const char* GetCommentConditionText(Condition* condition)
	{
		CommentCondition* comment = dynamic_cast<CommentCondition*>(condition);
		if (comment == 0)
		{
			return 0;
		}
		return comment->text;
	}

	// FUNCTION: ENGINE 0x105B2800
	bool IsCommentTrack(Track* track)
	{
		return dynamic_cast<CommentTrack*>(track) != 0;
	}

	// FUNCTION: ENGINE 0x105B2830
	const char* GetCommentTrackText(Track* track)
	{
		CommentTrack* comment = dynamic_cast<CommentTrack*>(track);
		if (comment == 0)
		{
			return 0;
		}
		return comment->text;
	}

	// ---- fight::StopAction ---------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B2910
	StopAction::~StopAction()
	{
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x105B29B0
	StopAction::StopAction(Track* listener, StopTrack* newTrack, Sequencer* newParent, core::IRefCount* newOwner)
		: Action(0x200), watch(listener), link(newTrack), parent(newParent), owner(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105B2880
	bool StopAction::Slot5(int arg, float value)
	{
		SetFlag(0x800 << (arg - 1), true);
		return true;
	}

	// FUNCTION: ENGINE 0x105B2A50
	bool StopAction::Slot7(int arg, float value)
	{
		StopTrack* track = link.object;
		if (track != 0)
		{
			int listener = (int)watch.track;
			if (track->conditions.Evaluate(listener, (int)parent, (int)owner, 0))
			{
				parent->EndPending();
				return false;
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B2A90
	Action* StopTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new StopAction(listener, this, (Sequencer*)effect, owner);
	}

	// ---- fight::SequenceAction -----------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B2B60
	SequenceAction::~SequenceAction()
	{
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x105B2C10
	SequenceAction::SequenceAction(Track* listener, SequenceTrack* newTrack, Branch* newBranch, int newPriority, Sequencer* newParent,
		core::IRefCount* newOwner)
		: Action(0x400), watch(listener), link(newTrack), branchWatch(newBranch), priority(newPriority), parent(newParent), owner(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105B2CD0
	void SequenceAction::Slot6()
	{
		if (link.object == 0 || branchWatch.branch == 0)
		{
			return;
		}
		ConditionList* conditions = &link.object->conditions;
		if (conditions != 0)
		{
			int listener = (int)watch.track;
			if (!conditions->Evaluate(listener, (int)parent, (int)owner, 0))
			{
				return;
			}
		}
		Branch* started = branchWatch.branch->Slot10(parent, owner, 0, 0);
		if (started != 0)
		{
			started->Slot11(parent, owner, priority);
		}
	}

	// FUNCTION: ENGINE 0x105B2D30
	Action* SequenceAction::Slot8(Action* other, core::IRefCount* effect, core::IRefCount* owner)
	{
		if (other == 0)
		{
			SequenceTrack* track = link.object;
			if (track == 0)
			{
				return 0;
			}
			Track* listener = watch.track;
			other = track->CreateAction(listener, effect, owner);
		}
		return Action::Slot8(other, effect, owner);
	}

	// FUNCTION: ENGINE 0x105B2D80
	Action* SequenceTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new SequenceAction(listener, this, branch.GetBranch(), priority, (Sequencer*)effect, owner);
	}

	// ---- fight::OpportunityAction --------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B2EA0
	OpportunityAction::~OpportunityAction()
	{
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x105B2F00
	bool OpportunityAction::Slot5(int arg, float value)
	{
		OpportunityCallback callback = gOpportunityCallback;
		first = arg - 1;
		second = arg - 1;
		if (callback != 0 && watch.track != 0)
		{
			callback((int)watch.track, (int)owner, gOpportunityCallbackArgument, &first, &second);
		}
		SetFlag(0x800 << first, true);
		SetFlag(0x800 << second, true);
		return true;
	}

	// FUNCTION: ENGINE 0x105B2F70
	void OpportunityAction::Slot6()
	{
		if (hook < 0.0f)
		{
			Branch* branch = started.branch;
			if (branch != 0)
			{
				branch->Slot11(parent, owner, priority);
			}
		}
	}

	// FUNCTION: ENGINE 0x105B3000
	OpportunityAction::OpportunityAction(Track* listener, OpportunityTrack* newTrack, float newDuration, float newHook,
		Branch* newBranch, int newPriority, Sequencer* newParent, core::IRefCount* newOwner)
		: Action(0x600), watch(listener), link(newTrack), duration(newDuration), hook(newHook), branchWatch(newBranch),
		priority(newPriority), parent(newParent), owner(0), first(0), second(0), elapsed(0.0f), started(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105B30F0
	bool OpportunityAction::Slot7(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		float limit = duration;
		float hookTime = hook;
		if (first == arg)
		{
			if (started.branch == 0 && (limit < 0.0f || elapsed <= limit) && branchWatch.branch != 0)
			{
				ConditionList* conditions = &link.object->conditions;
				bool pass = true;
				if (conditions != 0)
				{
					int listener = (int)watch.track;
					pass = conditions->Evaluate(listener, (int)parent, (int)owner, 0);
				}
				if (pass)
				{
					Branch* branch = branchWatch.branch->Slot10(parent, owner, 0, 0);
					if (branch != 0 && branch != parent->track)
					{
						started.Assign(branch);
					}
				}
			}
			elapsed = elapsed + value;
		}
		if (second == arg && hookTime >= 0.0f && started.branch != 0 && elapsed >= hookTime)
		{
			started.branch->Slot11(parent, owner, priority);
			return false;
		}
		return limit < 0.0f || limit >= elapsed || started.branch != 0;
	}

	// FUNCTION: ENGINE 0x105B3210
	Action* OpportunityAction::Slot8(Action* other, core::IRefCount* effect, core::IRefCount* newOwner)
	{
		if (other == 0)
		{
			OpportunityTrack* track = link.object;
			if (track == 0)
			{
				return 0;
			}
			Track* listener = watch.track;
			other = track->CreateAction(listener, effect, newOwner);
		}
		OpportunityAction* copy = (OpportunityAction*)other;
		copy->first = first;
		copy->second = second;
		copy->elapsed = elapsed;
		BranchWatch* target = &copy->started;
		Branch* branch = started.branch;
		if (branch != target->branch)
		{
			if (target->branch != 0)
			{
				target->branch->Unregister(target);
			}
			target->branch = branch;
			if (branch != 0)
			{
				branch->Register(target);
			}
		}
		return Action::Slot8(other, effect, newOwner);
	}

	// FUNCTION: ENGINE 0x105B32A0
	Action* OpportunityTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		float begin = timeBegin;
		float end = timeEnd;
		float duration = end - begin;
		float hookTime = timeHook - begin;
		if (hookTime < 0.0f && 0.0f <= timeHook)
		{
			hookTime = 0.0f;
		}
		return new OpportunityAction(listener, this, duration, hookTime, branch.GetBranch(), priority, (Sequencer*)effect, owner);
	}

	// ---- fight::ExecuteAction ------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105B3360
	Sequencer* ExecuteAction::GetChild()
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x105B3370
	void ExecuteAction::Slot6()
	{
		sequencer.Reset();
	}

	// FUNCTION: ENGINE 0x105B3400
	ExecuteAction::~ExecuteAction()
	{
		core::SafeReleaseRef(owner);
		sequencer.End();
	}

	// FUNCTION: ENGINE 0x105B34B0
	ExecuteAction::ExecuteAction(Track* listener, ExecuteTrack* newTrack, Sequencer* newParent, core::IRefCount* newOwner)
		: Action(0x760), watch(listener), link(newTrack), parent(newParent), owner(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
	}

	// FUNCTION: ENGINE 0x105B3560
	bool ExecuteAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		Branch* branch = link.object->branch.GetBranch();
		if (branch == 0)
		{
			return false;
		}
		ConditionList* conditions = &link.object->conditions;
		if (conditions != 0)
		{
			int listener = (int)watch.track;
			if (!conditions->Evaluate(listener, (int)parent, (int)owner, 0))
			{
				return false;
			}
		}
		Branch* started = branch->Slot10(parent, owner, 0, 0);
		if (started == 0)
		{
			return false;
		}
		sequencer.SetPending(started, (int)parent, owner, 0);
		return sequencer.Unknown105A45A0(true);
	}

	// FUNCTION: ENGINE 0x105B35F0
	Action* ExecuteAction::Slot8(Action* other, core::IRefCount* effect, core::IRefCount* newOwner)
	{
		if (other == 0)
		{
			ExecuteTrack* track = link.object;
			if (track == 0)
			{
				return 0;
			}
			Track* listener = watch.track;
			other = track->CreateAction(listener, effect, newOwner);
		}
		sequencer.CopyTo(&((ExecuteAction*)other)->sequencer, effect, newOwner);
		return Action::Slot8(other, effect, newOwner);
	}

	// FUNCTION: ENGINE 0x105B3650
	Action* ExecuteTrack::CreateAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new ExecuteAction(listener, this, (Sequencer*)effect, owner);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105A6F10
// FUNCTION: ENGINE 0x105A6F30
// FUNCTION: ENGINE 0x105B1A00
// FUNCTION: ENGINE 0x105B1A20
// FUNCTION: ENGINE 0x105B1A60
// FUNCTION: ENGINE 0x105B1AC0
// FUNCTION: ENGINE 0x105B1BA0
// FUNCTION: ENGINE 0x105B1CB0
// FUNCTION: ENGINE 0x105B1CD0
// FUNCTION: ENGINE 0x105B1D10
// FUNCTION: ENGINE 0x105B1D50
// FUNCTION: ENGINE 0x105B1E20
// FUNCTION: ENGINE 0x105B2230
// FUNCTION: ENGINE 0x105B2250
// FUNCTION: ENGINE 0x105B2290
// FUNCTION: ENGINE 0x105B22D0
// FUNCTION: ENGINE 0x105B23A0
// FUNCTION: ENGINE 0x105B24B0
// FUNCTION: ENGINE 0x105B24D0
// FUNCTION: ENGINE 0x105B2510
// FUNCTION: ENGINE 0x105B2570
// FUNCTION: ENGINE 0x105B2660
// FUNCTION: ENGINE 0x105B2A30
// FUNCTION: ENGINE 0x105B2CB0
// FUNCTION: ENGINE 0x105B30D0
// FUNCTION: ENGINE 0x105B3540
