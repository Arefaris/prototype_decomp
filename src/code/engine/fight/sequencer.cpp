// The fight sequencer: the list of actions a node runs, advanced against its clock. See sequencer.h for the model.
// Names are guesses (no assert path names this unit).
#include "code/engine/fight/branch.h"
#include "code/engine/fight/sequencer.h"

namespace fight
{
	int gActiveActions;
	int gPeakActiveActions;

	// ---- the reference count -----------------------------------------------------------------------------------

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
	bool Action::Slot4(int arg, float value)
	{
		(void)arg;
		(void)value;
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
}
