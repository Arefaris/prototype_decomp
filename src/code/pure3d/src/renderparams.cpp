// pure3d::RenderParams (RTTI name; unit around 0x1074E500 - 0x1074F800, file name guessed from the class). Names are
// guesses.
#include "code/pure3d/lighting.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1074ECE0
	void RenderParams::Unknown1074ECE0(float value)
	{
		unknown31C = value;
	}

	// FUNCTION: ENGINE 0x1074ED10
	void RenderParams::Unknown1074ED10(float value)
	{
		unknown318 = value;
	}

	// FUNCTION: ENGINE 0x1074ED30
	void RenderParams::Unknown1074ED30(int value)
	{
		unknown10 = value;
	}

	// FUNCTION: ENGINE 0x1074EE00
	int RenderParams::Unknown1074EE00()
	{
		return unknown10;
	}

	// FUNCTION: ENGINE 0x1074EE10
	int RenderParams::GetUnknown14()
	{
		return unknown14;
	}

	// FUNCTION: ENGINE 0x1074EE50
	float RenderParams::Unknown1074EE50()
	{
		return unknown34;
	}

	// FUNCTION: ENGINE 0x1074F0C0
	void RenderParams::Unknown1074F0C0(float value)
	{
		unknown314 = 0.01f > value ? 0.01f : value;
	}

	// FUNCTION: ENGINE 0x1074F110
	void RenderParams::Unknown1074F110(unsigned int index, float value)
	{
		unknown2FC[index] = value;
	}

	// FUNCTION: ENGINE 0x1074F130
	float RenderParams::Unknown1074F130(unsigned int index)
	{
		return unknown2FC[index];
	}

	// FUNCTION: ENGINE 0x1074F3B0
	void* RenderParams::GetViewState(int view)
	{
		return &views[view];
	}

	// FUNCTION: ENGINE 0x1074F3C0
	void* RenderParams::GetCameraData(int view)
	{
		return &cameras[view];
	}
}
