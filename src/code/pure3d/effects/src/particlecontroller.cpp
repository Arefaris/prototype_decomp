// pure3d::ParticleController (unit around 0x1074D240 - 0x1074D510; file name guessed from the class). Names are guesses.
#include "code/engine/camera/onfootcamera.h"
#include "code/pure3d/effects/particlecontroller.h"

namespace pure3d
{
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
