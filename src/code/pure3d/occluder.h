// pure3d::Occluder (RTTI name; bases pure3d::Entity, RefCounted, core::IRefCount): an oriented box that hides what
// lies behind it from a light; GetShadowPlanes builds the planes of its shadow volume. Unit around 0x1077F150 -
// 0x10780F00 (file name guessed from the class). Layout partial; names are guesses.
#ifndef PURE3D_OCCLUDER_H
#define PURE3D_OCCLUDER_H

#include "code/content/chunkhandler.h"
#include "code/math/obb.h"
#include "code/math/vector.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	// A plane of a shadow volume: normal and distance (inside when normal . p + d <= 0)
	struct ShadowPlane
	{
		ShadowPlane()
		{
		}
		ShadowPlane(float newX, float newY, float newZ, float newD)
		{
			x = newX;
			y = newY;
			z = newZ;
			d = newD;
		}

		float x;
		float y;
		float z;
		float d;
	};

	// Up to nine shadow planes
	struct ShadowPlaneList
	{
		void Clear()
		{
			if (end != planes)
			{
				end = planes;
			}
		}
		void PushBack(const ShadowPlane& plane)
		{
			if (end - planes != 9)
			{
				ShadowPlane* item = end++;
				if (item != 0)
				{
					*item = plane;
				}
			}
		}

		ShadowPlane planes[9];
		ShadowPlane* end;
	};

	class Occluder : public Entity
	{
	public:
		// 0x1077FB20: a unit box at the origin
		Occluder();
		// 0x1077FC00: the box (passed by value)
		explicit Occluder(math::OBB newBox);
		// 0x1077FF10
		Occluder(const Occluder& other);
		// Slot 2 (the body is 0x1077FB90, the deleting destructor 0x1077FBE0)
		virtual ~Occluder();
		// 0x1077FF70: a copy made with the pass's allocator
		Occluder* Clone();
		// 0x1077FFD0: the planes of the volume the box shadows from light: one through the light and each edge
		// between a face that sees the light and one that does not, and the faces that see it
		void GetShadowPlanes(ShadowPlaneList* planes, const math::Vector& light);

		math::OBB box;
		unsigned char unknown4C[4];
	};

	// RTTI: pure3d::OccluderLoader (chunk 0x124000, vftable 0x10E603A8): reads an occluder
	class OccluderLoader : public content::SimpleChunkHandler
	{
	public:
		// Declared first and not defined here, so that the vftable stays with the engine's own copy of the unit
		virtual ~OccluderLoader();

		// 0x1077FC70: the occluder a chunk describes (chunk 0x10029 holds the box)
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);
	};

	// What the last GetShadowPlanes saw, for the debug drawing (0x11282C08 - 0x11282C80): the far and near corners,
	// the first and last face normals, then the faces that saw the light
	extern math::Vector gOccluderCorners[2];
	extern math::Vector gOccluderNormals[2];
	extern math::Vector gOccluderFacePoints[3];
	extern math::Vector gOccluderFaceNormals[3];
}

#endif
