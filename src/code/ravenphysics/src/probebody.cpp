// A body of one sphere that the library keeps for its own queries (0x1127EB80 - 0x1127EB88): built once, then given a
// volume and a filter for each use. File and names are guesses.
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/engine/driving/carattributes.h"
#include "code/math/sphere.h"

namespace ravenphysics
{
	// A sphere of radius one around the origin
	struct UnitSphere : math::Sphere
	{
		UnitSphere()
		{
			centre.x = 0.0f;
			centre.y = 0.0f;
			centre.z = 0.0f;
			radius = engine::driving::gOne;
		}
	};

	// The body, its collision object and the sphere it was built from
	PhysicsObject* gProbeBody;           // 0x1127EB80
	CollisionObject* gProbeObject;       // 0x1127EB84
	CollisionVolume* gProbeSphere;       // 0x1127EB88

	// Builds the body around a unit sphere
	// FUNCTION: ENGINE 0x106A7070
	void Unknown106A7070()
	{
		gProbeSphere = new CollisionSphere(UnitSphere());
		gProbeObject = CreateCollisionObject(gProbeSphere, true, 1.0f);
		gProbeBody = PhysicsObject::Create(gProbeObject);
		gProbeBody->AddRef();
	}

	// Gives the body up
	// FUNCTION: ENGINE 0x106A70E0
	void Unknown106A70E0()
	{
		gProbeBody->Release();
	}

	// Puts a volume and a filter on the body and returns its collision object
	// FUNCTION: ENGINE 0x106A70F0
	CollisionObject* SetProbeVolume(CollisionVolume* volume, const BroadPhaseMasks* masks)
	{
		gProbeObject->volumes[0] = volume;
		gProbeBody->UpdateBounds();
		gProbeBody->SetFilter(masks);
		return gProbeObject;
	}

	// Puts the unit sphere back on the body
	// FUNCTION: ENGINE 0x106A7120
	void ResetProbeVolume()
	{
		gProbeObject->volumes[0] = gProbeSphere;
	}
}
