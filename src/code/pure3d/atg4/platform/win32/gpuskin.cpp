// pure3d::GpuSkin: the instanced skin the device draws with a vertex shader (the unit after skin.cpp in
// code/pure3d/atg4/platform/win32/). Names are guesses.
#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/shaderparameters.h"

namespace pure3d
{
	// 0x1127F358: the Direct3D 9 view of the pddi device the gpu skin takes its buffers from (name guess)
	extern dxDevice* gPddiDx;
	// 0x1127F1B8, 0x1127F1DC: the names of the shader parameters that set the primitive's bits 6 and 7 (name guesses)
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1B8;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1DC;

	// The scalar deleting destructor the compiler writes for the destructor (0x1072E200, not reconstructed)
	// FUNCTION: ENGINE 0x1072E2D0

	// FUNCTION: ENGINE 0x1072E3E0
	GpuSkin::GpuSkin(const VertexBufferDescription* vertices, const IndexBufferDescription* indices, unsigned int kind)
		: Primitive(0x4000), unknown1C(kind)
	{
		unknown140 = 0;
		centre.Set(0.0f, 0.0f, 0.0f);
		unknown16C = -1;
		parameters = *vertices;
		unknown138 = 0;
		dxVertexBuffer* vertexBuffer = gPddiDx->NewVertexBuffer(vertices);
		unknown138 = vertexBuffer;
		vertexBuffer->AddRef();
		unknown13C = 0;
		if ((unsigned int)indices->count > 0)
		{
			dxIndexBuffer* indexBuffer = gPddiDx->NewIndexBuffer(indices);
			unknown13C = (unsigned int)indexBuffer;
			indexBuffer->AddRef();
		}
		for (int i = 0; i < parameters.unknown4; i++)
		{
			if (gName1127F1B8 == parameters.parameters[i].name)
			{
				flagWord.SetBit(6, true);
			}
			else if (gName1127F1DC == parameters.parameters[i].name)
			{
				flagWord.SetBit(7, true);
			}
		}
	}
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
		PrimDrawDescGpuSkin desc(((PrimBufferOwner*)source)->format, world, 1, (void**)&unknown138, unknown13C, 0,
			unknown1C, kind, unknown140 + 8, 0);
		if (binding != 0)
		{
			desc.format = ((PrimBufferOwner*)binding)->format;
		}
		pddi->Unknown2(shader, &desc, parameters);
	}

	// FUNCTION: ENGINE 0x1072DFA0
	bool GpuSkin::FillBatch(void* batch, PrimitiveState* state, bool* unknown)
	{
		*unknown = false;
		return false;
	}

	// FUNCTION: ENGINE 0x1072DFB0
	void GpuSkin::GetBoundingBox(math::AABB* box)
	{
		math::Vector* outMax = &box->max;
		math::Vector* outMin = &box->min;
		outMax->x = bounds.max.x;
		outMax->y = bounds.max.y;
		outMax->z = bounds.max.z;
		outMin->x = bounds.min.x;
		outMin->y = bounds.min.y;
		outMin->z = bounds.min.z;
	}

	// FUNCTION: ENGINE 0x1072DFF0
	void GpuSkin::SetBoundingBox(const math::AABB& box)
	{
		bounds.max.x = box.max.x;
		bounds.max.y = box.max.y;
		bounds.max.z = box.max.z;
		bounds.min.x = box.min.x;
		bounds.min.y = box.min.y;
		bounds.min.z = box.min.z;
	}

	// FUNCTION: ENGINE 0x1072E030
	void GpuSkin::SetCentre(const math::Vector4& value)
	{
		centre.x = value.x;
		centre.y = value.y;
		centre.z = value.z;
		centre.w = value.w;
	}

	// The centre is a Vector4 but the caller's pointer (the vtable takes a Vector) is followed by a fourth float in
	// the engine too: it copies all four components
	// FUNCTION: ENGINE 0x1072E260
	void GpuSkin::GetCentre(math::Vector* out)
	{
		out[0].x = centre.x;
		out[0].y = centre.y;
		out[0].z = centre.z;
		out[1].x = centre.w;
	}

	// FUNCTION: ENGINE 0x1072E240
	int GpuSkin::GetUnknown9()
	{
		return unknown16C;
	}

	// FUNCTION: ENGINE 0x1072E250
	void GpuSkin::SetUnknown10(int value)
	{
		unknown16C = value;
	}
}
