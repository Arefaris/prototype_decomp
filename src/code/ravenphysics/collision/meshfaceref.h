// A reference to one triangle of a mesh volume: the handle of the mesh in the physics handle table and the number of
// the triangle in its grid (class and member names are guesses; RTTI does not name it). The methods reach the mesh
// through the table every time, so a reference outlives a mesh that is gone and answers IsValid false for it.
#ifndef RAVENPHYSICS_COLLISION_MESHFACEREF_H
#define RAVENPHYSICS_COLLISION_MESHFACEREF_H

#include "code/math/triangle.h"
#include "code/math/vector.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace ravenphysics
{
	// The handle of a mesh volume: the same pair as a CollisionHandle, with the lookups the mesh code calls (the
	// engine's copies of them, in another unit; names guessed)
	struct MeshHandle
	{
		// Names no mesh
		MeshHandle()
		{
			value = 0xffffffff;
		}

		// Whether the table still holds the mesh the handle was made for (0x106A7ED0)
		bool IsValid() const;
		// The mesh the handle names (0x106A7F00)
		CollisionVolume6* Get() const;

		union
		{
			unsigned int value;
			struct
			{
				unsigned short index;
				unsigned short serial;
			};
		};
	};

	// The normal of the triangle a, b, c (0x106673A0; name guessed)
	void CalculateNormal(const math::Vector* a, const math::Vector* b, const math::Vector* c, math::Vector* normal);

	// A line in the XZ plane, x * a + z * b = -c (a, b and c in the order of a vector's members; name guessed)
	struct XZLine
	{
		// Whether the point lies on the side the line's normal points to (0x10667C50)
		bool IsAbove(const math::Vector* point) const;

		float a;
		float b;
		float c;
	};

	struct MeshFaceRef
	{
		// The triangle of a mesh, or none for no mesh (0x10667660)
		void Set(CollisionVolume6* volume, unsigned short newFace);
		// Whether the mesh is still there and the reference names a triangle (0x10667690)
		bool IsValid() const;
		// Names no triangle (0x106676B0)
		void Clear();
		// One of the three corners, in the mesh's own space (0x106676C0)
		const math::Vector* GetCorner(int corner) const;
		// The three corners (0x10667760)
		void GetCorners(math::Vector* corners) const;
		// A corner in the world (0x106676F0) and the three of them (0x10667DE0, which remembers the last triangle it was
		// asked for; the second answers them by value, 0x10667F30)
		void GetWorldCorner(int corner, math::Vector* out) const;
		void GetWorldTriangle(math::Triangle* out) const;
		math::Triangle GetWorldTriangleCopy() const;
		// The centre of the triangle in the mesh's space (0x106677E0) and in the world (0x106678C0)
		void GetCentre(math::Vector* centre) const;
		void GetWorldCentre(math::Vector* centre) const;
		// The sum of the corners, in the mesh's space (0x106679C0) and in the world (0x10667A70)
		void GetCornerSum(math::Vector* sum) const;
		void GetWorldCornerSum(math::Vector* sum) const;
		// Whether the triangle has a neighbour over an edge (0x10667B40) and the neighbour (0x106680A0)
		bool HasNeighbour(int edge) const;
		MeshFaceRef GetNeighbourRef(int edge) const;
		// The difference between the highest and the lowest corner (0x10668040)
		float GetHeight() const;
		// One more than the dot product of the triangle's normal with the way down (0x10668120)
		float GetSlope() const;
		// Which of the corners the line cuts off from the others, or 0xFFFF when the point lies inside the triangle's
		// projection on the XZ plane or the line leaves all corners on one side (0x10668220)
		int FindCornerXZ(const XZLine* line, const math::Vector* point) const;
		// The three flag bits of the triangle (0x10667BC0 / 0x10667BE0 / 0x10667C00) and the six bits after them
		// (0x10667C20)
		unsigned int GetFlag0() const;
		unsigned int GetFlag1() const;
		unsigned int GetFlag2() const;
		unsigned int GetProperty() const;
		// The normal of the triangle in the mesh's space (0x10667F50) and in the world (0x10667F80)
		void GetNormal(math::Vector* normal) const;
		void GetWorldNormal(math::Vector* normal) const;

		MeshHandle mesh;           // 0x00
		unsigned short face;       // 0x04
	};
}

#endif
