#include "code/ravenphysics/callback.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x1082BD90
	void PhysicsContextCallBack::SetNext(PhysicsContextCallBack* callback)
	{
		mNext = callback;
	}
}
