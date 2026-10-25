// The hull of a convex collision volume and the volumes of type 3 made of one (unit 0x1067F7D0 - 0x1067FFE0, no assert
// path, so the file name is a guess).
#include "code/math/mathconstants.h"
#include "code/math/worldbounds.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/collisionvolumefactory.h"
#include <new>

namespace ravenphysics
{
	// A vector copied component by component
	static inline void CopyVector(math::Vector& to, const math::Vector& from)
	{
		to.x = from.x;
		to.y = from.y;
		to.z = from.z;
	}

	// The two vertices of an edge
	static inline void SetEdge(unsigned char* edge, unsigned char first, unsigned char second)
	{
		edge[0] = first;
		edge[1] = second;
	}

	// FUNCTION: ENGINE 0x1067FA30
	ConvexHullData::ConvexHullData()
	{
		refCount = 0;
		vertexCount = 0;
		edgeCount = 0;
		faceCount = 0;
		vertices = 0;
		edges = 0;
		faces = 0;
		unknown44 = 0;
		unknown48 = 0;
		unknown4C = 0;
	}

	// FUNCTION: ENGINE 0x1067FA60
	ConvexHullData::~ConvexHullData()
	{
		if (vertices != 0)
		{
			delete[] vertices;
		}
		if (edges != 0)
		{
			delete[] edges;
		}
		if (faces != 0)
		{
			delete[] faces;
		}
		if (unknown44 != 0)
		{
			delete[] (char*)unknown44;
		}
		if (unknown48 != 0)
		{
			delete[] (char*)unknown48;
		}
		if (unknown4C != 0)
		{
			delete[] (char*)unknown4C;
		}
	}

	// FUNCTION: ENGINE 0x1067FAD0
	void ConvexHullData::AddRef()
	{
		refCount++;
	}

	// FUNCTION: ENGINE 0x1067FB00
	ConvexHullHolder::ConvexHullHolder()
	{
		data = new ConvexHullData;
		data->AddRef();
	}

	// FUNCTION: ENGINE 0x1067FBA0
	void CollisionVolume3::Move(const math::Matrix& transform)
	{
		matrix.Multiply(matrix, transform);
		inverse = matrix;
		inverse.Invert();
		world.Transform(transform);
		bounds.SetTransformed(matrix, localBox);
	}

	// FUNCTION: ENGINE 0x1067FBF0
	CollisionVolume3::CollisionVolume3() :
		CollisionVolume(3)
	{
		hull = new ConvexHullData;
		hull->AddRef();
		matrix.Identity();
		inverse.Identity();
		world.z = 0.0f;
		world.y = 0.0f;
		world.x = 0.0f;
		localBox.min.x = 0.0f;
		localBox.min.y = 0.0f;
		localBox.min.z = 0.0f;
		localBox.max.x = 0.0f;
		localBox.max.y = 0.0f;
		localBox.max.z = 0.0f;
		local.z = 0.0f;
		local.y = 0.0f;
		local.x = 0.0f;
	}

	// FUNCTION: ENGINE 0x1067FCA0
	// NONMATCHING: the differences of the corners, the cross product and the sum of the plane's offset are scheduled in another order (the sum's association may differ), 66.5 %
#ifdef NONMATCHING
	CollisionVolume3::CollisionVolume3(const math::Triangle& triangle) :
		CollisionVolume(3)
	{
		hull = new ConvexHullData;
		hull->AddRef();
		math::Vector* centre = &hull->centre;
		centre->z = 0.0f;
		centre->y = 0.0f;
		centre->x = 0.0f;
		hull->vertices = (math::Vector*)operator new[](0x24);
		hull->edges = (unsigned char*)operator new[](6);
		hull->faces = (math::Plane*)operator new[](0x10);
		hull->vertexCount = 3;
		hull->edgeCount = 3;
		hull->faceCount = 1;
		const math::Vector& a = triangle.a;
		const math::Vector& b = triangle.b;
		const math::Vector& c = triangle.c;
		math::AABB* hullBounds = &hull->bounds;
		hullBounds->min.x = a.x;
		hullBounds->min.y = a.y;
		hullBounds->min.z = a.z;
		hullBounds->max.x = b.x;
		hullBounds->max.y = b.y;
		hullBounds->max.z = b.z;
		hullBounds = &hull->bounds;
		float low = hullBounds->min.x;
		if (!(c.x > low))
		{
			low = c.x;
		}
		hullBounds->min.x = low;
		low = hullBounds->min.y;
		if (!(c.y > low))
		{
			low = c.y;
		}
		hullBounds->min.y = low;
		low = hullBounds->min.z;
		if (!(c.z > low))
		{
			low = c.z;
		}
		hullBounds->min.z = low;
		float high = hullBounds->max.x;
		if (high < c.x)
		{
			high = c.x;
		}
		hullBounds->max.x = high;
		high = hullBounds->max.y;
		if (high < c.y)
		{
			high = c.y;
		}
		hullBounds->max.y = high;
		high = hullBounds->max.z;
		if (high < c.z)
		{
			high = c.z;
		}
		hullBounds->max.z = high;
		CopyVector(*hull->vertices, a);
		CopyVector(hull->vertices[1], b);
		CopyVector(hull->vertices[2], c);
		SetEdge(hull->edges, 0, 1);
		SetEdge(hull->edges + 2, 1, 2);
		SetEdge(hull->edges + 4, 2, 0);
		math::Vector second;
		second.z = a.z - c.z;
		second.y = a.y - c.y;
		second.x = a.x - c.x;
		math::Vector first;
		first.z = a.z - b.z;
		first.y = a.y - b.y;
		first.x = a.x - b.x;
		math::Vector normal;
		normal.Cross(first, second);
		normal.Normalize();
		math::Plane* face = hull->faces;
		face->normal.x = normal.x;
		face->normal.y = normal.y;
		face->normal.z = normal.z;
		face->d = math::WORLD_MIN - (face->normal.y * a.y + face->normal.x * a.x + a.z * normal.z);
		ConvexHullData* data = hull;
		localBox.max.x = data->bounds.max.x;
		localBox.max.y = data->bounds.max.y;
		localBox.max.z = data->bounds.max.z;
		localBox.min.x = data->bounds.min.x;
		localBox.min.y = data->bounds.min.y;
		localBox.min.z = data->bounds.min.z;
		CopyVector(local, data->centre);
		matrix = math::Matrix::IDENTITY;
		inverse = matrix;
		inverse.Invert();
		world.Transform(local, math::Matrix::IDENTITY);
		bounds.SetTransformed(matrix, localBox);
		bounds.SetTransformed(matrix, localBox);
	}
#endif

	// FUNCTION: ENGINE 0x1067FFE0
	CollisionVolume3::CollisionVolume3(const CollisionVolume3& other) :
		CollisionVolume(other)
	{
		hull = other.hull;
		if (hull != 0)
		{
			hull->AddRef();
		}
		matrix = other.matrix;
		inverse = other.inverse;
		world.x = other.world.x;
		world.y = other.world.y;
		world.z = other.world.z;
		localBox.max.x = other.localBox.max.x;
		localBox.max.y = other.localBox.max.y;
		localBox.max.z = other.localBox.max.z;
		localBox.min.x = other.localBox.min.x;
		localBox.min.y = other.localBox.min.y;
		localBox.min.z = other.localBox.min.z;
		local.x = other.local.x;
		local.y = other.local.y;
		local.z = other.local.z;
	}
}

// Kept copies of the unit's inline functions and template instances
