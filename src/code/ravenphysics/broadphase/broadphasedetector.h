// ravenphysics::BroadPhaseDetector and its single-axis sweep-and-prune implementation. Names and layout are guesses.
#ifndef RAVENPHYSICS_BROADPHASE_BROADPHASEDETECTOR_H
#define RAVENPHYSICS_BROADPHASE_BROADPHASEDETECTOR_H

#include "code/core/heap.h"
#include "code/math/vector.h"
#include "code/ravenphysics/intersectionproperties.h"

namespace ravenphysics
{
	class PhysicsObject;
	class CollisionObject;

	// The grid the broad phase quantises positions into: 16-bit coordinates per axis
	class BroadPhaseGrid
	{
	public:
		// The grid cell of a point, each coordinate clamped to 0 .. 65535 (0x10662F50)
		void Quantize(unsigned short* cell, const math::Vector& point);

		unsigned char unknown0[0xa0];
		math::Vector origin;
		math::Vector unknownAC;
		math::Vector scale;
	};

	// A box in the detector's bounds array (24 bytes)
	struct BroadPhaseBox
	{
		// Copies another box component by component, the maximum first
		void Set(const BroadPhaseBox& other)
		{
			boundsMax.x = other.boundsMax.x;
			boundsMax.y = other.boundsMax.y;
			boundsMax.z = other.boundsMax.z;
			boundsMin.x = other.boundsMin.x;
			boundsMin.y = other.boundsMin.y;
			boundsMin.z = other.boundsMin.z;
		}

		math::Vector boundsMin;
		math::Vector boundsMax;
	};

	// The three words of an object's filter the detector keeps next to its box (12 bytes): the two words of the
	// properties and one more
	struct BroadPhaseMasks : IntersectionProperties
	{
		BroadPhaseMasks()
		{
			unknown8 = 0;
		}

		// Takes the properties and keeps the third word
		void SetProperties(const IntersectionProperties& other)
		{
			*(IntersectionProperties*)this = other;
		}

		int unknown8;
	};

	// The pointers to the detector's arrays and their element accessors (0x1065FCF0 / 0x1065FD00 / 0x1065FD10; the
	// classes are guesses, the engine's compiler kept an out-of-line copy of each)
	struct BoxArray
	{
		BroadPhaseBox* At(int index);

		BroadPhaseBox* items;
	};

	struct VectorArray
	{
		math::Vector* At(int index);

		math::Vector* items;
	};

	struct MaskArray
	{
		BroadPhaseMasks* At(int index);

		BroadPhaseMasks* items;
	};

	// What one of the detector's tables is walked from: the head the walk starts at (32 bytes, copied whole by the
	// context's getters) and the run of records it walks (name guesses)
	struct DetectorHead
	{
		unsigned char unknown0[0x20];
	};

	struct DetectorTable
	{
		DetectorHead head; // 0x00
		void** records;    // 0x20
		int count;         // 0x24
	};

	// What the broad phase keeps per detector (RTTI class BroadPhaseDetector, vftable at 0)
	class BroadPhaseDetector
	{
	public:
		// The head of the detector: the objects it holds, the movable ones from the start, the static ones from
		// staticCount on, the boxes the sweep works on (the member names are guesses; the layout is what the
		// context unit's code reads)
		struct ObjectTable
		{
			// The counts and the records the detector keeps (0x10656170 - 0x106561D0)
			unsigned short GetMovableCount() const;
			unsigned short GetStaticCount() const;
			unsigned short GetUnknown8() const;
			unsigned int GetUnknown6() const;
			unsigned int GetUnknown4() const;
			unsigned int GetUnknownA() const;
			void*** GetObjects();

			unsigned short movableCount; // 0x00
			unsigned short staticCount;  // 0x02
			unsigned short unknown4;     // 0x04 (the four counters the context's statistics read)
			unsigned short unknown6;     // 0x06
			unsigned short unknown8;     // 0x08
			unsigned short unknownA;     // 0x0A
			void** objects;              // 0x0C
			unsigned char unknown10[0x18 - 0x10];
			BroadPhaseBox* boxes;        // 0x18
		};

		ObjectTable& Table()
		{
			return *(ObjectTable*)this;
		}

		// Takes every object out of the table and of the tables the detection walks (0x106848C0; name guess)
		void RemoveAll();
		// Takes an object into the table and stamps it with its box (0x10684740; name guess)
		void Add(PhysicsObject* object);
		// Takes it out again (0x10684840; name guess)
		void Remove(PhysicsObject* object);
		// The same out of the tables the detection walks, leaving the object's slots free (0x106846F0; name guess)
		void RemoveSecond(PhysicsObject* object);
		// Gives the tables back (0x106840A0; name guess)
		void Unknown106840A0();
		// Frees the three blocks the detector keeps
		~BroadPhaseDetector()
		{
			if (masks != 0)
			{
				core::FreeAligned(masks);
			}
			if (boxes != 0)
			{
				core::FreeAligned(boxes);
			}
			if (Table().objects != 0)
			{
				core::FreeAligned(Table().objects);
			}
		}
		// Overwrites the box / the filter words of one object (0x1065FD80 / 0x1065FDC0; name guesses)
		void SetBox(unsigned short index, const BroadPhaseBox* box);
		void SetMasks(unsigned short index, const BroadPhaseMasks* newMasks);
		// Tells the detector that a collision object of one of its bodies changed (0x10683510, another unit; name
		// guess)
		void UpdateCollisionObject(CollisionObject* object);

		unsigned char unknown0[0x18];
		BroadPhaseBox* boxes;            // 0x18
		unsigned char unknown1C[0x24 - 0x1C];
		BroadPhaseMasks* masks;          // 0x24 (one per object)
		unsigned char unknown28[0x34 - 0x28];
		DetectorHead unknown34;          // 0x34 (the head of the second table; name guess)
		unsigned char unknown54[0x6C - 0x54];
		// The address of the second table's head, of the area behind it, of the area at 0x10C and of the first
		// table's head (0x10656150, 0x10656160, 0x10656130, 0x10656140)
		DetectorHead* GetUnknown34();
		unsigned char* GetUnknown54();
		unsigned char* GetUnknown10C();
		DetectorHead* GetUnknown150();
		void** unknown6C;                // 0x6C (the same table's records and count)
		int unknown70;                   // 0x70
		unsigned char unknown74[0x10C - 0x74];
		unsigned char unknown10C[0x124 - 0x10C];
		void** unknown124;               // 0x124 (the first table's records and count)
		int unknown128;                  // 0x128
		unsigned char unknown12C[0x150 - 0x12C];
		DetectorHead unknown150;         // 0x150 (the head of the first table; name guess)
	};

	// One end of a box on the sweep axis (12 bytes): kind 2 or 1 opens the range, 0 closes it; overlapCount is the
	// number of open ranges after this end
	struct Endpoint
	{
		float position;
		unsigned short box;
		unsigned short kind;
		short overlapCount;
	};

	// Writes the begin and end endpoints (x of boundsMin / boundsMax) of boxes 0 .. total - 1, skipping empty and
	// huge boxes; the boxes from first on get kind 1 when their bit in flags is set, else 2. Returns the number of
	// endpoints written for them (0x106D9260; each array comes with its length, of which only the first is used)
	int BuildEndpoints(const BroadPhaseBox* boxes, unsigned int boxCount, const unsigned char* flags,
		unsigned int flagCount, Endpoint* second, unsigned int secondCount, Endpoint* first,
		unsigned int firstCount, unsigned int total, unsigned int firstBoxes);

	// A value ordered by an unsigned key (the sweep's sorted pair lists)
	struct SortEntry
	{
		unsigned int value;
		unsigned int key;

		bool operator<(const SortEntry& other) const
		{
			return key < other.key;
		}
	};
}

#endif
