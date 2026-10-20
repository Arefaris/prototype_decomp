// pure3d::GpuSkin: the instanced skin the device draws with a vertex shader (the unit after skin.cpp in
// code/pure3d/atg4/platform/win32/). Names are guesses.
#include "code/core/bitfield.h"
#include "code/core/refptr.h"
#include "code/pure3d/context.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/vertexdeclaration.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/shader.h"
#include "code/pure3d/shaderparameters.h"

// This unit's copies of the reference helpers for the bone palette
// FUNCTION: ENGINE 0x1072E0B0
template void core::SafeRelease<pure3d::MatrixPaletteList>(pure3d::MatrixPaletteList*& object);

// FUNCTION: ENGINE 0x1072E0D0
template void core::RefAssign<pure3d::MatrixPaletteList>(pure3d::MatrixPaletteList*& pointer,
	pure3d::MatrixPaletteList* object);

namespace pure3d
{
	// 0x1127F358: the Direct3D 9 view of the pddi device the gpu skin takes its buffers from (name guess)
	extern dxDevice* gPddiDx;
	// 0x1127F1B8, 0x1127F1DC: the names of the shader parameters that set the primitive's bits 6 and 7 (name guesses)
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1B8;
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1DC;

	// The reference helpers of the core region the states use for their buffer (0x1005E540 takes a reference to the
	// object and lets go of the one held, 0x1007F230 lets go and clears; name guesses)
	void AssignCoreRef(core::IRefCount*& pointer, core::IRefCount* object);
	void ReleaseCoreRef(core::IRefCount*& pointer);

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
			unknown13C = indexBuffer;
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
		return (int*)buffer;
	}

	// FUNCTION: ENGINE 0x1072DF10
	void GpuSkin::Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
		const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding)
	{
		GpuSkinState* gpuState = (GpuSkinState*)state;
		int kind = gpuState->GetBuffer()[0x38 / 4];
		void* source = gpuState->GetBindingSource();
		PrimDrawDescGpuSkin desc(((PrimBufferOwner*)source)->format, world, 1, (void**)&unknown138, (int)unknown13C, 0,
			unknown1C, kind, (int)unknown140 + 8, 0);
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

	// FUNCTION: ENGINE 0x1072DF00
	void GpuSkin::GetIndexDescription(IndexBufferDescription* description)
	{
		unknown13C->GetDescription(description);
	}

	// FUNCTION: ENGINE 0x1072E070
	void GpuSkin::LockIndices(dxIndexBufferState* lock)
	{
		unknown13C->Lock(lock);
	}

	// FUNCTION: ENGINE 0x1072E080
	void GpuSkin::UnlockBuffer()
	{
		if (unknown138 != 0)
		{
			unknown138->Unlock();
		}
	}

	// FUNCTION: ENGINE 0x1072E090
	void GpuSkin::UnlockIndices()
	{
		unknown13C->Unlock();
	}

	// FUNCTION: ENGINE 0x1072E200
	GpuSkin::~GpuSkin()
	{
		core::SafeRelease(unknown138);
		Unknown107076C0(&unknown13C);
		core::SafeRelease(unknown140);
	}

	// FUNCTION: ENGINE 0x1072E290
	void GpuSkin::SetPalette(MatrixPaletteList* palettes)
	{
		core::RefAssign(unknown140, palettes);
	}

	// FUNCTION: ENGINE 0x1072E380
	void GpuSkin::LockBuffer(dxVertexDeclaration* lock)
	{
		if (unknown138 != 0)
		{
			unknown138->Lock(lock, 0);
		}
		else
		{
			dxVertexDeclaration empty;
			*lock = empty;
		}
	}

	// The shader's flags are mirrored into the primitive's, two of them inverted
#pragma auto_inline(off)
	// FUNCTION: ENGINE 0x1072E2F0
	void GpuSkin::SetFlagsFromShader()
	{
		if (unknown18 != 0)
		{
			flagWord.SetBit(3, ((Shader*)unknown18)->flags.Test(2));
			flagWord.SetBit(1, ((Shader*)unknown18)->flags.Test(0));
			flagWord.SetBit(2, ((Shader*)unknown18)->flags.Test(1));
			flagWord.SetBit(4, !((Shader*)unknown18)->flags.Test(2));
			flagWord.SetBit(5, !((Shader*)unknown18)->flags.Test(2));
		}
	}
#pragma auto_inline(on)

	// FUNCTION: ENGINE 0x1072E4F0
	void GpuSkin::Unknown4(Shader* shader)
	{
		Primitive::Unknown4(shader);
		SetFlagsFromShader();
	}

	// FUNCTION: ENGINE 0x1072DDA0
	GpuSkinState::GpuSkinState(GpuSkin* skin) : PrimitiveState(skin), buffer(0), unknown20(0), shaderController(0)
	{
		primitive->GetBoundingBox(&bounds);
	}

	// FUNCTION: ENGINE 0x1072DDE0
	void GpuSkinState::Update(float dt)
	{
		int frame = pddi->GetFrameCount(0);
		if (frame != unknown20)
		{
			if (shaderController != 0)
			{
				shaderController->Advance(dt, false);
			}
			unknown20 = frame;
		}
	}

	// FUNCTION: ENGINE 0x1072DE20
	void GpuSkinState::Unknown5()
	{
		if (shaderController != 0)
		{
			shaderController->Reset();
		}
	}

	// FUNCTION: ENGINE 0x1072DE40
	bool GpuSkinState::Unknown6()
	{
		if (shaderController != 0 && !shaderController->Unknown20())
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1072DE60
	void GpuSkinState::GetBoundingBox(math::AABB* box)
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

	// FUNCTION: ENGINE 0x1072DE90
	void GpuSkinState::SetBoundingBox(const math::AABB& box)
	{
		bounds.max.x = box.max.x;
		bounds.max.y = box.max.y;
		bounds.max.z = box.max.z;
		bounds.min.x = box.min.x;
		bounds.min.y = box.min.y;
		bounds.min.z = box.min.z;
	}

	// FUNCTION: ENGINE 0x1072DED0
	ShaderAnimationController* GpuSkinState::GetShaderController()
	{
		return shaderController;
	}

	// FUNCTION: ENGINE 0x1072DEE0
	void GpuSkinState::Unknown8(void* source)
	{
		if (source == 0)
		{
			source = unknownC;
		}
		if (shaderController != 0)
		{
			shaderController->SetBindingSource(source);
		}
	}

	// FUNCTION: ENGINE 0x1072E100
	GpuSkinState::GpuSkinState(const GpuSkinState& other) : PrimitiveState(other), buffer(0), unknown20(0),
		shaderController(0)
	{
		bounds.max.x = other.bounds.max.x;
		bounds.max.y = other.bounds.max.y;
		bounds.max.z = other.bounds.max.z;
		bounds.min.x = other.bounds.min.x;
		bounds.min.y = other.bounds.min.y;
		bounds.min.z = other.bounds.min.z;
		AssignCoreRef(buffer, other.buffer);
		if (other.shaderController != 0)
		{
			core::RefAssign(shaderController, other.shaderController->Clone());
		}
	}

	// The scalar deleting destructor the compiler writes for the destructor below
	// FUNCTION: ENGINE 0x1072E2B0

	// FUNCTION: ENGINE 0x1072E190
	GpuSkinState::~GpuSkinState()
	{
		ReleaseCoreRef(buffer);
		core::SafeRelease(shaderController);
	}

	// FUNCTION: ENGINE 0x1072E1C0
	PrimitiveState* GpuSkinState::Unknown3()
	{
		return new GpuSkinState(*this);
	}

	// FUNCTION: ENGINE 0x1072E1E0
	void GpuSkinState::SetShaderController(ShaderAnimationController* controller)
	{
		core::RefAssign(shaderController, controller);
	}
}
