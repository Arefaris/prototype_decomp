// fight::Action: the flag word and the times of one node of a sequencer (see sequencer.h). The unit does not see
// the reference counter's constructor, so it saves the registers around that call; it sees SetFlag, which keeps them.
#include "code/engine/fight/sequencer.h"

namespace fight
{
	// FUNCTION: ENGINE 0x105A2440
	void Action::SetFlag(unsigned int flag, bool value)
	{
		if (value)
		{
			flags.all |= flag;
		}
		else
		{
			flags.all &= ~flag;
		}
	}

	// FUNCTION: ENGINE 0x105A23E0
	Action::Action(int newFlags)
	{
		flags.all = newFlags;
		next = 0;
		timeBegin = 0.0f;
		unknown14 = 0.0f;
		timeEnd = 0.0f;
		gActionCount = gActionCount + 1;
		if (gActionCount > gActionPeak)
		{
			gActionPeak = gActionCount;
		}
	}

	// FUNCTION: ENGINE 0x105A2530
	Action::~Action()
	{
		ReleaseActionList(next);
		gActionCount = gActionCount - 1;
	}

	// FUNCTION: ENGINE 0x105A2580
	void Action::End(bool reason)
	{
		SetFlag(8, reason);
		if (HasChild())
		{
			Sequencer* child = GetChild();
			if (child != 0)
			{
				for (Action* action = child->actions; action != 0; action = action->next)
				{
					action->End(reason);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x105A23C0
	Action* Action::GetNext() const
	{
		return next;
	}

	// FUNCTION: ENGINE 0x105A3DF0
	unsigned int Action::GetRunState() const
	{
		return flags.all & 3;
	}

	// FUNCTION: ENGINE 0x105A3E00
	void Action::SetFlag4(bool value)
	{
		SetFlag(4, value);
	}

	// FUNCTION: ENGINE 0x105A3E10
	float Action::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105A3E20
	float Action::GetTime14() const
	{
		return unknown14;
	}

	// FUNCTION: ENGINE 0x105A3E30
	float Action::GetTimeEnd() const
	{
		return timeEnd;
	}

	// FUNCTION: ENGINE 0x105A3E40
	void Action::SetTimeEnd(float value)
	{
		timeEnd = value;
	}

	// FUNCTION: ENGINE 0x105A3E50
	Action* Action::Clone(core::IRefCount* effect, core::IRefCount* owner)
	{
		return Slot8(0, effect, owner);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105A25D0
