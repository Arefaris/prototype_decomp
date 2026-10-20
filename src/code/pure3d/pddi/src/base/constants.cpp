// pure3d::pddiBaseContext::Constants, the table of the values the shaders ask for by name (unit around 0x10613A20 -
// 0x10613BA0, with the constructor and the destructor in the unit after 0x1061A3E0; the file name is guessed, no assert
// path survives).
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10613A20
	float* pddiBaseContext::Constants::GetValues()
	{
		return values;
	}

	// FUNCTION: ENGINE 0x10613A30
	unsigned int pddiBaseContext::Constants::GetCount()
	{
		return count;
	}

	// FUNCTION: ENGINE 0x10613A40
	void pddiBaseContext::Constants::SetFlag(const ConstantSlot& slot, bool on)
	{
		float* flags = values;
		unsigned int bit = 1 << slot.index;
		if (on)
		{
			*(unsigned int*)flags |= bit;
		}
		else
		{
			*(unsigned int*)flags &= ~bit;
		}
	}

	// FUNCTION: ENGINE 0x10613A70
	bool pddiBaseContext::Constants::GetFlag(const ConstantSlot& slot)
	{
		unsigned char word = (unsigned char)(*(unsigned int*)values >> slot.index);
		unsigned char result = word & 1;
		return result;
	}

	// FUNCTION: ENGINE 0x10613A90
	float pddiBaseContext::Constants::GetFloat(const ConstantSlot& slot)
	{
		return values[slot.index];
	}

	// FUNCTION: ENGINE 0x10613AA0
	float* pddiBaseContext::Constants::GetFloat2(const ConstantSlot& slot)
	{
		return values + slot.index;
	}

	// FUNCTION: ENGINE 0x10613AB0
	float* pddiBaseContext::Constants::GetFloat3(const ConstantSlot& slot)
	{
		return values + slot.index;
	}

	// FUNCTION: ENGINE 0x10613AC0
	float* pddiBaseContext::Constants::GetFloat4(const ConstantSlot& slot)
	{
		return values + slot.index;
	}

	// FUNCTION: ENGINE 0x10613AD0
	float* pddiBaseContext::Constants::GetMatrix(const ConstantSlot& slot)
	{
		return values + slot.index;
	}

	// FUNCTION: ENGINE 0x10613AE0
	pddiSurface* pddiBaseContext::Constants::GetTexture(const ConstantSlot& slot)
	{
		return *(pddiSurface**)&values[slot.index];
	}

	// FUNCTION: ENGINE 0x10613AF0
	void pddiBaseContext::Constants::GetSamplerAddress(const ConstantSlot& slot, int* u, int* v, int* w)
	{
		ReadSamplerAddress((SamplerEntry*)&values[slot.index], u, v, w);
	}

	// FUNCTION: ENGINE 0x10613B40
	void pddiBaseContext::Constants::GetSamplerFilters(const ConstantSlot& slot, int* minFilter, int* magFilter,
		int* mipFilter, unsigned int* anisotropy)
	{
		ReadSamplerFilters((SamplerEntry*)&values[slot.index], minFilter, magFilter, mipFilter, anisotropy);
	}

	// FUNCTION: ENGINE 0x10613BA0
	int pddiBaseContext::Constants::GetSamplerUnknown(const ConstantSlot& slot)
	{
		return ((SamplerEntry*)&values[slot.index])->bits.unknown;
	}
}
