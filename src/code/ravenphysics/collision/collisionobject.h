// ravenphysics collision objects and volumes (assert path code/ravenphysics/collision/src/collisionobject.cpp). Only the
// members the reconstructed code touches are named; the layout is partial and every name is a guess.
#ifndef RAVENPHYSICS_COLLISION_COLLISIONOBJECT_H
#define RAVENPHYSICS_COLLISION_COLLISIONOBJECT_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/math/capsule.h"
#include "code/math/matrix.h"
#include "code/math/sphere.h"
#include "code/math/vector.h"
#include "code/ravenphysics/context.h"

namespace ravenphysics
{
	class CollisionObject;
	class CollisionShape;
	class ConvexMesh;
	class PhysicsObject;

	// The query filters a volume asks for, accumulated by the object it belongs to (meanings unknown)
	struct CollisionFilter
	{
		unsigned int unknown0;
		unsigned int unknown4;
	};

	// The head shared by all collision volume types; type indexes the narrow phase's dispatch tables
	struct CollisionVolume
	{
		unsigned char type;
		unsigned char swapped;
		unsigned char material;
		unsigned char unknown3;
		math::Vector boundsMin;
		math::Vector boundsMax;
		CollisionFilter filter;     // 0x1C
		unsigned char unknown24[0x60 - 0x24];

		// The end every volume subclass's destructor reaches: marks the volume destroyed (0x10663EB0, another
		// unit)
		~CollisionVolume()
		{
			MarkDestroyed();
		}

		// Recomputes the volume's world bounds from the object's transform; a switch over the type byte that runs
		// the volume's own per-type update (0x10665690, another unit)
		void UpdateBounds(CollisionObject* object);
		// Raises the volume against a query, answering whether it hit and writing the point and the distance
		// (0x10663FE0, another unit)
		bool CastVolume(const void* query, math::Vector* point, float* distance);
		// A copy of the volume of the same type (0x10665990, another unit)
		CollisionVolume* Clone();

		// The per-type setters and bounds updates the object's Set*Volume methods call (0x10664BA0 / 0x10664C10,
		// 0x10665060 / 0x10665120, 0x10665790 / 0x106645D0, 0x10665510 / 0x106643E0, 0x10681DE0 / 0x10680AB0;
		// another unit, names are guesses)
		void SetCapsule(const math::Capsule& capsule);
		void UpdateCapsuleBounds(CollisionObject* object);
		void SetSphere(const math::Sphere& sphere);
		void UpdateSphereBounds(CollisionObject* object);
		void SetVolume2(const void* description);
		void UpdateBounds2(CollisionObject* object);
		void SetVolume4(const void* description);
		void UpdateBounds4(CollisionObject* object);
		void SetVolume6(const void* description);
		void UpdateBounds6(CollisionObject* object);
		// Hands the query setup to the volume (0x10665A90, another unit)
		void SetQuery(const void* query);
		// Writes the bounds and the type-specific part out (0x10664660, another unit)
		void Print();
		// Frees the volume's own array of faces and marks it destroyed (0x10681C40, another unit)
		void Destroy();
		// Gives up a type 6 volume's slot in the physics table and clears its mesh (0x10666640, another unit)
		void DestroyMesh();
		// The body of the destructor: writes the destroyed mark into the state byte (0x10663EB0, another unit)
		void MarkDestroyed();
		// Raises and lowers the state byte, the volume's destruction count (0x10663EC0 / 0x10663ED0, another unit)
		void Retain();
		void Release();
	};

	// A volume of type 3, and the face list a type 4 volume keeps at +0x60 (class and member names are guesses)
	class CollisionVolume3 : public CollisionVolume
	{
	public:
		// Gives every face of the volume a material (0x10654150, another unit)
		void SetMaterial(unsigned char material);
		// Frees the volume's own array of faces, then the base's mark (0x10681C40, another unit)
		~CollisionVolume3();
	};

	// A volume of type 4: the volume plus its face list (0x10654670 gives every face a material)
	struct CollisionVolume4 : CollisionVolume
	{
		CollisionVolume3 materials;    // 0x60
	};

	// One slot the geometry of a mesh volume refers to (its own unit names it)
	struct MeshSlot
	{
		unsigned int unknown0;
		unsigned int unknown4;
	};

	// A volume of type 6 (0x10666640; 0x130 bytes)
	struct CollisionVolume6 : CollisionVolume
	{
		unsigned char unknown60[0x110 - 0x60];
		MeshSlot* unknown110;      // 0x110
		unsigned char unknown114[0x130 - 0x114];
		~CollisionVolume6();
	};

	// The entry of the physics handle table that names one object (the table hands out the pair of a slot index and
	// the serial the slot carries; the names are guesses). An untouched handle names no slot.
	struct CollisionHandle
	{
		CollisionHandle()
		{
			value = 0xffffffff;
		}

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

	// One slot of the physics handle table (0x1127CAC0): the object and the serial it is registered under
	struct CollisionHandleEntry
	{
		void* object;
		unsigned int serial;
	};

	// The free slots of the handle table: a stack of 16-bit slot indexes over a block it does not grow itself
	// (name and members are guesses)
	struct CollisionSlotStack
	{
		unsigned short* begin;
		unsigned int size;
		unsigned int capacity;

		// Whether every slot is handed out (0x10653150)
		bool IsEmpty() const
		{
			return size == 0;
		}
		// Takes the top slot index off the stack (0x10653190)
		unsigned short Pop()
		{
			unsigned short index = begin[size - 1];
			size--;
			return index;
		}
		// Puts a slot index back on top (0x10653170)
		void Push(const unsigned short& index)
		{
			size++;
			unsigned short* slot = begin + size - 1;
			if (slot != 0)
			{
				*slot = index;
			}
		}
	};

	// The table the collision objects register themselves in (name guess; the class is created by 0x10653530 and
	// lives behind the pointer 0x1127CAC0)
	class CollisionObjectTable
	{
	public:
		// The free slots
		CollisionSlotStack free;
		// The slots
		CollisionHandleEntry* entries;    // 0x0C
		unsigned int entryCapacity;       // 0x10
		unsigned short slotCount;         // 0x14
		// One serial per slot, raised every time the slot is handed out
		unsigned short* serials;          // 0x18
		unsigned int serialCapacity;      // 0x1C

		// Takes a slot for the object and writes its handle (0x10653250)
		void Add(void* object, CollisionHandle* handle);
		// Gives the slot of the handle back when the serial still matches (0x106532B0)
		void Remove(CollisionHandle* handle);
	};

	// The transform and bounds of one collision object, the broad phase sees instead of the object itself
	// (class and member names are guesses; 0xE0 bytes, copied by 0x10669A70)
	class CollisionShape
	{
	public:
		unsigned char unknown0 : 1;
		unsigned char flag1 : 1;
		unsigned char flag2 : 1;
		unsigned char flag3 : 1;
		unsigned char flag4 : 1;
		unsigned char unknown5 : 3;
		unsigned char unknown1[7];
		CollisionObject* object;   // 0x08
		unsigned char unknownC[4];
		math::Vector unknown10;    // 0x10
		math::Vector unknown1C;    // 0x1C
		math::Vector unknown28;    // 0x28
		math::Vector unknown34;    // 0x34
		math::Vector unknown40;    // 0x40
		math::Vector unknown4C;    // 0x4C
		math::Vector unknown58;    // 0x58
		math::Vector unknown64;    // 0x64
		float boundsMinX;          // 0x70
		float boundsMinY;
		float boundsMinZ;
		float boundsMaxX;
		float boundsMaxY;
		float boundsMaxZ;
		float unknown88;           // 0x88
		float unknown8C;           // 0x8C
		math::Vector unknown90;    // 0x90
		math::Vector center;       // 0x9C
		// Recomputes the bounds and the centre from the object's transform (0x10669240, another unit)
		void Update(CollisionObject* object);
		// Recomputes the bounds from the transform the shape already has (0x10669C90, another unit)
		void Refresh();
		// Clears the two orientation vectors and the transform (0x10669C60, another unit)
		void Clear();
		// Sets the scale and remembers its inverse (0x106691B0, another unit)
		void SetScale(float scale);
		// Sets the inverse scale directly, or the scale when it is degenerate (0x10669200, another unit)
		void SetInverseScale(float inverse);
		// Copies six floats into the shape's vectors (0x106541C0, another unit)
		void SetVectors(const void* values);
		// Writes a position into the shape's offset vector (0x10669620, another unit)
		void SetPosition(math::Vector position);
		// Moves the shape to a point and marks it by the flag (0x10669E60, another unit)
		void MoveTo(math::Vector position, int flag);
		// Moves the shape from one point to another (0x10669F60, another unit)
		void MoveTo(math::Vector from, math::Vector to, int flag);
		// Sets the shape's width and marks it (0x1066A0B0, another unit)
		void SetSize(int a, int b, float size);
		// A copy of another shape, held by the object it is built for (0x10669A70, another unit)
		CollisionShape(const CollisionShape& other, CollisionObject* object);
		// Writes the transform, the matrices and the vectors out (0x10669730, another unit)
		void Print();
		// Empty (0x10669120, another unit)
		~CollisionShape();

		// The shape's own flags, in the bits of the byte at 0 (0x10654380, 0x106543A0, 0x10654410; the shape's
		// unit is elsewhere, these copies sit in this object file)
		void SetFlag3(bool value);
		bool IsFlag3();
		void SetFlag4(bool value);

		unsigned int unknownA8;    // 0xA8
		math::Vector unknownAC;    // 0xAC
		math::Vector unknownB8;    // 0xB8
		math::Vector unknownC4;    // 0xC4
		math::Vector unknownD0;    // 0xD0
		float radius;              // 0xDC
	};

	// One geometry element of a mesh (8 bytes; its own unit names it)
	struct MeshElement
	{
		unsigned int unknown0;
		unsigned int unknown4;
	};

	// The elements a mesh holds (begin / end / end of storage)
	struct MeshGeometry
	{
		MeshElement* begin;
		MeshElement* end;
		MeshElement* capacity;
	};

	// The mesh a mesh volume keeps its geometry in (0x38 bytes, a content::LoadObject of the RTTI; the class is only
	// declared here, its own unit builds it)
	class ConvexMesh : public content::LoadObject
	{
	public:
		// An empty mesh (0x10685E50, another unit)
		ConvexMesh();
		// Makes room for count geometry elements (0x106853F0, another unit)
		void Reserve(int count);
		// Appends one of the object's volumes (0x106855B0, another unit)
		void AddVolume(CollisionVolume* volume);

		unsigned char unknown8[0x28 - 8];
		MeshGeometry geometry;    // 0x28
		unsigned int unknown34;
	};

	// The physics object handle table (0x1127CAC0)
	extern CollisionObjectTable* gCollisionObjectTable;

	class CollisionObject
	{
	public:
		// Takes a slot in the physics handle table and clears every member but the transform (0x10655AE0)
		CollisionObject();
		// Gives the handle back, releases the mesh, destroys the volumes and deletes the shape (0x10655EA0)
		~CollisionObject();
		// Writes the transform, every volume and the shape out (0x10655A60)
		void Print();
		// Takes over the volume array, decides which volumes collide and initialises every volume (0x10655B60)
		void Initialize(CollisionVolume** newVolumes, unsigned int count);
		// A copy of the object with copies of its volumes and, unless unused, of its shape (0x10655BE0)
		CollisionObject* Clone(bool unused);
		// The radius of the box that holds every volume's bounds, or 0 when the volumes do not overlap
		// (0x10655DA0)
		float GetRadius() const;

		// Clears the changed flag and tells whether it was set
		bool TestAndClearChanged()
		{
			bool wasChanged = changed;
			changed = false;
			return wasChanged;
		}

		// Copies the transform into the object and refreshes the volumes and the shape (0x106544E0)
		void UpdateTransform(const math::Matrix& matrix);
		// The same and then the owner's bounds (0x10654580)
		void SetTransform(const math::Matrix& matrix);
		// Copies the transform and refreshes the volumes (0x10654C30)
		void SetMatrix(const math::Matrix& matrix);
		// Gives every volume (and the faces of a type 4 volume) a material (0x10654670)
		void SetMaterial(unsigned char material);
		// Hands the argument to every volume's query setup and refreshes their bounds (0x106546F0)
		void SetVolumeQuery(const void* query);
		// The shape the broad phase sees, released and replaced (0x10654790)
		CollisionShape* SetShape(CollisionShape* newShape);
		// The volume descriptions, one method per volume type (0x10654820 - 0x106549E0)
		void SetCapsuleVolume(int index, const math::Capsule& capsule);
		void SetSphereVolume(int index, const math::Sphere& sphere);
		void SetVolume2(int index, const void* description);
		void SetVolume4(int index, const void* description);
		void SetVolume6(int index, const void* description);
		// The nearest volume the query hits, with the point and the volume's index (0x10654AB0)
		void CastQuery(const void* query, math::Vector* point, float* distance, unsigned int* index);
		// Switches one volume's bit in the volume mask (0x10654BB0)
		void SetVolumeEnabled(unsigned int index, bool enabled);
		// Which volumes may collide (0x106544B0; meaning unknown)
		void SetUnknown70(int value);
		// Whether the object takes part in the simulation at all (0x106544C0)
		void SetActive(bool active);
		// The material of one of the object's volumes (0x106545E0)
		unsigned char GetVolumeMaterial(int index);
		// Marks one volume as the one whose type's swapped pair table is used (0x10654A50)
		void SetVolumeSwapped(int index, bool swapped);
		// Whether one of the volumes has this type (0x10654C70)
		bool HasVolumeType(unsigned short type);
		// The mesh the mesh volumes register in (0x10654CB0)
		void SetMesh(ConvexMesh* mesh);
		// The name of the object (0x10655D90)
		void SetName(core::Name<core::CaseSensitiveKey> newName);

		// The shape's vectors and floats (0x10654D30, 0x10654D80, 0x10655230, 0x10655280, 0x10655340,
		// 0x10655390, 0x10655460, 0x10655750, 0x10655510, 0x10655580)
		math::Vector* GetUnknown10();
		math::Vector* GetUnknown1C();
		math::Vector* GetUnknown40();
		math::Vector* GetUnknown4C();
		math::Vector* GetUnknown58();
		math::Vector* GetUnknown90();
		math::Vector* GetUnknown9C();
		math::Vector* GetUnknown34();
		float GetScale();
		float GetInverseScale();

		// The shape's own settings, one method per shape setter (0x10654CE0, 0x10654DD0, 0x10655190,
		// 0x106553E0, 0x106554B0, 0x10655520, 0x10655590, 0x10655600, 0x10655670)
		void Clear();
		void MoveTo(math::Vector position);
		void SetPosition(math::Vector position);
		void SetVectors(const void* values);
		void SetScale(float scale);
		void SetInverseScale(float inverse);
		void SetSize(math::Vector size);
		void SetSize(int a, int b, float size);

		// The shape's flags (0x106552D0, 0x10655330, 0x106555F0, 0x106556E0, 0x10655740, 0x10655960)
		void SetFlag3(bool value);
		bool IsFlag3();
		void SetFlag1(bool value);
		bool IsFlag2();
		bool IsFlag1();
		void SetFlag4(bool value);

		// Accumulates the volumes' query filters (0x106559C0)
		void UpdateProperties();

		math::Matrix transform;                     // 0x00
		core::Name<core::CaseSensitiveKey> name;    // 0x40
		CollisionHandle handle;                     // 0x48
		int unknown4C;                              // 0x4C
		CollisionVolume** volumes;                  // 0x50
		unsigned short volumeCount;                 // 0x54
		unsigned char changed : 1;                  // 0x56
		unsigned char unknown56 : 7;
		unsigned char unknown57;                    // 0x57
		unsigned int state;                         // 0x58 (bit 31: active, lower bits: the volume mask)
		IntersectionProperties properties;          // 0x5C
		CollisionShape* shape;                      // 0x64
		PhysicsObject* owner;                       // 0x68
		ConvexMesh* mesh;                           // 0x6C
		int unknown70;                              // 0x70
		unsigned char unknown74[0x0c];              // 0x74
	};
}

#endif
