// The animation states of the particle generators (unit around 0x10740700 - 0x10742400, the generators' file; the file
// name is a guess): each keeps copies of the float channels its generator's shape is animated with. Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/primitive.h"

// This unit's copies of the reference helpers for the generators' animation states and mesh data

// FUNCTION: ENGINE 0x10740B60
template void core::RefAssign<pure3d::ParticlePointGenerator::GeneratorAnimationState>(pure3d::ParticlePointGenerator::GeneratorAnimationState*& pointer, pure3d::ParticlePointGenerator::GeneratorAnimationState* object);

// FUNCTION: ENGINE 0x10740B90
template void core::SafeRelease<pure3d::ParticlePointGenerator::GeneratorAnimationState>(pure3d::ParticlePointGenerator::GeneratorAnimationState*& object);

// FUNCTION: ENGINE 0x10740BB0
template void core::RefAssign<pure3d::ParticlePlaneGenerator::GeneratorAnimationState>(pure3d::ParticlePlaneGenerator::GeneratorAnimationState*& pointer, pure3d::ParticlePlaneGenerator::GeneratorAnimationState* object);

// FUNCTION: ENGINE 0x10740BE0
template void core::SafeRelease<pure3d::ParticlePlaneGenerator::GeneratorAnimationState>(pure3d::ParticlePlaneGenerator::GeneratorAnimationState*& object);

// FUNCTION: ENGINE 0x10740C00
template void core::RefAssign<pure3d::ParticleSphereGenerator::GeneratorAnimationState>(pure3d::ParticleSphereGenerator::GeneratorAnimationState*& pointer, pure3d::ParticleSphereGenerator::GeneratorAnimationState* object);

// FUNCTION: ENGINE 0x10740C30
template void core::SafeRelease<pure3d::ParticleSphereGenerator::GeneratorAnimationState>(pure3d::ParticleSphereGenerator::GeneratorAnimationState*& object);

// FUNCTION: ENGINE 0x10740C50
template void core::RefAssign<pure3d::ParticleGridGenerator::GeneratorAnimationState>(pure3d::ParticleGridGenerator::GeneratorAnimationState*& pointer, pure3d::ParticleGridGenerator::GeneratorAnimationState* object);

// FUNCTION: ENGINE 0x10740C80
template void core::SafeRelease<pure3d::ParticleGridGenerator::GeneratorAnimationState>(pure3d::ParticleGridGenerator::GeneratorAnimationState*& object);

// FUNCTION: ENGINE 0x10740CA0
template void core::RefAssign<pure3d::ParticleMeshGenerator::MeshData>(pure3d::ParticleMeshGenerator::MeshData*& pointer, pure3d::ParticleMeshGenerator::MeshData* object);

// FUNCTION: ENGINE 0x10740CD0
template void core::SafeRelease<pure3d::ParticleMeshGenerator::MeshData>(pure3d::ParticleMeshGenerator::MeshData*& object);

// FUNCTION: ENGINE 0x10740AC0
template void core::RefAssign<pure3d::ParticleGeneratorData>(pure3d::ParticleGeneratorData*& pointer,
	pure3d::ParticleGeneratorData* object);

// FUNCTION: ENGINE 0x10740AF0
template void core::RefAssign<pure3d::RefCountedRotationChannel>(pure3d::RefCountedRotationChannel*& pointer,
	pure3d::RefCountedRotationChannel* object);

// FUNCTION: ENGINE 0x10740B20
template void core::SafeRelease<pure3d::ParticleGeneratorData>(pure3d::ParticleGeneratorData*& object);

// FUNCTION: ENGINE 0x10740B40
template void core::SafeRelease<pure3d::RefCountedRotationChannel>(pure3d::RefCountedRotationChannel*& object);

namespace pure3d
{
	// FUNCTION: ENGINE 0x10740740
	ParticlePointGenerator::GeneratorAnimationState::~GeneratorAnimationState()
	{
		if (hosp != 0)
		{
			delete hosp;
			hosp = 0;
		}
		if (vesp != 0)
		{
			delete vesp;
			vesp = 0;
		}
		if (rdva != 0)
		{
			delete rdva;
			rdva = 0;
		}
	}

	// FUNCTION: ENGINE 0x107407B0
	ParticlePlaneGenerator::GeneratorAnimationState::~GeneratorAnimationState()
	{
		if (wdt != 0)
		{
			delete wdt;
			wdt = 0;
		}
		if (hgt != 0)
		{
			delete hgt;
			hgt = 0;
		}
		if (hosp != 0)
		{
			delete hosp;
			hosp = 0;
		}
		if (vesp != 0)
		{
			delete vesp;
			vesp = 0;
		}
		if (rdva != 0)
		{
			delete rdva;
			rdva = 0;
		}
	}

	// FUNCTION: ENGINE 0x10740830
	ParticleSphereGenerator::GeneratorAnimationState::~GeneratorAnimationState()
	{
		if (rad != 0)
		{
			delete rad;
			rad = 0;
		}
		if (rdva != 0)
		{
			delete rdva;
			rdva = 0;
		}
	}

	// FUNCTION: ENGINE 0x10740880
	ParticleGridGenerator::GeneratorAnimationState::~GeneratorAnimationState()
	{
		if (wdt != 0)
		{
			delete wdt;
			wdt = 0;
		}
		if (hgt != 0)
		{
			delete hgt;
			hgt = 0;
		}
		if (hosp != 0)
		{
			delete hosp;
			hosp = 0;
		}
		if (vesp != 0)
		{
			delete vesp;
			vesp = 0;
		}
		if (rdva != 0)
		{
			delete rdva;
			rdva = 0;
		}
		if (hspc != 0)
		{
			delete hspc;
			hspc = 0;
		}
		if (vspc != 0)
		{
			delete vspc;
			vspc = 0;
		}
	}

	// FUNCTION: ENGINE 0x10741E40
	ParticlePointGenerator::GeneratorAnimationState::GeneratorAnimationState(AnimationGroup* group) : RefCounted(NO_BARRIER)
	{
		hosp = 0;
		vesp = 0;
		rdva = 0;
		if (group != 0)
		{
			hosp = new Float1Channel(*(Float1Channel*)group->FindChannel(0x50534F48, 0x31544C46));
			vesp = new Float1Channel(*(Float1Channel*)group->FindChannel(0x50534556, 0x31544C46));
			rdva = new Float1Channel(*(Float1Channel*)group->FindChannel(0x41564452, 0x31544C46));
		}
	}

	// FUNCTION: ENGINE 0x10741F10
	void ParticlePointGenerator::Unknown6(float time)
	{
		if (animation != 0)
		{
			animation->hosp->GetValue(time, &hosp);
			animation->vesp->GetValue(time, &vesp);
			animation->rdva->GetValue(time, &rdva);
		}
		Unknown10741120(time);
	}

	// FUNCTION: ENGINE 0x10741F90
	ParticlePlaneGenerator::GeneratorAnimationState::GeneratorAnimationState() : RefCounted(NO_BARRIER)
	{
		wdt = 0;
		hgt = 0;
		hosp = 0;
		vesp = 0;
		rdva = 0;
	}

	// FUNCTION: ENGINE 0x10741FE0
	ParticlePlaneGenerator::GeneratorAnimationState::GeneratorAnimationState(AnimationGroup* group) : RefCounted(NO_BARRIER)
	{
		wdt = 0;
		hgt = 0;
		hosp = 0;
		vesp = 0;
		rdva = 0;
		if (group != 0)
		{
			wdt = new Float1Channel(*(Float1Channel*)group->FindChannel(0x544457, 0x31544C46));
			hgt = new Float1Channel(*(Float1Channel*)group->FindChannel(0x544748, 0x31544C46));
			hosp = new Float1Channel(*(Float1Channel*)group->FindChannel(0x50534F48, 0x31544C46));
			vesp = new Float1Channel(*(Float1Channel*)group->FindChannel(0x50534556, 0x31544C46));
			rdva = new Float1Channel(*(Float1Channel*)group->FindChannel(0x41564452, 0x31544C46));
		}
	}

	// FUNCTION: ENGINE 0x10742120
	void ParticlePlaneGenerator::Unknown6(float time)
	{
		if (animation != 0)
		{
			animation->wdt->GetValue(time, &wdt);
			animation->hgt->GetValue(time, &hgt);
			animation->hosp->GetValue(time, &hosp);
			animation->vesp->GetValue(time, &vesp);
			animation->rdva->GetValue(time, &rdva);
		}
		Unknown10741120(time);
	}

	// FUNCTION: ENGINE 0x107421D0
	ParticleSphereGenerator::GeneratorAnimationState::GeneratorAnimationState() : RefCounted(NO_BARRIER)
	{
		rad = 0;
		rdva = 0;
	}

	// FUNCTION: ENGINE 0x10742210
	ParticleSphereGenerator::GeneratorAnimationState::GeneratorAnimationState(AnimationGroup* group) : RefCounted(NO_BARRIER)
	{
		rad = 0;
		rdva = 0;
		if (group != 0)
		{
			rad = new Float1Channel(*(Float1Channel*)group->FindChannel(0x444152, 0x31544C46));
			rdva = new Float1Channel(*(Float1Channel*)group->FindChannel(0x41564452, 0x31544C46));
		}
	}

	// FUNCTION: ENGINE 0x107422B0
	void ParticleSphereGenerator::Unknown6(float time)
	{
		if (animation != 0)
		{
			animation->rad->GetValue(time, &rad);
			animation->rdva->GetValue(time, &rdva);
		}
		Unknown10741120(time);
	}

	// FUNCTION: ENGINE 0x10742310
	ParticleGridGenerator::GeneratorAnimationState::GeneratorAnimationState() : RefCounted(NO_BARRIER)
	{
		wdt = 0;
		hgt = 0;
		hosp = 0;
		vesp = 0;
		rdva = 0;
		hspc = 0;
		vspc = 0;
	}

	// FUNCTION: ENGINE 0x10742360
	ParticleGridGenerator::GeneratorAnimationState::GeneratorAnimationState(AnimationGroup* group) : RefCounted(NO_BARRIER)
	{
		wdt = 0;
		hgt = 0;
		hosp = 0;
		vesp = 0;
		rdva = 0;
		hspc = 0;
		vspc = 0;
		if (group != 0)
		{
			wdt = new Float1Channel(*(Float1Channel*)group->FindChannel(0x544457, 0x31544C46));
			hgt = new Float1Channel(*(Float1Channel*)group->FindChannel(0x544748, 0x31544C46));
			hosp = new Float1Channel(*(Float1Channel*)group->FindChannel(0x50534F48, 0x31544C46));
			vesp = new Float1Channel(*(Float1Channel*)group->FindChannel(0x50534556, 0x31544C46));
			rdva = new Float1Channel(*(Float1Channel*)group->FindChannel(0x41564452, 0x31544C46));
			hspc = new Float1Channel(*(Float1Channel*)group->FindChannel(0x43505348, 0x31544C46));
			vspc = new Float1Channel(*(Float1Channel*)group->FindChannel(0x43505356, 0x31544C46));
		}
	}

	// FUNCTION: ENGINE 0x10742500
	void ParticleGridGenerator::Unknown6(float time)
	{
		if (animation != 0)
		{
			animation->wdt->GetValue(time, &wdt);
			animation->hgt->GetValue(time, &hgt);
			animation->hosp->GetValue(time, &hosp);
			animation->vesp->GetValue(time, &vesp);
			animation->rdva->GetValue(time, &rdva);
			animation->hspc->GetValue(time, &hspc);
			animation->vspc->GetValue(time, &vspc);
		}
		Unknown10741120(time);
	}

	// FUNCTION: ENGINE 0x107425F0
	void ParticleMeshGenerator::Unknown6(float time)
	{
		Unknown10741120(time);
	}
}
