#include "code/proto/navarea.h"

namespace engine
{
	namespace driving
	{
		extern const float gHalf;
		extern const float gTwo;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x10568010
	bool NavArea::IsOnFoot() const
	{
		if (areaType != 4 && areaType != 5 && areaType != 3 && areaType != 8)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10568040
	bool NavArea::IsCrossing() const
	{
		if (areaType != 1 && areaType != 3)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10568100
	int NavArea::GetVehicleCount() const
	{
		return vehicles.count;
	}

	// FUNCTION: ENGINE 0x10568110
	void NavArea::ClaimBackward()
	{
		if (backwardClaims > 0)
		{
			backwardClaims = 0;
		}
		backwardClaims--;
	}

	// FUNCTION: ENGINE 0x10568130
	void NavArea::ClaimForward()
	{
		if (forwardClaims > 0)
		{
			forwardClaims = 0;
		}
		forwardClaims--;
	}

	// FUNCTION: ENGINE 0x10568150
	void NavArea::ReleaseBackward()
	{
		if (backwardClaims < 0)
		{
			backwardClaims++;
		}
	}

	// FUNCTION: ENGINE 0x10568170
	void NavArea::ReleaseForward()
	{
		if (forwardClaims < 0)
		{
			forwardClaims++;
		}
	}

	// FUNCTION: ENGINE 0x105681F0
	float NavArea::GetBackwardLoad(float scale) const
	{
		return backwardClaims * (scale * 0.1f);
	}

	// FUNCTION: ENGINE 0x10568220
	float NavArea::GetForwardLoad(float scale) const
	{
		return forwardClaims * scale;
	}

	// FUNCTION: ENGINE 0x10568360
	void NavArea::AddWalker()
	{
		walkers++;
	}

	// FUNCTION: ENGINE 0x10568370
	void NavArea::RemoveWalker()
	{
		walkers--;
	}


	// FUNCTION: ENGINE 0x10567FD0
	float NavArea::GetScale() const
	{
		return scale;
	}

	// FUNCTION: ENGINE 0x10567FE0
	bool NavArea::IsDriveable() const
	{
		if (areaType != 4 && areaType != 0 && areaType != 5 && areaType != 6 && areaType != 7)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10569030
	void NavArea::SetLoads(float backward, float forward)
	{
		float areaScale = GetScale();
		float half = engine::driving::gHalf;
		float scaled = areaScale * 0.1f;
		int value = (int)(scaled * backward + half);
		if (value > 0xff)
		{
			value = 0xff;
		}
		backwardClaims = (unsigned char)value;
		value = (int)(areaScale * forward + half);
		if (value > 0xffff)
		{
			value = 0xffff;
		}
		forwardClaims = (short)value;
	}

	// FUNCTION: ENGINE 0x105690B0
	void NavArea::SetBackwardLoad(float load)
	{
		float scaled = GetScale() * 0.1f;
		int value = (int)(scaled * load + engine::driving::gHalf);
		if (value > 0xff)
		{
			value = 0xff;
		}
		backwardClaims = (unsigned char)value;
	}

	// FUNCTION: ENGINE 0x10569110
	// NONMATCHING: the engine loads the scale into an SSE register before the test and multiplies it in place behind
	// it; ours repeats the rest of the computation in both branches, best 33.3 %
#ifdef NONMATCHING
	void NavArea::SetForwardLoad(float load)
	{
		float areaScale = GetScale();
		if (areaScale > 350.0f)
		{
			areaScale *= engine::driving::gTwo;
		}
		int value = (int)(areaScale * load + engine::driving::gHalf);
		if (value > 0xffff)
		{
			value = 0xffff;
		}
		forwardClaims = (short)value;
	}
#endif

	// FUNCTION: ENGINE 0x10569170
	void NavArea::RefreshBackward()
	{
		if (backwardClaims >= 0)
		{
			if (IsDriveable())
			{
				SetBackwardLoad(1.0f);
				return;
			}
			backwardClaims = 0;
		}
	}

	// FUNCTION: ENGINE 0x105691A0
	void NavArea::RefreshForward()
	{
		if (forwardClaims >= 0)
		{
			if (IsOnFoot())
			{
				SetForwardLoad(0.1f);
				return;
			}
			forwardClaims = 0;
		}
	}
}

// Kept copies (template instances and wrappers of this unit):
