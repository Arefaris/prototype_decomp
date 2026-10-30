// The overlap tests of the narrow phase: one yes / no function per pair of collision volume types (capsule, box,
// sphere, two hull kinds, plane, mesh), reached through the second pair table (0x110C49A0). A hit is recorded in the
// contact buffer as a face-less entry. Names are guesses.
#include "code/math/capsule.h"
#include "code/math/obb.h"
#include "code/math/plane.h"
#include "code/math/sphere.h"
#include "code/math/vector.h"
#include "code/ravenphysics/collision/narrowphase/narrowphase.h"

namespace math
{
	// Library tests (another unit, 0x107DA110 - 0x107DC2B0)
	int Intersects(const Capsule& first, const Capsule& second);
	bool Intersects(const Capsule& first, const OBB& second);
	int Intersects(const Capsule& first, const Sphere& second);
	int Intersects(const Plane& first, const Capsule& second);
	bool Intersects(const OBB& first, const OBB& second);
	int Intersects(const OBB& first, const Sphere& second);
	int Intersects(const Plane& first, const OBB& second);
}

namespace ravenphysics
{
	// The test of two volumes of which at least one is a hull (another unit, 0x10677890)
	bool VolumesOverlap(CollisionVolume* a, CollisionVolume* b);

	// The tests of a volume against a mesh (0x106AE250 - 0x106AE8E0 in this unit's neighbourhood)
	bool OverlapCapsuleMeshTest(CollisionCapsule* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info);
	bool OverlapBoxMeshTest(CollisionOBB* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info);
	bool OverlapSphereMeshTest(CollisionSphere* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info);
	bool OverlapHullMeshTest(CollisionVolume3* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info);
	bool OverlapHullGroupMeshTest(CollisionVolume4* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info);

	// FUNCTION: ENGINE 0x106B2420
	bool OverlapCapsules(CollisionCapsule* a, CollisionCapsule* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if ((char)math::Intersects(a->capsule, b->capsule))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2450
	bool OverlapCapsuleBox(CollisionCapsule* a, CollisionOBB* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (math::Intersects(a->capsule, b->obb))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2480
	bool OverlapCapsuleSphere(CollisionCapsule* a, CollisionSphere* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if ((char)math::Intersects(a->capsule, b->sphere))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B24B0
	bool OverlapCapsuleHull(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B24E0
	bool OverlapCapsuleHullGroup(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2510
	bool OverlapCapsulePlane(CollisionCapsule* a, CollisionPlane* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if ((char)math::Intersects(b->plane, a->capsule))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2550
	bool OverlapBoxes(CollisionOBB* a, CollisionOBB* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (math::Intersects(a->obb, b->obb))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2580
	bool OverlapBoxSphere(CollisionOBB* a, CollisionSphere* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if ((char)math::Intersects(a->obb, b->sphere))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B25B0
	bool OverlapBoxHull(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B25E0
	bool OverlapBoxHullGroup(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2610
	bool OverlapBoxPlane(CollisionOBB* a, CollisionPlane* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if ((char)math::Intersects(b->plane, a->obb))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2650
	// NONMATCHING: 63.2 %: the engine loads the centre differences before the radii and keeps the sum of radii in xmm0, ours schedules the radii first
#ifdef NONMATCHING
	bool OverlapSpheres(CollisionSphere* a, CollisionSphere* b, ContactBuffer* contacts, CollideInfo* info)
	{
		float distanceSquared = math::DistanceSquared(a->sphere.centre, b->sphere.centre);
		float reach = a->sphere.radius + b->sphere.radius;
		if (distanceSquared <= reach * reach)
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x106B26C0
	bool OverlapSphereHull(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B26F0
	bool OverlapSphereHullGroup(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2720
	// NONMATCHING: 55.1 %: the engine reads the first argument into ecx and multiplies the sphere's component by the plane's, ours loads the plane's first
#ifdef NONMATCHING
	bool OverlapSpherePlane(CollisionSphere* a, CollisionPlane* b, ContactBuffer* contacts, CollideInfo* info)
	{
		float distance = b->plane.normal.z * a->sphere.centre.z + b->plane.normal.y * a->sphere.centre.y
			+ b->plane.normal.x * a->sphere.centre.x;
		if (a->sphere.radius - b->plane.d >= distance)
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x106B2780
	bool OverlapHulls(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B27B0
	bool OverlapHullHullGroup(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B27E0
	bool OverlapHullPlane(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2820
	bool OverlapHullGroups(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2850
	bool OverlapHullGroupPlane(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		if (VolumesOverlap(a, b))
		{
			contacts->AddFace(-1);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106B2540
	bool OverlapCapsuleMesh(CollisionCapsule* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info)
	{
		return OverlapCapsuleMeshTest(a, b, contacts, info);
	}

	// FUNCTION: ENGINE 0x106B2640
	bool OverlapBoxMesh(CollisionOBB* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info)
	{
		return OverlapBoxMeshTest(a, b, contacts, info);
	}

	// FUNCTION: ENGINE 0x106B2770
	bool OverlapSphereMesh(CollisionSphere* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info)
	{
		return OverlapSphereMeshTest(a, b, contacts, info);
	}

	// FUNCTION: ENGINE 0x106B2810
	bool OverlapHullMesh(CollisionVolume3* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info)
	{
		return OverlapHullMeshTest(a, b, contacts, info);
	}

	// FUNCTION: ENGINE 0x106B2880
	bool OverlapHullGroupMesh(CollisionVolume4* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info)
	{
		return OverlapHullGroupMeshTest(a, b, contacts, info);
	}

	// FUNCTION: ENGINE 0x106AE8D0
	bool OverlapHullGroupMeshTest(CollisionVolume4* a, CollisionVolume6* b, ContactBuffer* contacts, CollideInfo* info)
	{
		return OverlapHullMeshTest(&a->materials, b, contacts, info);
	}
}
