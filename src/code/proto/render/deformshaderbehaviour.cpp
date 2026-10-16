// proto::DeformShaderBehaviour: see the header. The file name and the names are guesses.
//
// DentBuffer::Push (0x102D41C0, the same unit) is only declared: the engine copies the 0x20-byte dent with eight
// x87 fld / fstp pairs, which is the compiler's copy *constructor* of the record, while the assignment our type gets
// is one `rep movsd` - the record type the engine copies that way is not recovered (25 %).
#include "code/proto/render/deformshaderbehaviour.h"

namespace proto
{
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
