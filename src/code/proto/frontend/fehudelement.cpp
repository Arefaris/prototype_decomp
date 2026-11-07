// proto::FEHudElement and proto::FEHudVariable: see fehudelement.h. Unit 0x104C0390 - 0x104C0450 and 0x104C23B0 -
// 0x104C2600 (no assert path; the file name is a guess).
#include "code/proto/frontend/fehudelement.h"

namespace engine
{
	// The movie the front end plays, by the handle the front end keeps (the unit is the Scaleform one)
	class FlashMovieHandle
	{
	public:
		// 0x10885D40: writes a variable of the movie
		void SetVariable(proto::FlashVariant newValue, const char* path);
		// 0x10885DA0: reads a variable of the movie into the variant given and answers it
		proto::FlashVariant* GetVariable(proto::FlashVariant* result, const char* path);
	};

	// The front end: its movie is at +0x2C (0x10864330 answers the front end)
	class FrontEnd
	{
	public:
		FlashMovieHandle* GetMovie()
		{
			return &movie;
		}

		unsigned char unknown0[0x2C];
		FlashMovieHandle movie;
	};
	FrontEnd* Unknown10864330();
}

namespace proto
{
	// FUNCTION: ENGINE 0x104C0390
	FEHudElement::FEHudElement()
	{
		shown = true;
		hideCount = 0;
	}

	// FUNCTION: ENGINE 0x104C03B0
	bool FEHudElement::Show(bool show)
	{
		if (show)
		{
			if (hideCount > 0)
			{
				hideCount--;
			}
		}
		else
		{
			hideCount++;
		}
		if (!shown)
		{
			if (show && hideCount <= 0)
			{
				OnShow(show);
				shown = true;
				return true;
			}
		}
		if (!show && shown && hideCount >= 1)
		{
			OnShow(show);
			shown = false;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x104C0450
	void FEHudElement::SetHideCount(const int& count)
	{
		int newCount = count;
		if (newCount >= 0)
		{
			hideCount = newCount;
			if (newCount == 0)
			{
				if (!shown)
				{
					OnShow(true);
					shown = true;
				}
			}
			else if (shown)
			{
				OnShow(false);
				shown = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x104C04A0
	int FEHudElement::GetHideCount() const
	{
		return hideCount;
	}

	// FUNCTION: ENGINE 0x104C23B0
	FEHudVariable::FEHudVariable()
	{
		changed = false;
	}

	// FUNCTION: ENGINE 0x104C23D0
	void FEHudVariable::Flush(bool force)
	{
		if (changed || force)
		{
			const char* path = GetPath();
			engine::Unknown10864330()->GetMovie()->SetVariable(value, path);
			changed = false;
		}
	}

	// FUNCTION: ENGINE 0x104C2430
	FlashVariant FEHudVariable::Get()
	{
		FlashVariant result;
		engine::FrontEnd* frontEnd = engine::Unknown10864330();
		const char* path = GetPath();
		return *frontEnd->movie.GetVariable(&result, path);
	}

	// FUNCTION: ENGINE 0x104C2590
	void FEHudVariable::Set(FlashValue newValue)
	{
		if (!(newValue == value))
		{
			value = newValue;
			changed = true;
		}
	}
}
