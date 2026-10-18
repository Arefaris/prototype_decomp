// ravenphysics::IntersectionProperties: what a query collides with, the filter words every collision object and every
// body carries (meanings unknown).
#ifndef RAVENPHYSICS_INTERSECTIONPROPERTIES_H
#define RAVENPHYSICS_INTERSECTIONPROPERTIES_H

namespace ravenphysics
{
	// What a query collides with (0x10653860 constructs it from the physics library's defaults; meanings unknown)
	struct IntersectionProperties
	{
		IntersectionProperties();
		IntersectionProperties(int a, int b)
		{
			unknown0 = a;
			unknown4 = b;
		}

		// Whether two sets of properties name the same thing (0x10653610)
		bool operator==(const IntersectionProperties& other) const;

		int unknown0;
		int unknown4;
	};
}

#endif
