#include "code/core/controllerxinput.h"

namespace core
{
	// FUNCTION: ENGINE 0x10648FF0
	float ControllerOutputPointXInput::GetValue()
	{
		return value;
	}

	// FUNCTION: ENGINE 0x10649000
	void ControllerOutputPointXInput::SetValue(float newValue)
	{
		if (newValue == value)
		{
			return;
		}

		dirty = true;
		if (newValue >= 1.0f)
		{
			value = 1.0f;
		}
		else if (newValue <= 0.0f)
		{
			value = 0.0f;
		}
		else
		{
			value = newValue;
		}
	}

	// FUNCTION: ENGINE 0x10649150
	unsigned int ControllerInputPointXInput::GetValueCount()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10649160
	unsigned int ControllerInputPointXInput::ReadValues(unsigned int count, float* values)
	{
		if (count > 0 && values != 0)
		{
			values[0] = Read(0);
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x106491E0
	void ControllerInputPointXInput::SetScale(float newScale)
	{
		if (newScale < 0.0f)
		{
			newScale = 0.0f;
		}
		else if (newScale > 1.0f)
		{
			newScale = 1.0f;
		}
		scale = newScale;
	}

	// FUNCTION: ENGINE 0x10649210
	float ControllerInputPointXInput::GetScale()
	{
		return scale;
	}

	// FUNCTION: ENGINE 0x10649220
	void ControllerInputPointXInput::SetBinding(void* newBinding, void* userData)
	{
		if (binding == 0)
		{
			bindingData = userData;
			binding = newBinding;
		}
	}

	// FUNCTION: ENGINE 0x10649240
	void ControllerInputPointXInput::ClearBinding(void* oldBinding)
	{
		if (binding == oldBinding)
		{
			binding = 0;
			bindingData = 0;
		}
	}

	// FUNCTION: ENGINE 0x10649260
	float ControllerInputPointXInput::Read(unsigned int* stateOut)
	{
		if (stateOut != 0)
		{
			*stateOut = state;
		}
		return minimum + (maximum - minimum) * value;
	}

	// FUNCTION: ENGINE 0x10649280
	void ControllerInputPointXInput::SetRange(float newMinimum, float newMaximum)
	{
		minimum = newMinimum;
		maximum = newMaximum;
	}

	// FUNCTION: ENGINE 0x106492A0
	void ControllerInputPointXInput::GetRange(float* minimumOut, float* maximumOut)
	{
		if (minimumOut != 0)
		{
			*minimumOut = minimum;
		}
		if (maximumOut != 0)
		{
			*maximumOut = maximum;
		}
	}
}
