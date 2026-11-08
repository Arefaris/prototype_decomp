// pure3d::ParticleSystem (RTTI name; bases Primitive, LockableRefCounted): the primitive a particle system chunk loads
// as. It keeps the renderer that draws its particles and the box and sphere around them. Member and slot names are
// guesses.
#ifndef PURE3D_EFFECTS_PARTICLESYSTEM_H
#define PURE3D_EFFECTS_PARTICLESYSTEM_H

#include "code/core/asynctask.h"
#include "code/math/aabb.h"
#include "code/math/vector.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// RTTI name pure3d::ParticleRenderer: draws the particles of a state (slot 3 is the draw call of the system)
	class ParticleRenderer : public RefCounted
	{
	public:
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
			const PrimStreamParameters* parameters);
	};

	// RTTI name pure3d::PSAsyncTaskCallback: the callback of the update task of a particle system state
	class PSAsyncTaskCallback : public core::AsyncTaskCallback
	{
	public:
		// 0x10709AB0
		PSAsyncTaskCallback();
		// 0x1073FD00
		virtual void OnResult(int result);
	};

	class ParticleSystem : public Primitive
	{
	public:
		// 0x10709AE0: an empty system; 0x1070AAA0: a system with the renderer of another one
		ParticleSystem();
		ParticleSystem(const ParticleSystem& other);
		// Slot 2 (0x1070B600 is the compiler's scalar deleting destructor)
		virtual ~ParticleSystem();
		// Slot 3 (0x10709B60): hands the draw on to the renderer
		virtual void Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
			const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding);
		virtual void GetBoundingBox(math::AABB* box);
		virtual void GetCentre(math::Vector* centre);
		virtual bool FillBatch(void* batch, PrimitiveState* state, bool* unknown);

		// 0x10709BD0 / 0x1070AB40
		ParticleRenderer* GetRenderer();
		void SetRenderer(ParticleRenderer* newRenderer);
		// 0x10709B80 / 0x10709BB0: the box and the centre the chunk gives
		void SetBoundingBox(const math::AABB& box);
		void SetCentre(const math::Vector4& newCentre);

		// The reference the system holds to its renderer: a member with a constructor, as the copy constructor
		// stores its zero through the member's address
		struct RendererReference
		{
			RendererReference() : pointer(0)
			{
			}

			ParticleRenderer* pointer;
		};

		// The centre starts at the origin (the constructor of its first three components)
		struct Centre : public math::Vector4
		{
			Centre()
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			}
		};

		RendererReference renderer;
		math::AABB bounds;
		Centre centre;
	};
}

#endif
