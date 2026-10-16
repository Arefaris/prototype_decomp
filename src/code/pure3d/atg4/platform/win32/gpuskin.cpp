// pure3d::GpuSkin: the instanced skin the device draws with a vertex shader (the unit after skin.cpp in
// code/pure3d/atg4/platform/win32/). Names are guesses.
#include "code/pure3d/pddi.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/shaderparameters.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1072DEC0
	int* GpuSkinState::GetBuffer()
	{
		return buffer;
	}

	// FUNCTION: ENGINE 0x1072DF10
	void GpuSkin::Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
		const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding)
	{
		GpuSkinState* gpuState = (GpuSkinState*)state;
		int kind = gpuState->GetBuffer()[0x38 / 4];
		void* source = gpuState->GetBindingSource();
		PrimDrawDesc desc(((PrimBufferOwner*)source)->format, world, 1, (void**)&unknown138, unknown13C, 0, unknown1C,
			kind, unknown140 + 8, 0);
		if (binding != 0)
		{
			desc.format = ((PrimBufferOwner*)binding)->format;
		}
		pddi->Unknown2(shader, &desc, parameters);
	}
}
