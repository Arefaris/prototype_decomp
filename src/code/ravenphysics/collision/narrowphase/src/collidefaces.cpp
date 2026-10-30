// The volume against a triangle of a mesh: each function takes the triangle's corners from the mesh's grid and hands
// them, the grid's record and the triangle's number on to the pair function proper. Names are guesses.
#include "code/ravenphysics/broadphase/broadphasegrid.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/collision/narrowphase/narrowphase.h"

namespace ravenphysics
{
	// The pair functions proper (another unit, 0x106CE140 - 0x106D72C0)
	void CollideFacePairFirst(void* volume, GridFace* record, math::Vector* corners, unsigned int flags, unsigned int face,
		ContactBuffer* contacts);
	void CollideFacePairSecond(void* volume, GridFace* record, math::Vector* corners, unsigned int flags, unsigned int face,
		ContactBuffer* contacts);
	void CollideFacePairThird(void* volume, GridFace* record, math::Vector* corners, unsigned int flags, unsigned int face,
		ContactBuffer* contacts);
	void CollideFacePairFourth(void* volume, GridFace* record, math::Vector* corners, unsigned int flags, unsigned int face,
		ContactBuffer* contacts);

	// FUNCTION: ENGINE 0x106B22B0
	void CollideFaceFirst(void* volume, CollisionVolume6* mesh, unsigned int face, ContactBuffer* contacts)
	{
		GridFace* record = mesh->grid.faces + (unsigned short)face;
		math::Vector corners[3];
		mesh->grid.GetTriangle((unsigned short)face, corners);
		CollideFacePairFirst(volume, record, corners, record->flags & 7, face, contacts);
	}

	// FUNCTION: ENGINE 0x106B2300
	void CollideFaceSecond(void* volume, CollisionVolume6* mesh, unsigned int face, ContactBuffer* contacts)
	{
		GridFace* record = mesh->grid.faces + (unsigned short)face;
		math::Vector corners[3];
		mesh->grid.GetTriangle((unsigned short)face, corners);
		CollideFacePairSecond(volume, record, corners, record->flags & 7, face, contacts);
	}

	// FUNCTION: ENGINE 0x106B2350
	void CollideFaceThird(void* volume, CollisionVolume6* mesh, unsigned int face, ContactBuffer* contacts)
	{
		GridFace* record = mesh->grid.faces + (unsigned short)face;
		math::Vector corners[3];
		mesh->grid.GetTriangle((unsigned short)face, corners);
		CollideFacePairThird(volume, record, corners, record->flags & 7, face, contacts);
	}

	// FUNCTION: ENGINE 0x106B23A0
	void CollideFaceFourth(void* volume, CollisionVolume6* mesh, unsigned int face, ContactBuffer* contacts)
	{
		GridFace* record = mesh->grid.faces + (unsigned short)face;
		math::Vector corners[3];
		mesh->grid.GetTriangle((unsigned short)face, corners);
		CollideFacePairFourth(volume, record, corners, record->flags & 7, face, contacts);
	}
}
