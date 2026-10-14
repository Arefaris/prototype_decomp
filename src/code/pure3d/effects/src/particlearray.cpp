// The float arrays of the particle generators (unit around 0x10740000 - 0x10748800; the file name is a guess, the
// unit also holds the generators). Names are guesses.
#include "code/pure3d/effects/particledata.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10748980
	void ParticleArray::MultiplyAdd(const ParticleArray& a, const ParticleArray& b, const ParticleArray& c)
	{
		float* destination = begin;
		const float* y = a.begin;
		const float* x = b.begin;
		const float* z = c.begin;
		float* limit = end;
		for (; destination < limit; destination += 4)
		{
			destination[0] = x[0] * y[0] + z[0];
			destination[1] = x[1] * y[1] + z[1];
			destination[2] = x[2] * y[2] + z[2];
			destination[3] = x[3] * y[3] + z[3];
			x += 4;
			y += 4;
			z += 4;
		}
	}
}
