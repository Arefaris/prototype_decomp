// The fight sequencer: the list of actions a node runs, advanced against its clock. See sequencer.h for the model.
// Names are guesses (no assert path names this unit).
#include "code/core/heap.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/chunk.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/fight/sequencer.h"

namespace engine
{
	// 0x10098F50: stores a reference counted pointer
	void AssignRefCounted(core::IRefCount** slot, core::IRefCount* value);
}

namespace fight
{
	int gActiveActions;
	int gPeakActiveActions;

	// ---- the reference count -----------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A7410
	RefCounted::RefCounted()
		: count(0)
	{
	}

	// FUNCTION: ENGINE 0x105A73D0
	RefCounted::~RefCounted()
	{
	}

	// FUNCTION: ENGINE 0x105A73E0
	void RefCounted::AddRef()
	{
		count = count + 1;
	}

	// FUNCTION: ENGINE 0x105A73F0
	void RefCounted::Release()
	{
		if (count < 2)
		{
			count = 0x8000000;
			delete this;
		}
		else
		{
			count = count - 1;
		}
	}

	// ---- the action's own vftable slots -----------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A2430
	Sequencer* Action::GetChild()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105A2460
	bool Action::Slot4(int mask, core::IRefCount* owner)
	{
		(void)mask;
		(void)owner;
		return true;
	}

	// FUNCTION: ENGINE 0x105A2470
	bool Action::Slot5(int arg, float value)
	{
		(void)arg;
		(void)value;
		return true;
	}

	// FUNCTION: ENGINE 0x105A2480
	void Action::Slot6()
	{
	}

	// FUNCTION: ENGINE 0x105A2490
	bool Action::Slot7(int arg, float value)
	{
		(void)arg;
		(void)value;
		return true;
	}

	// FUNCTION: ENGINE 0x105A24A0
	Action* Action::Slot8(Action* other, core::IRefCount* effect, core::IRefCount* owner)
	{
		(void)effect;
		(void)owner;
		if (other != 0)
		{
			other->flags = flags;
			other->timeBegin = timeBegin;
			other->unknown14 = unknown14;
			other->timeEnd = timeEnd;
		}
		return other;
	}

	// FUNCTION: ENGINE 0x105A4120
	void Sequencer::Clear()
	{
		ReleaseAction(unknown30);
		ReleaseAction(scheduled);
	}

	// FUNCTION: ENGINE 0x105A4140
	void Sequencer::Stop()
	{
		for (Action* action = actions; action != 0; action = action->next)
		{
			if (action->IsStarted())
			{
				if (action->Notifies())
				{
					action->Slot6();
				}
				gActiveActions = gActiveActions - 1;
				action->End(1);
			}
		}
		ReleaseActionList(actions2);
		ReleaseActionList(actions);
		clock = 0;
		SetTrack(0);
	}

	// FUNCTION: ENGINE 0x105A42F0
	void Sequencer::Update(int arg)
	{
		for (Action* action = actions; action != 0; action = action->next)
		{
			if (action->IsStarted())
			{
				if (!action->IsFinished())
				{
					if ((action->flags.all & (0x800 << arg)) != 0)
					{
						if (!action->Slot7(arg, action->timeEnd))
						{
							action->End(1);
						}
					}
					if (!action->IsFinished())
					{
						if (action->HasChild())
						{
							Sequencer* child = action->GetChild();
							if (child != 0)
							{
								child->Update(arg);
							}
						}
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x105A4780
	// EQUIVALENT: same instructions in the same order, different xmm numbering and stack-slot scheduling; the engine
	// also compares the peak counter with the other operand order
	void Sequencer::Advance(int arg, float dt)
	{
		if (pendingTrack != 0)
		{
			Stop();
			pendingTrack->Slot12(unknown20, unknown24, this);
			SetTrack(pendingTrack);
			core::SafeReleaseRef(unknown24);
			unknown20 = 0;
		}
		if (pendingTrack != 0)
		{
			pendingTrack->Unregister(&pendingTrack);
			pendingTrack = 0;
		}
		Schedule(scheduled);
		Clear();
		dt = timeScale * dt;
		float now = clock + dt;
		clock = now;
		for (Action* action = actions; action != 0; action = action->next)
		{
			float timeBegin = action->timeBegin;
			if (now >= timeBegin)
			{
				if (!action->IsStarted() && !action->IsFinished())
				{
					action->SetFlag(4, true);
					float elapsed = now - timeBegin;
					action->timeEnd = elapsed;
					gActiveActions = gActiveActions + 1;
					if (gPeakActiveActions < gActiveActions)
					{
						gPeakActiveActions = gActiveActions;
					}
					if (action->UsesTime() && !action->Slot5(arg, elapsed))
					{
						action->End(1);
					}
				}
				else
				{
					action->timeEnd = dt;
				}
				if (!action->IsFinished() && action->HasChild())
				{
					Sequencer* child = action->GetChild();
					if (child != 0)
					{
						child->Advance(arg, action->timeEnd);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x105A7BF0
	bool ConditionList::Evaluate(int a, int b, int c, int d)
	{
		Condition* condition = head;
		bool andMode = true;
		bool negate = false;
		bool result = true;
		if (condition != 0)
		{
			do
			{
				switch (condition->op)
				{
				case 1:
					andMode = false;
					break;
				case 2:
					negate = !negate;
					break;
				case 0:
					if (!result)
					{
						if (andMode)
						{
							return false;
						}
					}
					else if (!andMode)
					{
						return true;
					}
					result = condition->Evaluate(a, b, c, d);
					if (negate)
					{
						result = !result;
					}
					andMode = true;
					negate = false;
					break;
				}
				condition = condition->next;
			}
			while (condition != 0);
		}
		return result;
	}

	// ---- The actions' reference lists -----------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A24D0
	void ReleaseActionList(Action*& action)
	{
		if (action != 0)
		{
			action->Release();
			action = 0;
		}
	}

	// FUNCTION: ENGINE 0x105A3FA0
	void ReleaseAction(Action*& action)
	{
		if (action != 0)
		{
			action->Release();
			action = 0;
		}
	}

	// FUNCTION: ENGINE 0x105A24F0
	void AssignAction(Action*& slot, Action* value)
	{
		if (value != 0)
		{
			value->AddRef();
		}
		if (slot != 0)
		{
			slot->Release();
		}
		slot = value;
	}

	// FUNCTION: ENGINE 0x105A2560
	void Action::SetNext(Action* value)
	{
		AssignAction(next, value);
	}

	// ---- The sequencer --------------------------------------------------------------------------------------------

	// Makes a track node watch another track: the old one lets go, the new one takes the node in
	static __forceinline void AssignTrack(Branch*& slot, Branch* value)
	{
		if (value != slot)
		{
			if (slot != 0)
			{
				slot->Unregister(&slot);
			}
			slot = value;
			if (value != 0)
			{
				value->Register(&slot);
			}
		}
	}

	// FUNCTION: ENGINE 0x105A4020
	// EQUIVALENT: scheduling (the engine stores the time scale after the first six words, ours before them); 66.2 %
	Sequencer::Sequencer()
	{
		track = 0;
		unknownC = 0;
		unknown10 = 0;
		pendingTrack = 0;
		unknown18 = 0;
		unknown1C = 0;
		timeScale = 1.0f;
		unknown20 = 0;
		unknown24 = 0;
		unknown28 = 0;
		scheduled = 0;
		unknown30 = 0;
		actions = 0;
		actions2 = 0;
		clock = 0.0f;
	}

	// FUNCTION: ENGINE 0x105A4070
	void Sequencer::SetTrack(Branch* newTrack)
	{
		AssignTrack(track, newTrack);
	}

	// FUNCTION: ENGINE 0x105A41B0
	void Sequencer::Reset()
	{
		Stop();
		Clear();
		unknown28 = 0;
		core::SafeReleaseRef(unknown24);
		unknown20 = 0;
		Branch** watch = &pendingTrack;
		if (*watch != 0)
		{
			(*watch)->Unregister(watch);
			*watch = 0;
		}
	}

	// FUNCTION: ENGINE 0x105A44A0
	void Sequencer::End()
	{
		Reset();
		if (pendingTrack != 0)
		{
			pendingTrack->Unregister(&pendingTrack);
		}
		if (track != 0)
		{
			track->Unregister(&track);
		}
	}

	// FUNCTION: ENGINE 0x105A4200
	bool Sequencer::Schedule(Action* action)
	{
		if (action == 0)
		{
			return false;
		}
		action->timeBegin = clock + action->timeBegin;
		Action** tail = &actions2;
		if (*tail == 0)
		{
			AssignAction(actions, action);
		}
		else
		{
			(*tail)->SetNext(action);
		}
		AssignAction(*tail, action);
		for (Action* link = action->next; link != 0; link = link->next)
		{
			AssignAction(*tail, link);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A3EC0
	void Sequencer::EndPending()
	{
		for (Action* action = actions; action != 0; action = action->next)
		{
			action->End(1);
		}
	}

	// FUNCTION: ENGINE 0x105A43C0
	int Sequencer::CanSetPending(int priority) const
	{
		if (pendingTrack != 0 && priority >= unknown28)
		{
			return 0;
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x105A44D0
	bool Sequencer::SetPending(Branch* newTrack, int arg, core::IRefCount* owner, int priority)
	{
		if (newTrack == 0)
		{
			return false;
		}
		if (pendingTrack != 0 && priority >= unknown28)
		{
			return false;
		}
		AssignTrack(pendingTrack, newTrack);
		unknown20 = arg;
		engine::AssignRefCounted(&unknown24, owner);
		unknown28 = priority;
		return true;
	}

	// FUNCTION: ENGINE 0x105A45A0
	bool Sequencer::Unknown105A45A0(bool flag)
	{
		if (pendingTrack != 0)
		{
			return true;
		}
		if (flag && scheduled != 0)
		{
			return true;
		}
		if (actions != 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A45D0
	// EQUIVALENT: register allocation (the engine keeps the other sequencer in edi and the track slot in esi, ours the other way round) and the scheduling of two loads; 30.5 %
	void Sequencer::CopyTo(Sequencer* other, core::IRefCount* effect, core::IRefCount* owner)
	{
		other->Reset();
		AssignTrack(other->track, track);
		other->unknown20 = 0;
		core::SafeReleaseRef(other->unknown24);
		AssignTrack(other->pendingTrack, pendingTrack);
		if (pendingTrack != 0)
		{
			engine::AssignRefCounted(&other->unknown24, owner);
			other->unknown28 = unknown28;
			if (other->pendingTrack != 0)
			{
				other->pendingTrack->Unregister(&other->pendingTrack);
				other->pendingTrack = 0;
			}
		}
		other->timeScale = timeScale;
		other->clock = clock;
		for (Action* action = actions; action != 0; action = action->next)
		{
			if (!action->IsFinished())
			{
				if (effect == 0)
				{
					effect = (core::IRefCount*)other;
				}
				Action* copy = action->Slot8(0, effect, owner);
				if (copy != 0)
				{
					other->Schedule(copy);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x105A4270
	void Sequencer::Unknown105A4270(unsigned int flags, engine::GameObjectParams* params)
	{
		for (Action* action = actions; action != 0; action = action->next)
		{
			if (action->IsStarted() && !action->IsFinished())
			{
				if (action->HasFlag7())
				{
					if (!action->Slot4((int)flags, (core::IRefCount*)params))
					{
						action->End(1);
					}
				}
				if (!action->IsFinished() && action->HasChild())
				{
					Sequencer* child = action->GetChild();
					if (child != 0)
					{
						child->Unknown105A4270(flags, params);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x105A4910
	// EQUIVALENT: instruction selection (the engine clears the result through al, ours stores a constant); 94.7 %
	bool Sequencer::Unknown105A4910(bool flag)
	{
		Action* previous = 0;
		bool result = false;
		Action* action = actions;
		if (action != 0)
		{
			do
			{
				if (action->IsStarted())
				{
					if (!action->IsFinished() && action->HasChild())
					{
						Sequencer* child = action->GetChild();
						if (child != 0)
						{
							bool wait = action->HasFlag5();
							bool childResult = child->Unknown105A4910(!wait);
							if (wait)
							{
								if (childResult)
								{
									action->flags.all = action->flags.all & 0xfffffffc;
								}
								else
								{
									action->flags.all = (action->flags.all & 0xfffffffd) | 1;
								}
							}
							if (action->HasFlag6())
							{
								if (!child->Unknown105A45A0(true))
								{
									action->End(1);
								}
							}
						}
					}
					if (action->IsFinished())
					{
						if (action->Notifies())
						{
							action->Slot6();
						}
						gActiveActions = gActiveActions - 1;
					}
					else if (action->unknown14 >= 0.0f)
					{
						float remaining = action->unknown14 - action->timeEnd;
						if (0.0f > remaining)
						{
							if (action->Notifies())
							{
								action->Slot6();
							}
							gActiveActions = gActiveActions - 1;
							action->End(1);
						}
						else
						{
							action->unknown14 = remaining;
						}
					}
				}
				if (action->IsFinished())
				{
					if (actions2 == action)
					{
						AssignAction(actions2, previous);
					}
					action = action->next;
					if (previous == 0)
					{
						AssignAction(actions, action);
					}
					else
					{
						previous->SetNext(action);
					}
				}
				else
				{
					if ((action->flags.all & 3) == 0)
					{
						result = true;
					}
					previous = action;
					action = action->next;
				}
			}
			while (action != 0);
			if (result)
			{
				return result;
			}
		}
		if (flag)
		{
			if (track != 0 || actions != 0)
			{
				Stop();
			}
		}
		return result;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105A2520
// FUNCTION: ENGINE 0x105A3FC0
// FUNCTION: ENGINE 0x105A3FD0
// FUNCTION: ENGINE 0x105A3FE0
// FUNCTION: ENGINE 0x105A3FF0
// FUNCTION: ENGINE 0x105A4000
// FUNCTION: ENGINE 0x105A4010
