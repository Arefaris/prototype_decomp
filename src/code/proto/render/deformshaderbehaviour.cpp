// proto::DeformShaderBehaviour: see the header. The file name and the names are guesses.
#include "code/proto/render/deformshaderbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102D41C0
	// NONMATCHING: branch layout (the engine tests for a free slot with je, ours inverts it), 26 %
#ifdef NONMATCHING
	bool DentBuffer::Push(const Dent& dent)
	{
		if ((((unsigned char*)end - (unsigned char*)dents) & ~0x1Fu) == sizeof(dents))
		{
			return false;
		}
		Dent* slot = end;
		end = slot + 1;
		if (slot != 0)
		{
			*slot = dent;
		}
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x102D4350
	bool DeformShaderBehaviour::AddDent(const math::Vector& position, float unknownC, float unknown14, float unknown18)
	{
		Dent dent;
		dent.position.x = position.x;
		dent.position.y = position.y;
		dent.position.z = position.z;
		dent.unknownC = unknownC;
		dent.unknown10 = 0.0f;
		dent.unknown14 = unknown14;
		dent.unknown18 = unknown18;
		dent.unknown1C = 0.0f;
		return dents.Push(dent);
	}
}
