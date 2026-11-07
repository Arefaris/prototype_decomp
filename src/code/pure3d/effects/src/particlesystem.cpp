// pure3d::ParticleSystem and pure3d::ParticleSystemState (unit around 0x10709A00 - 0x1070E700; file name guessed
// from the classes). Names are guesses.
#include <math.h>

#include <new>

#include "code/core/refptr.h"
#include "code/math/matrix.h"
#include "code/pure3d/effects/particlesystem.h"
#include "code/pure3d/primitive.h"

// This unit's copies of the reference helpers for the renderer of a system
// FUNCTION: ENGINE 0x1070A490
template void core::RefAssign<pure3d::ParticleRenderer>(pure3d::ParticleRenderer*& pointer, pure3d::ParticleRenderer* object);

// FUNCTION: ENGINE 0x1070A4C0
template void core::SafeRelease<pure3d::ParticleRenderer>(pure3d::ParticleRenderer*& object);

namespace pure3d
{
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
}
