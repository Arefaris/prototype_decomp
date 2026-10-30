#include "code/proto/navarea.h"

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
}

// Kept copies (template instances and wrappers of this unit):
