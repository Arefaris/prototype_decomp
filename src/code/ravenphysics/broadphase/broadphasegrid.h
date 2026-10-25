// The grid a mesh volume keeps its triangles in (class and member names are guesses; RTTI does not name it). It sits
// at +0x30 of a CollisionVolume6 and is 0xF0 bytes long; Quantize (0x10662F50) turns a point into the 16-bit cell it
// lies in.
#ifndef RAVENPHYSICS_BROADPHASE_BROADPHASEGRID_H
#define RAVENPHYSICS_BROADPHASE_BROADPHASEGRID_H

#include "code/math/aabb.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace ravenphysics
{
	struct CollisionVolume6;
	struct CollisionFilter;

	// A triangle of the grid: the numbers of its three vertices and a word whose bits 9 - 14 pick the material
	struct GridFace
	{
		// The index into the grid's material table (0x10662E50)
		unsigned int GetMaterial() const;
		// One of the three vertices (0x10662960)
		unsigned short GetVertex(int index) const;
		// The three flag bits (0x10667370 / 0x10667380 / 0x10667390)
		unsigned int GetFlag0() const;
		unsigned int GetFlag1() const;
		unsigned int GetFlag2() const;

		unsigned short vertex[3];
		union
		{
			unsigned short flags;
			struct
			{
				unsigned char flag0 : 1;
				unsigned char flag1 : 1;
				unsigned char flag2 : 1;
			};
		};
	};

	// What the copies of a mesh volume share (0x10 bytes): a count of the owners and the blocks they free together
	struct MeshSlot
	{
		// Starts with no blocks (0x10665BE0)
		MeshSlot();
		// Frees the blocks (0x10665BF0)
		~MeshSlot();
		// One more owner (0x10665C20)
		void AddRef();
		// Sets the size of a record (0x10662E40)
		void SetRecordSize(unsigned int size);
		// One owner less; the last one frees the slot (0x10666290)
		void Release();

		unsigned int refCount;     // 0x00
		unsigned short* unknown4;  // 0x04 (an array, three words per triangle)
		unsigned char* unknown8;   // 0x08 (an array of records of unknownC bytes)
		unsigned int unknownC;     // 0x0C
	};

	// A 14-byte record of the grid (meaning unknown)
	struct MeshRecord
	{
		// The three numbers after the first (0x10667430) and the three after those (0x10667440)
		unsigned short GetFace(int index) const;
		unsigned short GetNeighbour(int index) const;

		unsigned short unknown[7];
	};

	// The filter words of one material of the grid
	struct MeshMaterial
	{
		unsigned int filter;
		unsigned int filter2;
	};

	class BroadPhaseGrid
	{
	public:
		// An empty grid with a fresh serial number (0x106662C0)
		BroadPhaseGrid();
		// A copy that shares the slot (0x106663D0)
		BroadPhaseGrid(const BroadPhaseGrid& other);
		// Copies the plain members of another grid (0x10665C50)
		BroadPhaseGrid& Assign(const BroadPhaseGrid& other);
		// Lets go of what the grid holds (0x10666430)
		void Destroy();

		// The grid cell of a point, each coordinate clamped to 0 .. 65535 (0x10662F50)
		void Quantize(unsigned short* cell, const math::Vector& point);
		// The point in grid units: its offset from the grid's origin times the scale (0x10662FB0)
		void ToGridUnits(math::Vector* out, const math::Vector* point);
		// The three corners of a triangle (0x10662E60) and its record with them (0x10662ED0)
		void GetTriangle(unsigned short face, math::Vector* corners);
		void GetTriangleAndFace(unsigned short face, GridFace* faceOut, math::Vector* corners);
		// The material table entry of a triangle (0x106636F0)
		MeshMaterial* GetMaterialOf(unsigned short face);
		// The record of the shared slot for a triangle, none when the slot has no records (0x10667630)
		unsigned char* GetSlotData(unsigned short index);

		CollisionVolume6* volume;       // 0x00
		math::Matrix matrix;            // 0x04
		math::Matrix inverse;           // 0x44
		unsigned int serial;            // 0x84
		bool transformed;               // 0x88
		unsigned int unknown8C;         // 0x8C
		unsigned short unknown90;       // 0x90
		unsigned short unknown92;       // 0x92
		void* tree;                     // 0x94
		GridFace* faces;                // 0x98
		math::Vector* vertices;         // 0x9C
		math::AABB bounds;              // 0xA0
		math::Vector scale;             // 0xB8
		float unknownC4;                // 0xC4
		bool unknownC8;                 // 0xC8
		MeshMaterial* materialsBegin;   // 0xCC
		MeshMaterial* materialsEnd;     // 0xD0
		unsigned char unknownD4[0xE0 - 0xD4];
		MeshSlot* slot;                 // 0xE0
		unsigned short* unknownE4;      // 0xE4
		int unknownE8;                  // 0xE8
		MeshRecord* unknownEC;          // 0xEC
	};
}

#endif
