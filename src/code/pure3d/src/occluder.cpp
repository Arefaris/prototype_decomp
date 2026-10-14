// pure3d::Occluder (unit around 0x1077F150 - 0x10780F00; file name guessed from the class). Names are guesses.
#include "code/math/obb.h"
#include "code/pure3d/occluder.h"

namespace pure3d
{
	// The box edges: the two faces they join and their corners
	struct OccluderEdge
	{
		int faceA;
		int faceB;
		int corner0;
		int corner1;
	};

	static const OccluderEdge OCCLUDER_EDGES[12] =
	{
		{ 1, 2, 3, 7 }, { 1, 3, 2, 3 }, { 1, 5, 2, 6 }, { 1, 0, 6, 7 }, { 0, 2, 5, 7 }, { 2, 3, 1, 3 },
		{ 3, 5, 0, 2 }, { 5, 0, 4, 6 }, { 4, 2, 1, 5 }, { 4, 3, 0, 1 }, { 4, 5, 0, 4 }, { 4, 0, 4, 5 }
	};

	// A corner on each face
	static const int OCCLUDER_FACE_CORNERS[6] = { 7, 7, 7, 0, 0, 0 };

	// a . b summed from z down
	static inline float DotZYX(const math::Vector& a, const math::Vector& b)
	{
		return a.z * b.z + a.y * b.y + a.x * b.x;
	}

	// FUNCTION: ENGINE 0x1077FFD0
	// EQUIVALENT: same operations in the same order; the engine schedules the face normals, the side tests and the
	// debug copies differently and keeps other values in registers
	void Occluder::GetShadowPlanes(ShadowPlaneList* planes, const math::Vector& light)
	{
		planes->Clear();
		math::Vector corners[8];
		for (unsigned int i = 0; i < 8; i++)
		{
			box.GetCorner(corners[i], (unsigned char)i);
		}
		math::Vector normals[6];
		normals[0].Sub(corners[4], corners[0]);
		normals[1].Sub(corners[6], corners[4]);
		normals[2].Sub(corners[7], corners[6]);
		normals[3].Set(-normals[0].x, -normals[0].y, -normals[0].z);
		normals[4].Set(-normals[1].x, -normals[1].y, -normals[1].z);
		normals[5].Set(-normals[2].x, -normals[2].y, -normals[2].z);
		gOccluderCorners[0] = corners[7];
		gOccluderCorners[1] = corners[0];
		gOccluderNormals[0] = normals[0];
		gOccluderNormals[1] = normals[5];
		// Which faces see the light (the first three pass through corner 7, the others through corner 0)
		unsigned short facing[6];
		for (int face = 0; face < 6; face++)
		{
			math::Vector d;
			d.Sub(light, corners[OCCLUDER_FACE_CORNERS[face]]);
			facing[face] = DotZYX(d, normals[face]) > 0.0f ? 0xFFFF : 0;
		}
		// The silhouette edges
		for (int edge = 0; edge < 12; edge++)
		{
			const OccluderEdge& e = OCCLUDER_EDGES[edge];
			if ((unsigned short)(facing[e.faceB] ^ facing[e.faceA]) == 0xFFFF)
			{
				math::Vector a;
				a.Sub(corners[e.corner0], light);
				math::Vector b;
				b.Sub(corners[e.corner1], light);
				math::Vector n;
				n.Cross(a, b);
				n.Normalize();
				float d = -DotZYX(light, n);
				if (!(-d >= DotZYX(box.centre, n)))
				{
					n.x *= -1.0f;
					n.y *= -1.0f;
					n.z *= -1.0f;
				}
				planes->PushBack(ShadowPlane(n.x, n.y, n.z, -DotZYX(light, n)));
			}
		}
		// The faces that see the light
		int seen = 0;
		for (int face = 0; face < 6; face++)
		{
			if (facing[face] == 0xFFFF)
			{
				math::Vector n(normals[face].x, normals[face].y, normals[face].z);
				n.NormalizeFast();
				const math::Vector& p = corners[OCCLUDER_FACE_CORNERS[face]];
				planes->PushBack(ShadowPlane(n.x, n.y, n.z, -DotZYX(p, n)));
				gOccluderFacePoints[seen] = math::Vector(p);
				gOccluderFaceNormals[seen].Set(n.x, n.y, n.z);
				seen++;
			}
		}
	}
}
