// pure3d::Mesh and pure3d::MeshState (unit around 0x10707400 - 0x10709A00; file name guessed from the classes).
// Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/context.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/vertexdeclaration.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/shader.h"
#include "code/pure3d/shaderparameters.h"

// This unit's copies of the reference helpers for the controllers and the offsets of a state
// FUNCTION: ENGINE 0x10707710
template void core::RefAssign<pure3d::ShaderAnimationController>(pure3d::ShaderAnimationController*& pointer,
	pure3d::ShaderAnimationController* object);

// FUNCTION: ENGINE 0x107077A0
template void core::SafeRelease<pure3d::ShaderAnimationController>(pure3d::ShaderAnimationController*& object);

// FUNCTION: ENGINE 0x107077E0
template void core::SafeRelease<pure3d::VertexRegionAnimController>(pure3d::VertexRegionAnimController*& object);

// FUNCTION: ENGINE 0x107076E0
template void core::RefAssign<pure3d::VertexOffsetList>(pure3d::VertexOffsetList*& pointer, pure3d::VertexOffsetList* object);

// FUNCTION: ENGINE 0x10707740
template void core::RefAssign<pure3d::SimpleFrameController>(pure3d::SimpleFrameController*& pointer,
	pure3d::SimpleFrameController* object);

// FUNCTION: ENGINE 0x10707770
template void core::RefAssign<pure3d::VertexRegionAnimController>(pure3d::VertexRegionAnimController*& pointer,
	pure3d::VertexRegionAnimController* object);

// FUNCTION: ENGINE 0x107077C0
template void core::SafeRelease<pure3d::SimpleFrameController>(pure3d::SimpleFrameController*& object);

// FUNCTION: ENGINE 0x10707800
template void core::SafeRelease<pure3d::VertexOffsetList>(pure3d::VertexOffsetList*& object);

namespace pure3d
{
	// 0x1127F358: the Direct3D 9 view of the pddi device the mesh takes its buffers from (name guess)
	extern dxDevice* gPddiDx;

	// FUNCTION: ENGINE 0x10707280
	void Mesh::Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
		const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding)
	{
		void* source = binding;
		if (binding == 0)
		{
			source = unknown18;
		}
		PrimGroupList* parts[2];
		if (state == 0)
		{
			PrimDrawDesc desc(((PrimBufferOwner*)source)->format, world, 1, (void**)&unknown20, unknown24, unknown1C, 0, 0,
				0);
			pddi->DrawPrimitive(shader, &desc, parameters);
		}
		else
		{
			if (binding == 0)
			{
				source = state->GetBindingSource();
			}
			PartStateView* view = (PartStateView*)state;
			PrimGroupList** slot = &view->groups[view->unknown38];
			if (*slot != 0)
			{
				parts[0] = unknown20;
				parts[1] = *slot;
				PrimDrawDesc desc(((PrimBufferOwner*)source)->format, world, 2, (void**)parts, unknown24, unknown1C, 0, 0,
					0);
				pddi->DrawPrimitive(shader, &desc, parameters);
			}
			else
			{
				PrimDrawDesc desc(((PrimBufferOwner*)source)->format, world, 1, (void**)&unknown20, unknown24, unknown1C,
					0, 0, 0);
				pddi->DrawPrimitive(shader, &desc, parameters);
			}
		}
	}

	// FUNCTION: ENGINE 0x10707330
	bool Mesh::FillBatch(void* batch, PrimitiveState* state, bool* unknown)
	{
		PrimBatch* data = (PrimBatch*)batch;
		data->unknown70 = unknown1C;
		data->unknown74 = 0;
		data->unknown78 = 0;
		data->unknown7C = 0;
		data->unknown80 = 0;
		data->unknown28 = 0;
		unknown24->PrepareBatch(data);
		*unknown = false;
		PrimGroupList* group = 0;
		if (state != 0)
		{
			PartStateView* view = (PartStateView*)state;
			PrimGroupList* found = view->groups[view->unknown38];
			if (found != 0)
			{
				group = found->AddGroup(data, 0);
				*unknown = true;
			}
		}
		unknown20->AddGroup(data, group);
		return true;
	}

	// FUNCTION: ENGINE 0x107073A0
	void Mesh::GetBoundingBox(math::AABB* box)
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

	// FUNCTION: ENGINE 0x107073E0
	void Mesh::SetBoundingBox(const math::AABB& box)
	{
		bounds.max.x = box.max.x;
		bounds.max.y = box.max.y;
		bounds.max.z = box.max.z;
		bounds.min.x = box.min.x;
		bounds.min.y = box.min.y;
		bounds.min.z = box.min.z;
	}

	// FUNCTION: ENGINE 0x10707420
	void Mesh::SetBoundingSphere(const math::Sphere& value)
	{
		sphere.centre.x = value.centre.x;
		sphere.centre.y = value.centre.y;
		sphere.centre.z = value.centre.z;
		sphere.radius = value.radius;
	}

	// FUNCTION: ENGINE 0x10707460
	unsigned int Mesh::GetUnknown148() const
	{
		return unknown148;
	}

	// FUNCTION: ENGINE 0x10707470
	void Mesh::LockVertices(dxVertexDeclaration* lock)
	{
		((dxVertexBuffer*)unknown20)->Lock(lock, 0);
	}

	// FUNCTION: ENGINE 0x10707490
	void Mesh::LockIndices(dxIndexBufferState* lock)
	{
		((dxIndexBuffer*)unknown24)->Lock(lock);
	}

	// FUNCTION: ENGINE 0x107074A0
	void Mesh::UnlockVertices()
	{
		((dxVertexBuffer*)unknown20)->Unlock();
	}

	// FUNCTION: ENGINE 0x107074B0
	void Mesh::Unknown107074B0()
	{
	}

	// FUNCTION: ENGINE 0x107074C0
	void Mesh::UnlockIndices()
	{
		((dxIndexBuffer*)unknown24)->Unlock();
	}

	// FUNCTION: ENGINE 0x107074D0
	bool Mesh::HasUnknown140()
	{
		return unknown140 != 0;
	}

	// FUNCTION: ENGINE 0x107078B0
	void Mesh::GetCentre(math::Vector* out)
	{
		out[0].x = sphere.centre.x;
		out[0].y = sphere.centre.y;
		out[0].z = sphere.centre.z;
		out[1].x = sphere.radius;
	}

	// FUNCTION: ENGINE 0x10707890
	int Mesh::GetUnknown9()
	{
		return unknown178;
	}

	// FUNCTION: ENGINE 0x107078A0
	void Mesh::SetUnknown10(int value)
	{
		unknown178 = value;
	}

	// FUNCTION: ENGINE 0x10707650
	void MeshState::GetBoundingBox(math::AABB* box)
	{
		primitive->GetBoundingBox(box);
	}

	// FUNCTION: ENGINE 0x10707640
	VertexOffsetList* MeshState::GetExpression()
	{
		return expression;
	}

	// FUNCTION: ENGINE 0x10707660
	FrameController* MeshState::GetController1()
	{
		return controller1;
	}

	// FUNCTION: ENGINE 0x10707670
	FrameController* MeshState::GetController2()
	{
		return controller2;
	}

	// FUNCTION: ENGINE 0x10707680
	FrameController* MeshState::GetController3()
	{
		return controller3;
	}

	// FUNCTION: ENGINE 0x10707A60
	void MeshState::SetController1(FrameController* value)
	{
		core::RefAssign(controller1, (ShaderAnimationController*)value);
	}

	// FUNCTION: ENGINE 0x10707AA0
	void MeshState::SetController2(FrameController* value)
	{
		core::RefAssign(controller2, (SimpleFrameController*)value);
	}

	// FUNCTION: ENGINE 0x10707AC0
	void MeshState::SetController3(FrameController* value)
	{
		core::RefAssign(controller3, (VertexRegionAnimController*)value);
	}

	// FUNCTION: ENGINE 0x107075A0
	void MeshState::Unknown5()
	{
		if (controller1 != 0)
		{
			controller1->Reset();
		}
		if (controller20 != 0)
		{
			controller20->Reset();
		}
		if (controller2 != 0)
		{
			controller2->Reset();
		}
		if (controller3 != 0)
		{
			controller3->Reset();
		}
	}

	// FUNCTION: ENGINE 0x107075F0
	bool MeshState::Unknown6()
	{
		if (controller1 != 0 && !controller1->Unknown20())
		{
			return false;
		}
		if (controller20 != 0 && !controller20->Unknown20())
		{
			return false;
		}
		if (controller2 != 0 && !controller2->Unknown20())
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10707690
	void MeshState::Unknown8(void* source)
	{
		if (source == 0)
		{
			source = unknownC;
		}
		if (controller1 != 0)
		{
			controller1->SetBindingSource(source);
		}
		if (controller20 != 0)
		{
			controller20->SetBindingSource(source);
		}
	}

	// FUNCTION: ENGINE 0x107076C0
	void Unknown107076C0(dxIndexBuffer** buffer)
	{
		if (*buffer != 0)
		{
			(*buffer)->Release();
			*buffer = 0;
		}
	}

	// FUNCTION: ENGINE 0x10707E90
	// EQUIVALENT: instruction selection (the engine masks the format word and compares the byte, where ours tests the bit; 86.9 %)
	Mesh::Mesh(const ShaderParameters* vertices, const ShaderParameters* stateVertices,
		const IndexBufferDescription* indices, int kind) : Primitive(2), unknown1C(kind)
	{
		unknown140 = 0;
		sphere.centre.x = 0.0f;
		sphere.centre.y = 0.0f;
		sphere.centre.z = 0.0f;
		unknown174 = true;
		unknown175 = true;
		unknown178 = -1;
		vertexBuffer = gPddiDx->NewVertexBuffer((const VertexBufferDescription*)vertices);
		vertexBuffer->AddRef();
		if (stateVertices != 0)
		{
			int size = 0;
			stateParameters = *stateVertices;
			for (unsigned int i = 0; i < (unsigned int)stateParameters.unknown4; i++)
			{
				stateParameters.parameters[i].value = size;
				size += stateParameters.GetElementSize(i);
			}
			for (unsigned int i = 0; i < (unsigned int)stateParameters.unknown4; i++)
			{
				stateParameters.parameters[i].unknown9 = size;
			}
			unknown144 = stateParameters.unknown0 * size;
			unknown140 = new unsigned char[unknown144];
		}
		indexBuffer = 0;
		if (indices != 0 && (unsigned int)indices->count > 0)
		{
			indexBuffer = gPddiDx->NewIndexBuffer(indices);
			indexBuffer->AddRef();
		}
		unsigned int format = vertices->unknownC;
		unknown148 = format;
		if ((format & 0x10) == 0x10)
		{
			flagWord.SetBit(6, true);
		}
		if ((unknown148 & 0x1000) != 0)
		{
			flagWord.SetBit(7, true);
		}
	}

	// The scalar deleting destructor the compiler writes for the destructor below
	// FUNCTION: ENGINE 0x10707AE0

	// FUNCTION: ENGINE 0x10707840
	Mesh::~Mesh()
	{
		if (unknown140 != 0)
		{
			delete[] (unsigned char*)unknown140;
		}
		core::SafeRelease(vertexBuffer);
		if (indexBuffer != 0)
		{
			Unknown107076C0(&indexBuffer);
		}
	}

	// The mesh takes the flags of the shader it is drawn with; the two vertex lighting flags follow the bytes at
	// +0x174 / +0x175
#pragma auto_inline(off)
	// FUNCTION: ENGINE 0x10707BB0
	void Mesh::SetFlagsFromShader()
	{
		if (unknown18 != 0)
		{
			flagWord.SetBit(8, ((Shader*)unknown18)->flags.Test(4));
			flagWord.SetBit(3, ((Shader*)unknown18)->flags.Test(2));
			flagWord.SetBit(1, ((Shader*)unknown18)->flags.Test(0));
			flagWord.SetBit(2, ((Shader*)unknown18)->flags.Test(1));
			bool value;
			if (unknown174 && !flagWord.Test(3))
			{
				value = true;
			}
			else
			{
				value = false;
			}
			flagWord.SetBit(4, value);
			if (unknown175 && !flagWord.Test(3))
			{
				value = true;
			}
			else
			{
				value = false;
			}
			flagWord.SetBit(5, value);
		}
	}
#pragma auto_inline(on)

	// FUNCTION: ENGINE 0x10707FF0
	void Mesh::Unknown4(Shader* shader)
	{
		Primitive::Unknown4(shader);
		SetFlagsFromShader();
	}

	// FUNCTION: ENGINE 0x10708010
	void Mesh::SetFlag174(bool value)
	{
		unknown174 = value;
		SetFlagsFromShader();
	}

	// FUNCTION: ENGINE 0x10708030
	void Mesh::SetFlag175(bool value)
	{
		unknown175 = value;
		SetFlagsFromShader();
	}

	// FUNCTION: ENGINE 0x107078E0
	void Mesh::DescribeStateVertices(dxVertexDeclaration* lock)
	{
		lock->unknown108 = (int)unknown140;
		lock->unknown0 = stateParameters.unknown0;
		lock->unknown4 = stateParameters.unknown4;
		for (int i = 0; i < stateParameters.unknown4; i++)
		{
			lock->elements[i] = stateParameters.parameters[i];
		}
	}

	// FUNCTION: ENGINE 0x10707970
	MeshState::MeshState(Mesh* mesh, const ShaderParameters* vertices, VertexOffsetList* list) : PrimitiveState(mesh)
	{
		controller1 = 0;
		controller20 = 0;
		controller2 = 0;
		controller3 = 0;
		expression = 0;
		unknown38 = 0;
		core::RefAssign(expression, list);
		if (vertices != 0)
		{
			for (int i = 0; i < 2; i++)
			{
				buffers[i] = gPddiDx->NewVertexBuffer((const VertexBufferDescription*)vertices);
				buffers[i]->AddRef();
			}
		}
		else
		{
			buffers[0] = 0;
			buffers[1] = 0;
		}
	}

	// The state's binding source: made from the primitive's shader when the state has none yet
	inline void* EnsureBindingSource(PrimitiveState* state)
	{
		Shader*& binding = (Shader*&)state->unknownC;
		if (binding == 0)
		{
			core::RefAssign(binding, (Shader*)((PartBindingSource*)state->primitive->unknown18)->CreateBinding());
		}
		return binding;
	}

	// FUNCTION: ENGINE 0x10707CA0
	// EQUIVALENT: instruction selection (the engine loads the second controller into a register before testing it, ours
	// tests the memory operand; 77 %)
	MeshState::MeshState(const MeshState& other) : PrimitiveState(other)
	{
		controller1 = 0;
		controller20 = 0;
		controller2 = 0;
		controller3 = 0;
		expression = 0;
		unknown38 = 0;
		if (other.expression != 0)
		{
			core::RefAssign(expression, new VertexOffsetList(*other.expression));
		}
		if (other.buffers[0] != 0)
		{
			ShaderParameters description;
			other.buffers[0]->Unknown10625FA0(&description);
			for (int i = 0; i < 2; i++)
			{
				buffers[i] = gPddiDx->NewVertexBuffer((const VertexBufferDescription*)&description);
				buffers[i]->AddRef();
			}
		}
		else
		{
			buffers[0] = 0;
			buffers[1] = 0;
		}
		if (other.controller1 != 0)
		{
			core::RefAssign(controller1, (ShaderAnimationController*)other.controller1->Clone());
			controller1->SetBindingSource(EnsureBindingSource(this));
		}
		if (other.controller20 != 0)
		{
			core::RefAssign(controller20, (ShaderAnimationController*)other.controller20->Clone());
			controller20->SetBindingSource(EnsureBindingSource(this));
		}
		if (other.controller2 != 0)
		{
			core::RefAssign(controller2, (SimpleFrameController*)other.controller2->Clone());
			if (dynamic_cast<VertexAnimController*>(controller2) != 0)
			{
				core::RefAssign(controller2, (SimpleFrameController*)other.controller2->Clone());
				((VertexAnimController*)controller2)->SetMeshState(this);
			}
			else
			{
				core::RefAssign(controller2, other.controller2);
			}
		}
		if (other.controller3 != 0)
		{
			core::RefAssign(controller3, (VertexRegionAnimController*)other.controller3->Clone());
			controller3->SetMeshState(this);
		}
	}

	// FUNCTION: ENGINE 0x10707E70
	PrimitiveState* MeshState::Unknown3()
	{
		return new MeshState(*this);
	}

	// The scalar deleting destructor the compiler writes for the destructor below
	// FUNCTION: ENGINE 0x10707C80

	// FUNCTION: ENGINE 0x10707A00
	MeshState::~MeshState()
	{
		core::SafeRelease(controller1);
		core::SafeRelease(controller20);
		core::SafeRelease(controller2);
		core::SafeRelease(controller3);
		core::SafeRelease(expression);
		for (int i = 1; i >= 0; i--)
		{
			core::SafeRelease(buffers[i]);
		}
	}

	// FUNCTION: ENGINE 0x107074F0
	void MeshState::Update(float dt)
	{
		int saved = unknown38;
		if (controller3 == 0)
		{
			unknown38 = saved + 1;
			if (unknown38 >= 2)
			{
				unknown38 = 0;
			}
		}
		else if (controller3->GetUnknownD8() == true)
		{
			unknown38 = (unknown38 + 1) % 2;
		}
		if (controller1 != 0)
		{
			controller1->Advance(dt, true);
		}
		if (controller20 != 0)
		{
			controller20->Advance(dt, true);
		}
		if (controller2 != 0)
		{
			controller2->Advance(dt, true);
			if (!((VertexAnimController*)controller2)->GetUnknown50())
			{
				unknown38 = saved;
			}
		}
		if (controller3 != 0)
		{
			controller3->Advance(0.0f, true);
		}
	}

	// FUNCTION: ENGINE 0x102E8BB0
	// A kept copy of an inline constructor
	ShaderParameters::ShaderParameters() : unknown0(0), unknown4(0), unknown8(2), unknownC(0)
	{
		unknown110 = false;
		unknown114 = 0;
	}

	// FUNCTION: ENGINE 0x10707B00
	ShaderParameters& ShaderParameters::operator=(const ShaderParameters& other)
	{
		unknown0 = other.unknown0;
		unknown4 = other.unknown4;
		unknown8 = other.unknown8;
		unknownC = other.unknownC;
		for (int i = 0; i < 16; i++)
		{
			parameters[i] = other.parameters[i];
		}
		unknown110 = other.unknown110;
		unknown114 = other.unknown114;
		return *this;
	}
}
