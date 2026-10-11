// Intersection tests between the math primitives (0x107D9A20 - 0x107DAB30). Free functions in namespace math;
// the unit's file name and the function names are guesses (no assert path survives for it).
#include <math.h>

#include "code/math/aabb.h"
#include "code/math/capsule.h"
#include "code/math/mathconstants.h"
#include "code/math/matrix3.h"
#include "code/math/obb.h"
#include "code/math/plane.h"
#include "code/math/segment.h"
#include "code/math/sphere.h"
#include "code/math/triangle.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"

// std::sort<float*> is called out of line, as the original does (its copy sits at 0x102CFF00 with another unit's
// code); declared here without <algorithm>, whose inline definition the compiler would expand
namespace std
{
	template<class RandomIt> void sort(RandomIt first, RandomIt last);
}

namespace math
{
	// 0x107D9A20: separating-axis test of a segment (midpoint offset delta from the box centre, half direction
	// direction scaled by length) against a box of half extents extents, in the box's axis space
	bool TestBoxAxes(const Vector& extents, const Vector& direction, const Vector& delta, float length);
	// 0x107D9CB0: separating-axis test of two boxes (extents, centre offset in A's space, rotation B in A's space)
	int TestBoxesSAT(const Vector& extentsA, const Vector& delta, const Matrix3& rotation, const Vector& extentsB);
	// 0x107DB250: separating-axis test of a triangle (three Vector4 corners) against a box (centre, half extents)
	int TriangleBoxOverlap(const Vector& centre, const Vector& halfExtents, Vector4* vertices);
	// 0x107DBD20: squared distance from the segment start + direction * t, t in [0, length], to a box of half
	// extents extents centred on the origin
	float SegmentBoxDistanceSquared(const Vector& extents, const Vector& start, const Vector& direction, float length);

	// FUNCTION: ENGINE 0x107D9B60
	// EQUIVALENT: same operations in the same order; the original schedules delta.y's subtraction after the push of
	// length (87.3 %)
	bool IntersectsAABB(const Vector& direction, const Vector& point, float length, const AABB& box)
	{
		Vector centre;
		centre.Add(box.max, box.min);
		centre.x *= 0.5f;
		centre.y *= 0.5f;
		centre.z *= 0.5f;
		Vector extents;
		extents.Sub(box.max, centre);
		Vector delta;
		delta.Sub(point, centre);
		return TestBoxAxes(extents, direction, delta, length);
	}

	// FUNCTION: ENGINE 0x107D9C20
	bool IntersectsOBB(const Vector& direction, const Vector& point, float length, const OBB& box)
	{
		const Matrix3& axes = *(const Matrix3*)box.axis;
		Vector localDirection;
		axes.TransformTransposed(direction, localDirection);
		Vector delta;
		delta.x = point.x - box.centre.x;
		delta.y = point.y - box.centre.y;
		delta.z = point.z - box.centre.z;
		Vector localDelta;
		axes.TransformTransposed(delta, localDelta);
		return TestBoxAxes(box.extents, localDirection, localDelta, length);
	}

	// FUNCTION: ENGINE 0x107DA110
	// EQUIVALENT: same operations in the same order; the x terms of r[0][1] and r[1][2] multiply a's axis by b's
	// where we get b's by a's (commutative). The reference locals for the two boxes are what make the other products
	// load b's axis first, as the original does (98.6 %)
	int Intersects(const OBB& a, const OBB& b)
	{
		// b's centre and axes in a's frame, then the box-box separating axis test
		Vector d;
		d.Sub(b.centre, a.centre);
		Vector t;
		t.x = a.axis[0].Dot(d);
		t.y = a.axis[1].Dot(d);
		t.z = a.axis[2].Dot(d);
		const OBB& aa = a;
		const OBB& bb = b;
		Matrix3 r;
		for (int j = 0; j < 3; j++)
		{
			r.m[0][j] = aa.axis[0].Dot(bb.axis[j]);
			r.m[1][j] = aa.axis[1].Dot(bb.axis[j]);
			r.m[2][j] = aa.axis[2].Dot(bb.axis[j]);
		}
		return TestBoxesSAT(a.extents, t, r, b.extents);
	}

	// FUNCTION: ENGINE 0x107DA360
	int Intersects(const OBB& obb, const AABB& box)
	{
		Vector centre;
		centre.Add(box.max, box.min);
		centre.x *= 0.5f;
		centre.y *= 0.5f;
		centre.z *= 0.5f;
		Vector extents;
		extents.Sub(box.max, centre);
		Vector delta;
		delta.Sub(obb.centre, centre);
		return TestBoxesSAT(extents, delta, *(const Matrix3*)obb.axis, obb.extents);
	}

	// FUNCTION: ENGINE 0x107DA410
	int Intersects(const OBB& box, const Sphere& sphere)
	{
		Vector d;
		d.Sub(sphere.centre, box.centre);
		float distanceSquared = 0.0f;
		for (int i = 3; i--; )
		{
			const Vector& v = box.axis[i];
			float excess = fabsf((v.x * d.x + v.y * d.y) + v.z * d.z) - (&box.extents.x)[i];
			if (excess > 0.0f)
			{
				distanceSquared += excess * excess;
			}
		}
		return sphere.radius * sphere.radius > distanceSquared;
	}

	// FUNCTION: ENGINE 0x107DA4D0
	int Intersects(const Capsule& a, const Capsule& b)
	{
		Segment segmentA;
		a.GetSegment(segmentA);
		Segment segmentB;
		b.GetSegment(segmentB);
		float r = a.radius + b.radius;
		return segmentA.DistanceSquared(segmentB) <= r * r;
	}

	// FUNCTION: ENGINE 0x107DA530
	int Intersects(const Capsule& capsule, const Sphere& sphere)
	{
		Segment segment;
		capsule.GetSegment(segment);
		float r = capsule.radius + sphere.radius;
		return segment.DistanceSquared(sphere.centre) <= r * r;
	}

	// FUNCTION: ENGINE 0x107DA580
	int Intersects(const Capsule& capsule, const Segment& other)
	{
		Segment segment;
		capsule.GetSegment(segment);
		float r = capsule.radius;
		return segment.DistanceSquared(other) <= r * r;
	}

	// FUNCTION: ENGINE 0x107DA5D0
	// NONMATCHING: the distance and the three dots match in form, but the original keeps normal z, y, x on the x87
	// stack (we load x first) and sums the projected radius as axis 2, axis 0, axis 1 where every source order gives
	// axis 1, axis 0, axis 2 (82.6 %)
#ifdef NONMATCHING
	int Intersects(const Plane& plane, const OBB& box)
	{
		Vector n(plane.normal);
		float distance = (box.centre.z * n.z + box.centre.y * n.y) + box.centre.x * n.x + plane.d;
		const Vector& a0 = box.axis[0];
		const Vector& a1 = box.axis[1];
		const Vector& a2 = box.axis[2];
		float r = fabsf((a2.x * n.x + a2.y * n.y) + a2.z * n.z) * box.extents.z + fabsf((a0.y * n.y + a0.z * n.z) + n.x * a0.x) * box.extents.x + fabsf((a1.x * n.x + a1.y * n.y) + a1.z * n.z) * box.extents.y;
		return distance <= r;
	}
#endif

	// FUNCTION: ENGINE 0x107DA660
	// EQUIVALENT: same operations; the original keeps normal.x in xmm1 and normal.z in xmm3, we get the reverse, and
	// the second dot product adds its x and y terms the other way round (76 %)
	int Intersects(const Plane& plane, const Capsule& capsule)
	{
		// The plane moved back by the radius; the capsule misses it when both segment ends are in front
		Plane shifted;
		shifted.normal.z = plane.normal.z;
		shifted.normal.y = plane.normal.y;
		shifted.normal.x = plane.normal.x;
		shifted.d = plane.d - capsule.radius;
		Segment segment;
		capsule.GetSegment(segment);
		return -shifted.d >= segment.start.x * shifted.normal.x + segment.start.y * shifted.normal.y + segment.start.z * shifted.normal.z
			|| -shifted.d >= segment.end.x * shifted.normal.x + segment.end.z * shifted.normal.z + segment.end.y * shifted.normal.y;
	}

	// FUNCTION: ENGINE 0x107DA850
	int ClassifyBox(const AABB& box, const Plane* planes, unsigned int count)
	{
		// Per plane: the corner nearest the back side (lo) in front means the box is outside; the far corner (hi) on or
		// in front means it crosses. Indexing planes[i] directly (no reference) gives the original's registers
		int result = 2;
		for (unsigned int i = 0; i < count; i++)
		{
			Vector hi;
			Vector lo;
			if (planes[i].normal.x >= 0.0f)
			{
				lo.x = box.min.x;
				hi.x = box.max.x;
			}
			else
			{
				lo.x = box.max.x;
				hi.x = box.min.x;
			}
			if (planes[i].normal.y >= 0.0f)
			{
				lo.y = box.min.y;
				hi.y = box.max.y;
			}
			else
			{
				lo.y = box.max.y;
				hi.y = box.min.y;
			}
			if (planes[i].normal.z >= 0.0f)
			{
				lo.z = box.min.z;
				hi.z = box.max.z;
			}
			else
			{
				lo.z = box.max.z;
				hi.z = box.min.z;
			}
			if (planes[i].normal.Dot(lo) + planes[i].d > 0.0f)
			{
				return 0;
			}
			if (planes[i].normal.Dot(hi) + planes[i].d >= 0.0f)
			{
				result = 1;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x107DBB10
	int Intersects(const Triangle& triangle, const OBB& box)
	{
		// The corners in the box's axis space; the array is reused for the (zero) centre and the extents, which is
		// what gives the original's frame (0x60 bytes, the two call arguments in local[1] and local[2])
		const Matrix3& axes = *(const Matrix3*)box.axis;
		Vector d;
		Vector local[3];
		d.Sub(triangle.a, box.centre);
		axes.TransformTransposed(d, local[0]);
		d.Sub(triangle.b, box.centre);
		axes.TransformTransposed(d, local[1]);
		d.Sub(triangle.c, box.centre);
		axes.TransformTransposed(d, local[2]);
		Vector4 vertices[3];
		for (int i = 0; i < 3; i++)
		{
			vertices[i].x = local[i].x;
			vertices[i].y = local[i].y;
			vertices[i].z = local[i].z;
			vertices[i].w = 0.0f;
		}
		local[1].Set(0.0f, 0.0f, 0.0f);
		local[2].Set(box.extents.x, box.extents.y, box.extents.z);
		return TriangleBoxOverlap(local[1], local[2], vertices);
	}

	// FUNCTION: ENGINE 0x107DBCC0
	int Intersects(const Triangle& triangle, const Sphere& sphere)
	{
		Vector closest;
		triangle.ClosestPoint(sphere.centre, closest);
		Vector d;
		d.Sub(sphere.centre, closest);
		return sqrtf(d.y * d.y + d.z * d.z + d.x * d.x) <= sphere.radius;
	}

	// FUNCTION: ENGINE 0x107DBD20
	// EQUIVALENT: same operations in the same order (14.9 %); the original keeps the loop counter in ebx and spills the
	// start offset and the direction component (into length's slot), and compares the start's excess on the x87
	float SegmentBoxDistanceSquared(const Vector& extents, const Vector& start, const Vector& direction, float length)
	{
		// The segment parameters where it crosses a face plane of a slab, sorted: the distance is convex between them
		float t[8];
		t[0] = 0.0f;
		t[1] = length;
		int count = 2;
		for (int i = 3; i != 0; )
		{
			i--;
			float d = (&direction.x)[i];
			if (!(EPSILON_SMALL > fabsf(d)))
			{
				float e = (&extents.x)[i];
				float s = (&start.x)[i];
				float inv = 1.0f / d;
				float a = (e - s) * inv;
				if (a > 0.0f && a < length)
				{
					t[count++] = a;
				}
				float b = (-e - s) * inv;
				if (b > 0.0f && b < length)
				{
					t[count++] = b;
				}
			}
		}
		std::sort(t, t + count);
		// The start's own distance, then the best point of each interval (a projection step from its midpoint)
		float best = 0.0f;
		for (int i = 3; i != 0; )
		{
			i--;
			float a = fabsf((&start.x)[i]);
			if (a - (&extents.x)[i] > 0.0f)
			{
				float excess = a - (&extents.x)[i];
				best = excess * excess + best;
			}
		}
		for (int i = 0; i < count - 1; i++)
		{
			if (best < EPSILON_SMALL)
			{
				break;
			}
			float mid = (t[i + 1] + t[i]) * 0.5f;
			float u = 0.0f;
			for (int j = 3; j != 0; )
			{
				j--;
				float d = (&direction.x)[j];
				float s = (&start.x)[j];
				float e = (&extents.x)[j];
				float p = d * mid + s;
				if (p - e > 0.0f)
				{
					u = (e - s) * d + u;
				}
				else if (e + p < 0.0f)
				{
					u = (-e - s) * d + u;
				}
				else
				{
					u = -s * d + u;
				}
			}
			if (t[i] > u)
			{
				u = t[i];
			}
			else if (u > t[i + 1])
			{
				u = t[i + 1];
			}
			float distance = 0.0f;
			float ex = fabsf(direction.x * u + start.x) - extents.x;
			if (ex > 0.0f)
			{
				distance = ex * ex;
			}
			float ey = fabsf(direction.y * u + start.y) - extents.y;
			if (ey > 0.0f)
			{
				distance = ey * ey + distance;
			}
			float ez = fabsf(u * direction.z + start.z) - extents.z;
			if (ez > 0.0f)
			{
				distance = ez * ez + distance;
			}
			if (distance < best)
			{
				best = distance;
			}
		}
		return best;
	}

	// FUNCTION: ENGINE 0x107DBFE0
	// EQUIVALENT: the separating-axis tests (three faces, three edge cross products) and the segment tail keep the
	// original's operations and order; the original reloads capsule.direction from memory for the tail where we reuse
	// the spilled test values, which costs us a fourth spill slot (28.7 %; float locals, a Vector copy of the centre,
	// a reference local and an offset Vector tried)
	bool IntersectsCentredBox(const Vector& extents, const Capsule& capsule)
	{
		float cx = capsule.centre.x;
		float adx = fabsf(capsule.direction.x);
		float h = capsule.halfLength;
		float r = capsule.radius;
		float ex = extents.x;
		if (fabsf(cx) > ex + adx * h + r)
		{
			return false;
		}
		float cy = capsule.centre.y;
		float ady = fabsf(capsule.direction.y);
		float ey = extents.y;
		if (fabsf(cy) > ey + ady * h + r)
		{
			return false;
		}
		float cz = capsule.centre.z;
		float adz = fabsf(capsule.direction.z);
		float ez = extents.z;
		if (fabsf(cz) > ez + adz * h + r)
		{
			return false;
		}
		if (fabsf(cz * capsule.direction.y - capsule.direction.z * cy) > ey * adz + ez * ady + r)
		{
			return false;
		}
		if (fabsf(cx * capsule.direction.z - cz * capsule.direction.x) > ex * adz + ez * adx + r)
		{
			return false;
		}
		if (fabsf(cy * capsule.direction.x - cx * capsule.direction.y) > ex * ady + ey * adx + r)
		{
			return false;
		}
		Vector start;
		start.x = cx - capsule.direction.x * capsule.halfLength;
		start.y = cy - capsule.direction.y * capsule.halfLength;
		start.z = cz - capsule.direction.z * capsule.halfLength;
		float distance = SegmentBoxDistanceSquared(extents, start, capsule.direction, capsule.halfLength * 2.0f);
		return capsule.radius * capsule.radius > distance;
	}

	// FUNCTION: ENGINE 0x107DC1D0
	// EQUIVALENT: same operations; the original defers the stores of local.centre.x / z past the member copies, we
	// store z first (60.8 %; Capsule copy construction, an operator- temporary and statement orders do not fix it)
	bool Intersects(const Capsule& capsule, const AABB& box)
	{
		Vector centre;
		centre.Add(box.max, box.min);
		centre.x *= 0.5f;
		centre.y *= 0.5f;
		centre.z *= 0.5f;
		Vector extents;
		extents.Sub(box.max, centre);
		Capsule local;
		local.centre.Sub(capsule.centre, centre);
		local.halfLength = capsule.halfLength;
		local.direction.x = capsule.direction.x;
		local.direction.y = capsule.direction.y;
		local.direction.z = capsule.direction.z;
		local.radius = capsule.radius;
		return IntersectsCentredBox(extents, local);
	}

	// FUNCTION: ENGINE 0x107DC2B0
	bool Intersects(const Capsule& capsule, const OBB& box)
	{
		const Matrix3& axes = *(const Matrix3*)box.axis;
		Vector direction;
		axes.TransformTransposed(capsule.direction, direction);
		Vector d;
		d.x = capsule.centre.x - box.centre.x;
		d.y = capsule.centre.y - box.centre.y;
		d.z = capsule.centre.z - box.centre.z;
		Vector centre;
		axes.TransformTransposed(d, centre);
		Capsule local;
		local.centre.x = centre.x;
		local.centre.y = centre.y;
		local.centre.z = centre.z;
		local.halfLength = capsule.halfLength;
		local.direction.x = direction.x;
		local.direction.y = direction.y;
		local.direction.z = direction.z;
		local.radius = capsule.radius;
		return IntersectsCentredBox(box.extents, local);
	}
}
