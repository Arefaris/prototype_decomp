// pure3d::Occluder (unit around 0x1077F150 - 0x10780F00; file name guessed from the class). Names are guesses.
#include "code/engine/driving/carattributes.h"
#include <string.h>

#include "code/math/obb.h"
#include "code/pure3d/occluder.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1077FC70
	// EQUIVALENT: the same reads, products and stores; the engine keeps the three cross products in other registers and copies the box with float moves (about 55 %)
	void OccluderLoader::LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
		content::LoadInventory* inventory)
	{
		unsigned char lengthByte;
		char occluderName[0x100];
		reader->Read(&lengthByte, 1, 1, 1);
		unsigned int length = lengthByte;
		reader->Read(occluderName, length, 1, 1);
		occluderName[length] = 0;
		{
			unsigned int version[2];
			reader->Read(version, 1, 4, 1);
		}
		Occluder* occluder = new Occluder();
		occluder->AddRef();
		if (reader->HasChunk())
		{
			do
			{
				if (reader->BeginChunk() == 0x10029)
				{
					unsigned int version[2];
					reader->Read(version, 1, 4, 1);
					math::OBB read;
					reader->Read(&read.centre, 3, 4, 1);
					reader->Read(&read.axis[0], 3, 4, 1);
					reader->Read(&read.axis[1], 3, 4, 1);
					math::Vector& a = read.axis[0];
					math::Vector& b = read.axis[1];
					read.axis[2].y = b.x * a.z - a.x * b.z;
					read.axis[2].z = b.y * a.x - a.y * b.x;
					read.axis[2].x = a.y * b.z - b.y * a.z;
					reader->Read(&read.extents, 3, 4, 1);
					occluder->box.centre.x = read.centre.x;
					occluder->box.centre.y = read.centre.y;
					occluder->box.centre.z = read.centre.z;
					occluder->box.axis[0].x = read.axis[0].x;
					occluder->box.axis[0].y = read.axis[0].y;
					occluder->box.axis[0].z = read.axis[0].z;
					occluder->box.axis[1].x = read.axis[1].x;
					occluder->box.axis[1].y = read.axis[1].y;
					occluder->box.axis[1].z = read.axis[1].z;
					occluder->box.axis[2].x = read.axis[2].x;
					occluder->box.axis[2].y = read.axis[2].y;
					occluder->box.axis[2].z = read.axis[2].z;
					occluder->box.extents.x = read.extents.x;
					occluder->box.extents.y = read.extents.y;
					occluder->box.extents.z = read.extents.z;
				}
				reader->EndChunk();
			}
			while (reader->HasChunk());
		}
		occluder->SetNameText(occluderName);
		*object = occluder;
		*name = content::ObjectName(occluderName, 1);
		if (strncmp("art/locations/manhattan/midgeo.p3d", (const char*)reader, 0xFF) == 0)
		{
			occluder->Release();
			*object = 0;
		}
	}

	// FUNCTION: ENGINE 0x1077FB20
	// EQUIVALENT: the engine loads the constant before it stores the vftable pointer and keeps it in one register for the later stores (79.8 %)
	Occluder::Occluder()
	{
		box.centre.x = 0.0f;
		box.centre.y = 0.0f;
		box.centre.z = 0.0f;
		float one = engine::driving::gOne;
		box.extents.x = one;
		box.extents.y = one;
		box.extents.z = one;
		box.axis[0].x = one;
		box.axis[0].y = 0.0f;
		box.axis[0].z = 0.0f;
		box.axis[1].x = 0.0f;
		box.axis[1].y = one;
		box.axis[1].z = 0.0f;
		box.axis[2].x = 0.0f;
		box.axis[2].y = 0.0f;
		box.axis[2].z = one;
	}

	// FUNCTION: ENGINE 0x1077FB90
	Occluder::~Occluder()
	{
	}

	// FUNCTION: ENGINE 0x1077FC00
	Occluder::Occluder(math::OBB newBox) : box(newBox)
	{
	}

	// FUNCTION: ENGINE 0x1077FF10
	Occluder::Occluder(const Occluder& other) : box(other.box)
	{
	}

	// FUNCTION: ENGINE 0x1077FF70
	Occluder* Occluder::Clone()
	{
		return new Occluder(*this);
	}

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
