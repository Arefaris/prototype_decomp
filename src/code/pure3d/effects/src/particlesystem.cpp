// pure3d::ParticleSystem and pure3d::ParticleSystemState (unit around 0x10709A00 - 0x1070E700; file name guessed
// from the classes). Names are guesses.
#include "code/math/matrix.h"
#include "code/pure3d/primitive.h"

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
		return inheritUnknown4BC ? parent->GetGeneratorUnknown10() : generator->unknown10;
	}
}
