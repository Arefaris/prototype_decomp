// The data types of the particle update code of pure3d (code/pure3d/effects/src/particles.cpp): the float arrays the
// generators keep their attributes in, the tables that say where each attribute of a particle block starts, the
// update data a system state is advanced with, and the channel wrappers a state animates its parameters with.
// Layouts follow what the update code reads; names are guesses unless the RTTI gives them.
#ifndef PURE3D_EFFECTS_PARTICLEDATA_H
#define PURE3D_EFFECTS_PARTICLEDATA_H

#include "code/core/bitfield.h"
#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/pure3d/channel.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	class ParticleUpdateData;

	// The frame a particle shows, the frame it fades to and the blend between the two (12 bytes per particle)
	struct ParticleFrameBlend
	{
		float from;
		float to;
		float blend;
	};

	// An array of floats in groups of four (the generators' attribute curves): `begin` and `end` bound the values,
	// `block` is the aligned allocation behind them (0x3C bytes; the constructor is 0x10742680)
	class ParticleArray
	{
	public:
		// 0x10742680: empty arrays
		ParticleArray();
		// 0x107485C0: frees the block and forgets the arrays
		void Free();
		// 0x10748980: this = b * a + c element by element (the three arrays have the length of this one)
		void MultiplyAdd(const ParticleArray& a, const ParticleArray& b, const ParticleArray& c);

		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
		int unknown18;
		int unknown1C;
		float* begin;
		float* end;
		core::BitField<unsigned int> bits0;
		core::BitField<unsigned int> bits1;
		core::BitField<unsigned int> bits2;
		core::BitField<unsigned int> bits3;
		void* block;
	};

	// The values a generator evaluates for the current time (0x16C bytes, a member of the generator at +0xD4): the
	// array of the current key and the arrays that scale and offset it
	class ParticleAttributes
	{
	public:
		// 0x1079CE80 (called with the update data, which it does not read): applies the scale and offset arrays
		// to the current values when the flag is set
		void Apply(ParticleUpdateData* data);

		ParticleArray values;
		ParticleArray unknown3C;
		ParticleArray unknown78;
		ParticleArray scale;
		ParticleArray offset;
		ParticleArray unknown12C;
		bool apply;
	};

	// What a system state is advanced with (RTTI pure3d::ParticleUpdateData): the time of the frame, the time step
	// and the position the particles are emitted relative to
	class ParticleUpdateData : public RefCounted
	{
	public:
		unsigned char unknown8[4];
		float time;
		unsigned char unknown10[4];
		float deltaTime;
		unsigned char unknown18[0x24];
		math::Vector position;
	};

	// Where the attributes of a block of particles start in the block (8 bytes per attribute: the offset, and a
	// value that the update code does not read)
	struct ParticleAttributeTable
	{
		struct Entry
		{
			int offset;
			int unknown4;
		};

		Entry entries[64];
	};

	// The wrappers a state keeps its animated parameters in (RTTI pure3d::RefCountedBoolChannel and the like)
	class RefCountedBoolChannel : public RefCounted
	{
	public:
		BoolChannel* channel;
	};

	class RefCountedFloat1Channel : public RefCounted
	{
	public:
		Float1Channel* channel;
	};

	class RefCountedVectorChannel : public RefCounted
	{
	public:
		VectorChannel* channel;
	};

	class RefCountedRotationChannel : public RefCounted
	{
	public:
		RotationChannel* channel;
	};

	// What a generator reads its curves from (RTTI pure3d::ParticleGeneratorData): the arrays behind the pointer at +8
	class ParticleGeneratorData : public RefCounted
	{
	public:
		void* arrays;
	};
}

#endif
