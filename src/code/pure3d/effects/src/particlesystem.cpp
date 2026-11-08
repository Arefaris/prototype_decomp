// pure3d::ParticleSystem and pure3d::ParticleSystemState (unit around 0x10709A00 - 0x1070E700; file name guessed
// from the classes). Names are guesses.
#include <math.h>

#include <new>

#include "code/core/refptr.h"
#include "code/pure3d/context.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/vertexdeclaration.h"
#include "code/math/matrix.h"
#include "code/pure3d/effects/multiarray.h"
#include "code/pure3d/effects/particlecontroller.h"
#include "code/pure3d/effects/particlesystem.h"
#include "code/pure3d/primitive.h"

// This unit's copies of the reference helpers for the renderer of a system
// FUNCTION: ENGINE 0x1070A490
template void core::RefAssign<pure3d::ParticleRenderer>(pure3d::ParticleRenderer*& pointer, pure3d::ParticleRenderer* object);

// FUNCTION: ENGINE 0x1070A4C0
template void core::SafeRelease<pure3d::ParticleRenderer>(pure3d::ParticleRenderer*& object);

// The copies the states' constructors and destructors use for what a state holds
// FUNCTION: ENGINE 0x1070A4E0
template void core::RefAssign<pure3d::ParticleSystemState::SharedDetails>(pure3d::ParticleSystemState::SharedDetails*& pointer,
	pure3d::ParticleSystemState::SharedDetails* object);

// FUNCTION: ENGINE 0x1070A540
template void core::RefAssign<pure3d::RefCountedBoolChannel>(pure3d::RefCountedBoolChannel*& pointer,
	pure3d::RefCountedBoolChannel* object);

// FUNCTION: ENGINE 0x1070A570
template void core::RefAssign<pure3d::RefCountedFloat1Channel>(pure3d::RefCountedFloat1Channel*& pointer,
	pure3d::RefCountedFloat1Channel* object);

// FUNCTION: ENGINE 0x1070A5A0
template void core::RefAssign<pure3d::RefCountedVectorChannel>(pure3d::RefCountedVectorChannel*& pointer,
	pure3d::RefCountedVectorChannel* object);

// FUNCTION: ENGINE 0x1070A710
template void core::SafeRelease<pure3d::RefCountedBoolChannel>(pure3d::RefCountedBoolChannel*& object);

// FUNCTION: ENGINE 0x1070A730
template void core::SafeRelease<pure3d::ParticleController>(pure3d::ParticleController*& object);

// FUNCTION: ENGINE 0x1070A750
template void core::SafeRelease<pure3d::ParticleGenerator>(pure3d::ParticleGenerator*& object);

// FUNCTION: ENGINE 0x1070A790
template void core::SafeRelease<pure3d::ParticleSystemState::SharedDetails>(pure3d::ParticleSystemState::SharedDetails*& object);

// FUNCTION: ENGINE 0x1070A7B0
template void core::SafeRelease<pure3d::RefCountedFloat1Channel>(pure3d::RefCountedFloat1Channel*& object);

// FUNCTION: ENGINE 0x1070A7D0
template void core::SafeRelease<pure3d::RefCountedVectorChannel>(pure3d::RefCountedVectorChannel*& object);

// FUNCTION: ENGINE 0x1070A7F0
template void core::SafeRelease<pure3d::ParticleSystemState>(pure3d::ParticleSystemState*& object);

// FUNCTION: ENGINE 0x1070A8B0
template void core::RefAssign<pure3d::ParticleSystemState>(pure3d::ParticleSystemState*& pointer,
	pure3d::ParticleSystemState* object);

// FUNCTION: ENGINE 0x1070A880
template void core::RefAssign<pure3d::dxVertexBuffer>(pure3d::dxVertexBuffer*& pointer, pure3d::dxVertexBuffer* object);

// FUNCTION: ENGINE 0x1070A8E0
template void core::RefAssign<pure3d::ParticleGenerator>(pure3d::ParticleGenerator*& pointer,
	pure3d::ParticleGenerator* object);

// The arrays of the attributes of a block of particles
// FUNCTION: ENGINE 0x1070B220
template pure3d::particles::MultiArray<57>::MultiArray();

// FUNCTION: ENGINE 0x1070B260
template pure3d::particles::MultiArray<57>::~MultiArray();

// FUNCTION: ENGINE 0x1070A440
template void pure3d::particles::MultiArray<57>::Free();

// FUNCTION: ENGINE 0x1070B550
template pure3d::particles::AttributeData<57>::AttributeData();

// FUNCTION: ENGINE 0x1070B5C0
template pure3d::particles::AttributeData<57>::~AttributeData();

// FUNCTION: ENGINE 0x1070AFE0
template pure3d::particles::Span pure3d::particles::AttributeData<57>::GetSpan0(int index);

// FUNCTION: ENGINE 0x1070B010
template pure3d::particles::Span pure3d::particles::AttributeData<57>::GetSpan0(int index) const;

// FUNCTION: ENGINE 0x1070B040
template pure3d::particles::Span pure3d::particles::AttributeData<57>::GetSpan1(int index);

// FUNCTION: ENGINE 0x1070B070
template pure3d::particles::Span pure3d::particles::AttributeData<57>::GetSpan1(int index) const;

// FUNCTION: ENGINE 0x1070B0A0
template pure3d::particles::Span pure3d::particles::AttributeData<57>::GetSpan2(int index);

// FUNCTION: ENGINE 0x1070B0D0
template pure3d::particles::Span pure3d::particles::AttributeData<57>::GetSpan2(int index) const;

// FUNCTION: ENGINE 0x1070B100
template pure3d::particles::Span pure3d::particles::AttributeData<57>::GetSpan3(int index);

// FUNCTION: ENGINE 0x1070B130
template pure3d::particles::Span pure3d::particles::AttributeData<57>::GetSpan3(int index) const;

// FUNCTION: ENGINE 0x1070B160
template int pure3d::particles::AttributeData<57>::GetCount0() const;

// FUNCTION: ENGINE 0x1070B1C0
template bool pure3d::particles::AttributeData<57>::IsEmpty1(int index) const;

// FUNCTION: ENGINE 0x1070B1E0
template bool pure3d::particles::AttributeData<57>::IsEmpty2(int index) const;

// FUNCTION: ENGINE 0x1070B200
template bool pure3d::particles::AttributeData<57>::IsEmpty3(int index) const;

namespace pure3d
{
	// FUNCTION: ENGINE 0x1070CC70
	ParticleData::ParticleData()
	{
	}

	// FUNCTION: ENGINE 0x1070CC90
	ParticleData::~ParticleData()
	{
	}

	// FUNCTION: ENGINE 0x10709CE0
	bool ParticleSystemState::GetUnknown490()
	{
		return unknown490;
	}

	// FUNCTION: ENGINE 0x10709D60
	math::Matrix* ParticleSystemState::GetTransform()
	{
		return &transform;
	}

	// FUNCTION: ENGINE 0x10709D70
	void* ParticleSystemState::GetGeneratorUnknown10()
	{
		return inheritUnknown4BC ? parent->GetGeneratorUnknown10() : &generator->unknown10;
	}

	// FUNCTION: ENGINE 0x10709CC0
	void ParticleSystemState::Unknown10709CC0(bool value)
	{
	}

	// FUNCTION: ENGINE 0x10709CD0
	void ParticleSystemState::Unknown10709CD0()
	{
	}

	// FUNCTION: ENGINE 0x10709E40
	void ParticleSystemState::Unknown10709E40(bool value)
	{
		unknown491 = value;
	}

	// FUNCTION: ENGINE 0x10709E50
	void ParticleSystemState::Unknown10709E50(float value)
	{
		unknown494 = value;
	}

	// FUNCTION: ENGINE 0x10709E70
	void ParticleSystemState::Unknown10709E70(float value)
	{
		unknown498 = value;
	}

	// FUNCTION: ENGINE 0x10709C40
	void ParticleSystemState::Update(float dt)
	{
		if (!(fabs(-dt) <= 0.00001f) && unknown4B8 && dt >= unknown4A8)
		{
			if (!unknown490 && unknown3FC != 0)
			{
				unknown3FC->Advance(dt, true);
			}
			if (unknown3F8 != 0)
			{
				unknown3F8->Advance(dt, true);
			}
		}
	}

	// FUNCTION: ENGINE 0x10709CF0
	bool ParticleSystemState::Unknown6()
	{
		return unknown3FC != 0 && generator != 0 && unknown3FC->Unknown20() && !generator->Unknown10741080();
	}

	// FUNCTION: ENGINE 0x10709D30
	void ParticleSystemState::SetTransform(const math::Matrix& value)
	{
		transform = value;
		if (generator != 0)
		{
			generator->SetTransform(value);
		}
	}

	// FUNCTION: ENGINE 0x1070D220
	// EQUIVALENT: instruction selection (the engine tests the controller pointer in memory and loads it again for the call,
	// ours loads it once; 31.5 %)
	void ParticleSystemState::Unknown5()
	{
		if (!inheritUnknown4BC)
		{
			generator->Unknown10742720();
			if (unknown3FC != 0)
			{
				unknown3FC->Reset();
			}
			Unknown1070C340();
		}
		transform.Identity();
		bounds.min.x = 0.0f;
		bounds.min.y = 0.0f;
		bounds.min.z = 0.0f;
		bounds.max.x = 0.0f;
		bounds.max.y = 0.0f;
		bounds.max.z = 0.0f;
	}

	// FUNCTION: ENGINE 0x1070D9A0
	void ParticleSystemState::GetBoundingBox(math::AABB* box)
	{
		if (inheritUnknown4BC)
		{
			parent->GetBoundingBox(box);
			return;
		}
		math::Vector* outMax = &box->max;
		math::Vector* outMin = &box->min;
		outMax->x = bounds.max.x;
		outMax->y = bounds.max.y;
		outMax->z = bounds.max.z;
		outMin->x = bounds.min.x;
		outMin->y = bounds.min.y;
		outMin->z = bounds.min.z;
	}

	// FUNCTION: ENGINE 0x10709AB0
	PSAsyncTaskCallback::PSAsyncTaskCallback()
	{
	}

	// FUNCTION: ENGINE 0x10709AE0
	ParticleSystem::ParticleSystem() : Primitive(0x10)
	{
		bounds.min.x = 0.0f;
		bounds.min.y = 0.0f;
		bounds.min.z = 0.0f;
		bounds.max.x = 0.0f;
		bounds.max.y = 0.0f;
		bounds.max.z = 0.0f;
		centre.x = 0.0f;
		centre.y = 0.0f;
		centre.z = 0.0f;
		centre.w = 0.0f;
	}

	// FUNCTION: ENGINE 0x1070AAA0
	ParticleSystem::ParticleSystem(const ParticleSystem& other) : Primitive(other)
	{
		core::RefAssign(renderer.pointer, other.renderer.pointer);
		bounds.min.Set(0.0f, 0.0f, 0.0f);
		bounds.max.Set(0.0f, 0.0f, 0.0f);
		centre.x = 0.0f;
		centre.y = 0.0f;
		centre.z = 0.0f;
		centre.w = 0.0f;
	}

	// FUNCTION: ENGINE 0x1070AB20
	ParticleSystem::~ParticleSystem()
	{
		core::SafeRelease(renderer.pointer);
	}

	// FUNCTION: ENGINE 0x10709B60
	void ParticleSystem::Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
		const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding)
	{
		renderer.pointer->Draw(shader, state, parameters);
	}

	// FUNCTION: ENGINE 0x10709B30
	void ParticleSystem::GetBoundingBox(math::AABB* box)
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

	// FUNCTION: ENGINE 0x1070AA80
	void ParticleSystem::GetCentre(math::Vector* out)
	{
		out[0].x = centre.x;
		out[0].y = centre.y;
		out[0].z = centre.z;
		out[1].x = centre.w;
	}

	// FUNCTION: ENGINE 0x10709BE0
	bool ParticleSystem::FillBatch(void* batch, PrimitiveState* state, bool* unknown)
	{
		*unknown = false;
		return false;
	}

	// FUNCTION: ENGINE 0x10709BD0
	ParticleRenderer* ParticleSystem::GetRenderer()
	{
		return renderer.pointer;
	}

	// FUNCTION: ENGINE 0x1070AB40
	void ParticleSystem::SetRenderer(ParticleRenderer* newRenderer)
	{
		core::RefAssign(renderer.pointer, newRenderer);
	}

	// FUNCTION: ENGINE 0x10709B80
	void ParticleSystem::SetBoundingBox(const math::AABB& box)
	{
		bounds.max.x = box.max.x;
		bounds.max.y = box.max.y;
		bounds.max.z = box.max.z;
		bounds.min.x = box.min.x;
		bounds.min.y = box.min.y;
		bounds.min.z = box.min.z;
	}

	// FUNCTION: ENGINE 0x10709BB0
	void ParticleSystem::SetCentre(const math::Vector4& newCentre)
	{
		centre.x = newCentre.x;
		centre.y = newCentre.y;
		centre.z = newCentre.z;
		centre.w = newCentre.w;
	}

	// FUNCTION: ENGINE 0x10709C00
	void ParticleSystemState::StartUpdate(float x, float y, float z, bool flag)
	{
		if (!inheritUnknown4BC)
		{
			BeginUpdate(x, y, z, flag);
		}
	}

	// FUNCTION: ENGINE 0x10709D90
	void ParticleSystemState::SetGeneratorUnknown254(float value)
	{
		if (generator != 0)
		{
			generator->SetUnknown254(value);
		}
	}

	// FUNCTION: ENGINE 0x10709E90
	float ParticleSystemState::GetUnknown494()
	{
		return unknown494;
	}

	// FUNCTION: ENGINE 0x10709EA0
	float ParticleSystemState::GetUnknown498()
	{
		return unknown498;
	}

	// FUNCTION: ENGINE 0x10709EB0
	bool ParticleSystemState::GetUnknown491()
	{
		return unknown491;
	}

	// FUNCTION: ENGINE 0x10709F10
	void ParticleSystemState::SetUnknown4BA(bool value)
	{
		unknown4BA = value;
	}

	// FUNCTION: ENGINE 0x10709EE0
	float ParticleSystemState::ScaleByFrameRate(float value)
	{
		return unknown3FC->Unknown8() * value;
	}

	// FUNCTION: ENGINE 0x1070AEB0
	float ParticleSystemState::GetValue(int index)
	{
		return inheritUnknown4BC ? parent->GetValue(index) : (&unknown2E0)[index];
	}

	// FUNCTION: ENGINE 0x1070AEE0
	float* ParticleSystemState::GetPair(int index)
	{
		return inheritUnknown4BC ? parent->GetPair(index) : (float*)&unknown2F8[index * 8];
	}

	// FUNCTION: ENGINE 0x1070AF10
	math::Vector* ParticleSystemState::GetVector(int index)
	{
		return inheritUnknown4BC ? parent->GetVector(index) : &(&unknown308)[index];
	}

	// FUNCTION: ENGINE 0x1070AF40
	math::Matrix* ParticleSystemState::GetMatrix(int index)
	{
		return inheritUnknown4BC ? parent->GetMatrix(index) : &(&unknown32C)[index];
	}

	// FUNCTION: ENGINE 0x1070AF70
	void ParticleSystemState::SetGenerator(ParticleGenerator* newGenerator)
	{
		core::SafeRelease(generator);
		core::RefAssign(generator, newGenerator);
		if (generator != 0)
		{
			newGenerator->unknown27C = unknown4B4;
		}
	}

	// FUNCTION: ENGINE 0x1070AB60
	void ParticleSystemState::SetParent(ParticleSystemState* newParent, const int* values)
	{
		core::RefAssign(parent, newParent);
		unknown4C4 = values[0];
		unknown4C8 = values[1];
		unknown4CC = values[2];
		unknown4D0 = values[3];
		GetParticleManager()->RegisterState(this);
		unsigned int count = newParent->inheritUnknown4BC ? newParent->parent->GetParticleCount() : newParent->particleCount;
		VertexBufferDescription description(count * 4, 0x18002022, 3, false);
		if (context->unknown6C)
		{
			core::RefAssign(vertexBuffers[0], gPddiDx ? gPddiDx->NewUnsupportedVertexBuffer(&description) : 0);
			core::RefAssign(vertexBuffers[1], gPddiDx ? gPddiDx->NewUnsupportedVertexBuffer(&description) : 0);
		}
		unknown4BB = true;
	}

	// FUNCTION: ENGINE 0x1070BD00
	particles::Span ParticleSystemState::GetSpan0(int index)
	{
		return inheritUnknown4BC ? parent->GetSpan0(index)
			: particles::Span(block + attributes2C0->entries[index].offset, block + attributes2C0->entries[index].unknown4);
	}

	// FUNCTION: ENGINE 0x1070BD60
	particles::Span ParticleSystemState::GetSpan1(int index)
	{
		return inheritUnknown4BC ? parent->GetSpan1(index)
			: particles::Span(block + attributes2C8->entries[index].offset, block + attributes2C8->entries[index].unknown4);
	}

	// FUNCTION: ENGINE 0x1070BDC0
	particles::Span ParticleSystemState::GetSpan2(int index)
	{
		return inheritUnknown4BC ? parent->GetSpan2(index)
			: particles::Span(block + attributes2D0->entries[index].offset, block + attributes2D0->entries[index].unknown4);
	}

	// FUNCTION: ENGINE 0x1070BE20
	particles::Span ParticleSystemState::GetSpan3(int index)
	{
		return inheritUnknown4BC ? parent->GetSpan3(index)
			: particles::Span(block + attributes2D8->entries[index].offset, block + attributes2D8->entries[index].unknown4);
	}

	// FUNCTION: ENGINE 0x1070C560
	unsigned int ParticleSystemState::CountParticles()
	{
		ParticleSystemState* owner = this;
		while (owner->inheritUnknown4BC)
		{
			owner = owner->parent;
		}
		const float* lives = (const float*)(owner->block + owner->attributes2D0->entries[1].offset);
		unsigned int count = owner->particleCount;
		while (count > 0)
		{
			count--;
			if (lives[count] != 1e12f)
			{
				count++;
				break;
			}
		}
		owner->liveCount = 0;
		for (unsigned int i = 0; i < count; i++)
		{
			if (lives[i] != 1e12f)
			{
				owner->liveCount++;
			}
		}
		return count;
	}
}
