#include "code/ravenphysics/collision/narrowphase/narrowphase.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106A8450
	bool ContactBuffer::AddFace(int face)
	{
		if (count < capacity)
		{
			Contact* contact = Next();
			contact->unknown2E = 1;
			contact->unknown28 = face;
			return true;
		}
		return false;
	}
}
