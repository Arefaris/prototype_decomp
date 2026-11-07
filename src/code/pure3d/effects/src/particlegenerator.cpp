// pure3d::ParticleGenerator and the generators built on it (unit around 0x10740000 - 0x10748800; the file name is a
// guess). Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/effects/particlecontroller.h"
#include "code/pure3d/primitive.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace choreo
{
	extern const float gMinusOne;
}

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

	// FUNCTION: ENGINE 0x10740450
	void ParticleGenerator::Unknown8()
	{
		attributes.ResetValues();
	}

	// FUNCTION: ENGINE 0x10740500
	void* ParticleGenerator::operator new(unsigned int size)
	{
		return AllocateParticle(size);
	}

	// FUNCTION: ENGINE 0x10740510
	void ParticleGenerator::operator delete(void* pointer)
	{
		FreeParticle(pointer);
	}

	// FUNCTION: ENGINE 0x10741080
	bool ParticleGenerator::Unknown10741080()
	{
		return unknown2F4 != unknown2F8;
	}

	// FUNCTION: ENGINE 0x107407A0
	bool ParticlePointGenerator::Unknown3()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10740820
	bool ParticlePlaneGenerator::Unknown3()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10740870
	bool ParticleSphereGenerator::Unknown3()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10740920
	bool ParticleGridGenerator::Unknown3()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10740930
	bool ParticleMeshGenerator::Unknown3()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10746B40
	// NONMATCHING: the engine stores the vftable after the load of the constant one (87.2 %)
#ifdef NONMATCHING
	ParticlePointGenerator::ParticlePointGenerator(unsigned int dataArgument, int maxParticles) :
		ParticleGenerator(dataArgument, maxParticles)
	{
		hosp = 90.0f;
		vesp = 90.0f;
		rdva = 0.0f;
		float one = engine::driving::gOne;
		animation = 0;
		unknown420 = one;
		unknown424 = one;
		unknown428 = one;
	}
#endif

	// FUNCTION: ENGINE 0x10746BB0
	ParticlePointGenerator::ParticlePointGenerator(const ParticlePointGenerator& other) : ParticleGenerator(other)
	{
		animation = 0;
		hosp = other.hosp;
		vesp = other.vesp;
		rdva = other.rdva;
		unknown420 = other.unknown420;
		unknown424 = other.unknown424;
		unknown428 = other.unknown428;
		core::RefAssign(animation, other.animation);
	}

	// FUNCTION: ENGINE 0x10746C40
	ParticlePointGenerator::ParticlePointGenerator(const ParticlePointGenerator& other, int maxParticles) :
		ParticleGenerator(other, maxParticles)
	{
		animation = 0;
		hosp = other.hosp;
		vesp = other.vesp;
		rdva = other.rdva;
		unknown420 = other.unknown420;
		unknown424 = other.unknown424;
		unknown428 = other.unknown428;
		core::RefAssign(animation, other.animation);
	}

	// FUNCTION: ENGINE 0x10746CD0
	ParticlePointGenerator::~ParticlePointGenerator()
	{
		core::SafeRelease(animation);
	}

	// FUNCTION: ENGINE 0x10746CF0
	ParticleGenerator* ParticlePointGenerator::Unknown5()
	{
		return new ParticlePointGenerator(*this);
	}

	// FUNCTION: ENGINE 0x10746D20
	ParticleGenerator* ParticlePointGenerator::Unknown4(int maxParticles)
	{
		return new ParticlePointGenerator(*this, maxParticles);
	}

	// FUNCTION: ENGINE 0x10746D50
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (68.8 %)
#ifdef NONMATCHING
	ParticlePlaneGenerator::ParticlePlaneGenerator(unsigned int dataArgument, int maxParticles) :
		ParticleGenerator(dataArgument, maxParticles)
	{
		wdt = 5.0f;
		hgt = 5.0f;
		hosp = 90.0f;
		vesp = 45.0f;
		rdva = 0.0f;
		float one = engine::driving::gOne;
		animation = 0;
		unknown428 = one;
		unknown42C = one;
		unknown430 = one;
		unknown434 = one;
		unknown438 = one;
		unknown43C = choreo::gMinusOne;
		unknown440 = choreo::gMinusOne;
	}
#endif

	// FUNCTION: ENGINE 0x10746E10
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (76.9 %)
#ifdef NONMATCHING
	ParticlePlaneGenerator::ParticlePlaneGenerator(const ParticlePlaneGenerator& other) : ParticleGenerator(other)
	{
		float one = engine::driving::gOne;
		animation = 0;
		wdt = other.wdt;
		hgt = other.hgt;
		hosp = other.hosp;
		vesp = other.vesp;
		rdva = other.rdva;
		unknown428 = one;
		unknown42C = one;
		unknown430 = one;
		unknown434 = one;
		unknown438 = one;
		unknown43C = choreo::gMinusOne;
		unknown440 = choreo::gMinusOne;
		core::RefAssign(animation, other.animation);
	}
#endif

	// FUNCTION: ENGINE 0x10746ED0
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (56.1 %)
#ifdef NONMATCHING
	ParticlePlaneGenerator::ParticlePlaneGenerator(const ParticlePlaneGenerator& other, int maxParticles) :
		ParticleGenerator(other, maxParticles)
	{
		float one = engine::driving::gOne;
		float minusOne = choreo::gMinusOne;
		animation = 0;
		wdt = other.wdt;
		hgt = other.hgt;
		hosp = other.hosp;
		vesp = other.vesp;
		rdva = other.rdva;
		unknown428 = one;
		unknown42C = one;
		unknown430 = one;
		unknown434 = one;
		unknown438 = one;
		unknown43C = minusOne;
		unknown440 = minusOne;
		core::RefAssign(animation, other.animation);
	}
#endif

	// FUNCTION: ENGINE 0x10746FA0
	ParticlePlaneGenerator::~ParticlePlaneGenerator()
	{
		core::SafeRelease(animation);
	}

	// FUNCTION: ENGINE 0x10746FC0
	ParticleGenerator* ParticlePlaneGenerator::Unknown5()
	{
		return new ParticlePlaneGenerator(*this);
	}

	// FUNCTION: ENGINE 0x10746FF0
	ParticleGenerator* ParticlePlaneGenerator::Unknown4(int maxParticles)
	{
		return new ParticlePlaneGenerator(*this, maxParticles);
	}

	// FUNCTION: ENGINE 0x10747020
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (89.4 %)
#ifdef NONMATCHING
	ParticleSphereGenerator::ParticleSphereGenerator(unsigned int dataArgument, int maxParticles) :
		ParticleGenerator(dataArgument, maxParticles)
	{
		float one = engine::driving::gOne;
		animation = 0;
		rad = one;
		rdva = 0.0f;
		unknown41C = one;
		unknown420 = one;
	}
#endif

	// FUNCTION: ENGINE 0x10747080
	ParticleSphereGenerator::ParticleSphereGenerator(const ParticleSphereGenerator& other) : ParticleGenerator(other)
	{
		animation = 0;
		rad = other.rad;
		rdva = other.rdva;
		unknown41C = other.unknown41C;
		unknown420 = other.unknown420;
		core::RefAssign(animation, other.animation);
	}

	// FUNCTION: ENGINE 0x107470F0
	ParticleSphereGenerator::ParticleSphereGenerator(const ParticleSphereGenerator& other, int maxParticles) :
		ParticleGenerator(other, maxParticles)
	{
		animation = 0;
		rad = other.rad;
		rdva = other.rdva;
		unknown41C = other.unknown41C;
		unknown420 = other.unknown420;
		core::RefAssign(animation, other.animation);
	}

	// FUNCTION: ENGINE 0x10747160
	ParticleSphereGenerator::~ParticleSphereGenerator()
	{
		core::SafeRelease(animation);
	}

	// FUNCTION: ENGINE 0x10747180
	ParticleGenerator* ParticleSphereGenerator::Unknown5()
	{
		return new ParticleSphereGenerator(*this);
	}

	// FUNCTION: ENGINE 0x107471B0
	ParticleGenerator* ParticleSphereGenerator::Unknown4(int maxParticles)
	{
		return new ParticleSphereGenerator(*this, maxParticles);
	}

	// FUNCTION: ENGINE 0x107471E0
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (68.5 %)
#ifdef NONMATCHING
	ParticleGridGenerator::ParticleGridGenerator(unsigned int dataArgument, int maxParticles) :
		ParticleGenerator(dataArgument, maxParticles)
	{
		float one = engine::driving::gOne;
		float minusOne = choreo::gMinusOne;
		wdt = 5.0f;
		hgt = 5.0f;
		hosp = 90.0f;
		vesp = 45.0f;
		rdva = 0.0f;
		animation = 0;
		hspc = one;
		vspc = one;
		unknown430 = minusOne;
		unknown434 = minusOne;
		unknown438 = one;
		unknown43C = one;
		unknown440 = one;
		unknown444 = one;
		unknown448 = one;
	}
#endif

	// FUNCTION: ENGINE 0x107472B0
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (50.7 %)
#ifdef NONMATCHING
	ParticleGridGenerator::ParticleGridGenerator(const ParticleGridGenerator& other) : ParticleGenerator(other)
	{
		float one = engine::driving::gOne;
		float minusOne = choreo::gMinusOne;
		animation = 0;
		wdt = other.wdt;
		hgt = other.hgt;
		hosp = other.hosp;
		vesp = other.vesp;
		rdva = other.rdva;
		hspc = other.hspc;
		vspc = other.vspc;
		unknown430 = minusOne;
		unknown434 = minusOne;
		unknown438 = one;
		unknown43C = one;
		unknown440 = one;
		unknown444 = one;
		unknown448 = one;
		core::RefAssign(animation, other.animation);
	}
#endif

	// FUNCTION: ENGINE 0x10747390
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (51.8 %)
#ifdef NONMATCHING
	ParticleGridGenerator::ParticleGridGenerator(const ParticleGridGenerator& other, int maxParticles) :
		ParticleGenerator(other, maxParticles)
	{
		float one = engine::driving::gOne;
		float minusOne = choreo::gMinusOne;
		animation = 0;
		wdt = other.wdt;
		hgt = other.hgt;
		hosp = other.hosp;
		vesp = other.vesp;
		rdva = other.rdva;
		hspc = other.hspc;
		vspc = other.vspc;
		unknown430 = minusOne;
		unknown434 = minusOne;
		unknown438 = one;
		unknown43C = one;
		unknown440 = one;
		unknown444 = one;
		unknown448 = one;
		core::RefAssign(animation, other.animation);
	}
#endif

	// FUNCTION: ENGINE 0x10747470
	ParticleGridGenerator::~ParticleGridGenerator()
	{
		core::SafeRelease(animation);
	}

	// FUNCTION: ENGINE 0x10747490
	ParticleGenerator* ParticleGridGenerator::Unknown5()
	{
		return new ParticleGridGenerator(*this);
	}

	// FUNCTION: ENGINE 0x107474C0
	ParticleGenerator* ParticleGridGenerator::Unknown4(int maxParticles)
	{
		return new ParticleGridGenerator(*this, maxParticles);
	}

	// FUNCTION: ENGINE 0x107474F0
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (81.0 %)
#ifdef NONMATCHING
	ParticleMeshGenerator::ParticleMeshGenerator(unsigned int dataArgument, int maxParticles) :
		ParticleGenerator(dataArgument, maxParticles)
	{
		float one = engine::driving::gOne;
		meshData = 0;
		unknown420 = 0;
		unknown424 = 0;
		unknown410 = one;
		unknown414 = one;
		unknown418 = one;
	}
#endif

	// FUNCTION: ENGINE 0x10747550
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (27.3 %)
#ifdef NONMATCHING
	ParticleMeshGenerator::ParticleMeshGenerator(const ParticleMeshGenerator& other) : ParticleGenerator(other)
	{
		float one = engine::driving::gOne;
		meshData = 0;
		unknown420 = 0;
		unknown424 = other.unknown424;
		core::RefAssign(meshData, other.meshData);
		unknown410 = one;
		unknown414 = one;
		unknown418 = one;
	}
#endif

	// FUNCTION: ENGINE 0x107475C0
	// NONMATCHING: the engine loads the constants before it stores the vftable and interleaves the member stores differently (30.2 %)
#ifdef NONMATCHING
	ParticleMeshGenerator::ParticleMeshGenerator(const ParticleMeshGenerator& other, int maxParticles) :
		ParticleGenerator(other, maxParticles)
	{
		float one = engine::driving::gOne;
		meshData = 0;
		unknown420 = 0;
		unknown424 = other.unknown424;
		core::RefAssign(meshData, other.meshData);
		unknown410 = one;
		unknown414 = one;
		unknown418 = one;
	}
#endif

	// FUNCTION: ENGINE 0x10747640
	ParticleMeshGenerator::~ParticleMeshGenerator()
	{
		core::SafeRelease(meshData);
	}

	// FUNCTION: ENGINE 0x10747660
	ParticleGenerator* ParticleMeshGenerator::Unknown5()
	{
		return new ParticleMeshGenerator(*this);
	}

	// FUNCTION: ENGINE 0x10747690
	ParticleGenerator* ParticleMeshGenerator::Unknown4(int maxParticles)
	{
		return new ParticleMeshGenerator(*this, maxParticles);
	}
}
