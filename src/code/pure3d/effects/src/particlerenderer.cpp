// pure3d::ParticleRenderer (unit around 0x10739930 - 0x10739B90; file name guessed from the class). Names are guesses.
#include <new>

#include "code/core/refptr.h"
#include "code/pure3d/effects/particlerenderer.h"
#include "code/pure3d/shader.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10739930
	// NONMATCHING: the engine saves edi before the first member store (97.1 %)
#ifdef NONMATCHING
	ParticleRenderer::ParticleRenderer()
	{
		unknown8 = 0;
		unknownC = 0;
		shader = 0;
		core::RefAssign(shader, new Shader("unlit"));
	}
#endif

	// FUNCTION: ENGINE 0x107399A0
	ParticleRenderer::~ParticleRenderer()
	{
		core::SafeRelease(shader);
	}
}
