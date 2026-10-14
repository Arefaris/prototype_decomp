// The update kernels of the particle code of pure3d (code/pure3d/effects/src/particles.cpp): each advances one
// attribute of every particle of a block (UpdateParticles picks the ones the system's flags ask for). All of them
// take the time step, the number of particles and a value of the state (+0x4B4) first, then the arrays of the
// attributes they read and write. Only the ones the reconstructed code defines have names of their own; the others
// are numbered by the bit of the flag that selects them (names are guesses).
#ifndef PURE3D_EFFECTS_PARTICLES_H
#define PURE3D_EFFECTS_PARTICLES_H

#include "code/pure3d/effects/particledata.h"

namespace pure3d
{
	// 0x107837F0: ages every particle by dt; one that has run out starts again with the life time and takes the
	// next frame (the one it faded to, or a new one when it showed a single frame), the blend runs from 0 to 1 over
	// the life time
	void UpdateFrameBlend(float dt, unsigned int count, int unknown2, ParticleFrameBlend* blends,
		const float* newFrames, void* unknown5, float* ages, const float* lifeTime);
	// 0x1078B550: the kernel of a feature that does nothing
	void UpdateNothing(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d);

	// 0x107836D0 and the rest (the other units of the particle code define them)
	void UpdateKernel00(float dt, unsigned int count, int unknown2, void* a, void* b);
	void UpdateKernel01(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e);
	void UpdateKernel02(float dt, unsigned int count, int unknown2, void* a, void* b);
	void UpdateKernel03(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e);
	void UpdateKernel04(float dt, unsigned int count, int unknown2, void* a, void* b, void* c);
	void UpdateKernel05(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e);
	void UpdateKernel06(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f);
	void UpdateKernel08(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f);
	void UpdateKernel09(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f);
	void UpdateKernel10(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f);
	void UpdateKernel11(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h, void* i, void* j, void* k, void* l);
	void UpdateKernel12(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h, void* i, void* j, void* k, void* l, void* m, void* n);
	void UpdateKernel13(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h, void* i, void* j, void* k, void* l, void* m, void* n, void* o, void* p);
	void UpdateKernel14(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h, void* i, void* j, void* k, void* l, void* m, void* n, void* o, void* p, void* q);
	void UpdateKernel15(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h, void* i, void* j, void* k, void* l, void* m, void* n, void* o, void* p, void* q);
	void UpdateKernel16(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h, void* i, void* j, void* k, void* l, void* m, void* n, void* o, void* p, void* q);
	void UpdateKernel17(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e);
	void UpdateKernel19(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h, void* i, void* j, void* k, void* l, void* m, void* n, void* o, void* p);
	void UpdateKernel20(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h);
	void UpdateKernel21(float dt, unsigned int count, int unknown2, void* a, void* b);
	void UpdateKernel22(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h, void* i);
	void UpdateKernel23(float dt, unsigned int count, int unknown2, void* a, void* b, void* c);
	void UpdateKernel24(float dt, unsigned int count, int unknown2, void* a, void* b);
	void UpdateKernel25(float dt, unsigned int count, int unknown2, void* a, void* b);
	void UpdateKernel26(float dt, unsigned int count, int unknown2, void* a, void* b, void* c, void* d, void* e, void* f);
}

#endif
