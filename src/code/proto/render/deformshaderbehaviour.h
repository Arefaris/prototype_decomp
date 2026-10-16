// proto::DeformShaderBehaviour (RTTI; vftable 0x10DEA3CC): the behaviour that dents a vehicle's deformation shader.
// It keeps the last four dents in a small ring at +4 and hands them to its DeformShaderModifier (vtable 0x10DEA3C0).
// The unit has no assert path, so the file name, the class layout and the member names are guesses.
#ifndef PROTO_RENDER_DEFORMSHADERBEHAVIOUR_H
#define PROTO_RENDER_DEFORMSHADERBEHAVIOUR_H

#include "code/math/vector.h"

namespace proto
{
	// One dent: where it is, the direction it was hit from and how deep it goes
	struct Dent
	{
		Dent()
		{
		}
		// The engine's copy of a dent runs component by component through the x87 unit (fld / fstp)
		Dent& operator=(const Dent& dent)
		{
			position.x = dent.position.x;
			position.y = dent.position.y;
			position.z = dent.position.z;
			unknownC = dent.unknownC;
			unknown10 = dent.unknown10;
			unknown14 = dent.unknown14;
			unknown18 = dent.unknown18;
			unknown1C = dent.unknown1C;
			return *this;
		}

		math::Vector position;   // +0x00
		float unknownC;          // +0x0C
		float unknown10;         // +0x10
		float unknown14;         // +0x14
		float unknown18;         // +0x18
		float unknown1C;         // +0x1C
	};

	// The four dents the shader keeps: the buffer runs from the object's own address and end points just past the
	// dent added last (0x84 bytes)
	class DentBuffer
	{
	public:
		// 0x102D41C0 (another function of the same unit): appends dent, false when the four slots are taken
		bool Push(const Dent& dent);

		Dent dents[4];
		Dent* end;
	};

	class DeformShaderBehaviour
	{
	public:
		// 0x102D4350: stores one more dent
		bool AddDent(const math::Vector& position, float unknownC, float unknown14, float unknown18);

		// +0 the vftable, +4 the dent ring
		unsigned char unknown0[4];
		DentBuffer dents;
	};
}

#endif
