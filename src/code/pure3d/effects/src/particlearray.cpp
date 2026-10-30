// The float arrays of the particle generators (unit around 0x10740000 - 0x10748800; the file name is a guess, the
// unit also holds the generators). Names are guesses.
#include "code/core/heap.h"
#include "code/pure3d/effects/particledata.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10742680
	// EQUIVALENT: the same stores and the same four calls; the engine keeps zero in ebx and the address of the first flag
	// word in edi across the calls, ours zero in edi and a fresh address per call (29.3 %)
	ParticleArray::ParticleArray() : unknown0(0), unknown4(0), unknown8(0), unknownC(0), unknown10(0), unknown14(0),
		unknown18(0), unknown1C(0), begin(0), end(0), block(0)
	{
	}

	// FUNCTION: ENGINE 0x107485C0
	void ParticleArray::Free()
	{
		if (block != 0)
		{
			core::FreeAligned(block);
			block = 0;
		}
		unknown0 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown1C = 0;
		begin = 0;
		end = 0;
	}

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
