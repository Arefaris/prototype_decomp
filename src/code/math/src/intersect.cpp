// Intersection tests between the math primitives (0x107D9A20 - 0x107DAB30). Free functions in namespace math;
// the unit's file name and the function names are guesses (no assert path survives for it).
#include <math.h>

#include "code/math/aabb.h"
#include "code/math/capsule.h"
#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
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
	bool TestBoxesSAT(const Vector& extentsA, const Vector& delta, const Matrix3& rotation, const Vector& extentsB);
	// 0x107DB250: separating-axis test of a triangle (three Vector4 corners) against a box (centre, half extents)
	bool TriangleBoxOverlap(const Vector& centre, const Vector& halfExtents, Vector4* vertices);
	// 0x107DA730: the plane through point with the given normal crosses the origin-centred box (not reconstructed)
	bool PlaneCrossesBox(const Vector& normal, const Vector& point, const Vector& halfExtents);
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

	// FUNCTION: ENGINE 0x107D9CB0
	// EQUIVALENT: the same 15 tests with the same sums in the same order (16.3 %, 1147 bytes against 1111); the x87
	// stack allocation differs: the original keeps all eight registers full and spills b.x where ours spills b.y, and
	// it reuses the dead pointer parameters' slots for t.y, t.z, a.y, a.z. Returns bool (al), so do its callers
	bool TestBoxesSAT(const Vector& a, const Vector& t, const Matrix3& r, const Vector& b)
	{
		// |r|, then the face axes of A and of B and the nine edge-pair axes (Gottschalk's separating axis test)
		float f[3][3];
		f[0][0] = fabsf(r.m[0][0]);
		f[1][0] = fabsf(r.m[1][0]);
		f[2][0] = fabsf(r.m[2][0]);
		f[0][1] = fabsf(r.m[0][1]);
		f[1][1] = fabsf(r.m[1][1]);
		f[2][1] = fabsf(r.m[2][1]);
		f[0][2] = fabsf(r.m[0][2]);
		f[1][2] = fabsf(r.m[1][2]);
		f[2][2] = fabsf(r.m[2][2]);
		if (fabsf(t.x) > f[0][0] * b.x + f[1][0] * b.y + f[2][0] * b.z + a.x)
		{
			return false;
		}
		if (fabsf(t.y) > f[0][1] * b.x + f[1][1] * b.y + f[2][1] * b.z + a.y)
		{
			return false;
		}
		if (fabsf(t.z) > f[0][2] * b.x + f[1][2] * b.y + f[2][2] * b.z + a.z)
		{
			return false;
		}
		if (fabsf(t.z * r.m[0][2] + t.y * r.m[0][1] + t.x * r.m[0][0]) > f[0][2] * a.z + f[0][1] * a.y + f[0][0] * a.x + b.x)
		{
			return false;
		}
		if (fabsf(t.z * r.m[1][2] + t.y * r.m[1][1] + t.x * r.m[1][0]) > f[1][2] * a.z + f[1][1] * a.y + f[1][0] * a.x + b.y)
		{
			return false;
		}
		if (fabsf(t.z * r.m[2][2] + t.y * r.m[2][1] + t.x * r.m[2][0]) > f[2][2] * a.z + f[2][1] * a.y + f[2][0] * a.x + b.z)
		{
			return false;
		}
		if (fabsf(t.z * r.m[0][1] - t.y * r.m[0][2]) > (f[0][1] * a.z + f[0][2] * a.y) + (f[2][0] * b.y + f[1][0] * b.z))
		{
			return false;
		}
		if (fabsf(t.z * r.m[1][1] - t.y * r.m[1][2]) > (f[1][1] * a.z + f[1][2] * a.y) + (f[2][0] * b.x + f[0][0] * b.z))
		{
			return false;
		}
		if (fabsf(t.z * r.m[2][1] - t.y * r.m[2][2]) > (f[2][1] * a.z + f[2][2] * a.y) + (f[1][0] * b.x + f[0][0] * b.y))
		{
			return false;
		}
		if (fabsf(t.x * r.m[0][2] - t.z * r.m[0][0]) > (f[0][0] * a.z + f[0][2] * a.x) + (f[2][1] * b.y + f[1][1] * b.z))
		{
			return false;
		}
		if (fabsf(t.x * r.m[1][2] - t.z * r.m[1][0]) > (f[1][0] * a.z + f[1][2] * a.x) + (f[2][1] * b.x + f[0][1] * b.z))
		{
			return false;
		}
		if (fabsf(t.x * r.m[2][2] - t.z * r.m[2][0]) > (f[2][0] * a.z + f[2][2] * a.x) + (f[1][1] * b.x + f[0][1] * b.y))
		{
			return false;
		}
		if (fabsf(t.y * r.m[0][0] - t.x * r.m[0][1]) > (f[0][0] * a.y + f[0][1] * a.x) + (f[2][2] * b.y + f[1][2] * b.z))
		{
			return false;
		}
		if (fabsf(t.y * r.m[1][0] - t.x * r.m[1][1]) > (f[1][0] * a.y + f[1][1] * a.x) + (f[2][2] * b.x + f[0][2] * b.z))
		{
			return false;
		}
		if (fabsf(t.y * r.m[2][0] - t.x * r.m[2][1]) > (f[2][0] * a.y + f[2][1] * a.x) + (f[1][2] * b.x + f[0][2] * b.y))
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x107DA110
	// EQUIVALENT: same operations in the same order; the x terms of r[0][1] and r[1][2] multiply a's axis by b's
	// where we get b's by a's (commutative). The reference locals for the two boxes are what make the other products
	// load b's axis first, as the original does (98.6 %)
	bool Intersects(const OBB& a, const OBB& b)
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
	bool Intersects(const OBB& obb, const AABB& box)
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

	// Akenine-Moller's triangle / box separating axis tests: the nine edge cross axes (AXISTEST), the box faces
	// (FINDMINMAX through Min / Max) and the triangle's plane
#define AXISTEST_X01(a, b, fa, fb) \
	p0 = a * v0.y - b * v0.z; \
	p2 = a * v2.y - b * v2.z; \
	if (p0 < p2) { minimum = p0; maximum = p2; } else { minimum = p2; maximum = p0; } \
	rad = fa * halfExtents.y + fb * halfExtents.z; \
	if (minimum > rad || maximum < -rad) return false;
#define AXISTEST_X2(a, b, fa, fb) \
	p0 = a * v0.y - b * v0.z; \
	p1 = a * v1.y - b * v1.z; \
	if (p0 < p1) { minimum = p0; maximum = p1; } else { minimum = p1; maximum = p0; } \
	rad = fa * halfExtents.y + fb * halfExtents.z; \
	if (minimum > rad || maximum < -rad) return false;
#define AXISTEST_Y02(a, b, fa, fb) \
	p0 = -a * v0.x + b * v0.z; \
	p2 = -a * v2.x + b * v2.z; \
	if (p0 < p2) { minimum = p0; maximum = p2; } else { minimum = p2; maximum = p0; } \
	rad = fa * halfExtents.x + fb * halfExtents.z; \
	if (minimum > rad || maximum < -rad) return false;
#define AXISTEST_Y1(a, b, fa, fb) \
	p0 = -a * v0.x + b * v0.z; \
	p1 = -a * v1.x + b * v1.z; \
	if (p0 < p1) { minimum = p0; maximum = p1; } else { minimum = p1; maximum = p0; } \
	rad = fa * halfExtents.x + fb * halfExtents.z; \
	if (minimum > rad || maximum < -rad) return false;
#define AXISTEST_Z12(a, b, fa, fb) \
	p1 = a * v1.x - b * v1.y; \
	p2 = a * v2.x - b * v2.y; \
	if (p2 < p1) { minimum = p2; maximum = p1; } else { minimum = p1; maximum = p2; } \
	rad = fa * halfExtents.x + fb * halfExtents.y; \
	if (minimum > rad || maximum < -rad) return false;
#define AXISTEST_Z0(a, b, fa, fb) \
	p0 = a * v0.x - b * v0.y; \
	p1 = a * v1.x - b * v1.y; \
	if (p0 < p1) { minimum = p0; maximum = p1; } else { minimum = p1; maximum = p0; } \
	rad = fa * halfExtents.x + fb * halfExtents.y; \
	if (minimum > rad || maximum < -rad) return false;

	// FUNCTION: ENGINE 0x107DB250
	// EQUIVALENT: the same tests in the same order (14.9 %, 2008 bytes against 1981); registers and spills differ.
	// Min / Max stay calls here as in the original (the function exceeds the inlining budget); the original calls
	// the kept copies at 0x10071300 / 0x1006FB70, ours its own, and returns bool like its callers
	bool TriangleBoxOverlap(const Vector& centre, const Vector& halfExtents, Vector4* vertices)
	{
		float minimum;
		float maximum;
		float p0;
		float p1;
		float p2;
		float rad;
		float fex;
		float fey;
		float fez;
		Vector v0;
		v0.Set(vertices[0].x - centre.x, vertices[0].y - centre.y, vertices[0].z - centre.z);
		Vector v1;
		v1.Set(vertices[1].x - centre.x, vertices[1].y - centre.y, vertices[1].z - centre.z);
		Vector v2;
		v2.Set(vertices[2].x - centre.x, vertices[2].y - centre.y, vertices[2].z - centre.z);
		Vector e0;
		e0.Sub(v1, v0);
		Vector e1;
		e1.Sub(v2, v1);
		Vector e2;
		e2.Sub(v0, v2);
		fex = fabsf(e0.x);
		fey = fabsf(e0.y);
		fez = fabsf(e0.z);
		AXISTEST_X01(e0.z, e0.y, fez, fey);
		AXISTEST_Y02(e0.z, e0.x, fez, fex);
		AXISTEST_Z12(e0.y, e0.x, fey, fex);
		fex = fabsf(e1.x);
		fey = fabsf(e1.y);
		fez = fabsf(e1.z);
		AXISTEST_X01(e1.z, e1.y, fez, fey);
		AXISTEST_Y02(e1.z, e1.x, fez, fex);
		AXISTEST_Z0(e1.y, e1.x, fey, fex);
		fex = fabsf(e2.x);
		fey = fabsf(e2.y);
		fez = fabsf(e2.z);
		AXISTEST_X2(e2.z, e2.y, fez, fey);
		AXISTEST_Y1(e2.z, e2.x, fez, fex);
		AXISTEST_Z12(e2.y, e2.x, fey, fex);
		if (Min(Min(v0.x, v1.x), v2.x) > halfExtents.x || Max(Max(v0.x, v1.x), v2.x) < -halfExtents.x)
		{
			return false;
		}
		if (Min(Min(v0.y, v1.y), v2.y) > halfExtents.y || Max(Max(v0.y, v1.y), v2.y) < -halfExtents.y)
		{
			return false;
		}
		if (Min(Min(v0.z, v1.z), v2.z) > halfExtents.z || Max(Max(v0.z, v1.z), v2.z) < -halfExtents.z)
		{
			return false;
		}
		Vector normal;
		normal.Cross(e0, e1);
		if (!PlaneCrossesBox(normal, v0, halfExtents))
		{
			return false;
		}
		return true;
	}

#undef AXISTEST_X01
#undef AXISTEST_X2
#undef AXISTEST_Y02
#undef AXISTEST_Y1
#undef AXISTEST_Z12
#undef AXISTEST_Z0

	// FUNCTION: ENGINE 0x107DBB10
	bool Intersects(const Triangle& triangle, const OBB& box)
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
