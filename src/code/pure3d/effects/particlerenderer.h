// pure3d::ParticleRenderer (RTTI: base RefCounted, 4 vftable slots; the Quad and Geometry particle renderers derive
// from it): draws the particles of a system with a shader. Member and slot names are guesses.
#ifndef PURE3D_EFFECTS_PARTICLERENDERER_H
#define PURE3D_EFFECTS_PARTICLERENDERER_H

#include "code/pure3d/entity.h"

namespace pure3d
{
	class Shader;
	class dxTexture;

	class ParticleRenderer : public RefCounted
	{
	public:
		// 0x10739930: makes the "unlit" shader; 0x107399A0: lets it go; the scalar deleting destructor is 0x10739B70
		ParticleRenderer();
		virtual ~ParticleRenderer();
		// Slot 3: pure
		virtual void Draw() = 0;

		dxTexture* unknown8;
		dxTexture* unknownC;
		Shader* shader;
	};
}

#endif
