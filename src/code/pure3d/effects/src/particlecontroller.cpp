// pure3d::ParticleController (unit around 0x1074D240 - 0x1074D510; file name guessed from the class). Names are guesses.
#include <float.h>

#include "code/engine/camera/onfootcamera.h"
#include "code/engine/driving/carattributes.h"
#include "code/pure3d/effects/particlecontroller.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1074D450
	void* ParticleController::operator new(unsigned int size)
	{
		return AllocateParticleAligned(size);
	}

	// FUNCTION: ENGINE 0x1074D460
	void ParticleController::operator delete(void* pointer)
	{
		FreeParticleAligned(pointer);
	}

	// FUNCTION: ENGINE 0x1074D470
	// NONMATCHING: the engine stores the vftable after the first two member stores (74.6 %)
#ifdef NONMATCHING
	ParticleController::ParticleController()
	{
		unknown48 = 100.0f;
		unknown4C = engine::driving::gThirty;
		unknown44 = true;
		unknown50 = 0.0f;
		ParticleController::Reset();
	}
#endif

	// FUNCTION: ENGINE 0x1074D4D0
	ParticleController::ParticleController(const ParticleController& other) : SimpleFrameController(other)
	{
		unknown44 = other.unknown44;
		unknown48 = other.unknown48;
		unknown4C = other.unknown4C;
		unknown50 = other.unknown50;
		ParticleController::Reset();
	}

	// FUNCTION: ENGINE 0x1074D240
	ParticleController::~ParticleController()
	{
	}

	// FUNCTION: ENGINE 0x1074D510
	ParticleController* ParticleController::Clone()
	{
		return new ParticleController(*this);
	}

	// FUNCTION: ENGINE 0x1074D400
	void ParticleController::Reset()
	{
		mEndFrame = unknown48;
		mCycleMode = 0;
		mStartFrame = 0.0f;
		mFrame = 0.0f;
		mNumCycles = unknown44 != true;
		mRemaining = GetRemaining();
		mForward = true;
		unknown50 = 0.0f;
	}

	// FUNCTION: ENGINE 0x1074D3F0
	bool ParticleController::Unknown20()
	{
		if (SimpleFrameController::Unknown20() == true)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1074D3D0
	float ParticleController::GetRemaining()
	{
		if (mCycleMode == 0)
		{
			if (unknown44 == true)
			{
				return FLT_MAX;
			}
			return mEndFrame - mStartFrame;
		}
		return AnimationFrameController::GetRemaining();
	}

	// The time the last step covered, in the units the update works in
	static __forceinline float StepTime(float speed, float rate)
	{
		return speed * rate * engine::camera::gThousandth;
	}

	// FUNCTION: ENGINE 0x1074D350
	float ParticleController::Step()
	{
		return AdvanceFrameCycle(&mRemaining, &mForward, mFrame, StepTime(unknown50, unknown4C), mStartFrame, mEndFrame,
			mNumCycles == 0, mCycleMode);
	}

	// FUNCTION: ENGINE 0x1074D290
	// NONMATCHING: the engine copies the old frame into two argument temporaries after the speed is stored (11 %)
#ifdef NONMATCHING
	void ParticleController::Advance(float dt, bool update)
	{
		float scaled = mRelativeSpeed * dt;
		unknown50 = scaled;
		dt = unknown4C * scaled * engine::camera::gThousandth;
		float previousFrame = mFrame;
		mFrame = AdvanceFrameCycle(&mRemaining, &mForward, previousFrame, dt, mStartFrame, mEndFrame, mNumCycles == 0,
			mCycleMode);
		state->BeginUpdate(mFrame, previousFrame, dt, mNumCycles == 0);
		unknown50 = 0.0f;
	}
#endif

	// FUNCTION: ENGINE 0x1074D250
	void ParticleController::Unknown5()
	{
	}

	// FUNCTION: ENGINE 0x1074D260
	bool ParticleController::Unknown25()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1074D270
	bool ParticleController::IsSupported(Animation* animation)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1074D280
	void ParticleController::SetTarget(Entity* target)
	{
	}

	// FUNCTION: ENGINE 0x1074D3A0
	float ParticleController::GetUnknown1074D3A0()
	{
		return unknown50 * unknown4C * engine::camera::gThousandth;
	}

	// FUNCTION: ENGINE 0x1074D3B0
	float ParticleController::Unknown8()
	{
		return unknown4C;
	}

	// FUNCTION: ENGINE 0x1074D3C0
	float ParticleController::Unknown9()
	{
		return unknown48;
	}
}
