// The update kernels of the particle code of pure3d (code/pure3d/effects/src/particles.cpp): each advances one
// attribute of every particle of a block (UpdateParticles picks the ones the system's flags ask for). All of them
// take the time step, the number of particles and a value of the state (+0x4B4) first, then the arrays of the
// attributes they read and write. Only the ones the reconstructed code defines have names of their own; the others
// are numbered by the bit of the flag that selects them (names are guesses).
#ifndef PURE3D_EFFECTS_PARTICLES_H
#define PURE3D_EFFECTS_PARTICLES_H

#include "code/pure3d/effects/particledata.h"

namespace core
{
	class AsyncTaskCallback;
}

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

	// One link of the chain of batches the particle task runs a kernel on (0x5C bytes): the arrays the kernel reads
	// and writes, the time step, the number of particles, a value of the state and the chain's result, which the
	// first link keeps
	struct ParticleKernelBatch
	{
		void* buffers[18];
		float dt;
		unsigned int count;
		int unknown50;
		int result;
		ParticleKernelBatch* next;
	};

	// The task functions that run one kernel on a chain of batches (the unit of the particle task manager)
	// 0x1073C1C0
	void RunUpdateKernel00(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C210
	void RunUpdateKernel01(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C270
	void RunUpdateKernel02(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C2C0
	void RunUpdateKernel03(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C320
	void RunUpdateKernel04(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C370
	void RunUpdateKernel05(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C3D0
	void RunUpdateKernel06(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C430
	void RunUpdateFrameBlend(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C490
	void RunUpdateKernel08(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C4F0
	void RunUpdateKernel09(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C550
	void RunUpdateKernel10(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C5B0
	void RunUpdateKernel11(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C620
	void RunUpdateKernel12(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C6A0
	void RunUpdateKernel13(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C720
	void RunUpdateKernel14(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C7B0
	void RunUpdateKernel15(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C840
	void RunUpdateKernel16(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C8D0
	void RunUpdateKernel21(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C920
	void RunUpdateKernel22(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C990
	void RunUpdateKernel17(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073C9F0
	void RunUpdateKernel23(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073CA40
	void RunUpdateKernel24(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073CA90
	void RunUpdateKernel25(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073CAE0
	void RunUpdateNothing(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073CB30
	void RunUpdateKernel26(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073CB90
	void RunUpdateKernel19(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
	// 0x1073CC10
	void RunUpdateKernel20(ParticleKernelBatch* head, core::AsyncTaskCallback* callback);
}

#endif
