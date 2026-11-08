#include "code/proto/frontend/fehudawareness.h"

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
}

namespace proto
{
	// 0x11098D54: the movie clip of the awareness indicator
	static const char* sAwarenessClip = "mcAnchor.awarenessHUD";

	// FUNCTION: ENGINE 0x104CB670
	FEHudAwareness::FEHudAwareness() : state(0), percent(0), stateChanges(0), percentChanges(0),
		visible("_level0.mcAnchor.awarenessHUD._visible")
	{
		visible.Set(FlashValue(true));
	}

	// FUNCTION: ENGINE 0x104CB640
	FEHudAwareness::~FEHudAwareness()
	{
	}

	// FUNCTION: ENGINE 0x104CB4D0
	void FEHudAwareness::Update(bool force)
	{
		visible.Flush(force);
		if (stateChanges > 0 || force)
		{
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", sAwarenessClip, "SetAwarenessWatched", state);
		}
		if (percentChanges > 0 || force)
		{
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d", sAwarenessClip, "SetAwarenessPercent", percent);
		}
		stateChanges = 0;
		percentChanges = 0;
	}

	// FUNCTION: ENGINE 0x104CB660
	void FEHudAwareness::OnShow(bool shown)
	{
		SetShown(shown);
	}

	// FUNCTION: ENGINE 0x104CB600
	void FEHudAwareness::SetShown(bool shown)
	{
		visible.Set(FlashValue(shown));
		visible.Flush(true);
	}

	// FUNCTION: ENGINE 0x104CB580
	void FEHudAwareness::SetWatched(bool watched)
	{
		int oldState = state;
		if (!watched)
		{
			state = 0;
		}
		else
		{
			state = (percent >= 100) + 1;
		}
		if (oldState != state)
		{
			stateChanges++;
		}
	}

	// FUNCTION: ENGINE 0x104CB5C0
	bool FEHudAwareness::IsWatched() const
	{
		return state != 0;
	}

	// FUNCTION: ENGINE 0x104CB5D0
	void FEHudAwareness::SetPercent(int newPercent)
	{
		if (percent != newPercent)
		{
			percentChanges++;
			percent = newPercent;
			SetWatched(IsWatched());
		}
	}
}
