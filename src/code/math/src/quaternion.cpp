#include "code/math/quaternion.h"

namespace math
{
	// FUNCTION: ENGINE 0x107CE220
	// NONMATCHING: same instructions, but the original keeps this in eax and q in ecx (we get the reverse)
#ifdef NONMATCHING
	void Quaternion::MakeClosest(const Quaternion& q)
	{
		if (x * q.x + y * q.y + z * q.z + w * q.w < 0.0f)
		{
			x = -x;
			y = -y;
			z = -z;
			w = -w;
		}
	}
#endif
}
