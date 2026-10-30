// pure3d::ParticleGenerator and the generators built on it (unit around 0x10740000 - 0x10748800; the file name is a
// guess). Names are guesses.
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10740460
	void ParticleGenerator::SetTransform(const math::Matrix& newTransform)
	{
		unknown50 = transform;
		transform = newTransform;
		unknown10 = newTransform;
	}

	// FUNCTION: ENGINE 0x107404B0
	void ParticleGenerator::Unknown107404B0(float value)
	{
		unknown280 = value;
	}

	// FUNCTION: ENGINE 0x10741080
	bool ParticleGenerator::Unknown10741080()
	{
		return unknown2F4 != unknown2F8;
	}
}
