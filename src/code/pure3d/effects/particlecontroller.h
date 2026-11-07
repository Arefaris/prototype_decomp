// pure3d::ParticleController (RTTI name; bases SimpleFrameController, AnimationFrameController, FrameController): the
// controller that advances a particle system state by the time of the frame. Member and slot names are guesses.
#ifndef PURE3D_EFFECTS_PARTICLECONTROLLER_H
#define PURE3D_EFFECTS_PARTICLECONTROLLER_H

#include "code/pure3d/primitive.h"

namespace pure3d
{
	class ParticleSystemState;

	// 0x106E7EC0: moves a frame on by dt inside the range the way the cycle mode says (the function behind
	// Animation::AdvanceFrame; name guess)
	float AdvanceFrameCycle(float* remaining, bool* forward, float frame, float dt, float start, float end, bool unlimited,
		int mode);
	// 0x10714F50 / 0x10715060: the aligned allocation of the particle code (name guess) and its release; 0x10714FA0 /
	// 0x107150B0: the same without the alignment
	void* AllocateParticleAligned(unsigned int size);
	void FreeParticleAligned(void* pointer);
	void* AllocateParticle(unsigned int size);
	void FreeParticle(void* pointer);

	class ParticleController : public SimpleFrameController
	{
	public:
		// 0x1074D470 / 0x1074D4D0 / 0x1074D240
		ParticleController();
		ParticleController(const ParticleController& other);
		virtual ~ParticleController();
		// 0x1074D450 / 0x1074D460
		static void* operator new(unsigned int size);
		static void operator delete(void* pointer);

		// Slot 4 (0x1074D290): moves the frame on by the speed and starts the update of the particles; slot 18
		// (0x1074D3D0): the time left; slot 20 (0x1074D3F0); slot 21 (0x1074D400): starts again; slot 26 (0x1074D510)
		virtual void Advance(float dt, bool update);
		virtual float GetRemaining();
		virtual bool Unknown20();
		virtual void Reset();
		// Slot 3 (0x1074D280), 5 (0x1074D250): do nothing
		virtual void SetTarget(Entity* target);
		virtual void Unknown5();
		// Slots 8 / 9 (0x1074D3B0 / 0x1074D3C0): two of the controller's settings
		virtual float Unknown8();
		virtual float Unknown9();
		// Slot 24 (0x1074D270): false; slot 25 (0x1074D260): true
		virtual bool IsSupported(Animation* animation);
		virtual bool Unknown25();
		virtual ParticleController* Clone();
		// 0x1074D350: moves the frame on by the time the last step covered
		float Step();
		// 0x1074D3A0: the time the last step covered, in the units the update works in
		float GetUnknown1074D3A0();

		ParticleSystemState* state;
		bool unknown44;
		float unknown48;
		float unknown4C;
		float unknown50;
		unsigned char unknown54[4];
	};
}

#endif
