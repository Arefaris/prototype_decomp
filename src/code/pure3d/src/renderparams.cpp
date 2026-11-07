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

	// FUNCTION: ENGINE 0x1074ED40
	void RenderParams::SetUnknown4C(int value)
	{
		unknown4C = value;
	}

	// FUNCTION: ENGINE 0x1074ED50
	void RenderParams::SetUnknown24(const math::Vector* value)
	{
		unknown24.x = value->x;
		unknown24.y = value->y;
		unknown24.z = value->z;
	}

	// FUNCTION: ENGINE 0x1074ED70
	void RenderParams::SetUnknown18(const math::Vector* value)
	{
		unknown18.x = value->x;
		unknown18.y = value->y;
		unknown18.z = value->z;
	}

	// FUNCTION: ENGINE 0x1074ED90
	void RenderParams::SetUnknown30(float value)
	{
		unknown30 = value;
	}

	// FUNCTION: ENGINE 0x1074EDA0
	void RenderParams::SetUnknown34(float value)
	{
		unknown34 = value;
	}

	// FUNCTION: ENGINE 0x1074EDB0
	void RenderParams::SetUnknown38(unsigned int value)
	{
		unknown38 = (float)value;
	}

	// FUNCTION: ENGINE 0x1074EDD0
	void RenderParams::SetUnknown3C(float value)
	{
		unknown3C = value;
	}

	// FUNCTION: ENGINE 0x1074EDE0
	void RenderParams::SetUnknown40(float value)
	{
		unknown40 = value;
	}

	// FUNCTION: ENGINE 0x1074EDF0
	void RenderParams::SetUnknown44(float value)
	{
		unknown44 = value;
	}

	// FUNCTION: ENGINE 0x1074EE20
	const math::Vector* RenderParams::GetUnknown24()
	{
		return &unknown24;
	}

	// FUNCTION: ENGINE 0x1074EE30
	const math::Vector* RenderParams::GetUnknown18()
	{
		return &unknown18;
	}

	// FUNCTION: ENGINE 0x1074EE40
	float RenderParams::GetUnknown30()
	{
		return unknown30;
	}

	// FUNCTION: ENGINE 0x1074EE60
	int RenderParams::GetUnknown38()
	{
		return (int)unknown38;
	}

	// FUNCTION: ENGINE 0x1074EE70
	float RenderParams::GetUnknown3C()
	{
		return unknown3C;
	}

	// FUNCTION: ENGINE 0x1074EE80
	float RenderParams::GetUnknown40()
	{
		return unknown40;
	}

	// FUNCTION: ENGINE 0x1074EE90
	float RenderParams::GetUnknown44()
	{
		return unknown44;
	}

	// FUNCTION: ENGINE 0x1074EEA0
	bool RenderParams::IsKind4()
	{
		return unknown48 == 4;
	}

	// FUNCTION: ENGINE 0x1074EEC0
	bool RenderParams::IsKind8()
	{
		return unknown48 == 8;
	}

	// FUNCTION: ENGINE 0x1074EED0
	bool RenderParams::IsKind361()
	{
		return unknown48 == 3 || unknown48 == 6 || unknown48 == 1;
	}

	// FUNCTION: ENGINE 0x1074EEF0
	bool RenderParams::IsKind254()
	{
		return unknown48 == 2 || unknown48 == 5 || unknown48 == 4;
	}

	// FUNCTION: ENGINE 0x1074EF20
	int RenderParams::GetUnknown1074EF20()
	{
		return IsKind254() ? 1 : 2;
	}
}
