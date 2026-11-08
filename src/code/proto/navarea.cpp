#include "code/proto/navarea.h"
#include "code/math/random.h"
#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
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

	// FUNCTION: ENGINE 0x105680A0
	void NavArea::AddVehicle(VehicleBehaviour* vehicle)
	{
		vehicles.PushFront(reinterpret_cast<container::DoubleListBase::Node*>(static_cast<container::ListBase::Node*>(vehicle)));
	}

	// FUNCTION: ENGINE 0x105680D0
	void NavArea::RemoveVehicle(VehicleBehaviour* vehicle)
	{
		vehicles.Remove(reinterpret_cast<container::DoubleListBase::Node*>(static_cast<container::ListBase::Node*>(vehicle)));
	}

	// FUNCTION: ENGINE 0x10568060
	bool NavArea::ContainsVehicle(VehicleBehaviour* vehicle)
	{
		if (vehicles.count != 0)
		{
			container::ListBase::Node* node = reinterpret_cast<container::ListBase::Node*>(vehicles.head);
			while (node != 0)
			{
				if (static_cast<VehicleBehaviour*>(node) == vehicle)
				{
					return true;
				}
				node = node->next;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10568240
	bool NavArea::IsBackwardFull(float scale)
	{
		if ((float)(unsigned int)vehicles.count >= GetBackwardLoad(scale))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10568290
	bool NavArea::IsForwardFull(float scale)
	{
		if ((float)walkers >= GetForwardLoad(scale))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10568190
	bool NavArea::HasRoom(float count, float capacity)
	{
		float room = capacity - count;
		if (room >= engine::driving::gOne)
		{
			return true;
		}
		if (room > math::gRandom->Range(0.0f, 1.0f))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105682D0
	bool NavArea::HasBackwardRoom(float scale)
	{
		float capacity = GetBackwardLoad(scale);
		unsigned int count = vehicles.count;
		return HasRoom((float)count, capacity);
	}

	// FUNCTION: ENGINE 0x10568320
	// NONMATCHING: the engine converts the walker count through a stack word with fild, ours with cvtsi2ss, 62.2 %
#ifdef NONMATCHING
	bool NavArea::HasForwardRoom(float scale)
	{
		return HasRoom((float)walkers, GetForwardLoad(scale));
	}
#endif

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
